/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:04:51 BST 2019 keithdhedger@gmail.com

 * This file (xmlescape.cpp) is part of CastReceiver.

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

void testdead(void)
{
fprintf(stderr,"never ....");
}

void xmlescape_real(const char *str, char *target, int *length,int attribute)
{
	if (target != NULL)
		{
			int len = 0;

			for (/**/; *str; str++)
				{
					if (*str == '<')
						{
							memcpy(target + len, "&lt;", 4);
							len += 4;
						}
					else if (attribute && (*str == '"'))
						{
							memcpy(target + len, "%22", 3);
							len += 3;
						}
					else if (*str == '>')
						{
							memcpy(target + len, "&gt;", 4);
							len += 4;
						}
					else if (*str == '&')
						{
							memcpy(target + len, "&amp;", 5);
							len += 5;
						}
					else
						{
							target[len++] = *str;
						}
				}
			target[len] = '\0';

			if (length != NULL)
				*length = len;
		}
	else if (length != NULL)
		{
			int len = 0;

			for (/**/; *str; str++)
				{
					if (*str == '<')
						{
							len += 4;
						}
					else if (attribute && (*str == '"'))
						{
							len += 3;
						}
					else if (*str == '>')
						{
							len += 4;
						}
					else if (*str == '&')
						{
							len += 5;
						}
					else
						{
							len++;
						}
				}

			*length = len;
		}
}

char *xmlescape(const char *str, int attribute)
{
	int len;
	char *out;

	xmlescape_real(str, NULL, &len, attribute);
	out = (char *)malloc(len + 1);
	xmlescape_real(str, out, NULL, attribute);
	return(out);
}
