/* upnp_connmgr.h - UPnP Connection Manager definitions
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

#ifndef _UPNP_CONNMGR_H
#define _UPNP_CONNMGR_H

//#include "common.h"

#define CONNMGR_TYPE	"urn:schemas-upnp-org:service:ConnectionManager:1"
#define CONNMGR_SERVICE_ID "urn:upnp-org:serviceId:ConnectionManager"
#define CONNMGR_SCPD_URL "/upnp/renderconnmgrSCPD.xml"
#define CONNMGR_CONTROL_URL "/upnp/control/renderconnmgr1"
#define CONNMGR_EVENT_URL "/upnp/event/renderconnmgr1"

typedef enum
{
	CONNMGR_VAR_AAT_CONN_MGR,
	CONNMGR_VAR_SINK_PROTO_INFO,
	CONNMGR_VAR_AAT_CONN_STATUS,
	CONNMGR_VAR_AAT_AVT_ID,
	CONNMGR_VAR_AAT_DIR,
	CONNMGR_VAR_AAT_RCS_ID,
	CONNMGR_VAR_AAT_PROTO_INFO,
	CONNMGR_VAR_AAT_CONN_ID,
	CONNMGR_VAR_SRC_PROTO_INFO,
	CONNMGR_VAR_CUR_CONN_IDS,
	CONNMGR_VAR_UNKNOWN,
	CONNMGR_VAR_COUNT
} connmgr_variable;

typedef enum
{
	CONNMGR_CMD_GETCURRENTCONNECTIONIDS,
	CONNMGR_CMD_GETPROTOCOLINFO,
	CONNMGR_CMD_PREPAREFORCONNECTION,
	CONNMGR_CMD_UNKNOWN,
	CONNMGR_CMD_COUNT
} connmgr_cmd;

extern struct service connmgr_service_;

int connmgr_init(const char* filter);
void register_mime_type(const char *mime_type);

#endif /* _UPNP_CONNMGR_H */
