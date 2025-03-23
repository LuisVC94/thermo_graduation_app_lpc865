#ifndef PWM_CONTROLLER_H_
#define PWM_CONTROLLER_H_

#include <stdint.h>
#include <stdbool.h>
#include "pin_init.h"
#include "fsl_ftm.h"

#define PWM_FREQUENCY 1000

void pwm_controller_init(void);

void pwm_controller_set_dutty_cycle(FTM_Type **base, ftm_chnl_t *channels, uint8_t *dutty, uint8_t n_channels);

#endif /* PWM_CONTROLLER_H_ */
