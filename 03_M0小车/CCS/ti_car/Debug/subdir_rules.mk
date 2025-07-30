################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"F:/TI/CCS/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"F:/04_daima/CCS/ti_car" -I"F:/04_daima/CCS/ti_car/BSP" -I"F:/04_daima/CCS/ti_car/BSP/BMI088" -I"F:/04_daima/CCS/ti_car/BSP/BMI088/inc" -I"F:/04_daima/CCS/ti_car/BSP/BMI088/Klman_Yaw" -I"F:/04_daima/CCS/ti_car/BSP/Button" -I"F:/04_daima/CCS/ti_car/BSP/gray" -I"F:/04_daima/CCS/ti_car/BSP/Motor" -I"F:/04_daima/CCS/ti_car/BSP/Oled" -I"F:/04_daima/CCS/ti_car/BSP/Pid" -I"F:/04_daima/CCS/ti_car/BSP/Task_manage" -I"F:/04_daima/CCS/ti_car/BSP/UART" -I"F:/04_daima/CCS/ti_car/BSP/Control" -I"F:/04_daima/CCS/ti_car/BSP/Encoder" -I"F:/04_daima/CCS/ti_car/Debug" -I"F:/TI/CCS/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"F:/TI/CCS/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1120577231: ../empty.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"F:/TI/CCS/ccs/utils/sysconfig_1.21.1/sysconfig_cli.bat" --script "F:/04_daima/CCS/ti_car/empty.syscfg" -o "." -s "F:/TI/CCS/mspm0_sdk_2_05_01_00/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1120577231 ../empty.syscfg
device.opt: build-1120577231
device.cmd.genlibs: build-1120577231
ti_msp_dl_config.c: build-1120577231
ti_msp_dl_config.h: build-1120577231
Event.dot: build-1120577231

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"F:/TI/CCS/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"F:/04_daima/CCS/ti_car" -I"F:/04_daima/CCS/ti_car/BSP" -I"F:/04_daima/CCS/ti_car/BSP/BMI088" -I"F:/04_daima/CCS/ti_car/BSP/BMI088/inc" -I"F:/04_daima/CCS/ti_car/BSP/BMI088/Klman_Yaw" -I"F:/04_daima/CCS/ti_car/BSP/Button" -I"F:/04_daima/CCS/ti_car/BSP/gray" -I"F:/04_daima/CCS/ti_car/BSP/Motor" -I"F:/04_daima/CCS/ti_car/BSP/Oled" -I"F:/04_daima/CCS/ti_car/BSP/Pid" -I"F:/04_daima/CCS/ti_car/BSP/Task_manage" -I"F:/04_daima/CCS/ti_car/BSP/UART" -I"F:/04_daima/CCS/ti_car/BSP/Control" -I"F:/04_daima/CCS/ti_car/BSP/Encoder" -I"F:/04_daima/CCS/ti_car/Debug" -I"F:/TI/CCS/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"F:/TI/CCS/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: F:/TI/CCS/mspm0_sdk_2_05_01_00/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"F:/TI/CCS/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"F:/04_daima/CCS/ti_car" -I"F:/04_daima/CCS/ti_car/BSP" -I"F:/04_daima/CCS/ti_car/BSP/BMI088" -I"F:/04_daima/CCS/ti_car/BSP/BMI088/inc" -I"F:/04_daima/CCS/ti_car/BSP/BMI088/Klman_Yaw" -I"F:/04_daima/CCS/ti_car/BSP/Button" -I"F:/04_daima/CCS/ti_car/BSP/gray" -I"F:/04_daima/CCS/ti_car/BSP/Motor" -I"F:/04_daima/CCS/ti_car/BSP/Oled" -I"F:/04_daima/CCS/ti_car/BSP/Pid" -I"F:/04_daima/CCS/ti_car/BSP/Task_manage" -I"F:/04_daima/CCS/ti_car/BSP/UART" -I"F:/04_daima/CCS/ti_car/BSP/Control" -I"F:/04_daima/CCS/ti_car/BSP/Encoder" -I"F:/04_daima/CCS/ti_car/Debug" -I"F:/TI/CCS/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"F:/TI/CCS/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


