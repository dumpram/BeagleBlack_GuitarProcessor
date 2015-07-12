/** @file DEP.h
 *
 * @brief header file of of DEP application. Contains all necessary includes, definitions and
 *	declarations of DEP application. For more infromation reffer to technical documentation.
 * @author Ivan Pavic
 * @version 1.0
 */

#ifndef _DEP_H_ 
#define _DEP_H_

/** UNIX includes **/

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

/** JACK includes **/

#include <jack/jack.h>

/** FFT library **/

#include <fftw3.h>

/** User includes **/

#include "beagleblack_gpio.h"
#include "beagleblack_lcd.h"
#include "digital_effects.h"
#include "ipc_sockets.h"
#include "user_interface.h"


void init_audio_client(processor_t *processor);
void processor_init(processor_t *processor, lcd_pinout *lcd);

typedef jack_default_audio_sample_t audio_sample_t;
typedef jack_nframes_t nframes_t;
typedef jack_port_t audio_port_t;
typedef jack_client_t audio_client_t;

#endif

