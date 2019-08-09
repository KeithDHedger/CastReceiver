/* output.h - Output module frontend
 *
 * Copyright (C) 2007 Ivo Clarysse, (C) 2012 Henner Zeller
 *
 * This file is part of GMediaRender.
 *
 * GMediaRender is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License,or
 * (at your option) any later version.
 *
 * GMediaRender is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GMediaRender; if not,write to the Free Software
 * Foundation,Inc.,51 Franklin Street,Fifth Floor,Boston,
 * MA 02110-1301,USA.
 *
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
