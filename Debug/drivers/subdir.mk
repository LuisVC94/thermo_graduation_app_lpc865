################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_ftm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_mrt.c \
../drivers/fsl_power.c \
../drivers/fsl_reset.c \
../drivers/fsl_swm.c \
../drivers/fsl_usart.c 

C_DEPS += \
./drivers/fsl_adc.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_ftm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_mrt.d \
./drivers/fsl_power.d \
./drivers/fsl_reset.d \
./drivers/fsl_swm.d \
./drivers/fsl_usart.d 

OBJS += \
./drivers/fsl_adc.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_ftm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_mrt.o \
./drivers/fsl_power.o \
./drivers/fsl_reset.o \
./drivers/fsl_swm.o \
./drivers/fsl_usart.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC865M201JBD64 -DCPU_LPC865M201JBD64_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\device" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\audio_reader" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\component\uart" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\drivers" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\utilities" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\device\periph3" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\CMSIS" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\CMSIS\m-profile" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\CMSIS\DSP\Include" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\CMSIS\DSP\PrivateInclude" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\board" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\Common" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\LED_RGB" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_adc.d ./drivers/fsl_adc.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_ftm.d ./drivers/fsl_ftm.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_mrt.d ./drivers/fsl_mrt.o ./drivers/fsl_power.d ./drivers/fsl_power.o ./drivers/fsl_reset.d ./drivers/fsl_reset.o ./drivers/fsl_swm.d ./drivers/fsl_swm.o ./drivers/fsl_usart.d ./drivers/fsl_usart.o

.PHONY: clean-drivers

