#include "app.h"
#include "audio_reader.h"

static uint8_t g_app_task_flag = 0;
static uint8_t g_audio_task_flag = 0;
static uint8_t g_brightness		= 0;

static app_modes_t g_app_mode = k_static_color_mode;

static rgb_led_pixel_t g_pixel1 = {0};
static rgb_led_pixel_t g_pixel2 = {0};
static rgb_led_pixel_t g_pixel3 = {0};

void app_init(void)
{
    mrt_config_t mrtConfig;
    uint32_t mrt_clock;

	init_leds_rgb();
	audio_reader_init();

	// MRT init -----------------------------------------------------------------
	mrt_clock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
    MRT_GetDefaultConfig(&mrtConfig);
    MRT_Init(MRT0, &mrtConfig);
    MRT_SetupChannelMode(MRT0, kMRT_Channel_0, kMRT_RepeatMode);
    MRT_SetupChannelMode(MRT0, kMRT_Channel_1, kMRT_RepeatMode);
    MRT_EnableInterrupts(MRT0, kMRT_Channel_0, kMRT_TimerInterruptEnable);
    MRT_EnableInterrupts(MRT0, kMRT_Channel_1, kMRT_TimerInterruptEnable);
    EnableIRQ(MRT0_IRQn);
    MRT_StartTimer(MRT0, kMRT_Channel_0, USEC_TO_COUNT(1000000/TASK_FREQUENCY, mrt_clock));
    MRT_StartTimer(MRT0, kMRT_Channel_1, USEC_TO_COUNT(1000000/AUDO_SAMPLE_FREQ, mrt_clock));
    // --------------------------------------------------------------------------
}

void app_set_frequency(uint32_t frequency)
{
    uint32_t mrt_clock;
	mrt_clock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
    MRT_StartTimer(MRT0, kMRT_Channel_0, USEC_TO_COUNT(1000000/frequency, mrt_clock));
}

void app_set_mode(app_modes_t app_modes_t)
{
	g_app_mode = app_modes_t;
}

void app_set_color(rgb_led_pixel_t *pixel1, rgb_led_pixel_t *pixel2, rgb_led_pixel_t *pixel3, uint8_t max_g_brightness)
{
	g_pixel1.r = pixel1->r;
	g_pixel1.g = pixel1->g;
	g_pixel1.b = pixel1->b;

	g_pixel2.r = pixel2->r;
	g_pixel2.g = pixel2->g;
	g_pixel2.b = pixel2->b;

	g_pixel3.r = pixel3->r;
	g_pixel3.g = pixel3->g;
	g_pixel3.b = pixel3->b;

	g_brightness = max_g_brightness;
}

void app_set_brightness(uint8_t max_g_brightness)
{
	g_brightness = max_g_brightness;
}

void app_configure_change_colors(uint32_t count)
{
	rgb_led_pixel_t color;
	if(count < 100)
	{
		color.r = 100;
		color.g = count;
		color.b = 0;
	}
	else if(count < 200)
	{
		color.r = 100 - (count-100);
		color.g = 100;
		color.b = 0;
	}
	else if(count < 300)
	{
		color.r = 0;
		color.g = 100;
		color.b = count - 200;
	}
	else if(count < 400)
	{
		color.r = 0;
		color.g = 100 - (count-300);
		color.b = 100;
	}
	else if(count < 500)
	{
		color.r = count - 400;
		color.g = 0;
		color.b = 100;
	}
	else
	{
		color.r = 100;
		color.g = 0;
		color.b = 100 - (count-500);
	}
	app_set_color(&color, &color, &color, g_brightness);
}

void app_configure_rainbow_colors(uint32_t count)
{
	if(count < 100)
	{
		g_pixel1.r = 100 - count;
		g_pixel1.g = count;
		g_pixel1.b = 0;

		g_pixel2.r = 0;
		g_pixel2.g = 100 - count;
		g_pixel2.b = count;

		g_pixel3.r = count;
		g_pixel3.g = 0;
		g_pixel3.b = 100 - count;
	}
	else if(count < 200)
	{
		g_pixel1.r = 0;
		g_pixel1.g = 200 - count;
		g_pixel1.b = count - 100;

		g_pixel2.r = count - 100;
		g_pixel2.g = 0;
		g_pixel2.b = 200 - count;

		g_pixel3.r = 200 - count;
		g_pixel3.g = count - 100;
		g_pixel3.b = 0;
	}
	else
	{
		g_pixel1.r = count - 200;
		g_pixel1.g = 0;
		g_pixel1.b = 300 - count;

		g_pixel2.r = 300 - count;
		g_pixel2.g = count - 200;
		g_pixel2.b = 0;

		g_pixel3.r = 0;
		g_pixel3.g = 300 - count;
		g_pixel3.b = count - 200;
	}
}

void app_task(void)
{
	static float32_t max_music_val = 0;
	static float32_t min_music_val = 0;
	static uint32_t s_state = 0;
	static uint8_t brightness = 0;
	float32_t prom_music_val = 0;
	float32_t music_val = 0;
	if(g_app_task_flag)
	{
		switch(g_app_mode)
		{
			case k_static_color_mode:
				g_pixel1.brightness = g_brightness;
				g_pixel2.brightness = g_brightness;
				g_pixel3.brightness = g_brightness;
				led_rgb_set_color(k_led_rgb_1, &g_pixel1);
				led_rgb_set_color(k_led_rgb_2, &g_pixel2);
				led_rgb_set_color(k_led_rgb_3, &g_pixel3);
			break;
			case k_breathe_color_mode:
				g_pixel1.brightness = brightness;
				g_pixel2.brightness = brightness;
				g_pixel3.brightness = brightness;
				led_rgb_set_color(k_led_rgb_1, &g_pixel1);
				led_rgb_set_color(k_led_rgb_2, &g_pixel2);
				led_rgb_set_color(k_led_rgb_3, &g_pixel3);

				brightness = (s_state == 0)? (brightness+1):(brightness-1);
				if(brightness >= g_brightness) s_state = 1;
				else if(brightness == 0) s_state = 0;

			break;
			case k_change_color_mode:
				if(s_state >= 600) s_state = 0;
				else s_state ++;

				app_configure_change_colors(s_state);
				g_pixel1.brightness = g_brightness;
				g_pixel2.brightness = g_brightness;
				g_pixel3.brightness = g_brightness;
				led_rgb_set_color(k_led_rgb_1, &g_pixel1);
				led_rgb_set_color(k_led_rgb_2, &g_pixel2);
				led_rgb_set_color(k_led_rgb_3, &g_pixel3);

			break;
			case k_rainbow_mode:
				if(s_state >= 300) s_state = 0;
				else s_state ++;

				app_configure_rainbow_colors(s_state);
				g_pixel1.brightness = g_brightness;
				g_pixel2.brightness = g_brightness;
				g_pixel3.brightness = g_brightness;
				led_rgb_set_color(k_led_rgb_1, &g_pixel1);
				led_rgb_set_color(k_led_rgb_2, &g_pixel2);
				led_rgb_set_color(k_led_rgb_3, &g_pixel3);
			break;
			case k_audio_blink_mode:
				music_val = get_music_val()*100.0;
				max_music_val = (max_music_val < music_val)? music_val:(max_music_val-1);
				min_music_val = (min_music_val > music_val)? music_val:(min_music_val+1);
				prom_music_val = (max_music_val + min_music_val)/2;
				g_pixel3.brightness = 100;
				g_pixel3.r = 0;
				g_pixel3.g = 0;
				g_pixel3.b = max_music_val-prom_music_val;
				led_rgb_set_color(k_led_rgb_1, &g_pixel3);
				led_rgb_set_color(k_led_rgb_2, &g_pixel3);
				led_rgb_set_color(k_led_rgb_3, &g_pixel3);

			break;
			default:

			break;
		}
		g_app_task_flag = 0;
	}
	if(g_audio_task_flag)
	{
		// TODO audio task
		g_audio_task_flag = 0;
	}
}

void MRT0_IRQHandler(void)
{
	if(MRT_GetStatusFlags(MRT0, kMRT_Channel_0) & kMRT_TimerInterruptFlag)
	{
		g_app_task_flag = 1;
	    MRT_ClearStatusFlags(MRT0, kMRT_Channel_0, kMRT_TimerInterruptFlag);
	}
	if(MRT_GetStatusFlags(MRT0, kMRT_Channel_1) & kMRT_TimerInterruptFlag)
	{
		g_audio_task_flag = 1;
	    MRT_ClearStatusFlags(MRT0, kMRT_Channel_1, kMRT_TimerInterruptFlag);
	}
}
