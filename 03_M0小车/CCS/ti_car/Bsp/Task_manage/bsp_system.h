#ifndef __BSP_SYSTEM_H_
#define __BSP_SYSTEM_H_

#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_i2c.h"

#include "stdarg.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"


/* ======== 驱动库头文件 =======*/
#include "hw_oled.h"
#include "multi_button.h"
#include "BMI088driver.h"
#include "BMI088reg.h"
#include "BMI088Middleware.h"
#include "hw_encoder.h"
#include "pid.h"
#include "Bsp_Motor.h"
#include "hardware_iic.h"

/* ======== 组件库头文件 =======*/
#include "system.h"
#include "ekf_yaw.h"


//app
//#include "scheduler.h"
#include "app_oled.h"
#include "multi_button_user.h"
#include "encoder_user.h"
#include "pid_user.h"
#include "gray_app.h"
#include "uart_app.h"

extern volatile int uwTick;

extern uint8_t menu_select;
extern uint8_t Car_mode;

extern uint8_t key_val;
extern uint8_t key_old;
extern uint8_t key_down;
extern uint8_t key_up;
extern uint8_t KeyNum;

extern float yaw_deg;
extern float gyro[3], accel[3], temp;

#endif
