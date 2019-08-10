/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:04:38 BST 2019 keithdhedger@gmail.com

 * This file (xmldoc.h) is part of CastReceiver.

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

#ifndef _XMLDOC_H
#define _XMLDOC_H


struct xmldoc *xmldoc_new(void);

void xmldoc_free(struct xmldoc *doc);
char *xmldoc_tostring(struct xmldoc *doc);
struct xmldoc *xmldoc_parsexml(const char *xml_text);

struct xmlelement *xmldoc_new_topelement(struct xmldoc *doc,const char *elementName,const char *xmlns);

struct xmlelement *xmlelement_new(struct xmldoc *doc,const char *elementName);

void xmlelement_add_element(struct xmldoc *doc,struct xmlelement *parent,struct xmlelement *child);
void xmlelement_add_text(struct xmldoc *doc,struct xmlelement *parent,const char *text);
void xmlelement_set_attribute(struct xmldoc *doc,struct xmlelement *element,const char *name,const char *value);
void add_value_element(struct xmldoc *doc,struct xmlelement *parent,const char *tagname,const char *value);

// Find element in document. This returns a newly allocated struct.
struct xmlelement *find_element_in_doc(struct xmldoc *doc,const char *key);
// Find element in document. This returns a newly allocated struct.
struct xmlelement *find_element_in_element(struct xmlelement *element,const char *key);
// Returns a newly allocated string representing the element value.
char *get_node_value(struct xmlelement *element);
struct xmlelement *add_attributevalue_element(struct xmldoc *doc,struct xmlelement *parent,const char *tagname,const char *attribute_name,const char *value);
void add_value_element_int(struct xmldoc *doc,struct xmlelement *parent,const char *tagname,int value);
void add_value_element_long(struct xmldoc *doc,struct xmlelement *parent,const char *tagname,long long value);

#endif /* _XMLDOC_H */
