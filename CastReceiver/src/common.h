/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:00:32 BST 2019 keithdhedger@gmail.com

 * This file (common.h) is part of CastReceiver.

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

#ifndef _COMMON_
#define _COMMON_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <glib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <upnp/upnp.h>
#include <upnp/ithread.h>
#include <upnp/upnptools.h>

#include <stdbool.h>

#include "config.h"

#include "xmldoc.h"
#include "xmlescape.h"
#include "webserver.h"
#include "upnp_device.h"
#include "upnp.h"
#include "output.h"
#include "variable-container.h"
#include "upnp_transport.h"
#include "upnp_connmgr.h"
#include "upnp_control.h"
#include "upnp_renderer.h"


extern const char	*playerCommand;
extern bool			exitOnStop;

struct xmldoc;
struct xmlelement *gen_specversion(struct xmldoc *doc,int major,int minor);
struct service *upnp_connmgr_get_service(void);

static inline void freeAndNull(char **data)
{
	if((data!=NULL) && (*data!=NULL))
		{
			free(*data);
			*data=NULL;
		}
}

#endif
