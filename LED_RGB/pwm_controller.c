#include "pwm_controller.h"

static bool g_ftm0_update = false;
static bool g_ftm1_update = false;

void pwm_controller_init(void)
{
    ftm_config_t 				ftm_config;
    ftm_chnl_pwm_signal_param_t pwm_config;

    FTM_GetDefaultConfig(&ftm_config);
    ftm_config.prescale = FTM_CalculateCounterClkDiv(FTM0, PWM_FREQUENCY, CLOCK_GetFreq(kCLOCK_CoreSysClk));
    FTM_Init(FTM0, &ftm_config);
    FTM_Init(FTM1, &ftm_config);

    pwm_config.chnlNumber 				= kFTM_Chnl_0;
    pwm_config.dutyCyclePercent 		= 0;
    pwm_config.enableComplementary 		= false;
    pwm_config.enableDeadtime 			= false;
    pwm_config.firstEdgeDelayPercent 	= 0;
    pwm_config.level 					= kFTM_HighTrue;

    FTM_SetupPwm(FTM0, &pwm_config, 1U, kFTM_EdgeAlignedPwm, PWM_FREQUENCY,  CLOCK_GetFreq(kCLOCK_CoreSysClk));
    pwm_config.chnlNumber 				= kFTM_Chnl_1;
    FTM_SetupPwm(FTM0, &pwm_config, 1U, kFTM_EdgeAlignedPwm, PWM_FREQUENCY,  CLOCK_GetFreq(kCLOCK_CoreSysClk));
    pwm_config.chnlNumber 				= kFTM_Chnl_2;
    FTM_SetupPwm(FTM0, &pwm_config, 1U, kFTM_EdgeAlignedPwm, PWM_FREQUENCY,  CLOCK_GetFreq(kCLOCK_CoreSysClk));
    pwm_config.chnlNumber 				= kFTM_Chnl_3;
    FTM_SetupPwm(FTM0, &pwm_config, 1U, kFTM_EdgeAlignedPwm, PWM_FREQUENCY,  CLOCK_GetFreq(kCLOCK_CoreSysClk));
    pwm_config.chnlNumber 				= kFTM_Chnl_4;
    FTM_SetupPwm(FTM0, &pwm_config, 1U, kFTM_EdgeAlignedPwm, PWM_FREQUENCY,  CLOCK_GetFreq(kCLOCK_CoreSysClk));
    pwm_config.chnlNumber 				= kFTM_Chnl_5;
    FTM_SetupPwm(FTM0, &pwm_config, 1U, kFTM_EdgeAlignedPwm, PWM_FREQUENCY,  CLOCK_GetFreq(kCLOCK_CoreSysClk));

    pwm_config.chnlNumber 				= kFTM_Chnl_0;
    FTM_SetupPwm(FTM1, &pwm_config, 1U, kFTM_EdgeAlignedPwm, PWM_FREQUENCY,  CLOCK_GetFreq(kCLOCK_CoreSysClk));
    pwm_config.chnlNumber 				= kFTM_Chnl_1;
    FTM_SetupPwm(FTM1, &pwm_config, 1U, kFTM_EdgeAlignedPwm, PWM_FREQUENCY,  CLOCK_GetFreq(kCLOCK_CoreSysClk));
    pwm_config.chnlNumber 				= kFTM_Chnl_2;
    FTM_SetupPwm(FTM1, &pwm_config, 1U, kFTM_EdgeAlignedPwm, PWM_FREQUENCY,  CLOCK_GetFreq(kCLOCK_CoreSysClk));

    FTM_EnableInterrupts(FTM0, kFTM_TimeOverflowInterruptEnable);
    FTM_EnableInterrupts(FTM1, kFTM_TimeOverflowInterruptEnable);
    EnableIRQ(FTM0_IRQn);
    EnableIRQ(FTM1_IRQn);

    FTM_StartTimer(FTM0, kFTM_SystemClock);
    FTM_StartTimer(FTM1, kFTM_SystemClock);
}

void pwm_controller_set_dutty_cycle(FTM_Type **base, ftm_chnl_t *channels, uint8_t *dutty, uint8_t n_channels)
{
	uint8_t index;

	for(index = 0; index < n_channels; index ++)
	{
		FTM_UpdatePwmDutycycle(base[index], channels[index], kFTM_EdgeAlignedPwm, dutty[index]);
		if(base[index] == FTM0) g_ftm0_update = true;
		if(base[index] == FTM1) g_ftm1_update = true;
	}
}

void FTM0_IRQHandler(void)
{
	if(g_ftm0_update)
	{
	    FTM_SetSoftwareTrigger(FTM0, true);
	}
    FTM_ClearStatusFlags(FTM0, FTM_GetStatusFlags(FTM0));
}

void FTM1_IRQHandler(void)
{
	if(g_ftm1_update)
	{
	    FTM_SetSoftwareTrigger(FTM1, true);
	}
    FTM_ClearStatusFlags(FTM1, FTM_GetStatusFlags(FTM1));
}
