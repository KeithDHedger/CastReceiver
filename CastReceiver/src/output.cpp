/*
 *
 * ©K. D. Hedger. Sun  4 Aug 16:06:08 BST 2019 keithdhedger@gmail.com

 * This file (output.c) is part of gmrender-resurrect.

 * gmrender-resurrect is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation,either version 3 of the License,or
 * at your option) any later version.

 * gmrender-resurrect is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with gmrender-resurrect.  If not,see <http://www.gnu.org/licenses/>.
 */

/* output.c - Output module frontend
 *
 * Copyright(C) 2007 Ivo Clarysse,(C) 2012 Henner Zeller
 *
 * This file is part of GMediaRender.
 *
 * GMediaRender is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License,or
 *(at your option) any later version.
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

//#include "output.h"
#include "common.h"

char		*omxplayerURI=NULL;
GMainLoop	*main_loop_=NULL;

void exit_loop_sighandler(int sig)
{
	if(main_loop_)
		g_main_loop_quit(main_loop_);
}

int output_loop()
{
	/* Create a main loop that runs the default GLib main context */
	main_loop_=g_main_loop_new(NULL,false);

	signal(SIGINT,&exit_loop_sighandler);
	signal(SIGTERM,&exit_loop_sighandler);

	g_main_loop_run(main_loop_);

	return(0);
}

void output_set_uri(const char *uri)
{
	if(uri==NULL)
		return;
	if(strcasestr(uri,".jpg")!=NULL)
		return;

	output_stop();
	freeAndNull(&omxplayerURI);
	asprintf(&omxplayerURI,"%s",uri);
	fprintf(stderr,"uri=omxplayerURI=%s\n",omxplayerURI);
}

int output_play(void)
{
	char	*command;
//omxplayer -vo fbdev2 -vf scale=1920:1019 ../Battle\ Los\ Angeles.iso
//omxplayer -vo fbdev2 -vf scale=1920:1080 -keepaspect -quiet &>/dev/null ../Battle\ Los\ Angeles.iso

	if(omxplayerURI!=NULL)
		{
			fprintf(stderr,">>>>>>>>  output_play omxplayer %s<<\n",omxplayerURI);
//rpi version			asprintf(&command,"omxplayer --key-config ~/.config/omxkey.config %s\n",omxplayerURI);
			asprintf(&command,"omxplayer '%s'\n",omxplayerURI);
			system(command);
			if(exitOnStop==true)
				g_main_loop_quit(main_loop_);
		}
	return(0);
}

int output_stop(void)
{
	//freeAndNull(&omxplayerURI);
	//fprintf(stderr,">>>stop<<<\n");
	return(0);
}
