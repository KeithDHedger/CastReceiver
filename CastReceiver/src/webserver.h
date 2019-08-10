/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:04:16 BST 2019 keithdhedger@gmail.com

 * This file (webserver.h) is part of CastReceiver.

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


#ifndef _WEBSERVER_H
#define _WEBSERVER_H

struct WebServerFile
{
	off_t pos;
	const char *contents;
	size_t len;
};

struct virtual_file
{
	const char *virtual_fname;
	const char *contents;
	const char *content_type;
	size_t len;
	struct virtual_file *next;
};

// Start the webserver with the registered files.
gboolean webserver_register_callbacks(void);

int webserver_register_buf(const char *path,const char *contents,const char *content_type);
int webserver_register_file(const char *path,const char *content_type);

#endif /* _WEBSERVER_H */
