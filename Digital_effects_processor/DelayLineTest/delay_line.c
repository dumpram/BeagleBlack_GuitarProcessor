#include "delay_line.h"

delay_line_t *createDelayLine(int delay) {
	if (delay >= DELAY_LINE_MAX) {
		return NULL;
	}
	delay_line_t *delayLine = (delay_line_t *) malloc(sizeof(delay_line_t));
	int i;
	for (i = 0; i < DELAY_LINE_MAX; i++) {
		delayLine -> samples[i] = 0;	
	}
	setDelay(delayLine, delay);
	return delayLine;
}	
audio_sample_t endOfDelayLine(delay_line_t *line) {
	return *(line -> rptr);
}

audio_sample_t startOfDelayLine(delay_line_t *line) {
	audio_sample_t *wtemp;
	wtemp = line -> wptr;
	if (wtemp - 1 < 0) {
		wtemp += DELAY_LINE_MAX;
	}
	return *(wtemp-1);
}

audio_sample_t shiftDelayLine(delay_line_t *line, audio_sample_t sample) {
	audio_sample_t forExport;
	*(line -> wptr) = sample;    
	(line -> wptr)++;
	forExport = *(line -> rptr); 
	(line -> rptr)++;
	if (((line -> wptr) - (line -> samples)) >= DELAY_LINE_MAX) {
		(line -> wptr) -= DELAY_LINE_MAX;	
	}
	if (((line -> rptr) - (line -> samples)) >= DELAY_LINE_MAX) {
		(line -> rptr) -= DELAY_LINE_MAX;	
	}
	return forExport;
}

void setDelay(delay_line_t *line, int delay) {
	(line -> rptr) = (line -> samples);
	(line -> wptr) = (line -> samples);
	(line -> rptr) = (line -> wptr) - delay;
	while ((line -> rptr) < (line -> samples)) {
		(line -> rptr) += DELAY_LINE_MAX;	
	}
}
