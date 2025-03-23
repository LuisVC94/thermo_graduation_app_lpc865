################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/peripherals.c \
../board/pin_mux.c 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/peripherals.d \
./board/pin_mux.d 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/peripherals.o \
./board/pin_mux.o 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c board/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC865M201JBD64 -DCPU_LPC865M201JBD64_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\board" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\Common" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\LED_RGB" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\source" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\device" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\component\uart" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\drivers" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\utilities" -I"C:\Workspaces_NXP\Graduacion\thermo_graduation_app_lpc865\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-board

clean-board:
	-$(RM) ./board/board.d ./board/board.o ./board/clock_config.d ./board/clock_config.o ./board/peripherals.d ./board/peripherals.o ./board/pin_mux.d ./board/pin_mux.o

.PHONY: clean-board

