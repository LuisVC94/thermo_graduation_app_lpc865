################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Common/pin_init.c 

C_DEPS += \
./Common/pin_init.d 

OBJS += \
./Common/pin_init.o 


# Each subdirectory must supply rules for building sources it contributes
Common/%.o: ../Common/%.c Common/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC865M201JBD64 -DCPU_LPC865M201JBD64_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"C:\Workspaces_NXP\Grad\thermo_graduation_app_lpc865\device" -I"C:\Workspaces_NXP\Grad\thermo_graduation_app_lpc865\audio_reader" -I"C:\Workspaces_NXP\Grad\thermo_graduation_app_lpc865\component\uart" -I"C:\Workspaces_NXP\Grad\thermo_graduation_app_lpc865\drivers" -I"C:\Workspaces_NXP\Grad\thermo_graduation_app_lpc865\utilities" -I"C:\Workspaces_NXP\Grad\thermo_graduation_app_lpc865\device\periph3" -I"C:\Workspaces_NXP\Grad\thermo_graduation_app_lpc865\CMSIS" -I"C:\Workspaces_NXP\Grad\thermo_graduation_app_lpc865\CMSIS\m-profile" -I"C:\Workspaces_NXP\Grad\thermo_graduation_app_lpc865\CMSIS\DSP\Include" -I"C:\Workspaces_NXP\Grad\thermo_graduation_app_lpc865\CMSIS\DSP\PrivateInclude" -I"C:\Workspaces_NXP\Grad\thermo_graduation_app_lpc865\board" -I"C:\Workspaces_NXP\Grad\thermo_graduation_app_lpc865\Common" -I"C:\Workspaces_NXP\Grad\thermo_graduation_app_lpc865\LED_RGB" -I"C:\Workspaces_NXP\Grad\thermo_graduation_app_lpc865\source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Common

clean-Common:
	-$(RM) ./Common/pin_init.d ./Common/pin_init.o

.PHONY: clean-Common

