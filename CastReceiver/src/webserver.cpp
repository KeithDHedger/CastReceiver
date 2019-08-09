/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:04:06 BST 2019 keithdhedger@gmail.com

 * This file (webserver.cpp) is part of CastReceiver.

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

struct virtual_file *virtual_files=NULL;

int webserver_register_buf(const char *path,const char *contents,const char *content_type)
{
	struct virtual_file *entry;

	entry=(virtual_file *)malloc(sizeof(struct virtual_file));
	if (entry==NULL)
		return(-1);

	entry->len=strlen(contents);
	entry->contents=contents;
	entry->virtual_fname=path;
	entry->content_type=content_type;
	entry->next=virtual_files;
	virtual_files=entry;

	return(0);
}

int webserver_register_file(const char *path,const char *content_type)
{
	char local_fname[PATH_MAX];
	struct stat buf;
	struct virtual_file *entry;
	int rc;

//	snprintf(local_fname,sizeof(local_fname),"%s%s",PKG_DATADIR,strrchr(path,'/'));//TODO//
	snprintf(local_fname,sizeof(local_fname),"%s%s",DATADIR,strrchr(path,'/'));

	rc=stat(local_fname,&buf);
	if (rc)
		return(-1);

	entry=(virtual_file *)malloc(sizeof(struct virtual_file));
	if (entry==NULL)
		return(-1);

	if (buf.st_size)
		{
			char *cbuf;
			FILE *in;
			in=fopen(local_fname,"r");
			if (in==NULL)
				{
					free(entry);
					return(-1);
				}
			cbuf=(char *)malloc(buf.st_size);
			if (cbuf==NULL)
				{
					free(entry);
					return(-1);
				}
			if (fread(cbuf,buf.st_size,1,in)!=1)
				{
					free(entry);
					free(cbuf);
					return(-1);
				}
			fclose(in);
			entry->len=buf.st_size;
			entry->contents=cbuf;

		}
	else
		{
			entry->len=0;
			entry->contents=NULL;
		}
	entry->virtual_fname=path;
	entry->content_type=content_type;
	entry->next=virtual_files;
	virtual_files=entry;

	return(0);
}

int webserver_get_info(const char *filename,UpnpFileInfo *info)
{
	struct virtual_file *virtfile=virtual_files;

	while (virtfile!=NULL)
		{
			if (strcmp(filename,virtfile->virtual_fname)==0)
				{
					UpnpFileInfo_set_FileLength(info,virtfile->len);
					UpnpFileInfo_set_LastModified(info,0);
					UpnpFileInfo_set_IsDirectory(info,0);
					UpnpFileInfo_set_IsReadable(info,1);
					const char *contentType =ixmlCloneDOMString(virtfile->content_type);
					UpnpFileInfo_set_ContentType(info,contentType);
					return(0);
				}
			virtfile=virtfile->next;
		}
	return(-1);
}

UpnpWebFileHandle webserver_open(const char *filename,enum UpnpOpenFileMode mode)
{
	if (mode!=UPNP_READ)
		return(NULL);

	for (struct virtual_file *vf=virtual_files; vf; vf=vf->next)
		{
			if (strcmp(filename,vf->virtual_fname)==0)
				{
					struct WebServerFile *file=( WebServerFile *)malloc(sizeof(struct WebServerFile));
					file->pos=0;
					file->len=vf->len;
					file->contents=vf->contents;
					return(file);
				}
		}

	return(NULL);
}

inline int minimum(int a,int b)
{
	return((a<b)?a:b);
}

int webserver_read(UpnpWebFileHandle fh,char *buf,size_t buflen)
{
	struct WebServerFile *file=(struct WebServerFile *) fh;
	ssize_t len=-1;

	len=minimum(buflen,file->len - file->pos);
	memcpy(buf,file->contents+file->pos,len);

	if (len >=0)
		file->pos += len;

	return(len);
}

int webserver_close(UpnpWebFileHandle fh)
{
	struct WebServerFile *file=(struct WebServerFile *) fh;

	free(file);

	return(0);
}

gboolean webserver_register_callbacks(void)
{
	gboolean result =
	    (UpnpVirtualDir_set_GetInfoCallback((VDCallback_GetInfo)webserver_get_info)==UPNP_E_SUCCESS
	     && UpnpVirtualDir_set_OpenCallback((VDCallback_Open)webserver_open)==UPNP_E_SUCCESS
	     && UpnpVirtualDir_set_ReadCallback((VDCallback_Read)webserver_read)==UPNP_E_SUCCESS
	     && UpnpVirtualDir_set_CloseCallback((VDCallback_Close)webserver_close)==UPNP_E_SUCCESS);
	return(result);
}
