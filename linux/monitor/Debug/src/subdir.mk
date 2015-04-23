################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Conf.cpp \
../src/GSMUtils.cpp \
../src/I2CDevice.cpp \
../src/Logger.cpp \
../src/NotificationService.cpp \
../src/PDUMessage.cpp \
../src/SMSHandler.cpp \
../src/SMSNotificationHandler.cpp \
../src/Serial.cpp \
../src/boot.cpp 

OBJS += \
./src/Conf.o \
./src/GSMUtils.o \
./src/I2CDevice.o \
./src/Logger.o \
./src/NotificationService.o \
./src/PDUMessage.o \
./src/SMSHandler.o \
./src/SMSNotificationHandler.o \
./src/Serial.o \
./src/boot.o 

CPP_DEPS += \
./src/Conf.d \
./src/GSMUtils.d \
./src/I2CDevice.d \
./src/Logger.d \
./src/NotificationService.d \
./src/PDUMessage.d \
./src/SMSHandler.d \
./src/SMSNotificationHandler.d \
./src/Serial.d \
./src/boot.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"/home/abs/work/workspace-cpp/monitor/linux/monitor/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


