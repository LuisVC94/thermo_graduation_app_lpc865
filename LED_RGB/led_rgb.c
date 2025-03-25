#include "led_rgb.h"

const FTM_Type* c_leds_ftm_array[LEDS_RGB_AVAILABLE][3] =
{
		{FTM0, FTM0, FTM0},
		{FTM0, FTM0, FTM0},
		{FTM1, FTM1, FTM1}
};

// In RGB format ---------------------------------------------
const ftm_chnl_t c_leds_channel_array[LEDS_RGB_AVAILABLE][3] =
{
		{kFTM_Chnl_2, kFTM_Chnl_0, kFTM_Chnl_1},
		{kFTM_Chnl_5, kFTM_Chnl_3, kFTM_Chnl_4},
		{kFTM_Chnl_2, kFTM_Chnl_0, kFTM_Chnl_1}
};

void init_leds_rgb(void)
{
	pwm_controller_init();
}

void led_rgb_set_color(rgb_leds_t led, rgb_led_pixel_t *pixel)
{
	static uint8_t s_rgb[3];
	s_rgb[0] = ((uint32_t)pixel->r)*((uint32_t)pixel->brightness)/100;
	s_rgb[1] = ((uint32_t)pixel->g)*((uint32_t)pixel->brightness)/100;
	s_rgb[2] = ((uint32_t)pixel->b)*((uint32_t)pixel->brightness)/100;
	pwm_controller_set_dutty_cycle((FTM_Type**)c_leds_ftm_array[(uint32_t)led], (ftm_chnl_t*)c_leds_channel_array[(uint32_t)led], s_rgb, 3);
}
