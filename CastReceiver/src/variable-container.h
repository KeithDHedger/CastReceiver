/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:03:53 BST 2019 keithdhedger@gmail.com

 * This file (variable-container.h) is part of CastReceiver.

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


#ifndef VARIABLE_CONTAINER_H
#define VARIABLE_CONTAINER_H

typedef void (*variable_change_listener_t)(void *userdata,int var_num, const char *var_name,const char *old_value,const char *new_value);
typedef struct variable_container variable_container_t;
typedef struct upnp_last_change_builder upnp_last_change_builder_t;
typedef struct upnp_last_change_collector upnp_last_change_collector_t;

struct cb_list
{
	variable_change_listener_t callback;
	void *userdata;
	struct cb_list *next;
};

struct variable_container
{
	int variable_num;
	const char **variable_names;
	char **values;
	struct cb_list *callbacks;
};

variable_container_t *VariableContainer_new(int variable_num,const char **variable_names,const char **variable_init_values);
int VariableContainer_get_num_vars(variable_container_t *object);
const char *VariableContainer_get(variable_container_t *object, int var,const char **name);
int VariableContainer_change(variable_container_t *object,int variable_num, const char *value);
void VariableContainer_register_callback(variable_container_t *object,variable_change_listener_t callback,void *userdata);
upnp_last_change_builder_t *UPnPLastChangeBuilder_new(const char *xml_namespace);
void UPnPLastChangeBuilder_delete(upnp_last_change_builder_t *builder);

void UPnPLastChangeBuilder_add(upnp_last_change_builder_t *builder,const char *name, const char *value);
char *UPnPLastChangeBuilder_to_xml(upnp_last_change_builder_t *builder);
void UPnPLastChangeCollector_add_ignore(upnp_last_change_collector_t *object,int variable_num);
void UPnPLastChangeCollector_start(upnp_last_change_collector_t *object);
void UPnPLastChangeCollector_finish(upnp_last_change_collector_t *object);

void UPnPLastChangeCollector_notify(upnp_last_change_collector_t *obj);
void UPnPLastChangeCollector_callback(void *userdata,int var_num, const char *var_name,const char *old_value,const char *new_value);

#endif  /* VARIABLE_CONTAINER_H */
