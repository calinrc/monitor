################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GSMUtils.cpp \
../src/I2CDevice.cpp \
../src/Logger.cpp \
../src/PDUMessage.cpp \
../src/SMSHandler.cpp \
../src/Serial.cpp \
../src/main.cpp 

OBJS += \
./src/GSMUtils.o \
./src/I2CDevice.o \
./src/Logger.o \
./src/PDUMessage.o \
./src/SMSHandler.o \
./src/Serial.o \
./src/main.o 

CPP_DEPS += \
./src/GSMUtils.d \
./src/I2CDevice.d \
./src/Logger.d \
./src/PDUMessage.d \
./src/SMSHandler.d \
./src/Serial.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"/home/abs/work/workspace-cpp/monitor/linux/monitor/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


