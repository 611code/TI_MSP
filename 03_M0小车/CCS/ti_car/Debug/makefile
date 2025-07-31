################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := F:/TI/CCS/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS

GEN_OPTS__FLAG := @"./device.opt" 
GEN_CMDS__FLAG := -Wl,-l"./device_linker.cmd" 

ORDERED_OBJS += \
"./empty.o" \
"./ti_msp_dl_config.o" \
"./startup_mspm0g350x_ticlang.o" \
"./Bsp/ADC/adc_app.o" \
"./Bsp/BMI088/BMI088Middleware.o" \
"./Bsp/BMI088/BMI088driver.o" \
"./Bsp/BMI088/Klman_Yaw/ekf_yaw.o" \
"./Bsp/Button/multi_button.o" \
"./Bsp/Button/multi_button_user.o" \
"./Bsp/Encoder/encoder_user.o" \
"./Bsp/Encoder/hw_encoder.o" \
"./Bsp/Motor/Bsp_Motor.o" \
"./Bsp/Oled/app_oled.o" \
"./Bsp/Oled/hw_oled.o" \
"./Bsp/Pid/pid.o" \
"./Bsp/Pid/pid_user.o" \
"./Bsp/Task_manage/scheduler.o" \
"./Bsp/Task_manage/system.o" \
"./Bsp/Task_manage/task_manage.o" \
"./Bsp/UART/ringbuffer.o" \
"./Bsp/UART/uart_app.o" \
"./Bsp/gray/IIC.o" \
"./Bsp/gray/No_Mcu_gray.o" \
"./Bsp/gray/gray_app.o" \
"./Bsp/gray/hardware_iic.o" \
$(GEN_CMDS__FLAG) \
-Wl,-ldevice.cmd.genlibs \
-Wl,-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Bsp/ADC/subdir_vars.mk
-include Bsp/BMI088/subdir_vars.mk
-include Bsp/BMI088/Klman_Yaw/subdir_vars.mk
-include Bsp/Button/subdir_vars.mk
-include Bsp/Encoder/subdir_vars.mk
-include Bsp/Motor/subdir_vars.mk
-include Bsp/Oled/subdir_vars.mk
-include Bsp/Pid/subdir_vars.mk
-include Bsp/Task_manage/subdir_vars.mk
-include Bsp/UART/subdir_vars.mk
-include Bsp/gray/subdir_vars.mk
-include subdir_rules.mk
-include Bsp/ADC/subdir_rules.mk
-include Bsp/BMI088/subdir_rules.mk
-include Bsp/BMI088/Klman_Yaw/subdir_rules.mk
-include Bsp/Button/subdir_rules.mk
-include Bsp/Encoder/subdir_rules.mk
-include Bsp/Motor/subdir_rules.mk
-include Bsp/Oled/subdir_rules.mk
-include Bsp/Pid/subdir_rules.mk
-include Bsp/Task_manage/subdir_rules.mk
-include Bsp/UART/subdir_rules.mk
-include Bsp/gray/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
ti_car.out 

EXE_OUTPUTS__QUOTED += \
"ti_car.out" 


# All Target
all: $(OBJS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "ti_car.out"

# Tool invocations
ti_car.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"F:/TI/CCS/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/bin/tiarmclang.exe" @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -gdwarf-3 -Wl,-m"ti_car.map" -Wl,-i"F:/TI/CCS/mspm0_sdk_2_05_01_00/source" -Wl,-i"F:/04_daima/CCS/ti_car" -Wl,-i"F:/04_daima/CCS/ti_car/Debug/syscfg" -Wl,-i"F:/TI/CCS/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/lib" -Wl,--diag_wrap=off -Wl,--display_error_number -Wl,--warn_sections -Wl,--xml_link_info="ti_car_linkInfo.xml" -Wl,--rom_model -o "ti_car.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "empty.o" "ti_msp_dl_config.o" "startup_mspm0g350x_ticlang.o" "Bsp\ADC\adc_app.o" "Bsp\BMI088\BMI088Middleware.o" "Bsp\BMI088\BMI088driver.o" "Bsp\BMI088\Klman_Yaw\ekf_yaw.o" "Bsp\Button\multi_button.o" "Bsp\Button\multi_button_user.o" "Bsp\Encoder\encoder_user.o" "Bsp\Encoder\hw_encoder.o" "Bsp\Motor\Bsp_Motor.o" "Bsp\Oled\app_oled.o" "Bsp\Oled\hw_oled.o" "Bsp\Pid\pid.o" "Bsp\Pid\pid_user.o" "Bsp\Task_manage\scheduler.o" "Bsp\Task_manage\system.o" "Bsp\Task_manage\task_manage.o" "Bsp\UART\ringbuffer.o" "Bsp\UART\uart_app.o" "Bsp\gray\IIC.o" "Bsp\gray\No_Mcu_gray.o" "Bsp\gray\gray_app.o" "Bsp\gray\hardware_iic.o" 
	-$(RM) "empty.d" "ti_msp_dl_config.d" "startup_mspm0g350x_ticlang.d" "Bsp\ADC\adc_app.d" "Bsp\BMI088\BMI088Middleware.d" "Bsp\BMI088\BMI088driver.d" "Bsp\BMI088\Klman_Yaw\ekf_yaw.d" "Bsp\Button\multi_button.d" "Bsp\Button\multi_button_user.d" "Bsp\Encoder\encoder_user.d" "Bsp\Encoder\hw_encoder.d" "Bsp\Motor\Bsp_Motor.d" "Bsp\Oled\app_oled.d" "Bsp\Oled\hw_oled.d" "Bsp\Pid\pid.d" "Bsp\Pid\pid_user.d" "Bsp\Task_manage\scheduler.d" "Bsp\Task_manage\system.d" "Bsp\Task_manage\task_manage.d" "Bsp\UART\ringbuffer.d" "Bsp\UART\uart_app.d" "Bsp\gray\IIC.d" "Bsp\gray\No_Mcu_gray.d" "Bsp\gray\gray_app.d" "Bsp\gray\hardware_iic.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

