/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:05:15 BST 2019 keithdhedger@gmail.com

 * This file (xmlescape.h) is part of CastReceiver.

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

#ifndef _XMLESCAPE_H
#define _XMLESCAPE_H

// XML escape string "str". If "attribute" is 1, then this is considered
// to be within an xml attribute (i.e. quotes are escaped as well).
// Returns a malloc()ed string; caller needs to free().
char *xmlescape(const char *str, int attribute);

#endif /* _XMLESCAPE_H */
