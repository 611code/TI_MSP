#ifndef BSP_MOTOR_H
#define BSP_MOTOR_H

#include "bsp_system.h"

// #define Motor_tim htim2

//#define BIN1_Pin GPIO_PIN_0
//#define BIN1_GPIO_Port GPIOC
//#define BIN2_Pin GPIO_PIN_1
//#define BIN2_GPIO_Port GPIOC
//#define AIN1_Pin GPIO_PIN_2
//#define AIN1_GPIO_Port GPIOC
//#define AIN2_Pin GPIO_PIN_3
//#define AIN2_GPIO_Port GPIOC
/*电机方向引脚控制宏定义*/
#define AIN1_SET    DL_GPIO_setPins(GPIO_AIN_PORT,GPIO_AIN_PIN_AIN1_PIN)
#define AIN1_RESET  DL_GPIO_clearPins(GPIO_AIN_PORT,GPIO_AIN_PIN_AIN1_PIN)
#define AIN2_SET    DL_GPIO_setPins(GPIO_AIN_PORT,GPIO_AIN_PIN_AIN2_PIN)
#define AIN2_RESET  DL_GPIO_clearPins(GPIO_AIN_PORT,GPIO_AIN_PIN_AIN2_PIN)

#define BIN1_SET    DL_GPIO_setPins(GPIO_BIN_PORT,GPIO_BIN_PIN_BIN1_PIN)
#define BIN1_RESET  DL_GPIO_clearPins(GPIO_BIN_PORT,GPIO_BIN_PIN_BIN1_PIN)
#define BIN2_SET    DL_GPIO_setPins(GPIO_BIN_PORT,GPIO_BIN_PIN_BIN2_PIN)
#define BIN2_RESET  DL_GPIO_clearPins(GPIO_BIN_PORT,GPIO_BIN_PIN_BIN2_PIN)

/*电机PWM限幅宏定义,ARR为1000*/
#define  PWM_MAX   1000   /*正方向最大速度*/
#define  PWM_MIN  -1000   /*负方向最大速度*/

/*电机使能标志位*/
extern uint8_t g_is_motor1_en;
extern uint8_t g_is_motor2_en;

/*电机控制函数*/
void load_motor_pwm(int motor1_pwm,int motor2_pwm);
void limit_motor_pwm(int *p_motor1_pwm,int *p_motor2_pwm);
int find_abs(int p);
void set_motor1_enable(void);
void set_motor1_disable(void);
void set_motor2_enable(void);
void set_motor2_disable(void);

#endif
