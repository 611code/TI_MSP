#include "system.h"

volatile int uwTick;

uint16_t pid_timer50ms;
uint16_t menu_timer30ms;
uint8_t measure_timer50ms;
uint8_t button_timer10ms;
uint8_t gary_timer10ms;
uint8_t yaw_timer5ms;
uint8_t uart_timer200ms;
uint8_t pos_flag=0;
uint8_t yaw_count=100;
uint8_t Control_mode=0;

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

void task_run(void)
{
    
    if(button_timer10ms>=10)
    {
        button_timer10ms = 0;
        key_proc();
    }
    if(gary_timer10ms>=15)
    {
        gary_timer10ms = 0;
        Gray_Task();
    }
    if(measure_timer50ms >= 50)//50ms一周期 
    {
        measure_timer50ms=0;
        Encoder_Task();
    }
    if(uart_timer200ms >= 200)//50ms一周期 
    {
        uart_timer200ms=0;
        uart_proc();
    }
    // if(menu_timer30ms >= 30)//50ms一周期 
    // {
    //     menu_timer30ms=0;
        
    // }
}

void TIMER_TICK_INST_IRQHandler(void)
{
	// 1ms归零中断触发
	if (DL_TimerA_getPendingInterrupt(TIMER_TICK_INST) == DL_TIMER_IIDX_ZERO)
	{
        uwTick++;
		
        yaw_timer5ms++;
        // menu_timer30ms++;
		measure_timer50ms++;
		button_timer10ms++;
		gary_timer10ms++;
        uart_timer200ms++;
		pid_timer50ms++;
        if(yaw_timer5ms>=5)
        {
            yaw_timer5ms=0;
            Yaw_Task();
        }
        if(pid_timer50ms>=50)
        {
            pid_timer50ms=0;
            line3_loop_update(1.5f,1.5f);
        }
	}
}