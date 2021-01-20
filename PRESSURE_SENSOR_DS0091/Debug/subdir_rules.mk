################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1000/ccs/tools/compiler/ti-cgt-arm_20.2.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/19152/Desktop/MSP432 FreeRTOS/PRESSURE_SENSOR_DS0091" --include_path="C:/Users/19152/Desktop/MSP432 FreeRTOS/PRESSURE_SENSOR_DS0091/Debug" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/posix/ccs" --include_path="C:/Users/19152/Desktop/FreeRTOSv10.3.1/FreeRTOSv10.3.1/FreeRTOS/Source/include" --include_path="C:/Users/19152/Desktop/FreeRTOSv10.3.1/FreeRTOSv10.3.1/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/Users/19152/Desktop/MSP432 FreeRTOS/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/ti/ccs1000/ccs/tools/compiler/ti-cgt-arm_20.2.0.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/19152/Desktop/MSP432 FreeRTOS/PRESSURE_SENSOR_DS0091/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1433210223: ../pressureSensor.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1000/ccs/utils/sysconfig_1.4.0/sysconfig_cli.bat" -s "C:/ti/simplelink_msp432p4_sdk_3_40_01_02/.metadata/product.json" -o "syscfg" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-1433210223 ../pressureSensor.syscfg
syscfg/ti_drivers_config.h: build-1433210223
syscfg/syscfg_c.rov.xs: build-1433210223
syscfg/: build-1433210223

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1000/ccs/tools/compiler/ti-cgt-arm_20.2.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/19152/Desktop/MSP432 FreeRTOS/PRESSURE_SENSOR_DS0091" --include_path="C:/Users/19152/Desktop/MSP432 FreeRTOS/PRESSURE_SENSOR_DS0091/Debug" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/posix/ccs" --include_path="C:/Users/19152/Desktop/FreeRTOSv10.3.1/FreeRTOSv10.3.1/FreeRTOS/Source/include" --include_path="C:/Users/19152/Desktop/FreeRTOSv10.3.1/FreeRTOSv10.3.1/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/Users/19152/Desktop/MSP432 FreeRTOS/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/ti/ccs1000/ccs/tools/compiler/ti-cgt-arm_20.2.0.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/19152/Desktop/MSP432 FreeRTOS/PRESSURE_SENSOR_DS0091/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


