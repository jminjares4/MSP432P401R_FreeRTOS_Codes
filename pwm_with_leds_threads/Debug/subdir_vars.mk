################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../MSP_EXP432P401R_FREERTOS.cmd 

SYSCFG_SRCS += \
../pwm_with_leds_threads.syscfg 

C_SRCS += \
../main_freertos.c \
../pwm_with_leds_threads.c \
./syscfg/ti_drivers_config.c 

GEN_FILES += \
./syscfg/ti_drivers_config.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./main_freertos.d \
./pwm_with_leds_threads.d \
./syscfg/ti_drivers_config.d 

OBJS += \
./main_freertos.obj \
./pwm_with_leds_threads.obj \
./syscfg/ti_drivers_config.obj 

GEN_MISC_FILES += \
./syscfg/ti_drivers_config.h \
./syscfg/syscfg_c.rov.xs 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"main_freertos.obj" \
"pwm_with_leds_threads.obj" \
"syscfg\ti_drivers_config.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\ti_drivers_config.h" \
"syscfg\syscfg_c.rov.xs" 

C_DEPS__QUOTED += \
"main_freertos.d" \
"pwm_with_leds_threads.d" \
"syscfg\ti_drivers_config.d" 

GEN_FILES__QUOTED += \
"syscfg\ti_drivers_config.c" 

C_SRCS__QUOTED += \
"../main_freertos.c" \
"../pwm_with_leds_threads.c" \
"./syscfg/ti_drivers_config.c" 

SYSCFG_SRCS__QUOTED += \
"../pwm_with_leds_threads.syscfg" 


