################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../28003x_generic_flash_lnk.cmd \
../f28003x_headers_nonBIOS.cmd 

SYSCFG_SRCS += \
../cancom_util.syscfg 

LIB_SRCS += \
E:/1.\ KZQ342_Project/Project_SDK/c2000ware/driverlib/f28003x/driverlib/ccs/Release/driverlib.lib 

ASM_SRCS += \
../f28003x_codestartbranch.asm 

C_SRCS += \
./syscfg/board.c \
./syscfg/c2000ware_libraries.c \
../cancom_util_main.c \
../device.c \
../f28003x_globalvariabledefs.c \
E:/1.\ KZQ342_Project/Project_SDK/c2000ware/driverlib/f28003x/driverlib/mcan.c \
E:/1.\ KZQ342_Project/Project_SDK/c2000ware/driverlib/f28003x/driverlib/spi.c 

GEN_FILES += \
./syscfg/board.c \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt \
./syscfg/c2000ware_libraries.c 

GEN_MISC_DIRS += \
./syscfg 

C_DEPS += \
./syscfg/board.d \
./syscfg/c2000ware_libraries.d \
./cancom_util_main.d \
./device.d \
./f28003x_globalvariabledefs.d \
./mcan.d \
./spi.d 

GEN_OPTS += \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt 

OBJS += \
./syscfg/board.obj \
./syscfg/c2000ware_libraries.obj \
./cancom_util_main.obj \
./device.obj \
./f28003x_codestartbranch.obj \
./f28003x_globalvariabledefs.obj \
./mcan.obj \
./spi.obj 

ASM_DEPS += \
./f28003x_codestartbranch.d 

GEN_MISC_FILES += \
./syscfg/board.h \
./syscfg/board.cmd.genlibs \
./syscfg/board.json \
./syscfg/pinmux.csv \
./syscfg/c2000ware_libraries.cmd.genlibs \
./syscfg/c2000ware_libraries.h \
./syscfg/clocktree.h 

GEN_MISC_DIRS__QUOTED += \
"syscfg" 

OBJS__QUOTED += \
"syscfg\board.obj" \
"syscfg\c2000ware_libraries.obj" \
"cancom_util_main.obj" \
"device.obj" \
"f28003x_codestartbranch.obj" \
"f28003x_globalvariabledefs.obj" \
"mcan.obj" \
"spi.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\board.h" \
"syscfg\board.cmd.genlibs" \
"syscfg\board.json" \
"syscfg\pinmux.csv" \
"syscfg\c2000ware_libraries.cmd.genlibs" \
"syscfg\c2000ware_libraries.h" \
"syscfg\clocktree.h" 

C_DEPS__QUOTED += \
"syscfg\board.d" \
"syscfg\c2000ware_libraries.d" \
"cancom_util_main.d" \
"device.d" \
"f28003x_globalvariabledefs.d" \
"mcan.d" \
"spi.d" 

GEN_FILES__QUOTED += \
"syscfg\board.c" \
"syscfg\board.opt" \
"syscfg\c2000ware_libraries.opt" \
"syscfg\c2000ware_libraries.c" 

ASM_DEPS__QUOTED += \
"f28003x_codestartbranch.d" 

SYSCFG_SRCS__QUOTED += \
"../cancom_util.syscfg" 

C_SRCS__QUOTED += \
"./syscfg/board.c" \
"./syscfg/c2000ware_libraries.c" \
"../cancom_util_main.c" \
"../device.c" \
"../f28003x_globalvariabledefs.c" \
"E:/1. KZQ342_Project/Project_SDK/c2000ware/driverlib/f28003x/driverlib/mcan.c" \
"E:/1. KZQ342_Project/Project_SDK/c2000ware/driverlib/f28003x/driverlib/spi.c" 

ASM_SRCS__QUOTED += \
"../f28003x_codestartbranch.asm" 


