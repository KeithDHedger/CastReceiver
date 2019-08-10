/*
 *
 * ©K. D. Hedger. Fri  9 Aug 15:03:21 BST 2019 keithdhedger@gmail.com

 * This file (upnp_transport.cpp) is part of CastReceiver.

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

const char *transport_variable_names[] =
{
	[TRANSPORT_VAR_TRANSPORT_STATUS]="TransportStatus",
	[TRANSPORT_VAR_NEXT_AV_URI]="NextAVTransportURI",
	[TRANSPORT_VAR_NEXT_AV_URI_META]="NextAVTransportURIMetaData",
	[TRANSPORT_VAR_CUR_TRACK_META]="CurrentTrackMetaData",
	[TRANSPORT_VAR_REL_CTR_POS]="RelativeCounterPosition",
	[TRANSPORT_VAR_AAT_INSTANCE_ID]="A_ARG_TYPE_InstanceID",
	[TRANSPORT_VAR_AAT_SEEK_TARGET]="A_ARG_TYPE_SeekTarget",
	[TRANSPORT_VAR_PLAY_MEDIUM]="PlaybackStorageMedium",
	[TRANSPORT_VAR_REL_TIME_POS]="RelativeTimePosition",
	[TRANSPORT_VAR_REC_MEDIA]="PossibleRecordStorageMedia",
	[TRANSPORT_VAR_CUR_PLAY_MODE]="CurrentPlayMode",
	[TRANSPORT_VAR_TRANSPORT_PLAY_SPEED]="TransportPlaySpeed",
	[TRANSPORT_VAR_PLAY_MEDIA]="PossiblePlaybackStorageMedia",
	[TRANSPORT_VAR_ABS_TIME_POS]="AbsoluteTimePosition",
	[TRANSPORT_VAR_CUR_TRACK]="CurrentTrack",
	[TRANSPORT_VAR_CUR_TRACK_URI]="CurrentTrackURI",
	[TRANSPORT_VAR_CUR_TRANSPORT_ACTIONS]="CurrentTransportActions",
	[TRANSPORT_VAR_NR_TRACKS]="NumberOfTracks",
	[TRANSPORT_VAR_AV_URI]="AVTransportURI",
	[TRANSPORT_VAR_ABS_CTR_POS]="AbsoluteCounterPosition",
	[TRANSPORT_VAR_CUR_REC_QUAL_MODE]="CurrentRecordQualityMode",
	[TRANSPORT_VAR_CUR_MEDIA_DUR]="CurrentMediaDuration",
	[TRANSPORT_VAR_AAT_SEEK_MODE]="A_ARG_TYPE_SeekMode",
	[TRANSPORT_VAR_AV_URI_META]="AVTransportURIMetaData",
	[TRANSPORT_VAR_REC_MEDIUM]="RecordStorageMedium",
	[TRANSPORT_VAR_REC_MEDIUM_WR_STATUS]="RecordMediumWriteStatus",
	[TRANSPORT_VAR_LAST_CHANGE]="LastChange",
	[TRANSPORT_VAR_CUR_TRACK_DUR]="CurrentTrackDuration",
	[TRANSPORT_VAR_TRANSPORT_STATE]="TransportState",
	[TRANSPORT_VAR_POS_REC_QUAL_MODE]="PossibleRecordQualityModes",
	[TRANSPORT_VAR_UNKNOWN]=NULL
};

const char kZeroTime[]="0:00:00";
const char *transport_default_values[] =
{
	[TRANSPORT_VAR_TRANSPORT_STATUS]="OK",
	[TRANSPORT_VAR_NEXT_AV_URI]="",
	[TRANSPORT_VAR_NEXT_AV_URI_META]="",
	[TRANSPORT_VAR_CUR_TRACK_META]="",
	[TRANSPORT_VAR_REL_CTR_POS]="2147483647",
	[TRANSPORT_VAR_AAT_INSTANCE_ID]="0",
	[TRANSPORT_VAR_AAT_SEEK_TARGET]="",
	[TRANSPORT_VAR_PLAY_MEDIUM]="UNKNOWN",
	[TRANSPORT_VAR_REL_TIME_POS]=kZeroTime,
	[TRANSPORT_VAR_REC_MEDIA]="NOT_IMPLEMENTED",
	[TRANSPORT_VAR_CUR_PLAY_MODE]="NORMAL",
	[TRANSPORT_VAR_TRANSPORT_PLAY_SPEED]="1",
	[TRANSPORT_VAR_PLAY_MEDIA]="NETWORK,UNKNOWN",
	[TRANSPORT_VAR_ABS_TIME_POS]="NOT_IMPLEMENTED",
	[TRANSPORT_VAR_CUR_TRACK]="0",
	[TRANSPORT_VAR_CUR_TRACK_URI]="",
	[TRANSPORT_VAR_CUR_TRANSPORT_ACTIONS]="PLAY",	
	[TRANSPORT_VAR_NR_TRACKS]="0",
	[TRANSPORT_VAR_AV_URI]="",
	[TRANSPORT_VAR_ABS_CTR_POS]="2147483647",
	[TRANSPORT_VAR_CUR_REC_QUAL_MODE]="NOT_IMPLEMENTED",
	[TRANSPORT_VAR_CUR_MEDIA_DUR]="",
	[TRANSPORT_VAR_AAT_SEEK_MODE]="TRACK_NR",
	[TRANSPORT_VAR_AV_URI_META]="",
	[TRANSPORT_VAR_REC_MEDIUM]="NOT_IMPLEMENTED",
	[TRANSPORT_VAR_REC_MEDIUM_WR_STATUS]="NOT_IMPLEMENTED",
	[TRANSPORT_VAR_LAST_CHANGE]="<Event xmlns=\"urn:schemas-upnp-org:metadata-1-0/AVT/\"/>",
	[TRANSPORT_VAR_CUR_TRACK_DUR]=kZeroTime,
	[TRANSPORT_VAR_TRANSPORT_STATE]="STOPPED",
	[TRANSPORT_VAR_POS_REC_QUAL_MODE]="NOT_IMPLEMENTED",
	[TRANSPORT_VAR_UNKNOWN]=NULL
};

const char *transport_states[] =
{
	"STOPPED",
	"PLAYING",
	"PAUSED_PLAYBACK",
	NULL
};

const char *transport_stati[] =
{
	"OK",
	"ERROR_OCCURRED",
	" vendor-defined ",
	NULL
};

struct var_meta transport_var_meta[] =
{
	[TRANSPORT_VAR_TRANSPORT_STATUS]={SENDEVENT_NO,DATATYPE_STRING,transport_stati,NULL,NULL},
	[TRANSPORT_VAR_NEXT_AV_URI]={SENDEVENT_NO,DATATYPE_STRING,NULL,NULL},
	[TRANSPORT_VAR_NEXT_AV_URI_META]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_CUR_TRACK_META]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_REL_CTR_POS]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_AAT_INSTANCE_ID]={ SENDEVENT_NO,DATATYPE_UI4,NULL,NULL,NULL },
	[TRANSPORT_VAR_AAT_SEEK_TARGET]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_PLAY_MEDIUM]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_REL_TIME_POS]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_REC_MEDIA]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_CUR_PLAY_MODE]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_TRANSPORT_PLAY_SPEED]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_PLAY_MEDIA]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_ABS_TIME_POS]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_CUR_TRACK]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_CUR_TRACK_URI]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_CUR_TRANSPORT_ACTIONS]={SENDEVENT_NO,DATATYPE_STRING,NULL,NULL,NULL},
	[TRANSPORT_VAR_NR_TRACKS]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_AV_URI]={SENDEVENT_NO,DATATYPE_STRING,NULL,NULL,NULL},
	[TRANSPORT_VAR_ABS_CTR_POS]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_CUR_REC_QUAL_MODE]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_CUR_MEDIA_DUR]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_AAT_SEEK_MODE]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_AV_URI_META]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_REC_MEDIUM]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_REC_MEDIUM_WR_STATUS]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_LAST_CHANGE]={SENDEVENT_YES,DATATYPE_STRING,NULL,NULL,NULL},
	[TRANSPORT_VAR_CUR_TRACK_DUR]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_TRANSPORT_STATE]={ SENDEVENT_NO,DATATYPE_STRING,transport_states,NULL,NULL },
	[TRANSPORT_VAR_POS_REC_QUAL_MODE]={SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL},
	[TRANSPORT_VAR_UNKNOWN]={ SENDEVENT_NO,DATATYPE_UNKNOWN,NULL,NULL,NULL }
};

struct argument instanceID={ "InstanceID",PARAM_DIR_IN,TRANSPORT_VAR_AAT_INSTANCE_ID };
struct argument arg2={ "CurrentURI",PARAM_DIR_IN,TRANSPORT_VAR_AV_URI };
struct argument arg3={ "CurrentURIMetaData",PARAM_DIR_IN,TRANSPORT_VAR_AV_URI_META };
struct argument *arguments_setavtransporturi[] = {&instanceID,&arg2,&arg3,NULL};
/*
{
	& (struct argument) { "InstanceID",PARAM_DIR_IN,TRANSPORT_VAR_AAT_INSTANCE_ID },
	& (struct argument) { "CurrentURI",PARAM_DIR_IN,TRANSPORT_VAR_AV_URI },
	& (struct argument) { "CurrentURIMetaData",PARAM_DIR_IN,TRANSPORT_VAR_AV_URI_META },
	NULL

{
	{ "InstanceID",PARAM_DIR_IN,TRANSPORT_VAR_AAT_INSTANCE_ID },
	{ "CurrentURI",PARAM_DIR_IN,TRANSPORT_VAR_AV_URI },
	{ "CurrentURIMetaData",PARAM_DIR_IN,TRANSPORT_VAR_AV_URI_META },
	NULL
}
};
*/
//struct argument arg4={"InstanceID",PARAM_DIR_IN,TRANSPORT_VAR_AAT_INSTANCE_ID};
struct argument arg5={"PlayMedia",PARAM_DIR_OUT,TRANSPORT_VAR_PLAY_MEDIA};
struct argument arg6={"RecMedia",PARAM_DIR_OUT,TRANSPORT_VAR_REC_MEDIA};
struct argument arg7={"RecQualityModes",PARAM_DIR_OUT,TRANSPORT_VAR_POS_REC_QUAL_MODE};
struct argument *arguments_getdevicecapabilities[] ={&instanceID,&arg5,&arg6,&arg7,NULL};
/*
{
	& (struct argument) { "InstanceID",PARAM_DIR_IN,TRANSPORT_VAR_AAT_INSTANCE_ID },
	& (struct argument) { "PlayMedia",PARAM_DIR_OUT,TRANSPORT_VAR_PLAY_MEDIA },
	& (struct argument) { "RecMedia",PARAM_DIR_OUT,TRANSPORT_VAR_REC_MEDIA },
	& (struct argument) { "RecQualityModes",PARAM_DIR_OUT,TRANSPORT_VAR_POS_REC_QUAL_MODE },
	NULL
};
*/

//struct argument arg8={ "InstanceID",PARAM_DIR_IN,TRANSPORT_VAR_AAT_INSTANCE_ID };
struct argument arg9={ "PlayMode",PARAM_DIR_OUT,TRANSPORT_VAR_CUR_PLAY_MODE };
struct argument arg10={ "RecQualityMode",PARAM_DIR_OUT,TRANSPORT_VAR_CUR_REC_QUAL_MODE };

struct argument *arguments_gettransportsettings[] ={&instanceID,&arg9,&arg10,NULL};
/*
{
	& (struct argument) { "InstanceID",PARAM_DIR_IN,TRANSPORT_VAR_AAT_INSTANCE_ID },
	& (struct argument) { "PlayMode",PARAM_DIR_OUT,TRANSPORT_VAR_CUR_PLAY_MODE },
	& (struct argument) { "RecQualityMode",PARAM_DIR_OUT,TRANSPORT_VAR_CUR_REC_QUAL_MODE },
	NULL
};
*/

//struct argument arg11={ "InstanceID",PARAM_DIR_IN,TRANSPORT_VAR_AAT_INSTANCE_ID };
struct argument *arguments_stop[] ={&instanceID,NULL};
/*
{
	& (struct argument) { "InstanceID",PARAM_DIR_IN,TRANSPORT_VAR_AAT_INSTANCE_ID },
	NULL
};
*/

//struct argument arg12={ "InstanceID",PARAM_DIR_IN,TRANSPORT_VAR_AAT_INSTANCE_ID };
struct argument arg13={ "Speed",PARAM_DIR_IN,TRANSPORT_VAR_TRANSPORT_PLAY_SPEED };
struct argument *arguments_play[] ={&instanceID,&arg13,NULL};
//{
//	& (struct argument) { "InstanceID",PARAM_DIR_IN,TRANSPORT_VAR_AAT_INSTANCE_ID },
//	& (struct argument) { "Speed",PARAM_DIR_IN,TRANSPORT_VAR_TRANSPORT_PLAY_SPEED },
//	NULL
//};

//struct argument arg14={ "InstanceID",PARAM_DIR_IN,TRANSPORT_VAR_AAT_INSTANCE_ID };
struct argument arg15={ "Actions",PARAM_DIR_OUT,TRANSPORT_VAR_CUR_TRANSPORT_ACTIONS };
struct argument *arguments_getcurrenttransportactions[] ={&instanceID,&arg15,NULL};
//{
//	& (struct argument) { "InstanceID",PARAM_DIR_IN,TRANSPORT_VAR_AAT_INSTANCE_ID },
//	& (struct argument) { "Actions",PARAM_DIR_OUT,TRANSPORT_VAR_CUR_TRANSPORT_ACTIONS },
//	NULL
//};

struct argument **argument_list[] =
{
	[TRANSPORT_CMD_GETCURRENTTRANSPORTACTIONS]=arguments_getcurrenttransportactions,
	[TRANSPORT_CMD_GETDEVICECAPABILITIES]=    arguments_getdevicecapabilities,
	[TRANSPORT_CMD_GETTRANSPORTSETTINGS]=     arguments_gettransportsettings,
	[TRANSPORT_CMD_PLAY]=                     arguments_play,
	[TRANSPORT_CMD_SETAVTRANSPORTURI]=        arguments_setavtransporturi,
	[TRANSPORT_CMD_STOP]=                     arguments_stop,
	[TRANSPORT_CMD_UNKNOWN] =	NULL
};

// Our 'instance' variables.
enum transport_state transport_state_=TRANSPORT_STOPPED;
variable_container_t *state_variables_=NULL;

/* protects transport_values,and service-specific state */

ithread_mutex_t transport_mutex;

void service_lock(void)
{
	ithread_mutex_lock(&transport_mutex);
	if (transport_service_.last_change)
		UPnPLastChangeCollector_start(transport_service_.last_change);
}

void service_unlock(void)
{
	if (transport_service_.last_change)
		UPnPLastChangeCollector_finish(transport_service_.last_change);
	ithread_mutex_unlock(&transport_mutex);
}

int obtain_instanceid(struct action_event *event,int *instance)
{
	const char *value=upnp_get_string(event,"InstanceID");
	if (value==NULL)
		{
			upnp_set_error(event,UPNP_SOAP_E_INVALID_ARGS,"Missing InstanceID");
			return(-1);
		}
	return(0);
}

// Replace given variable without sending an state-change event.
int replace_var(transport_variable_t varnum,const char *new_value)
{
	return(VariableContainer_change(state_variables_,varnum,new_value));
}

const char *get_var(transport_variable_t varnum)
{
	return(VariableContainer_get(state_variables_,varnum,NULL));
}

// Transport uri always comes in uri/meta pairs. Set these and also the related
// track uri/meta variables.
// Returns 1,if this meta-data likely needs to be updated while the stream
// is playing (e.g. radio broadcast).
int replace_transport_uri_and_meta(const char *uri,const char *meta)
{
	replace_var(TRANSPORT_VAR_AV_URI,uri);
	replace_var(TRANSPORT_VAR_AV_URI_META,meta);

	// This influences as well the tracks. If there is a non-empty URI,
	// we have exactly one track.
	const char *tracks=(uri!=NULL && strlen(uri) > 0) ? "1" : "0";
	replace_var(TRANSPORT_VAR_NR_TRACKS,tracks);

	// We only really want to send back meta data if we didn't get anything
	// useful or if this is an audio item.
	const int requires_stream_meta_callback=(strlen(meta)==0)
	                                        || strstr(meta,"object.item.audioItem");
	return(requires_stream_meta_callback);
}

// Similar to replace_transport_uri_and_meta() above,but current values.
void replace_current_uri_and_meta(const char *uri,const char *meta)
{
	const char *tracks=(uri!=NULL && strlen(uri) > 0) ? "1" : "0";
	replace_var(TRANSPORT_VAR_CUR_TRACK,tracks);
	replace_var(TRANSPORT_VAR_CUR_TRACK_URI,uri);
	replace_var(TRANSPORT_VAR_CUR_TRACK_META,meta);
}

void change_transport_state(enum transport_state new_state)
{
	transport_state_=new_state;
	if (!replace_var(TRANSPORT_VAR_TRANSPORT_STATE,transport_states[new_state]))
		return;

	const char *available_actions=NULL;
	switch (new_state)
		{
		case TRANSPORT_STOPPED:
			if (strlen(get_var(TRANSPORT_VAR_AV_URI))==0)
				available_actions="PLAY";
			else
				available_actions="PLAY,SEEK";
			break;
		case TRANSPORT_PLAYING:
			available_actions="PAUSE,STOP,SEEK";
			break;
		case TRANSPORT_PAUSED_PLAYBACK:
			available_actions="PLAY,STOP,SEEK";
			break;
		}

	if (available_actions)
		replace_var(TRANSPORT_VAR_CUR_TRANSPORT_ACTIONS,available_actions);
}

/* UPnP action handlers */

int set_avtransport_uri(struct action_event *event)
{
	if (obtain_instanceid(event,NULL) < 0)
		return(-1);

	const char *uri=upnp_get_string(event,"CurrentURI");
	if (uri==NULL)
		return(-1);

	service_lock();
	const char *meta=upnp_get_string(event,"CurrentURIMetaData");
	// Transport URI/Meta set now,current URI/Meta when it starts playing.
	int requires_meta_update=replace_transport_uri_and_meta(uri,meta);

	if (transport_state_==TRANSPORT_PLAYING)
		{
			// Uh,wrong state.
			// Usually,this should not be called while we are PLAYING,only
			// STOPPED or PAUSED. But if actually some controller sets this
			// while playing,probably the best is to update the current
			// current URI/Meta as well to reflect the state best.
			replace_current_uri_and_meta(uri,meta);
		}

	output_set_uri(uri);
	service_unlock();

	return(0);
}

int get_current_transportactions(struct action_event *event)
{
	return(0);
}

int get_transport_settings(struct action_event *event)
{
	if (obtain_instanceid(event,NULL) < 0)
		return(-1);
	return(0);
}

int get_device_caps(struct action_event *event)
{
	if (obtain_instanceid(event,NULL) < 0)
		return(-1);
	return(0);
}

int stop(struct action_event *event)
{
	if (obtain_instanceid(event,NULL) < 0)
		return(-1);

	service_lock();
	switch (transport_state_)
		{
		case TRANSPORT_STOPPED:
			break;
		case TRANSPORT_PLAYING:
		case TRANSPORT_PAUSED_PLAYBACK:
			output_stop();
			change_transport_state(TRANSPORT_STOPPED);
			break;
		}
	service_unlock();

	return(0);
}

void inform_play_transition_from_output(int fb)
{
	service_lock();
	switch (fb)
		{
		case PLAY_STOPPED:
			replace_transport_uri_and_meta("","");
			replace_current_uri_and_meta("","");
			change_transport_state(TRANSPORT_STOPPED);
			break;
		}
	service_unlock();
}

int play(struct action_event *event)
{
	if (obtain_instanceid(event,NULL) < 0)
		return(-1);

	int rc=0;
	service_lock();
	switch (transport_state_)
		{
		case TRANSPORT_PLAYING:
			// Nothing to change.
			break;

		case TRANSPORT_STOPPED:
			// If we were stopped before,we start a new song now. So just
			// set the time to zero now; otherwise we will see the old
			// value of the previous song until it updates some fractions
			// of a second later.
			replace_var(TRANSPORT_VAR_REL_TIME_POS,kZeroTime);

		/* >>> fall through */

		case TRANSPORT_PAUSED_PLAYBACK:
			//if (output_play(&inform_play_transition_from_output)) {
			if (output_play())
				{
					upnp_set_error(event,704,"Playing failed");
					rc=-1;
				}
			else
				{
					change_transport_state(TRANSPORT_PLAYING);
					const char *av_uri=get_var(TRANSPORT_VAR_AV_URI);
					const char *av_meta=get_var(TRANSPORT_VAR_AV_URI_META);
					replace_current_uri_and_meta(av_uri,av_meta);
				}
			break;
		}
	service_unlock();

	return(rc);
}

struct action transport_actions[] =
{
	[TRANSPORT_CMD_GETCURRENTTRANSPORTACTIONS]={"GetCurrentTransportActions",get_current_transportactions},
	[TRANSPORT_CMD_GETDEVICECAPABILITIES]=    {"GetDeviceCapabilities",get_device_caps},
	[TRANSPORT_CMD_GETTRANSPORTSETTINGS]=     {"GetTransportSettings",get_transport_settings},
	[TRANSPORT_CMD_PLAY]=                     {"Play",play},
	[TRANSPORT_CMD_SETAVTRANSPORTURI]=        {"SetAVTransportURI",set_avtransport_uri},	/* RC9800i */
	[TRANSPORT_CMD_STOP]=                     {"Stop",stop},
	[TRANSPORT_CMD_UNKNOWN]=                 {NULL,NULL}
};

struct service *upnp_transport_get_service(void)
{
	if (transport_service_.variable_container==NULL)
		{
			state_variables_=VariableContainer_new(TRANSPORT_VAR_COUNT,transport_variable_names,transport_default_values);
			transport_service_.variable_container=state_variables_;
		}
	return(&transport_service_);
}


void upnp_transport_register_variable_listener(variable_change_listener_t cb,void *userdata)
{
	VariableContainer_register_callback(state_variables_,cb,userdata);
}

struct service transport_service_={&transport_mutex,TRANSPORT_SERVICE_ID,TRANSPORT_TYPE,TRANSPORT_SCPD_URL,TRANSPORT_CONTROL_URL,TRANSPORT_EVENT_URL,TRANSPORT_EVENT_XML_NS,transport_actions,argument_list,transport_variable_names,NULL,NULL,transport_var_meta,TRANSPORT_VAR_UNKNOWN,TRANSPORT_CMD_UNKNOWN,NULL,NULL};
