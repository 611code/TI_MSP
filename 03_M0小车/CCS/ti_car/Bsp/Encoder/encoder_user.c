#include "encoder_user.h"
#include "hw_encoder.h"

extern Encoder left_encoder;
extern Encoder right_encoder;

float g_motor1_journey_cm=0;
float g_motor2_journey_cm=0;
float rev1,rev2;

int32_t last_sigma_motor1 = 0;
int32_t last_sigma_motor2 = 0;


/**
 * @brief 初始化编码器应用
 */
// void Encoder_Init(void)
// {
//   Encoder_Driver_Init(&left_encoder, &htim4, 1);
//   Encoder_Driver_Init(&right_encoder, &htim1, 0);
// }

/**
 * @brief 编码器应用运行任务 (应由调度器周期性调用)
 */
void Encoder_Task(void)
{
  Encoder_Driver_Update(&left_encoder);
  Encoder_Driver_Update(&right_encoder);
	rev1=(float)left_encoder.count/ENCODER_PPR;
	rev2=(float)right_encoder.count/ENCODER_PPR;
	  // 本周期增量脉冲
  int32_t delta1 = left_encoder.total_count - last_sigma_motor1;
  int32_t delta2 = right_encoder.total_count - last_sigma_motor2;
  last_sigma_motor1 = left_encoder.total_count;
  last_sigma_motor2 = right_encoder.total_count;
	rev1 = (float)delta1 / ENCODER_PPR*20.0f;
	rev2 = (float)delta2 / ENCODER_PPR*20.0f;
	float result1 = (float)left_encoder.total_count / ENCODER_PPR;
	g_motor1_journey_cm = result1 * (WHEEL_DIAMETER_CM * 3.1416);
	float result2 = (float)right_encoder.total_count / ENCODER_PPR;
	g_motor2_journey_cm = result2 * (WHEEL_DIAMETER_CM * 3.1416);
  
//  Uart_Printf(&huart1, "Left:%.2fcm/s  Right:%.2fcm/s\r\n", left_encoder.speed_cm_s, right_encoder.speed_cm_s);
}