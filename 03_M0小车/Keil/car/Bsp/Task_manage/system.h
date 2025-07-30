#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "bsp_system.h"

void delay_ms(unsigned int ms);
void delay_us(unsigned int us);
void timer_init(void);
void task_run(void);

#endif
