################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1551109839: ../cancom_util.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.23.1/sysconfig_cli.bat" --script "E:/1. KZQ342_Project/Project_DemoApp/cancom_util.syscfg" -o "syscfg" -s "E:/1. KZQ342_Project/Project_SDK/c2000ware/.metadata/sdk.json" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1551109839 ../cancom_util.syscfg
syscfg/board.h: build-1551109839
syscfg/board.cmd.genlibs: build-1551109839
syscfg/board.opt: build-1551109839
syscfg/board.json: build-1551109839
syscfg/pinmux.csv: build-1551109839
syscfg/c2000ware_libraries.cmd.genlibs: build-1551109839
syscfg/c2000ware_libraries.opt: build-1551109839
syscfg/c2000ware_libraries.c: build-1551109839
syscfg/c2000ware_libraries.h: build-1551109839
syscfg/clocktree.h: build-1551109839
syscfg: build-1551109839

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O1 --opt_for_speed=3 --fp_mode=relaxed --include_path="E:/1. KZQ342_Project/Project_DemoApp" --include_path="E:/1. KZQ342_Project/Project_SDK" --include_path="E:/1. KZQ342_Project/Project_SDK/libraries/utilities/types/include" --include_path="E:/1. KZQ342_Project/Project_SDK/solutions/tidm_02012_ecompressor/common/include/" --include_path="E:/1. KZQ342_Project/Project_SDK/solutions/tidm_02012_ecompressor/f28003x/drivers/include" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/driverlib/f28003x/driverlib" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/device_support/f28003x/common/include/" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/device_support/f28003x/headers/include/" --include_path="C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=_INLINE --define=_FLASH --define=_F28003x --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="E:/1. KZQ342_Project/Project_DemoApp/Flash/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O1 --opt_for_speed=3 --fp_mode=relaxed --include_path="E:/1. KZQ342_Project/Project_DemoApp" --include_path="E:/1. KZQ342_Project/Project_SDK" --include_path="E:/1. KZQ342_Project/Project_SDK/libraries/utilities/types/include" --include_path="E:/1. KZQ342_Project/Project_SDK/solutions/tidm_02012_ecompressor/common/include/" --include_path="E:/1. KZQ342_Project/Project_SDK/solutions/tidm_02012_ecompressor/f28003x/drivers/include" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/driverlib/f28003x/driverlib" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/device_support/f28003x/common/include/" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/device_support/f28003x/headers/include/" --include_path="C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=_INLINE --define=_FLASH --define=_F28003x --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="E:/1. KZQ342_Project/Project_DemoApp/Flash/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O1 --opt_for_speed=3 --fp_mode=relaxed --include_path="E:/1. KZQ342_Project/Project_DemoApp" --include_path="E:/1. KZQ342_Project/Project_SDK" --include_path="E:/1. KZQ342_Project/Project_SDK/libraries/utilities/types/include" --include_path="E:/1. KZQ342_Project/Project_SDK/solutions/tidm_02012_ecompressor/common/include/" --include_path="E:/1. KZQ342_Project/Project_SDK/solutions/tidm_02012_ecompressor/f28003x/drivers/include" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/driverlib/f28003x/driverlib" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/device_support/f28003x/common/include/" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/device_support/f28003x/headers/include/" --include_path="C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=_INLINE --define=_FLASH --define=_F28003x --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="E:/1. KZQ342_Project/Project_DemoApp/Flash/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

mcan.obj: E:/1.\ KZQ342_Project/Project_SDK/c2000ware/driverlib/f28003x/driverlib/mcan.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O1 --opt_for_speed=3 --fp_mode=relaxed --include_path="E:/1. KZQ342_Project/Project_DemoApp" --include_path="E:/1. KZQ342_Project/Project_SDK" --include_path="E:/1. KZQ342_Project/Project_SDK/libraries/utilities/types/include" --include_path="E:/1. KZQ342_Project/Project_SDK/solutions/tidm_02012_ecompressor/common/include/" --include_path="E:/1. KZQ342_Project/Project_SDK/solutions/tidm_02012_ecompressor/f28003x/drivers/include" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/driverlib/f28003x/driverlib" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/device_support/f28003x/common/include/" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/device_support/f28003x/headers/include/" --include_path="C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=_INLINE --define=_FLASH --define=_F28003x --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="mcan.d_raw" --include_path="E:/1. KZQ342_Project/Project_DemoApp/Flash/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

spi.obj: E:/1.\ KZQ342_Project/Project_SDK/c2000ware/driverlib/f28003x/driverlib/spi.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O1 --opt_for_speed=3 --fp_mode=relaxed --include_path="E:/1. KZQ342_Project/Project_DemoApp" --include_path="E:/1. KZQ342_Project/Project_SDK" --include_path="E:/1. KZQ342_Project/Project_SDK/libraries/utilities/types/include" --include_path="E:/1. KZQ342_Project/Project_SDK/solutions/tidm_02012_ecompressor/common/include/" --include_path="E:/1. KZQ342_Project/Project_SDK/solutions/tidm_02012_ecompressor/f28003x/drivers/include" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/driverlib/f28003x/driverlib" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/device_support/f28003x/common/include/" --include_path="E:/1. KZQ342_Project/Project_SDK/c2000ware/device_support/f28003x/headers/include/" --include_path="C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=_INLINE --define=_FLASH --define=_F28003x --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="spi.d_raw" --include_path="E:/1. KZQ342_Project/Project_DemoApp/Flash/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


