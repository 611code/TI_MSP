#include "hw_encoder.h"


static volatile uint32_t gpio_interrup;

Encoder left_encoder;
Encoder right_encoder;


// 仅开启中断
void encoder_init(void)
{
	// 编码器引脚外部中断
	NVIC_ClearPendingIRQ(GPIO_ENCODER_INT_IRQN);
	NVIC_EnableIRQ(GPIO_ENCODER_INT_IRQN);
    left_encoder.reverse = 0;
    right_encoder.reverse = 1;
    DL_GPIO_clearInterruptStatus(GPIOA, GPIO_ENCODER_PIN_LA_PIN);
    DL_GPIO_clearInterruptStatus(GPIOA, GPIO_ENCODER_PIN_RA_PIN);
}


/*******************************************************
函数功能：外部中断模拟编码器信号
入口函数：无
返回  值：无
***********************************************************/
void GROUP1_IRQHandler(void)
{
    if (DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1) == GPIO_ENCODER_INT_IIDX)
    {
        gpio_interrup = DL_GPIO_getEnabledInterruptStatus(GPIOA, GPIO_ENCODER_PIN_LA_PIN | GPIO_ENCODER_PIN_RA_PIN);
     // encoder LA
        if ((gpio_interrup & GPIO_ENCODER_PIN_LA_PIN))
        {
            if (DL_GPIO_readPins(GPIOA, GPIO_ENCODER_PIN_LB_PIN))
            {
                left_encoder.temp_count--;
            }
            else
            {
                left_encoder.temp_count++;
            }
            // 清除状态
            DL_GPIO_clearInterruptStatus(GPIOA, GPIO_ENCODER_PIN_LA_PIN);
        }
        // encoder RA
        if ((gpio_interrup & GPIO_ENCODER_PIN_RA_PIN))
        {
            if (DL_GPIO_readPins(GPIOA, GPIO_ENCODER_PIN_RB_PIN))
            {
                right_encoder.temp_count--;
            }
            else
            {
                right_encoder.temp_count++;
            }
            DL_GPIO_clearInterruptStatus(GPIOA, GPIO_ENCODER_PIN_RA_PIN);
        }
    
    }
    
    
}

int32_t TI_Exti_GetCouter(Encoder* encoder)
{
    return encoder->temp_count;
}

void Ti_Exti_SetCounter(Encoder* encoder,uint32_t count)
{
   encoder->temp_count=count;
}
/**
 * @brief 更新编码器数据 (应周期性调用, 例如10ms一次)
 */
void Encoder_Driver_Update(Encoder* encoder)
{
  // 1. 读取原始计数值
	encoder->count = (int32_t)TI_Exti_GetCouter(encoder);
  
	// 2. 处理编码器反向
     encoder->count = encoder->reverse == 0 ? encoder->count : -encoder->count;

  // 3. 清零硬件计数器，为下个周期做准备
  Ti_Exti_SetCounter(encoder, 0);

  // 4. 累计总数
  encoder->total_count += encoder->count;

  // 5. 计算速度 (cm/s)
  // 速度 = (计数值 / PPR) * 周长 / 采样时间
  encoder->speed_cm_s = ((float)(encoder->count) / (float)ENCODER_PPR * (float)WHEEL_CIRCUMFERENCE_CM / (float)SAMPLING_TIME_S);
}
