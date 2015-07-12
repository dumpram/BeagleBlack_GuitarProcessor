/** @file delay_line.h
 *
 * @brief File contains declarations of functions which are necessary for delay line structure in 
 *	digital signal processing. Documentation of functions can be found in delay_line.h header file. 
 * @author Ivan Pavic
 * @version 1.0
 */
#ifndef _DELAY_LINE_H_
#define _DELAY_LINE_H_


#include "audio_types.h"

#define DELAY_LINE_MAX 15000

typedef struct delay_line delay_line_t;
/**
 * Structure represent delay line object.
 */
struct delay_line {
	audio_sample_t samples[DELAY_LINE_MAX];
	audio_sample_t *wptr;
	audio_sample_t *rptr;
};
/**
 * Function creates delay line with given delay.
 * @param delay: delay for delay line
 */
delay_line_t *createDelayLine(int delay);
/**
 * Function gets sample from start of delay line given as parameter.
 * @param line: pointer to delay line structure
 * @retval returns audio_sample_t from start of delay line.
 */
audio_sample_t endOfDelayLine(delay_line_t *line);
/**
 * Function gets sample from start of delay line given as parameter.
 * @param line: pointer to delay line structure
 * @retval returns audio_sample_t from start of delay line.
 */
audio_sample_t startOfDelayLine(delay_line_t *line);
/**
 * Function shifts samples in delay line given as parameter and returns value form
 * end of delay line.
 * @param line: pointer to delay line structure
 * @param sample: sample to insert in delay line
 * @retval returns sample from end of delay line
 */
audio_sample_t shiftDelayLine(delay_line_t *line, audio_sample_t sample);
/**
 * Functions sets delay in delay line given as parameter.
 * @param line: pointer to delay line structure
 * @param delay: delay for delay line
 *
 */
void setDelay(delay_line_t *line, int delay);
#endif
