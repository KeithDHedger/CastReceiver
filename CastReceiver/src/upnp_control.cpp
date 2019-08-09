/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:02:14 BST 2019 keithdhedger@gmail.com

 * This file (upnp_control.cpp) is part of CastReceiver.

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

ithread_mutex_t control_mutex;
const char *control_variable_names[]={[CONTROL_VAR_UNKNOWN]=NULL};
variable_container_t *state_variablesUPNPControl_=NULL;
struct argument **argument_listUPNPControl[]={[CONTROL_CMD_UNKNOWN]=NULL};
struct action control_actions[]={[CONTROL_CMD_UNKNOWN]={NULL,NULL}};
struct var_meta control_var_meta[]={[CONTROL_VAR_UNKNOWN]={ SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL}};

void upnp_control_register_variable_listener(variable_change_listener_t cb,void *userdata)
{
	VariableContainer_register_callback(state_variablesUPNPControl_,cb,userdata);
}

struct service control_service={&control_mutex,CONTROL_SERVICE_ID,CONTROL_TYPE,CONTROL_SCPD_URL,CONTROL_CONTROL_URL,CONTROL_EVENT_URL,NULL,control_actions,argument_listUPNPControl,control_variable_names,NULL,NULL,control_var_meta,CONTROL_VAR_UNKNOWN,CONTROL_CMD_UNKNOWN,NULL,NULL};
