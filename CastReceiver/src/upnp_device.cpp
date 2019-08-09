/* upnp_device.c - Generic UPnP device handling
 *
 * Copyright (C) 2005-2007   Ivo Clarysse
 *
 * This file is part of GMediaRender.
 *
 * GMediaRender is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License,or
 * (at your option) any later version.
 *
 * GMediaRender is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GMediaRender; if not,write to the Free Software
 * Foundation,Inc.,51 Franklin Street,Fifth Floor,Boston,
 * MA 02110-1301,USA.
 *
 */

/*
 *
 * ©K. D. Hedger. Thu  8 Aug 16:14:43 BST 2019 keithdhedger@gmail.com

 * This file (upnp_device.c) is part of gmrender-resurrect.

 * gmrender-resurrect is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.

 * gmrender-resurrect is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with gmrender-resurrect.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "common.h"

struct upnp_device
{
	struct upnp_device_descriptor *upnp_device_descriptor;
	ithread_mutex_t device_mutex;
	UpnpDevice_Handle device_handle;
};

void upnp_set_error(struct action_event *event,int error_code,const char *format,...)
{
	char buffer[80];
	UpnpString *errStr=UpnpString_new();
	const char *errStrC;
	event->status=-1;

	va_list ap;
	va_start(ap,format);
	vsnprintf(buffer,sizeof(buffer),format,ap);
	va_end(ap);
	UpnpActionRequest_set_ActionResult(event->request,NULL);
	UpnpActionRequest_set_ErrCode(event->request,UPNP_SOAP_E_ACTION_FAILED);
	UpnpString_set_String(errStr,buffer);
	UpnpActionRequest_set_ErrStr(event->request,errStr);
	errStrC=UpnpActionRequest_get_ErrStr_cstr(event->request);
}

const char *upnp_get_string(struct action_event *event,const char *key)
{
	IXML_Node *node;

	node=(IXML_Node *)UpnpActionRequest_get_ActionRequest(event->request);
	if (node==NULL)
		{
			upnp_set_error(event,UPNP_SOAP_E_INVALID_ARGS,"Invalid action request document");
			return(NULL);
		}
	node=ixmlNode_getFirstChild(node);
	if (node==NULL)
		{
			upnp_set_error(event,UPNP_SOAP_E_INVALID_ARGS,"Invalid action request document");
			return(NULL);
		}
	node=ixmlNode_getFirstChild(node);

	for (/**/; node!=NULL; node=ixmlNode_getNextSibling(node))
		{
			if (strcmp(ixmlNode_getNodeName(node),key)==0)
				{
					node=ixmlNode_getFirstChild(node);
					const char *node_value=(node!=NULL ? ixmlNode_getNodeValue(node) : NULL);
					return(node_value!=NULL ? node_value : "");
				}
		}

	upnp_set_error(event,UPNP_SOAP_E_INVALID_ARGS,"Missing action request argument (%s)",key);
	return(NULL);
}

int handle_subscription_request(struct upnp_device *priv,UpnpSubscriptionRequest *sr_event)
{
	struct service *srv;
	int rc;

	const char *serviceId =UpnpSubscriptionRequest_get_ServiceId_cstr(sr_event);
	const char *udn=UpnpSubscriptionRequest_get_UDN_cstr(sr_event);
	srv=find_service(priv->upnp_device_descriptor,serviceId);
	if (srv==NULL)
		return(-1);

	int result=-1;
	ithread_mutex_lock(&(priv->device_mutex));

	// There is really only one variable evented: LastChange
	const char *eventvar_names[] =
	{
		"LastChange",
		NULL
	};

	const char *eventvar_values[]={NULL,NULL};

	// Build the current state of the variables as one gigantic initial
	// LastChange update.
	ithread_mutex_lock(srv->service_mutex);
	const int var_count =VariableContainer_get_num_vars(srv->variable_container);
	// TODO(hzeller): maybe use srv->last_change directly ?
	upnp_last_change_builder_t *builder=UPnPLastChangeBuilder_new(srv->event_xml_ns);
	for (int i=0; i < var_count; ++i)
		{
			const char *name;
			const char *value =VariableContainer_get(srv->variable_container,i,&name);
			// Send over all variables except "LastChange" itself. Also all
			// A_ARG_TYPE variables are not evented.
			if (value && strcmp("LastChange",name)!=0 && strncmp("A_ARG_TYPE_",name,strlen("A_ARG_TYPE_"))!=0)
				UPnPLastChangeBuilder_add(builder,name,value);
		}

	ithread_mutex_unlock(srv->service_mutex);
	char *xml_value=UPnPLastChangeBuilder_to_xml(builder);
	eventvar_values[0]=xmlescape(xml_value,0);
	free(xml_value);
	UPnPLastChangeBuilder_delete(builder);

	const char *sid=UpnpSubscriptionRequest_get_SID_cstr(sr_event);
	rc=UpnpAcceptSubscription(priv->device_handle,udn,serviceId,eventvar_names,eventvar_values,1,sid);
	if (rc==UPNP_E_SUCCESS)
		result=0;

	ithread_mutex_unlock(&(priv->device_mutex));

	free((char*)eventvar_values[0]);

	return(result);
}

int handle_action_request(struct upnp_device *priv,UpnpActionRequest *ar_event)
{
	struct service *event_service;
	struct action *event_action;

	const char *serviceID=UpnpActionRequest_get_ServiceID_cstr(ar_event);
	const char *actionName=UpnpActionRequest_get_ActionName_cstr(ar_event);

	event_service=find_service(priv->upnp_device_descriptor,serviceID);
	event_action=find_action(event_service,actionName);
	if (event_action==NULL)
		{
			UpnpActionRequest_set_ActionResult(ar_event,NULL);
			UpnpActionRequest_set_ErrCode(ar_event,401);
			return(-1);
		}

	// We want to send the LastChange event only after the action is
	// finished - just to be conservative,we don't know how clients
	// react to get LastChange notifictions while in the middle of
	// issuing an action.
	//
	// So we nest the change collector level here,so that we only send the
	// LastChange after the action is finished ().
	//
	// Note,this is,in fact,only a preparation and not yet working as
	// described above: we are still in the middle
	// of executing the event-callback while sending the last change
	// event implicitly when calling UPnPLastChangeCollector_finish() below.
	// It would be good to enqueue the upnp_device_notify() after
	// the action event is finished.
	if (event_service->last_change)
		{
			ithread_mutex_lock(event_service->service_mutex);
			UPnPLastChangeCollector_start(event_service->last_change);
			ithread_mutex_unlock(event_service->service_mutex);
		}

	if (event_action->callback)
		{
			struct action_event event;
			int rc;
			event.request=ar_event;
			event.status=0;
			event.service=event_service;
			event.device=priv;

			rc=(event_action->callback) (&event);
			if (rc==0)
				UpnpActionRequest_set_ErrCode(event.request,UPNP_E_SUCCESS);

			IXML_Document *actionResult =UpnpActionRequest_get_ActionResult(ar_event);
			if (actionResult==NULL)
				{
					actionResult =UpnpMakeActionResponse(actionName,event_service->service_type,0,NULL);
					UpnpActionRequest_set_ActionResult(event.request,actionResult);
				}
		}
	else
		{
			int errCode=UpnpActionRequest_get_ErrCode(ar_event);
			int sock=UpnpActionRequest_get_Socket(ar_event);
			const char *errStr=UpnpActionRequest_get_ErrStr_cstr(ar_event);
			const char *actionName=UpnpActionRequest_get_ActionName_cstr(ar_event);
			const char *devUDN=UpnpActionRequest_get_DevUDN_cstr(ar_event);
			const char *serviceID=UpnpActionRequest_get_ServiceID_cstr(ar_event);
			UpnpActionRequest_set_ErrCode(ar_event,UPNP_E_SUCCESS);
		}

	if (event_service->last_change)     // See comment above.
		{
			ithread_mutex_lock(event_service->service_mutex);
			UPnPLastChangeCollector_finish(event_service->last_change);
			ithread_mutex_unlock(event_service->service_mutex);
		}
	return(0);
}

int event_handler(Upnp_EventType EventType,void *event,void *userdata)
{
	struct upnp_device *priv=(struct upnp_device *) userdata;
	switch (EventType)
		{
		case UPNP_CONTROL_ACTION_REQUEST:
			handle_action_request(priv,(UpnpActionRequest*)event);
			break;

		case UPNP_CONTROL_GET_VAR_REQUEST:
			break;

		case UPNP_EVENT_SUBSCRIPTION_REQUEST:
			handle_subscription_request(priv,(UpnpSubscriptionRequest*)event);
			break;

		default:
			break;
		}
	return(0);
}

gboolean initialize_device(struct upnp_device_descriptor *device_def,struct upnp_device *result_device,const char *ip_address,unsigned short port)
{
	int rc;
	char *buf;

	rc=UpnpInit(ip_address,port);
	/* There have been situations reported in which UPNP had issues
	 * initializing right after network came up. #129
	 */
	int retries_left=60;
	const int kRetryTimeMs=1000;
	while (rc!=UPNP_E_SUCCESS && retries_left--)
		{
			usleep(kRetryTimeMs * 1000);
			rc=UpnpInit(ip_address,port);
		}

	if (UPNP_E_SUCCESS!=rc)
		return(false);

	rc=UpnpEnableWebserver(true);
	if (UPNP_E_SUCCESS!=rc)
		return(false);

	if (!webserver_register_callbacks())
		return(false);

	rc=UpnpAddVirtualDir("/upnp");
	if (UPNP_E_SUCCESS!=rc)
		return(false);

	buf=upnp_create_device_desc(device_def);
	rc=UpnpRegisterRootDevice2(UPNPREG_BUF_DESC,buf,strlen(buf),1,(Upnp_FunPtr)&event_handler,result_device,&(result_device->device_handle));
	free(buf);

	if (UPNP_E_SUCCESS!=rc)
		return(false);

	rc=UpnpSendAdvertisement(result_device->device_handle,100);
	if (UPNP_E_SUCCESS!=rc)
		return(false);

	return(true);
}

struct upnp_device *upnp_device_init(struct upnp_device_descriptor *device_def,const char *ip_address,unsigned short port)
{
	int rc;
	char *buf;
	struct service *srv;

	if (device_def->init_function)
		{
			rc=device_def->init_function();
			if (rc!=0)
				return(NULL);
		}

	struct upnp_device *result_device=(upnp_device*)malloc(sizeof(*result_device));
	result_device->upnp_device_descriptor=device_def;
	ithread_mutex_init(&(result_device->device_mutex),NULL);

	/* generate and register service schemas in web server */
	for (int i=0; (srv=device_def->services[i]); i++)
		{
			buf=upnp_get_scpd(srv);
			webserver_register_buf(srv->scpd_url,buf,"text/xml");
		}

	if (!initialize_device(device_def,result_device,ip_address,port))
		{
			UpnpFinish();
			free(result_device);
			return(NULL);
		}

	return(result_device);
}

void upnp_device_shutdown(struct upnp_device *device)
{
	UpnpFinish();
}

struct service *find_service(struct upnp_device_descriptor *device_def,const char *service_id)
{
	struct service *event_service;
	int serviceNum=0;

	while (event_service =device_def->services[serviceNum],event_service!=NULL)
		{
			if (strcmp(event_service->service_id,service_id)==0)
				return(event_service);
			serviceNum++;
		}
	return(NULL);
}

struct xmlelement *gen_desc_servicelist(struct upnp_device_descriptor *device_def,struct xmldoc *doc)
{
	int i;
	struct service *srv;
	struct xmlelement *top;
	struct xmlelement *parent;

	top=xmlelement_new(doc,"serviceList");

	for (i=0; (srv=device_def->services[i]); i++)
		{
			parent=xmlelement_new(doc,"service");
			add_value_element(doc,parent,"serviceType",srv->service_type);
			add_value_element(doc,parent,"serviceId",srv->service_id);
			add_value_element(doc,parent,"SCPDURL",srv->scpd_url);
			add_value_element(doc,parent,"controlURL",srv->control_url);
			add_value_element(doc,parent,"eventSubURL",srv->event_url);
			xmlelement_add_element(doc,top,parent);
		}

	return(top);
}

struct xmldoc *generate_desc(struct upnp_device_descriptor *device_def)
{
	struct xmldoc *doc;
	struct xmlelement *root;
	struct xmlelement *child;
	struct xmlelement *parent;

	doc=xmldoc_new();

	root=xmldoc_new_topelement(doc,"root","urn:schemas-upnp-org:device-1-0");
	child=gen_specversion(doc,1,0);
	xmlelement_add_element(doc,root,child);
	parent=xmlelement_new(doc,"device");
	xmlelement_add_element(doc,root,parent);
	add_value_element(doc,parent,"deviceType",device_def->device_type);
	add_value_element(doc,parent,"presentationURL",device_def->presentation_url);
	add_value_element(doc,parent,"friendlyName",device_def->friendlyName);
	add_value_element(doc,parent,"manufacturer",device_def->manufacturer);
	add_value_element(doc,parent,"manufacturerURL",device_def->manufacturer_url);
	add_value_element(doc,parent,"modelDescription",device_def->model_description);
	add_value_element(doc,parent,"modelName",device_def->model_name);
	add_value_element(doc,parent,"modelNumber",device_def->model_number);
	add_value_element(doc,parent,"modelURL",device_def->model_url);
	add_value_element(doc,parent,"UDN",device_def->udn);
	child=gen_desc_servicelist(device_def,doc);
	xmlelement_add_element(doc,parent,child);

	return(doc);
}

char *upnp_create_device_desc(struct upnp_device_descriptor *device_def)
{
	char *result=NULL;
	struct xmldoc *doc;

	doc=generate_desc(device_def);

	if (doc!=NULL)
		{
			result=xmldoc_tostring(doc);
			xmldoc_free(doc);
		}
	return(result);
}
