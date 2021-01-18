################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../MSP_EXP432P401R_FREERTOS.cmd 

SYSCFG_SRCS += \
../empty.syscfg 

C_SRCS += \
../GPS.c \
../empty.c \
./syscfg/ti_drivers_config.c \
../main_freertos.c 

GEN_FILES += \
./syscfg/ti_drivers_config.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./GPS.d \
./empty.d \
./syscfg/ti_drivers_config.d \
./main_freertos.d 

OBJS += \
./GPS.obj \
./empty.obj \
./syscfg/ti_drivers_config.obj \
./main_freertos.obj 

GEN_MISC_FILES += \
./syscfg/ti_drivers_config.h \
./syscfg/syscfg_c.rov.xs 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"GPS.obj" \
"empty.obj" \
"syscfg\ti_drivers_config.obj" \
"main_freertos.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\ti_drivers_config.h" \
"syscfg\syscfg_c.rov.xs" 

C_DEPS__QUOTED += \
"GPS.d" \
"empty.d" \
"syscfg\ti_drivers_config.d" \
"main_freertos.d" 

GEN_FILES__QUOTED += \
"syscfg\ti_drivers_config.c" 

C_SRCS__QUOTED += \
"../GPS.c" \
"../empty.c" \
"./syscfg/ti_drivers_config.c" \
"../main_freertos.c" 

SYSCFG_SRCS__QUOTED += \
"../empty.syscfg" 


