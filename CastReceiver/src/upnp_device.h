/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:02:54 BST 2019 keithdhedger@gmail.com

 * This file (upnp_device.h) is part of CastReceiver.

 * CastReceiver is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.

 * CastReceiver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with CastReceiver.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _UPNP_DEVICE_H
#define _UPNP_DEVICE_H

struct upnp_device_descriptor
{
	int (*init_function) (void);
	const char *device_type;
	const char *friendlyName;
	const char *manufacturer;
	const char *manufacturer_url;
	const char *model_description;
	const char *model_name;
	const char *model_number;
	const char *model_url;
	const char *serial_number;
	const char *udn;
	const char *upc;
	const char *presentation_url;
	const char *mime_filter;
	struct icon **icons;
	struct service **services;
};

struct upnp_device
{
	struct upnp_device_descriptor *upnp_device_descriptor;
	ithread_mutex_t device_mutex;
	UpnpDevice_Handle device_handle;
};

//struct upnp_device;
struct action_event;

struct upnp_device *upnp_device_init(struct upnp_device_descriptor *device_def,const char *ip_address,unsigned short port);

void upnp_device_shutdown(struct upnp_device *device);

int upnp_add_response(struct action_event *event,const char *key,const char *value);
void upnp_set_error(struct action_event *event,int error_code,const char *format,...);

// Returns a readonly value stored in the action event. Returned value
// only valid for the life-time of "event".
const char *upnp_get_string(struct action_event *event,const char *key);

// Append variable,identified by the variable number,to the event,
// store the value under the given parameter name. The caller needs to provide
// a valid variable number (assert()-ed).
void upnp_append_variable(struct action_event *event,int varnum,const char *paramname);

int upnp_device_notify(struct upnp_device *device,const char *serviceID,const char **varnames,const char **varvalues,int varcount);

struct service *find_service(struct upnp_device_descriptor *device_def,const char *service_name);

// Returns a newly allocated string with the device descriptor.
char *upnp_create_device_desc(struct upnp_device_descriptor *device_def);

#endif /* _UPNP_DEVICE_H */
