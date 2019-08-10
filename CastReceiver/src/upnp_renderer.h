/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:03:12 BST 2019 keithdhedger@gmail.com

 * This file (upnp_renderer.h) is part of CastReceiver.

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


#ifndef _UPNP_RENDERER_H
#define _UPNP_RENDERER_H

//#include "common.h"

int upnp_renderer_init(void);
struct upnp_device_descriptor *upnp_renderer_descriptor(const char *name,const char *uuid);

#endif /* _UPNP_RENDERER_H */
