#ifndef _DIGITAL_EFFECTS_H
#define _DIGITAL_EFFECTS_H


#include <math.h>
#include <semaphore.h>

#include "delay_line.h"
#include "audio_types.h"

#define EFFECTS_NUM 5
#define SWITCH_NUM 3

#define MAX_FILTER_NUM 16
#define SAMPLE_FREQ 48000

typedef struct processor processor_t;
typedef struct distortion distortion_t;
typedef struct reverb reverb_t;
typedef struct eq eq_t;
typedef struct biquad_filter biquad_filter_t;
typedef struct digital_effect digital_effect_t;


struct digital_effect {
    void (*effect_algorithm)(audio_sample_t *samples, digital_effect_t* self); 
};

struct distortion {
    double psaturation;
    double nsaturation;
    double gain;
};

struct biquad_filter {
	double a0, a1, a2, b0, b1, b2;
	double sigFreq, dBgain, qFactor;
	delay_line_t *sampleDelayLine;
	delay_line_t *responseDelayLine;
	void (*calcCoefficients)(biquad_filter_t *);
};

struct reverb {
    int delay;
    double decay;
    delay_line_t *delayLine;
};

struct processor {
    int switch_state[SWITCH_NUM];
    int switch_id_list[SWITCH_NUM];
    lcd_pinout *lcd;
    int update;
    distortion_t *dist;
    reverb_t *reverb;
    biquad_filter_t *filter[MAX_FILTER_NUM];

};

distortion_t *create_distortion();
reverb_t *create_reverb();
biquad_filter_t *create_biquad_filter(void (*calcCoefficients)(biquad_filter_t*), 
                                                double sigFreq, 
                                                double dBgain, 
                                                double qFactor);
/**
 * Function processes data given as argument with algorithms implemented in 
 * digital effects array.
 */
void digital_signal_processing(audio_sample_t *samples, processor_t *processor);
/**
 * Function initializes array of digital effects.
 */ 
void init_digital_effects();

/* Digital effects algorithms */
void effect_reverb(audio_sample_t *samples, processor_t *processor);
void effect_distortion(audio_sample_t *samples, processor_t *processor);
void effect_delay(audio_sample_t *samples, processor_t *processor);
void effect_filters(audio_sample_t *samples, processor_t *processor);
void effect_tuner(audio_sample_t *samples, processor_t *processor);

void set_delay(int delay);

/* Filter calculation functions */
void peak_eq_filter(biquad_filter_t *filter);
void high_pass_filter(biquad_filter_t *filter);
void low_shelf_filter(biquad_filter_t *filter);

/** Frequency analysis task **/
void tuner_task(processor_t *processor);

#endif
