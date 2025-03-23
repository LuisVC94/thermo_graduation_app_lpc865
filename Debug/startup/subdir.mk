################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_lpc865.c 

C_DEPS += \
./startup/startup_lpc865.d 

OBJS += \
./startup/startup_lpc865.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC865M201JBD64 -DCPU_LPC865M201JBD64_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\board" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\Common" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\LED_RGB" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\source" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\device" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\component\uart" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\drivers" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\utilities" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-startup

clean-startup:
	-$(RM) ./startup/startup_lpc865.d ./startup/startup_lpc865.o

.PHONY: clean-startup

