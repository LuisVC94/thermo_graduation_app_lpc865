#include "pin_init.h"
#include "fsl_clock.h"

void pin_init_all(void)
{
	pin_init_uart();
	pin_init_adc();
	pin_init_ftm();
}

void pin_init_uart(void)
{

}

void pin_init_adc(void)
{
	CLOCK_EnableClock(kCLOCK_Iocon);
	CLOCK_EnableClock(kCLOCK_Swm);
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_7, IOCON_HYS_EN);
    SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN0, true);
	CLOCK_DisableClock(kCLOCK_Swm);
}

void pin_init_ftm(void)
{
	CLOCK_EnableClock(kCLOCK_Iocon);
	CLOCK_EnableClock(kCLOCK_Swm);
	SWM_SetFlextimerPinSelect(SWM0, kSWM_FTM0_CH0, kSWM_FTM_Selection1);
	SWM_SetFlextimerPinSelect(SWM0, kSWM_FTM0_CH1, kSWM_FTM_Selection1);
	SWM_SetFlextimerPinSelect(SWM0, kSWM_FTM0_CH2, kSWM_FTM_Selection0);
	SWM_SetFlextimerPinSelect(SWM0, kSWM_FTM0_CH3, kSWM_FTM_Selection0);
	SWM_SetFlextimerPinSelect(SWM0, kSWM_FTM0_CH4, kSWM_FTM_Selection1);
	SWM_SetFlextimerPinSelect(SWM0, kSWM_FTM0_CH5, kSWM_FTM_Selection0);

	SWM_SetFlextimerPinSelect(SWM0, kSWM_FTM1_CH0, kSWM_FTM_Selection1);
	SWM_SetFlextimerPinSelect(SWM0, kSWM_FTM1_CH1, kSWM_FTM_Selection1);
	SWM_SetFlextimerPinSelect(SWM0, kSWM_FTM1_CH2, kSWM_FTM_Selection0);
	CLOCK_DisableClock(kCLOCK_Swm);
}


