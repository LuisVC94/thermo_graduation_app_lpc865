#ifndef APP_H_
#define APP_H_

#include "led_rgb.h"
#include "fsl_mrt.h"

#define MIN_MAX_AUDIO		0.1
#define MIN_AVAILABLE_AUDIO 0.002
#define AUDO_SAMPLE_FREQ 	20000
#define TASK_FREQUENCY 		100

typedef enum _app_modes_t
{
	k_static_color_mode,
	k_breathe_color_mode,
	k_change_color_mode,
	k_rainbow_mode,
	k_audio_blink_mode,
	k_audio_fft_mode
} app_modes_t;

void app_init(void);

void app_set_frequency(uint32_t frequency);

void app_set_mode(app_modes_t app_modes_t);

void app_set_color(rgb_led_pixel_t *pixel1, rgb_led_pixel_t *pixel2, rgb_led_pixel_t *pixel3, uint8_t max_g_brightness);

void app_set_brightness(uint8_t max_g_brightness);

void app_task(void);

#endif /* APP_H_ */
