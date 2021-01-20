################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../MSP_EXP432P401R_FREERTOS.cmd 

SYSCFG_SRCS += \
../bluetooth.syscfg 

C_SRCS += \
../bluetooth.c \
./syscfg/ti_drivers_config.c \
../main_freertos.c 

GEN_FILES += \
./syscfg/ti_drivers_config.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./bluetooth.d \
./syscfg/ti_drivers_config.d \
./main_freertos.d 

OBJS += \
./bluetooth.obj \
./syscfg/ti_drivers_config.obj \
./main_freertos.obj 

GEN_MISC_FILES += \
./syscfg/ti_drivers_config.h \
./syscfg/syscfg_c.rov.xs 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"bluetooth.obj" \
"syscfg\ti_drivers_config.obj" \
"main_freertos.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\ti_drivers_config.h" \
"syscfg\syscfg_c.rov.xs" 

C_DEPS__QUOTED += \
"bluetooth.d" \
"syscfg\ti_drivers_config.d" \
"main_freertos.d" 

GEN_FILES__QUOTED += \
"syscfg\ti_drivers_config.c" 

C_SRCS__QUOTED += \
"../bluetooth.c" \
"./syscfg/ti_drivers_config.c" \
"../main_freertos.c" 

SYSCFG_SRCS__QUOTED += \
"../bluetooth.syscfg" 


