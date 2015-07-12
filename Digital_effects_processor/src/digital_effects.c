/** @file digital_effects.c
 *
 * @brief file contains implementations of digital effects for sound processing.
 * @author Ivan Pavic
 * @version 1.0
 */
 
#include <DEP.h>
#include "digital_effects.h"

#define MAX_DELAY 15000
#define EQ_SAMPLE_NUMBER 16
#define TUNER_SET_NUMBER 50


static void (*effects[EFFECTS_NUM])(audio_sample_t *samples, processor_t *processor);

static fftw_complex tuner_freq_data[TUNER_SET_NUMBER * 1024 * 2];
static fftw_complex tuner_time_data[TUNER_SET_NUMBER * 1024 * 2];

static int tunerCounter = 0;
static int tunerCopy = 1;
static char tunerTable[1368][3];
static char toneTable[12][3] = {"E", "F", "F#", "G", "G#", "A", "A#", "B", "C", "C#", "D", "D#"};

void digital_signal_processing(audio_sample_t *samples, processor_t *processor) {
    int i;
    
    /** Process samples with algorithms **/
    for(i = 0; i < EFFECTS_NUM; i++) {
        (*effects[i])(samples, processor);
    }
    return;
}

void init_digital_effects() {
    effects[0] = effect_tuner;
    effects[1] = effect_distortion;
    effects[2] = effect_reverb;
    effects[3] = effect_filters;
    effects[4] = effect_delay;
}

void effect_delay(audio_sample_t *samples, processor_t *processor) {
    
}

void effect_reverb(audio_sample_t *samples, processor_t *processor) {
    int i;
    
    if (processor -> switch_state[1]) {
        return;
    }
    
    for (i = 0; i < 1024; i++) {
        samples[i] = samples[i] + (processor -> reverb -> decay) * endOfDelayLine(processor -> reverb -> delayLine);
        shiftDelayLine(processor -> reverb -> delayLine, samples[i]);
    }
    return;
}

void effect_distortion(audio_sample_t *samples, processor_t *processor) {
    int i;
    
    if (processor -> switch_state[0]) {
        return;
    }
    
    for (i = 0; i < 1024; i++) {
        samples[i] *= processor -> dist -> gain;
        if (samples[i] > processor -> dist -> psaturation) {
            samples[i] = processor -> dist -> psaturation;
        }
        if (samples[i] < (-(processor -> dist -> nsaturation))) {
            samples[i] = -(processor -> dist -> nsaturation);
        }
    }
}

void effect_filters(audio_sample_t *samples, processor_t *processor) {
	int i, j;
	double a0, a1, a2, b0, b1, b2, t;
	delay_line_t *sampleDlyLine, *respDlyLine;	
	for (i = 0; i < 8; i++) {
		a0 = processor -> filter[i] -> a0;
		a1 = processor -> filter[i] -> a1;
		a2 = processor -> filter[i] -> a2;
		b0 = processor -> filter[i] -> b0;
		b1 = processor -> filter[i] -> b1;
		b2 = processor -> filter[i] -> b2;
		sampleDlyLine = processor -> filter[i] -> sampleDelayLine;
		respDlyLine = processor -> filter[i] -> responseDelayLine;
		for (j = 0; j < 1024; j++) {
			t = samples[j];
		    	samples[j] = (b0/a0) * samples[j] + (b1/a0) * startOfDelayLine(sampleDlyLine) + (b2/a0) * endOfDelayLine(sampleDlyLine)
			    			- (a1/a0) * startOfDelayLine(respDlyLine) - (a2/a0) * endOfDelayLine(respDlyLine);
            		shiftDelayLine(sampleDlyLine, t);
            		shiftDelayLine(respDlyLine, samples[j]);
		}	
	}
}

void effect_tuner(audio_sample_t *samples, processor_t *processor) {
    if (processor -> switch_state[2]) {
        return;
    }
    int i;
    if (tunerCopy && tunerCounter < TUNER_SET_NUMBER) {
        for(i = 0; i < 1024; i++) {
            tuner_time_data[1024 * tunerCounter + i][0] = samples[i];
            tuner_time_data[1024 * tunerCounter + i][1] = 0;
        }
        tunerCounter++;
    } else if (tunerCopy && tunerCounter == TUNER_SET_NUMBER) {
        //fprintf(stderr, "Iskopirao!\n");
        tunerCounter = 0;
        tunerCopy = 0;
    } else if (!tunerCopy) {
        //fprintf(stderr, "Čekam!\n");
    }
}

distortion_t *create_distortion() {
    distortion_t *forExport = (distortion_t *) malloc(sizeof(distortion_t));
    forExport -> psaturation = 0.1;
    forExport -> nsaturation = 0.1;
    forExport -> gain = 10;
    return forExport;
}

reverb_t *create_reverb() {
    reverb_t *forExport = (reverb_t *) malloc(sizeof(reverb_t));
    forExport -> decay = 0.6;
    forExport -> delay = 8000;
    forExport -> delayLine = createDelayLine(8000);
    return forExport;
}

biquad_filter_t *create_biquad_filter(void (*calcCoefficients)(biquad_filter_t*), double sigFreq, double dBgain, double qFactor) {
	biquad_filter_t *forExport = (biquad_filter_t *) malloc(sizeof(biquad_filter_t));
	forExport -> sampleDelayLine = createDelayLine(2);
	forExport -> responseDelayLine = createDelayLine(2);
	forExport -> sigFreq = sigFreq;
	forExport -> dBgain = dBgain;
	forExport -> qFactor = qFactor;
	forExport -> calcCoefficients = calcCoefficients;
	forExport -> calcCoefficients(forExport);
	return forExport;
}

void peak_eq_filter(biquad_filter_t *filter) {
    double w0 = (2.0 * M_PI * filter -> sigFreq) / SAMPLE_FREQ;
    double alpha = sin(w0)/(2 * filter -> qFactor);
    double A = sqrt(pow(10, ((filter -> dBgain)/40)));
    filter -> b0 = 1 + alpha * A;
    filter -> b1 = -2 * cos(w0);
    filter -> b2 = 1 - alpha * A;
    filter -> a0 = 1 + alpha/A;
    filter -> a1 = -2 * cos(w0);
    filter -> a2 = 1 - alpha/A;
    double a0 = filter -> a0;
    fprintf(stderr, "Podesio! %f %f %f %f %f %f\n", filter->b0/a0, filter->b1/a0, filter->b2/a0, filter->a1/a0, filter->a2/a0, filter->dBgain);
}

void high_pass_filter(biquad_filter_t *filter) {
    double w0 = (2.0 * M_PI * filter -> sigFreq) / SAMPLE_FREQ;
    double alpha = sin(w0)/(2 * filter -> qFactor);
    double A = sqrt(pow(10, ((filter -> dBgain)/40)));
    filter -> b0 = (1 + cos(w0))/2;
    filter -> b1 = -(1 + cos(w0));
    filter -> b2 = (1 + cos(w0))/2;
    filter -> a0 = 1 + alpha;
    filter -> a1 = -2 * cos(w0);
    filter -> a2 = 1 - alpha;
}

void low_shelf_filter(biquad_filter_t *filter) {
    double w0 = (2.0 * M_PI * filter -> sigFreq) / SAMPLE_FREQ;
    double alpha = sin(w0)/(2 * filter -> qFactor);
    double A = sqrt(pow(10, ((filter -> dBgain)/20)));
    filter -> b0 =  A*( (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha );
    filter -> b1 =  2*A*( (A-1) - (A+1)*cos(w0));
    filter -> b2 = A*( (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha);
    filter -> a0 = (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha;
    filter -> a1 = -2*( (A-1) + (A+1)*cos(w0));
    filter -> a2 = (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha;
    fprintf(stderr, "Podesio! %f %f %f %f %f %f\n", filter->b0, filter->b1, filter->b2, filter->a1, filter->a2, alpha);
}

int findMaxIndex() {
    int i, max = 0;
    double real, imag, absolute, max_value = 0;
    //for(i = 50; i < TUNER_SET_NUMBER * 1024/2 + 1; i++) {
    for(i = 700; i < 1400; i++) {
        tuner_freq_data[i][0] += tuner_freq_data[i / 4][0] + tuner_freq_data[i / 2][0] + tuner_freq_data[i * 4][0] + tuner_freq_data[i * 8][0];
        tuner_freq_data[i][1] += tuner_freq_data[i / 4][0] + tuner_freq_data[i / 2][0] + tuner_freq_data[i * 4][0] + tuner_freq_data[i * 8][0];
    }
    for(i = 700; i < 1400; i++) {
        real = tuner_freq_data[i][0];
        imag = tuner_freq_data[i][1];
        absolute = sqrt(real * real + imag * imag);
        
        if (absolute > max_value) {
            max_value = absolute;
            max = i;
        }
    }
    return max;
}

void tuner_task(processor_t *processor) {
    fftw_plan fft;
    int maxIndex, i;
    double maxFreq;
    char str[20];
    genTunerTable();
    while(1) {
        while(tunerCopy) usleep(20000);
        memcpy(tuner_time_data + TUNER_SET_NUMBER * 1024, tuner_time_data, sizeof(fftw_complex) * 1024 * TUNER_SET_NUMBER);
        fft  = fftw_plan_dft_1d(1024 * TUNER_SET_NUMBER * 2, tuner_time_data, tuner_freq_data, FFTW_FORWARD, FFTW_ESTIMATE);
        
        fftw_execute(fft);
        maxIndex = findMaxIndex();
        maxFreq = maxIndex * (48000./((TUNER_SET_NUMBER * 1024.0) * 2));
        fprintf(stderr, "Maksimalna frekvencija je: %f, indeks: %d\n", maxFreq, maxIndex);
        sprintf(str, "Freq = %6.2f Hz", maxFreq);
        tunerPrint(str, maxIndex);
        fprintf(stderr, "%s\n", str);
        if (!(processor -> switch_state[2])) {
            lcd_disp(processor -> lcd, str);
        }
        tunerCopy = 1;
    }
}



void genTunerTable() {
	double START = 330.0;
    double korak = pow(2, 1./12);
	double i, donja, gornja;
	int brojac_tonova = 0, koraka_doli, koraka_gori, punjac_polja = 0;
	for(i = START; i <= START * 2; i*=korak) {
		donja = i/korak;
		gornja = i*korak;
		koraka_doli = (i - donja) * 32./15;
		koraka_gori = (gornja - i) * 32./15;
		if(i != START) {koraka_doli = koraka_doli / 2;}
		koraka_gori = koraka_gori / 2;
		if(brojac_tonova == 1 || brojac_tonova == 2 || brojac_tonova == 4 || brojac_tonova == 8 || brojac_tonova == 11) {
			koraka_doli += 1;		
		}
		if(brojac_tonova == 3) {
			koraka_doli -= 3;
		}
		if(brojac_tonova == 7 || brojac_tonova == 10 || brojac_tonova == 9) {
			koraka_doli -= 1;
		}
		printf("TON:%s, KD:%d, KG:%d\n", toneTable[brojac_tonova], koraka_doli, koraka_gori);
		while((koraka_doli--)) strcat(tunerTable[punjac_polja++], ">");
		strcat(tunerTable[punjac_polja++],toneTable[brojac_tonova++]);
		while((koraka_gori--)) strcat(tunerTable[punjac_polja++], "<");
	}
	double pocetna = START/korak;
	int promjena = (START - pocetna) * 32./15;
	pocetna = START - promjena * 15./32;
	printf("PUNJAC: %d\n", punjac_polja);
	double R = 48000./(1024 * 50 * 2);
	for(punjac_polja = 0; punjac_polja < 800; punjac_polja++) {
	    printf("%f: %d. %s\n",pocetna + punjac_polja * R, punjac_polja + 665, tunerTable[punjac_polja]);	
	}
}

void tunerPrint(char *str, int index) {
    index -= 665;
    int tuneCounter = 0, i;
    while(!strcmp(tunerTable[index], ">")) {
        index++;
        if(tuneCounter < 7) tuneCounter++;
    }
    while(!strcmp(tunerTable[index], "<")) {
        index--;
        if(tuneCounter > -6) tuneCounter--;
    }
    printf("TUNER COUNTER: %d\n", tuneCounter);
    tuneCounter /= 2;
    for(i = 0; i < 16; i++) {
        *(str + i) = '-';
    }
    if(tuneCounter > 0) {
        *(str + 7 - tuneCounter) = '>';
    }
    if(tuneCounter < 0) {
        *(str - tuneCounter + 7) = '<';
    }
    if(tuneCounter == 0) {
        *(str + 6) = '>';
        *(str + 8) = '<';
    }
    *(str + 7) = tunerTable[index][0];
    if(strlen(tunerTable[index]) == 2) {
        *(str + 15) = '#';
    }
    *(str + 16) = '\0';
}
