#ifndef _HW_ENCODER_H_
#define _HW_ENCODER_H_

#include "ti_msp_dl_config.h"
// --- 用户需要根据实际情况修改这里的宏定义 ---
// 编码器每转一圈的脉冲数 (PPR)
#define ENCODER_PPR (13 * 28 * 1) // 13线/相, 30倍减速比, 1倍频
// 车轮直径 (单位: 厘米)
#define WHEEL_DIAMETER_CM 6.5f
// --- 修改结束 ---

// 自动计算周长和采样时间
#define PI 3.14159265f
#define WHEEL_CIRCUMFERENCE_CM (WHEEL_DIAMETER_CM * PI)
#define SAMPLING_TIME_S 0.050f // 采样时间, 与 Scheduler 中的任务周期一致 (10ms)

#define Exti_IRQHandler GROUP1_IRQHandler

/**
 * @brief 编码器数据结构体
 */
typedef struct
{
  volatile long long temp_count; // 保存实时计数值
  unsigned char reverse; // 编码器的方向是否反转。0-正常，1-反转
  int16_t count;          // 当前采样周期内的原始计数值
  int32_t total_count;    // 累计总计数值
  float speed_cm_s;     // 计算出的速度 (cm/s)
} Encoder;



#define SPEED_ENCODER_VALUE_MAX (-(SPEED_ENCODER_VALUE_MIN))
#define SPEED_ENCODER_VALUE_MID 0
#define SPEED_ENCODER_VALUE_MIN (-100)

#define DISTANCE_ENCODER_VALUE_MAX (-(DISTANCE_ENCODER_VALUE_MIN))
#define DISTANCE_ENCODER_VALUE_MID 0
#define DISTANCE_ENCODER_VALUE_MIN (-360)

void encoder_init(void);
int32_t TI_Exti_GetCouter(Encoder* encoder);
void Ti_Exti_SetCounter(Encoder* encoder,uint32_t count);
void Encoder_Driver_Update(Encoder* encoder);

// void encoder_init(void);
// int get_encoder_count(void);
// ENCODER_DIR get_encoder_dir(void);
// void encoder_update_repeat(void);
// void encoder_update_continue(void);
// long long get_temp_encoder(void);

#endif
