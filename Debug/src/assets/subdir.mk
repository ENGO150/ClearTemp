################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/assets/api.c \
../src/assets/flags.c \
../src/assets/tools.c 

OBJS += \
./src/assets/api.o \
./src/assets/flags.o \
./src/assets/tools.o 

C_DEPS += \
./src/assets/api.d \
./src/assets/flags.d \
./src/assets/tools.d 


# Each subdirectory must supply rules for building sources it contributes
src/assets/%.o: ../src/assets/%.c src/assets/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


