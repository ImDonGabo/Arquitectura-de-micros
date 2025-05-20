################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/SwTimers.c \
../source/btn_debounce.c \
../source/gpio_driver.c \
../source/main.c \
../source/matriz.c \
../source/semihost_hardfault.c \
../source/utick_timer.c 

C_DEPS += \
./source/SwTimers.d \
./source/btn_debounce.d \
./source/gpio_driver.d \
./source/main.d \
./source/matriz.d \
./source/semihost_hardfault.d \
./source/utick_timer.d 

OBJS += \
./source/SwTimers.o \
./source/btn_debounce.o \
./source/gpio_driver.o \
./source/main.o \
./source/matriz.o \
./source/semihost_hardfault.o \
./source/utick_timer.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica6_GVC_KVTR\source" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica6_GVC_KVTR\utilities" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica6_GVC_KVTR\drivers" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica6_GVC_KVTR\device" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica6_GVC_KVTR\startup" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica6_GVC_KVTR\component\uart" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica6_GVC_KVTR\component\lists" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica6_GVC_KVTR\CMSIS" -I"C:\Users\gabit\OneDrive\Documentos\mcu\Practica6_GVC_KVTR\board" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/SwTimers.d ./source/SwTimers.o ./source/btn_debounce.d ./source/btn_debounce.o ./source/gpio_driver.d ./source/gpio_driver.o ./source/main.d ./source/main.o ./source/matriz.d ./source/matriz.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/utick_timer.d ./source/utick_timer.o

.PHONY: clean-source

