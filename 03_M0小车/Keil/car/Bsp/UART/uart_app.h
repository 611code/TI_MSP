// #ifndef __UART_APP_H__
// #define __UART_APP_H__

// #include "Bsp_System.h"

// void uart_proc(void);

// #endif

#ifndef __UART_APP_H_
#define __UART_APP_H_

#include "bsp_system.h"

void uart0_send_char(char ch); //串口0发送单个字符
void uart0_send_string(char* str); //串口0发送字符串
void uart_proc(void);


#endif

