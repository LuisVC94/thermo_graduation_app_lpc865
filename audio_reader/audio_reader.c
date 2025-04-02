#include "audio_reader.h"
#include "fsl_adc.h"
#include "fsl_power.h"
#include "fsl_device_registers.h"

const float32_t c_ultra_low_pass_filtter[] = {1.000000000000000, 0.993736471541615, -0.996868235770807, 0.996868235770807}; // Low pass filtter 20Hz

static adc_result_info_t gAdcResultInfoStruct;
static float32_t g_audio_filttered = 0;
static float32_t g_audio_peak = 0;
static float32_t g_audio_peak_short = 0;

void audio_reader_init(void)
{
	uint8_t adc_calib_status;
	uint32_t frequency = 0U;
    adc_config_t adcConfigStruct;
    adc_conv_seq_config_t adcConvSeqConfigStruct;
    // ADC init -----------------------------------------------------------------------
    /* Attach FRO clock to ADC0. */
    CLOCK_Select(kADC_Clk_From_Fro);
    CLOCK_SetClkDivider(kCLOCK_DivAdcClk, 1U);
    /* Power on ADC0. */
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);

    adcConfigStruct.clockMode = kADC_ClockSynchronousMode;
    adcConfigStruct.clockDividerNumber = 1;
    adcConfigStruct.enableLowPowerMode = false;
    adcConfigStruct.voltageRange = kADC_HighVoltageRange;
    ADC_Init(ADC0, &adcConfigStruct);

    frequency = CLOCK_GetFreq(kCLOCK_Fro) / CLOCK_GetClkDivider(kCLOCK_DivAdcClk);
    adc_calib_status = ADC_DoSelfCalibration(ADC0, frequency);
    // ---------------------------------------------------------------------------------
    // ADC channel init ----------------------------------------------------------------
    adcConvSeqConfigStruct.seqSampleTimeNumber = 0U;
	adcConvSeqConfigStruct.channelMask = 1;
	adcConvSeqConfigStruct.triggerMask      = 0U;
	adcConvSeqConfigStruct.triggerPolarity  = kADC_TriggerPolarityPositiveEdge;
	adcConvSeqConfigStruct.enableSingleStep = false;
	adcConvSeqConfigStruct.enableSyncBypass = false;
	adcConvSeqConfigStruct.interruptMode    = kADC_InterruptForEachSequence;
	ADC_SetConvSeqAConfig(ADC0, &adcConvSeqConfigStruct);
	ADC_EnableConvSeqA(ADC0, true);
	ADC_DoSoftwareTriggerConvSeqA(ADC0);
    while (!ADC_GetChannelConversionResult(ADC0, 0, &gAdcResultInfoStruct));
    ADC_GetConvSeqAGlobalConversionResult(ADC0, &gAdcResultInfoStruct);
    // ---------------------------------------------------------------------------------
    ADC_EnableInterrupts(ADC0, kADC_ConvSeqAInterruptEnable);
    NVIC_EnableIRQ(ADC0_SEQA_IRQn);
}

float32_t get_music_val(void)
{
	float32_t val;
	val = ((((float32_t)gAdcResultInfoStruct.result)/4095.0)-0.5)*2.0;
	return val;
}


float32_t get_audio_filttered()
{
	return g_audio_filttered;
}

float32_t get_audio_peak()
{
	return g_audio_peak;
}

float32_t get_audio_peak_short()
{
	return g_audio_peak;
}

void audio_reader_task(void)
{
	static float32_t s_prev_input = 0;
	float32_t input = get_music_val();
	ADC_DoSoftwareTriggerConvSeqA(ADC0);

	g_audio_filttered = c_ultra_low_pass_filtter[1]*g_audio_filttered + c_ultra_low_pass_filtter[2]*input + c_ultra_low_pass_filtter[3]*s_prev_input;

	g_audio_peak = (g_audio_peak < input)? input:((g_audio_peak > 0.0)? (g_audio_peak-DECREASE_VALUE_PEAK_DETECTOR):0);
	g_audio_peak_short = (g_audio_peak_short < input)? input:((g_audio_peak_short > 0.0)? (g_audio_peak_short-DECREASE_VALUE_PEAK_DETECTOR_SHORT):0);
}

void ADC0_SEQA_IRQHandler(void)
{
    if (kADC_ConvSeqAInterruptFlag & ADC_GetStatusFlags(ADC0))
    {
        ADC_GetChannelConversionResult(ADC0, 0, &gAdcResultInfoStruct);
        ADC_ClearStatusFlags(ADC0, kADC_ConvSeqAInterruptFlag);
    }
}
