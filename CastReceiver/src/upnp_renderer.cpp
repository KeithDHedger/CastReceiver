/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:03:04 BST 2019 keithdhedger@gmail.com

 * This file (upnp_renderer.cpp) is part of CastReceiver.

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

#include "common.h"


struct service *upnp_services[3];
struct upnp_device_descriptor render_device= {upnp_renderer_init,"urn:schemas-upnp-org:device:MediaRenderer:1","CastReceiver","Ivo Clarysse,Henner Zeller","http://github.com/hzeller/gmrender-resurrect",PACKAGE_STRING,PACKAGE_NAME,PACKAGE_VERSION,"http://github.com/hzeller/gmrender-resurrect","1","uuid:CastReceiver-1_0-000-000-002","","",NULL,NULL};

int upnp_renderer_init(void)
{
	upnp_services[0]=upnp_transport_get_service();
	upnp_services[1]=upnp_connmgr_get_service();
	upnp_services[2]=NULL;
	render_device.services=upnp_services;
	return(connmgr_init(render_device.mime_filter));
}

struct upnp_device_descriptor *upnp_renderer_descriptor(const char *friendlyName,const char *uuid)
{
	render_device.friendlyName=friendlyName;

	char *udn=NULL;
	if (asprintf(&udn,"uuid:%s",uuid) > 0)
		render_device.udn=udn;
	return(&render_device);
}
