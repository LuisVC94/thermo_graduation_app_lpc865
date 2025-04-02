#ifndef AUDIO_READER_H_
#define AUDIO_READER_H_

#include "arm_math.h"

#define DECREASE_VALUE_PEAK_DETECTOR 0.0001
#define DECREASE_VALUE_PEAK_DETECTOR_SHORT 0.01

void audio_reader_init(void);

float32_t get_music_val(void);

float32_t get_audio_filttered();

float32_t get_audio_peak();

float32_t get_audio_peak_short();

void audio_reader_task(void);

#endif /* AUDIO_READER_H_ */
