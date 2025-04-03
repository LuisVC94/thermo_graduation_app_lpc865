#include <stdint.h>
#include "pin_init.h"
#include "app.h"
#include "fsl_gpio.h"

int main(void)
{
	static uint8_t s_pressed = 0;
	static app_modes_t s_app_mode = 0;
	uint32_t gpio_stat;
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
	app_set_frequency(20);
	while(1)
	{
		gpio_stat = GPIO_PinRead(GPIO, 0, 4);
		if((!s_pressed) && (!gpio_stat))
		{
			s_pressed = 1;
			s_app_mode = (s_app_mode < 5)? (s_app_mode+1):0;
			app_set_mode(s_app_mode);
		}
		else if(gpio_stat)
		{
			s_pressed = 0;
		}
		app_task();
	}
	return 0;
}
