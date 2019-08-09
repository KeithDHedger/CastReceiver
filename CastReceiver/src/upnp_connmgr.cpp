/* upnp_connmgr.c - UPnP Connection Manager routines
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

//#include "upnp_connmgr.h"
#include "common.h"

ithread_mutex_t connmgr_mutex;

//struct argument **argument_listX[]={NULL,NULL,NULL,NULL,NULL};
struct argument **argument_listX[]={[CONNMGR_CMD_GETCURRENTCONNECTIONIDS]=NULL,[CONNMGR_CMD_GETPROTOCOLINFO]=NULL,[CONNMGR_CMD_PREPAREFORCONNECTION]=NULL,[CONNMGR_CMD_UNKNOWN]=NULL};

const char *connmgr_default_values[]={[CONNMGR_VAR_AAT_CONN_MGR]=NULL,[CONNMGR_VAR_SINK_PROTO_INFO]=NULL,[CONNMGR_VAR_AAT_CONN_STATUS]=NULL,[CONNMGR_VAR_AAT_AVT_ID]=NULL,[CONNMGR_VAR_AAT_DIR]=NULL,[CONNMGR_VAR_AAT_RCS_ID]=NULL,[CONNMGR_VAR_AAT_PROTO_INFO]=NULL,[CONNMGR_VAR_AAT_CONN_ID]=NULL,[CONNMGR_VAR_SRC_PROTO_INFO]=NULL,[CONNMGR_VAR_CUR_CONN_IDS]=NULL,[CONNMGR_VAR_UNKNOWN]=NULL};

const char *connmgr_variable_names[]=
{
	[CONNMGR_VAR_AAT_CONN_MGR]="A_ARG_TYPE_ConnectionManager",
	[CONNMGR_VAR_SINK_PROTO_INFO]="SinkProtocolInfo",
	[CONNMGR_VAR_AAT_CONN_STATUS]="A_ARG_TYPE_ConnectionStatus",
	[CONNMGR_VAR_AAT_AVT_ID]="A_ARG_TYPE_AVTransportID",
	[CONNMGR_VAR_AAT_DIR]="A_ARG_TYPE_Direction",
	[CONNMGR_VAR_AAT_RCS_ID]="A_ARG_TYPE_RcsID",
	[CONNMGR_VAR_AAT_PROTO_INFO]="A_ARG_TYPE_ProtocolInfo",
	[CONNMGR_VAR_AAT_CONN_ID]="A_ARG_TYPE_ConnectionID",
	[CONNMGR_VAR_SRC_PROTO_INFO]="SourceProtocolInfo",
	[CONNMGR_VAR_CUR_CONN_IDS]="CurrentConnectionIDs",
	[CONNMGR_VAR_UNKNOWN]=NULL

};

struct var_meta connmgr_var_meta[]=
{
	[CONNMGR_VAR_AAT_CONN_MGR]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL},
	[CONNMGR_VAR_SINK_PROTO_INFO]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL},
	[CONNMGR_VAR_AAT_CONN_STATUS]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL},
	[CONNMGR_VAR_AAT_AVT_ID]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL},
	[CONNMGR_VAR_AAT_DIR]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL},
	[CONNMGR_VAR_AAT_RCS_ID]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL},
	[CONNMGR_VAR_AAT_PROTO_INFO]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL},
	[CONNMGR_VAR_AAT_CONN_ID]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL},
	[CONNMGR_VAR_SRC_PROTO_INFO]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL},
	[CONNMGR_VAR_CUR_CONN_IDS]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL},
	[CONNMGR_VAR_UNKNOWN]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL}
};

int get_protocol_info(struct action_event *event)
{
	return(event->status);
}

struct service *upnp_connmgr_get_service(void)
{
	if (connmgr_service_.variable_container==NULL)
		connmgr_service_.variable_container=VariableContainer_new(CONNMGR_VAR_COUNT,connmgr_variable_names,connmgr_default_values);
	return(&connmgr_service_);
}

int connmgr_init(const char* filter)
{
	const char 		*buf="";
	struct service	*srv=upnp_connmgr_get_service();

	VariableContainer_change(srv->variable_container,CONNMGR_VAR_SINK_PROTO_INFO,buf);
	return(0);
}

struct action connmgr_actions[]=
{
	[CONNMGR_CMD_GETCURRENTCONNECTIONIDS]={NULL,NULL},
	[CONNMGR_CMD_GETPROTOCOLINFO]={"GetProtocolInfo",get_protocol_info},
	[CONNMGR_CMD_PREPAREFORCONNECTION]={NULL,NULL},
	[CONNMGR_CMD_UNKNOWN]={NULL,NULL}
};

struct service connmgr_service_={&connmgr_mutex,CONNMGR_SERVICE_ID,CONNMGR_TYPE,CONNMGR_SCPD_URL,CONNMGR_CONTROL_URL,CONNMGR_EVENT_URL,NULL,connmgr_actions,argument_listX,connmgr_variable_names,NULL,NULL,connmgr_var_meta,CONNMGR_VAR_UNKNOWN,CONNMGR_CMD_UNKNOWN,NULL,NULL};
