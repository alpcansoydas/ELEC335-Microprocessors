################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../asm.s 

OBJS += \
./asm.o 

S_DEPS += \
./asm.d 


# Each subdirectory must supply rules for building sources it contributes
asm.o: ../asm.s
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -c -x assembler-with-cpp -MMD -MP -MF"asm.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

