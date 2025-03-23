#include <stdint.h>
#include "pin_init.h"
#include "pwm_controller.h"

int main(void)
{
	pin_init_all();
	pwm_controller_init();
	while(1)
	{

	}
	return 0;
}
