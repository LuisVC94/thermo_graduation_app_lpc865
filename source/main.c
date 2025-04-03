#include <stdint.h>
#include "pin_init.h"
#include "app.h"

int main(void)
{
	rgb_led_pixel_t pixel1, pixel2, pixel3;
	pin_init_all();
	app_init();

	pixel1.r = 0;
	pixel1.g = 100;
	pixel1.b = 0;
	pixel1.brightness = 100;

	pixel2.r = 0;
	pixel2.g = 0;
	pixel2.b = 100;
	pixel2.brightness = 100;

	pixel3.r = 100;
	pixel3.g = 0;
	pixel3.b = 0;
	pixel3.brightness = 100;
	app_set_color(&pixel1, &pixel2, &pixel3, 100);
	app_set_mode(k_audio_fft_mode);
	app_set_frequency(20);
	while(1)
	{
		app_task();
	}
	return 0;
}
