/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:00:18 BST 2019 keithdhedger@gmail.com

 * This file (common.cpp) is part of CastReceiver.

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

bool		exitOnStop=false;
const char	*playerCommand="omxplayer --key-config ~/.config/omxkey.config ";

struct xmlelement *gen_specversion(struct xmldoc *doc,int major,int minor)
{
	struct xmlelement *top;

	top=xmlelement_new(doc,"specVersion");

	add_value_element_int(doc,top,"major",major);
	add_value_element_int(doc,top,"minor",minor);

	return(top);
}
