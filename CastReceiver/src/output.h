/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:00:56 BST 2019 keithdhedger@gmail.com

 * This file (output.h) is part of CastReceiver.

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

#ifndef _OUTPUT_H
#define _OUTPUT_H

//#include "common.h"

enum
{
	PLAY_STOPPED,
	PLAY_STARTED_NEXT_STREAM,
};

int output_loop(void);
void output_set_uri(const char *uri);
int output_play(void);
int output_stop(void);

#endif /* _OUTPUT_H */
