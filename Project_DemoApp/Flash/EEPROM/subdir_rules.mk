################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
EEPROM/%.obj: ../EEPROM/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O1 --opt_for_speed=3 --fp_mode=relaxed --include_path="E:/1. KZQ342_Project/Project_DemoApp" --include_path="E:/1. KZQ342_Project/Project_SDK" --include_path="E:/1. KZQ342_Project/Project_SDK/libraries/utilities/types/include" --include_path="E:/1. KZQ342_Project/Project_SDK/solutions/tidm_02012_ecompressor/common/include/" --include_path="E:/1. KZQ342_Project/Project_SDK/solutions/tidm_02012_ecompressor/f28003x/drivers/include" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/driverlib/f28003x/driverlib" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/device_support/f28003x/common/include/" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/device_support/f28003x/headers/include/" --include_path="C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=_INLINE --define=_FLASH --define=_F28003x --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="EEPROM/$(basename $(<F)).d_raw" --include_path="E:/1. KZQ342_Project/Project_DemoApp/Flash/syscfg" --obj_directory="EEPROM" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


