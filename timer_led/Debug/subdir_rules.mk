################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Jesus Minjares/Desktop/MSP432 FreeRTOS/timer_led" --include_path="C:/Users/Jesus Minjares/Desktop/MSP432 FreeRTOS/timer_led/Debug" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/posix/ccs" --include_path="C:/Users/Jesus Minjares/Desktop/FreeRTOS Operating System/FreeRTOSv202012.00/FreeRTOS/Source/include" --include_path="C:/Users/Jesus Minjares/Desktop/FreeRTOS Operating System/FreeRTOSv202012.00/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/Users/Jesus Minjares/Desktop/MSP432 FreeRTOS/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/Jesus Minjares/Desktop/MSP432 FreeRTOS/timer_led/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1476970977:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1476970977-inproc

build-1476970977-inproc: ../timer.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs930/ccs/utils/sysconfig/sysconfig_cli.bat" -s "C:/ti/simplelink_msp432p4_sdk_3_40_01_02/.metadata/product.json" -o "syscfg" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-1476970977 ../timer.syscfg
syscfg/ti_drivers_config.h: build-1476970977
syscfg/syscfg_c.rov.xs: build-1476970977
syscfg/: build-1476970977

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Jesus Minjares/Desktop/MSP432 FreeRTOS/timer_led" --include_path="C:/Users/Jesus Minjares/Desktop/MSP432 FreeRTOS/timer_led/Debug" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/posix/ccs" --include_path="C:/Users/Jesus Minjares/Desktop/FreeRTOS Operating System/FreeRTOSv202012.00/FreeRTOS/Source/include" --include_path="C:/Users/Jesus Minjares/Desktop/FreeRTOS Operating System/FreeRTOSv202012.00/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/Users/Jesus Minjares/Desktop/MSP432 FreeRTOS/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/Jesus Minjares/Desktop/MSP432 FreeRTOS/timer_led/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


