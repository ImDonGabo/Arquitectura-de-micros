################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/boot_multicore_slave.c \
../startup/startup_lpc55s69_cm33_core0.c 

C_DEPS += \
./startup/boot_multicore_slave.d \
./startup/startup_lpc55s69_cm33_core0.d 

OBJS += \
./startup/boot_multicore_slave.o \
./startup/startup_lpc55s69_cm33_core0.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica2_GVC_KVTR\source" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica2_GVC_KVTR\drivers" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica2_GVC_KVTR\CMSIS" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica2_GVC_KVTR\CMSIS\m-profile" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica2_GVC_KVTR\device" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica2_GVC_KVTR\device\periph" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica2_GVC_KVTR\utilities" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica2_GVC_KVTR\utilities\str" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica2_GVC_KVTR\utilities\debug_console_lite" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica2_GVC_KVTR\component\uart" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica2_GVC_KVTR\board" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -fno-builtin -imacros "C:\Users\gabit\OneDrive\Documentos\mcu\Practica2_GVC_KVTR\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-startup

clean-startup:
	-$(RM) ./startup/boot_multicore_slave.d ./startup/boot_multicore_slave.o ./startup/startup_lpc55s69_cm33_core0.d ./startup/startup_lpc55s69_cm33_core0.o

.PHONY: clean-startup

