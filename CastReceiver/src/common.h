/******************************************************
*
*     ©keithhedger Mon  5 Aug 20:25:10 BST 2019
*     kdhedger68713@gmail.com
*
*     common.h
* 
******************************************************/

#ifndef _COMMON_
#define _COMMON_

//#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>
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

extern bool	exitOnStop;

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
