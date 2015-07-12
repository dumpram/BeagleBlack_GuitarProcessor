#ifndef _DELAY_LINE_H_
#define _DELAY_LINE_H_

//#include "audio_types.h"
#include <stdio.h>
#define DELAY_LINE_MAX 15000

typedef struct delay_line delay_line_t;
typedef double audio_sample_t; 

struct delay_line {
	audio_sample_t samples[DELAY_LINE_MAX];
	audio_sample_t *wptr;
	audio_sample_t *rptr;
};

delay_line_t *createDelayLine(int delay);
audio_sample_t endOfDelayLine(delay_line_t *line);
audio_sample_t startOfDelayLine(delay_line_t *line);
audio_sample_t shiftDelayLine(delay_line_t *line, audio_sample_t sample);
void setDelay(delay_line_t *line, int delay);
#endif