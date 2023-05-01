################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LPC804_Project.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/LPC804_Project.d \
./source/semihost_hardfault.d 

OBJS += \
./source/LPC804_Project.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC804UK -DCPU_LPC804UK_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\djs\Documents\MCUXpressoIDE_11.7.1_9221\workspace\LPC804_Project\drivers" -I"C:\Users\djs\Documents\MCUXpressoIDE_11.7.1_9221\workspace\LPC804_Project\CMSIS" -I"C:\Users\djs\Documents\MCUXpressoIDE_11.7.1_9221\workspace\LPC804_Project\device" -I"C:\Users\djs\Documents\MCUXpressoIDE_11.7.1_9221\workspace\LPC804_Project\component\uart" -I"C:\Users\djs\Documents\MCUXpressoIDE_11.7.1_9221\workspace\LPC804_Project\utilities" -I"C:\Users\djs\Documents\MCUXpressoIDE_11.7.1_9221\workspace\LPC804_Project\board" -I"C:\Users\djs\Documents\MCUXpressoIDE_11.7.1_9221\workspace\LPC804_Project\source" -I"C:\Users\djs\Documents\MCUXpressoIDE_11.7.1_9221\workspace\LPC804_Project\drivers" -I"C:\Users\djs\Documents\MCUXpressoIDE_11.7.1_9221\workspace\LPC804_Project\CMSIS" -I"C:\Users\djs\Documents\MCUXpressoIDE_11.7.1_9221\workspace\LPC804_Project\device" -I"C:\Users\djs\Documents\MCUXpressoIDE_11.7.1_9221\workspace\LPC804_Project\component\uart" -I"C:\Users\djs\Documents\MCUXpressoIDE_11.7.1_9221\workspace\LPC804_Project\utilities" -I"C:\Users\djs\Documents\MCUXpressoIDE_11.7.1_9221\workspace\LPC804_Project\board" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/LPC804_Project.d ./source/LPC804_Project.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

