/* upnp_control.h - UPnP RenderingControl definitions
 *
 * Copyright (C) 2005   Ivo Clarysse
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
#ifndef _UPNP_CONTROL_H
#define _UPNP_CONTROL_H

//#include "common.h"

#define CONTROL_TYPE "urn:schemas-upnp-org:service:RenderingControl:1"
#define CONTROL_SERVICE_ID "urn:upnp-org:serviceId:RenderingControl"
#define CONTROL_SCPD_URL "/upnp/rendercontrolSCPD.xml"
#define CONTROL_CONTROL_URL "/upnp/control/rendercontrol1"
#define CONTROL_EVENT_URL "/upnp/event/rendercontrol1"

enum {CONTROL_VAR_UNKNOWN,CONTROL_VAR_COUNT};
enum {CONTROL_CMD_UNKNOWN,CONTROL_CMD_COUNT};

extern struct service control_service_;
void upnp_control_init(struct upnp_device *device);
struct service *upnp_control_get_service(void);
void upnp_control_register_variable_listener(variable_change_listener_t cb,void *userdata);

#endif /* _UPNP_CONTROL_H */
