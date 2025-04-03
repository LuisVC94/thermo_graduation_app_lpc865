#include "audio_reader.h"
#include "fsl_adc.h"
#include "fsl_power.h"
#include "fsl_device_registers.h"

const float32_t c_ultra_high_pass_filtter[] = {1.000000000000000, 0.993736471541615, -0.996868235770807, 0.996868235770807}; // High pass filtter 20Hz

const float32_t c_low_pass_filtter[] = {1.000000000000000, 0.881618592363189, -0.059190703818405, -0.059190703818405}; // Low pass filtter 200Hz
const float32_t c_mid_high_pass_filtter[] = {1.000000000000000, 0.854080685463467, -0.927040342731733, 0.927040342731733}; // Mid High pass filtter 500Hz
const float32_t c_mid_low_pass_filtter[] = {1.000000000000000, 0.509525449494429, -0.245237275252786, -0.245237275252786}; // Mid Low pass filtter 2000Hz
const float32_t c_high_pass_filtter[] = {1.000000000000000, 0.158384440324536, -0.579192220162268, 0.579192220162268}; // High pass filtter 4000Hz

static adc_result_info_t gAdcResultInfoStruct;
static float32_t g_audio_filttered = 0;
static float32_t g_audio_peak = 0;
static float32_t g_audio_peak_short = 0;


static float32_t g_audio_low = 0;
static float32_t g_audio_mid = 0;
static float32_t g_audio_high = 0;

static float32_t g_audio_peak_low  = 0;
static float32_t g_audio_peak_mid  = 0;
static float32_t g_audio_peak_high = 0;

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

float32_t get_audio_low()
{
	return g_audio_low;
}

float32_t get_audio_mid()
{
	return g_audio_mid;
}

float32_t get_audio_high()
{
	return g_audio_high;
}

float32_t get_audio_peak()
{
	return g_audio_peak;
}

float32_t get_audio_peak_low()
{
	return g_audio_peak_low;
}

float32_t get_audio_peak_mid()
{
	return g_audio_peak_mid;
}

float32_t get_audio_peak_high()
{
	return g_audio_peak_high;
}

float32_t get_audio_peak_short()
{
	return g_audio_peak_short;
}

void audio_reader_task(void)
{
	static float32_t s_prev_input = 0;
	static float32_t s_prev_input_filt = 0;
	static float32_t s_prev_mid_low = 0;
	static float32_t s_prev_mid_high = 0;
	static float32_t s_prev_mid_high_inp = 0;
	float32_t input = get_music_val();
	ADC_DoSoftwareTriggerConvSeqA(ADC0);

	g_audio_filttered = c_ultra_high_pass_filtter[1]*s_prev_input_filt + c_ultra_high_pass_filtter[2]*input + c_ultra_high_pass_filtter[3]*s_prev_input;

	// EQ ----------------------------------------------------------------------------------------------------------------------------------------------------
	g_audio_low = c_low_pass_filtter[1]*g_audio_low + c_low_pass_filtter[2]*g_audio_filttered + c_low_pass_filtter[3]*s_prev_input_filt;

	g_audio_mid = c_mid_low_pass_filtter[1]*s_prev_mid_low + c_mid_low_pass_filtter[2]*g_audio_filttered + c_mid_low_pass_filtter[3]*s_prev_input_filt;
	s_prev_mid_low = g_audio_mid;

	g_audio_mid = c_mid_high_pass_filtter[1]*s_prev_mid_high + c_mid_high_pass_filtter[2]*g_audio_mid + c_mid_high_pass_filtter[3]*s_prev_mid_high_inp;
	s_prev_mid_high = g_audio_mid;
	s_prev_mid_high_inp = s_prev_mid_low;

	g_audio_high = c_high_pass_filtter[1]*g_audio_high + c_high_pass_filtter[2]*g_audio_filttered + c_high_pass_filtter[3]*s_prev_input_filt;
	s_prev_input_filt = g_audio_filttered;
	s_prev_input = input;
	// -------------------------------------------------------------------------------------------------------------------------------------------------------

	g_audio_peak = (g_audio_peak < g_audio_filttered)? g_audio_filttered:((g_audio_peak > DECREASE_VALUE_PEAK_DETECTOR)? (g_audio_peak-DECREASE_VALUE_PEAK_DETECTOR):0);
	g_audio_peak_short = (g_audio_peak_short < g_audio_filttered)? g_audio_filttered:((g_audio_peak_short > DECREASE_VALUE_PEAK_DETECTOR_SHORT)? (g_audio_peak_short-DECREASE_VALUE_PEAK_DETECTOR_SHORT):0);

	g_audio_peak_low = (g_audio_peak_low < g_audio_low)? g_audio_low:((g_audio_peak_low > DECREASE_VALUE_PEAK_DETECTOR_SHORT)? (g_audio_peak_low-DECREASE_VALUE_PEAK_DETECTOR_SHORT):0);
	g_audio_peak_mid = (g_audio_peak_mid < g_audio_mid)? g_audio_mid:((g_audio_peak_mid > DECREASE_VALUE_PEAK_DETECTOR_SHORT)? (g_audio_peak_mid-DECREASE_VALUE_PEAK_DETECTOR_SHORT):0);
	g_audio_peak_high = (g_audio_peak_high < g_audio_high)? g_audio_high:((g_audio_peak_high > DECREASE_VALUE_PEAK_DETECTOR_SHORT)? (g_audio_peak_high-DECREASE_VALUE_PEAK_DETECTOR_SHORT):0);
}

void ADC0_SEQA_IRQHandler(void)
{
    if (kADC_ConvSeqAInterruptFlag & ADC_GetStatusFlags(ADC0))
    {
        ADC_GetChannelConversionResult(ADC0, 0, &gAdcResultInfoStruct);
        ADC_ClearStatusFlags(ADC0, kADC_ConvSeqAInterruptFlag);
    }
}
