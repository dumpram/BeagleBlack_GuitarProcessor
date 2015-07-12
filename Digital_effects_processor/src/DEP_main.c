/** @file DEP_main.c
 *
 * @brief main file of of Digital Effects Processor application.
 * @author Ivan Pavic
 * @version 1.0.1.
 */

/** Header with all necessary declarations **/
#include <DEP.h>

/** Global audio port pointers **/
static audio_port_t *input_port;
static audio_port_t *output_port;

/* Application is visible as client to JACK audio server */
audio_client_t *client;

/**
 * Function gets audio sample data from input port. It delegates data to all 
 * observers and processes it. After processing data is sent to output port.
 */
int process(nframes_t nframes, void *arg) {
    /** Pointers to memory locations of input and output samples **/

    audio_sample_t *input, *output;
    processor_t *processor = (processor_t *) arg;
    input = jack_port_get_buffer (input_port, nframes);
    output = jack_port_get_buffer (output_port, nframes);
    
    /** Digital Signal Processing **/
    digital_signal_processing(input, processor);
   
    /** Copying files to output memory location **/ 
    memcpy(output, input, sizeof(audio_sample_t) * nframes);
    
    return 0;
}

void jack_shutdown(void *arg) {
    exit(1);
}

/**
 * Initializes and runs JACK audio client. Connects physical audio input
 * to input of JACK audio client. Additionally it connects output of client
 * to left and right playback port.
 */
void initAudioClient(processor_t *processor) {
    const char **ports;
	const char *client_name = "DEP";
	const char *server_name = NULL;
	jack_options_t options = JackNullOption;
	jack_status_t status;
	
	/* Open a client connection to the JACK server */
	client = jack_client_open (client_name, options, &status, server_name);
	if (client == NULL) {
		fprintf (stderr, "jack_client_open() failed, "
			 "status = 0x%2.0x\n", status);
		if (status & JackServerFailed) {
			fprintf (stderr, "Unable to connect to JACK server\n");
		}
		exit (1);
	}
	
	if (status & JackServerStarted) {
		fprintf (stderr, "JACK server started\n");
	}
	if (status & JackNameNotUnique) {
		client_name = jack_get_client_name(client);
		fprintf (stderr, "unique name `%s' assigned\n", client_name);
	}

	/* Set callback function for client. Function will be called every cycle */
	jack_set_process_callback (client, process, processor);

	/* Set shutdown function for client. Function will be called on shutdown */
	jack_on_shutdown (client, jack_shutdown, 0);

	/* Create two ports(global) */
	input_port = jack_port_register (client, "input",
					 JACK_DEFAULT_AUDIO_TYPE,
					 JackPortIsInput, 0);
	output_port = jack_port_register (client, "output",
					  JACK_DEFAULT_AUDIO_TYPE,
					  JackPortIsOutput, 0);
					  
	if ((input_port == NULL) || (output_port == NULL)) {
		fprintf(stderr, "no more JACK ports available\n");
		exit (1);
	}
	
	/* Activate JACK client. Callback function will be called every cycle */
	if (jack_activate (client)) {
		fprintf (stderr, "cannot activate client");
		exit (1);
	}
	/* Connect the ports. Connects client's ports to physical inputs and outputs */
	ports = jack_get_ports (client, NULL, NULL,
				JackPortIsPhysical|JackPortIsOutput);
	if (ports == NULL) {
		fprintf(stderr, "no physical capture ports\n");
		exit (1);
	}
	if (jack_connect (client, ports[0], jack_port_name (input_port))) {
		fprintf (stderr, "cannot connect input ports\n");
	}
	ports = jack_get_ports (client, NULL, NULL,
				JackPortIsPhysical|JackPortIsInput);
	if (ports == NULL) {
		fprintf(stderr, "no physical playback ports\n");
		exit (1);
	}
	if (jack_connect (client, jack_port_name (output_port), ports[0])) {
		fprintf (stderr, "cannot connect output ports\n");
	}
	
	if (jack_connect (client, jack_port_name (output_port), ports[1])) {
		fprintf (stderr, "cannot connect output ports\n");
	}
	free (ports);
}
/**
 * Function intializes processor structure which is description of whole system 
 * for digital sound processing. Additionally it starts JACK audio client and 
 * server.
 */
void initProcessor(processor_t *processor) {
	init_digital_effects();
	switch_init();
	processor -> switch_id_list[0] = SWITCH_GPIO_1;
	processor -> switch_id_list[1] = SWITCH_GPIO_2;
	processor -> switch_id_list[2] = SWITCH_GPIO_3;
	processor -> reverb = create_reverb();
	processor -> dist = create_distortion();
   	processor -> lcd = create_lcd();
   	double qFactor = 1/sqrt(2);
   	double qFactorL = 0.001;
   	processor -> filter[0] = create_biquad_filter(peak_eq_filter, 64, 0, qFactorL);
   	processor -> filter[1] = create_biquad_filter(peak_eq_filter, 125, 0, qFactorL);
   	processor -> filter[2] = create_biquad_filter(peak_eq_filter, 250, 0, qFactorL);
   	processor -> filter[3] = create_biquad_filter(peak_eq_filter, 500, 0, qFactorL);
   	processor -> filter[4] = create_biquad_filter(peak_eq_filter, 1000, 0, qFactorL);
   	processor -> filter[5] = create_biquad_filter(peak_eq_filter, 2000, 0, qFactor);
   	processor -> filter[6] = create_biquad_filter(peak_eq_filter, 4000, 0, qFactor);
   	processor -> filter[7] = create_biquad_filter(peak_eq_filter, 8000, 0, qFactor);
	initAudioClient(processor);
}


/**
 * Main function of application. Registers inputs and outputs in OS and connects 
 * them. If necessary JACK server will be started. Additionally, threads for 
 * frequency analysis, IPC communication and GPIO changes are started.
 */
int main() {
	pthread_t switch_handler, ipc_rack_handler, freq_analysis_handler;
	processor_t processor;
    initProcessor(&processor);
    
   	if(pthread_create(&switch_handler, NULL, switch_monitor, &processor)) {
   		perror("Couldn't create 'switch_monitor' thread!");
   	}
   	if(pthread_create(&ipc_rack_handler, NULL, ipc_audio_effects, &processor)) {
   		perror("Couldn't create 'ipc_audio_effects' thread!");
   	}
   	if(pthread_create(&freq_analysis_handler, NULL, tuner_task, &processor)) {
   	 	perror("Couldn't create 'tuner_task' thread!");
   	}
    sleep(-1);
	return 0;	
}
 

