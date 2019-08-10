/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:00:44 BST 2019 keithdhedger@gmail.com

 * This file (output.cpp) is part of CastReceiver.

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

char		*omxplayerURI=NULL;
GMainLoop	*mainLoop=NULL;

void exit_loop_sighandler(int sig)
{
	if(mainLoop)
		g_main_loop_quit(mainLoop);
}

int output_loop()
{
	/* Create a main loop that runs the default GLib main context */
	mainLoop=g_main_loop_new(NULL,false);

	signal(SIGINT,&exit_loop_sighandler);
	signal(SIGTERM,&exit_loop_sighandler);

	g_main_loop_run(mainLoop);

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
			asprintf(&command,"%s '%s'\n",playerCommand,omxplayerURI);
			system(command);
			if(exitOnStop==true)
				{
					fprintf(stderr,"DO exit ... \n");
					g_main_loop_quit(mainLoop);
//					fprintf(stderr,"DO exit 1 ... \n");
//					UpnpFinish();
//					fprintf(stderr,"DO exit 2 ... \n");
				}
		}
	return(0);
}

int output_stop(void)
{
	//freeAndNull(&omxplayerURI);
	fprintf(stderr,">>>stop<<<\n");
	return(0);
}
