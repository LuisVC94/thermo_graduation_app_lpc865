################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/app.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/app.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/app.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC865M201JBD64 -DCPU_LPC865M201JBD64_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\device" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\audio_reader" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\component\uart" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\drivers" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\utilities" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\device\periph3" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\CMSIS" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\CMSIS\m-profile" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\CMSIS\DSP\Include" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\CMSIS\DSP\PrivateInclude" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\board" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\Common" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\LED_RGB" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/app.d ./source/app.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

