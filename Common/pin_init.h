#ifndef PIN_INIT_H_
#define PIN_INIT_H_

#include "fsl_swm.h"
#include "fsl_iocon.h"

// ADC PINS -----------------------------------
#define ADC_CH0_PORT 	0
#define ADC_CH0_PIN 	7

#define ADC_CH1_PORT 	0
#define ADC_CH1_PIN 	6
// --------------------------------------------

// FTM PINS -----------------------------------
#define FTM0_CH0_PORT 	1
#define FTM0_CH0_PIN 	1

#define FTM0_CH1_PORT 	1
#define FTM0_CH1_PIN 	2

#define FTM0_CH2_PORT 	0
#define FTM0_CH2_PIN 	19

#define FTM0_CH3_PORT 	0
#define FTM0_CH3_PIN 	20

#define FTM0_CH4_PORT 	1
#define FTM0_CH4_PIN 	5

#define FTM0_CH5_PORT 	0
#define FTM0_CH5_PIN 	22

#define FTM1_CH0_PORT 	1
#define FTM1_CH0_PIN 	8

#define FTM1_CH1_PORT 	1
#define FTM1_CH1_PIN 	9

#define FTM1_CH2_PORT 	0
#define FTM1_CH2_PIN 	26
// --------------------------------------------

void pin_init_all(void);

void pin_init_uart(void);

void pin_init_adc(void);

void pin_init_ftm(void);

#endif /* PIN_INIT_H_ */
