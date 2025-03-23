################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LED_RGB/led_rgb.c \
../LED_RGB/pwm_controller.c 

C_DEPS += \
./LED_RGB/led_rgb.d \
./LED_RGB/pwm_controller.d 

OBJS += \
./LED_RGB/led_rgb.o \
./LED_RGB/pwm_controller.o 


# Each subdirectory must supply rules for building sources it contributes
LED_RGB/%.o: ../LED_RGB/%.c LED_RGB/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC865M201JBD64 -DCPU_LPC865M201JBD64_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\board" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\Common" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\LED_RGB" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\source" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\device" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\component\uart" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\drivers" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\utilities" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-LED_RGB

clean-LED_RGB:
	-$(RM) ./LED_RGB/led_rgb.d ./LED_RGB/led_rgb.o ./LED_RGB/pwm_controller.d ./LED_RGB/pwm_controller.o

.PHONY: clean-LED_RGB

