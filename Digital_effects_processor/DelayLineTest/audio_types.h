#ifndef _AUDIO_TYPES_H_
#define _AUDIO_TYPES_H_

#include <jack/jack.h>

typedef jack_default_audio_sample_t audio_sample_t;
typedef jack_nframes_t nframes_t;
typedef jack_port_t audio_port_t;
typedef jack_client_t audio_client_t;


#endif