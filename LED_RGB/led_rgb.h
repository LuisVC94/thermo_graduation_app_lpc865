#ifndef LED_RGB_H_
#define LED_RGB_H_

#include "pwm_controller.h"

#define LEDS_RGB_AVAILABLE 3

typedef enum _rgb_leds_t
{
	k_led_rgb_1,
	k_led_rgb_2,
	k_led_rgb_3,
} rgb_leds_t;

typedef struct _rgb_led_pixel_t
{
	uint8_t r, g, b;
	uint8_t brightness;
} rgb_led_pixel_t;

void init_leds_rgb(void);

void led_rgb_set_color(rgb_leds_t led, rgb_led_pixel_t *pixel);

#endif /* LED_RGB_H_ */
