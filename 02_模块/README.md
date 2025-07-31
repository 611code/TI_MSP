# 关于system.h头文件

里面内容如下

volatile int uwTick要外部声明一下，这个要用到。

```
#include "system.h"

volatile int uwTick;

//搭配滴答定时器实现的精确ms延时
void delay_ms(unsigned int ms)
{
  delay_cycles( (CPUCLK_FREQ/1000) * (ms) );
}

void delay_us(unsigned int us)
{
  delay_cycles( (CPUCLK_FREQ/1000000) * (us) );
}

// void SysTick_Handler(void)
// {
//    uwTick++;
// }


void timer_init(void)
{
	// 定时器中断
	NVIC_ClearPendingIRQ(TIMER_TICK_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_TICK_INST_INT_IRQN);
}

void TIMER_TICK_INST_IRQHandler(void)
{
	// 1ms归零中断触发
	if (DL_TimerA_getPendingInterrupt(TIMER_TICK_INST) == DL_TIMER_IIDX_ZERO)
	{
        uwTick++;
		//添加任务
		//eg:yaw_timer5ms++;
		//if(yaw_timer5ms>=5)
        //{
        //    yaw_timer5ms=0;
        //    Yaw_Task();//执行相应任务
        //}
	}
}
```

