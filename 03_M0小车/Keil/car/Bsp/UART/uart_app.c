// #include "uart_app.h"

// #define BUUFER_SIZE 64

// #define SENSOR_COUNT 8

// // ??????????:
// extern bool rb_peek(char *c);  // ?????????,??????
// extern bool rb_get(char *c);   // ????????,??????
// /* ?????:?? '$'???????? '#' */
// typedef enum {
//     WAIT_DOLLAR,
//     PARSE_DIGITS,
//     WAIT_HASH
// } ParseState;

// static ParseState parse_state = WAIT_DOLLAR;
// static int        parsed_num  = 0;

// /**
//  * @brief  ?????????,???? $num#
//  * @param  byte  ????
//  * @param  out   ????????????
//  * @retval true  ????????,*out = num
//  * @retval false ??????
//  */
// bool Serial_ParseDollarByte(uint8_t byte, int *out)
// {
//     switch (parse_state)
//     {
//     case WAIT_DOLLAR:
//         if (byte == '$') {
//             parsed_num  = 0;
//             parse_state = PARSE_DIGITS;
//         }
//         break;

//     case PARSE_DIGITS:
//         if (byte >= '0' && byte <= '9') {
//             parsed_num = parsed_num * 10 + (byte - '0');
//         }
//         else if (byte == '#') {
//             /* ?????????? '#', ????????(num=0) */
//             *out        = parsed_num;
//             parse_state = WAIT_DOLLAR;
//             return true;
//         }
//         else {
//             /* ?????????,??,???? */
//             parse_state = WAIT_DOLLAR;
//         }
//         break;

//     case WAIT_HASH:
//         /* ?????????,????? PARSE_DIGITS ????? '#' */
//         parse_state = WAIT_DOLLAR;
//         break;
//     }
//     return false;
// }
// bool parse_next_float(char *out_hex8, float *out_val) {
//     char c;
//     // 1. ?? '*'
//     do {
//         if (!rb_get(&c)) return false;  // ????
//     } while (c != '*');

//     // 2. ? 8 ? hex ??
//     for (int i = 0; i < 8; i++) {
//         if (!rb_get(&c)) return false;  // ?????
//         out_hex8[i] = c;
//     }
//     out_hex8[8] = '\0';

//     // 3. ??? '#'
//     if (!rb_get(&c) || c != '#') {
//         // ????:?????????
//         return false;
//     }

//     // 4. hex ???? uint32_t
//     uint32_t bits = (uint32_t)strtoul(out_hex8, NULL, 16);

//     // 5. bit-level ? float
//     union {
//         uint32_t u;
//         float    f;
//     } conv;
//     conv.u = bits;
//     *out_val = conv.f;

//     return true;
// }

// int parse_sensors(float sensors[SENSOR_COUNT]) {
//     char hexstr[9];
//     float  val;
//     int    idx = 0;
//     while (idx < SENSOR_COUNT) {
//         if (!parse_next_float(hexstr, &val)) {
//             // ??????????,???
//             break;
//         }
//         sensors[idx++] = val;
//     }
//     return idx;  // ????????
// }
// bool parse_first_frame(const char *buf, size_t len, float sensors[8]) {
//     for (size_t i = 0; i + 9 < len; ++i) {
//         // ????
//         if (buf[i] == '&') {
//             // ??? i+9 ????? '#'
//             if (buf[i+9] == '#') {
//                 // ???? '0'/'1' -> 0.0f/1.0f
//                 for (size_t j = 0; j < 8; ++j) {
//                     char c = buf[i+1+j];
//                     if (c == '0') {
//                         sensors[j] = 0.0f;
//                     } else if (c == '1') {
//                         sensors[j] = 1.0f;
//                     } else {
//                         // ????,????
//                         return false;
//                     }
//                 }
//                 return true;
//             }
//         }
//     }
//     // ???????
//     return false;
// }
// int32_t ParseNumFromUsartBuffer(const uint8_t *pBuffer, uint16_t len)
// {
//     const char *start = NULL;
//     const char *end = NULL;
//     uint16_t i;

//     // ??????? '$' ? '#' ???
//     for (i = 0; i < len; i++)
//     {
//         if (pBuffer[i] == '$')
//         {
//             start = (const char *)&pBuffer[i];
//             // ? '$' ?????? '#'
//             for (uint16_t j = i + 1; j < len; j++)
//             {
//                 if (pBuffer[j] == '#')
//                 {
//                     end = (const char *)&pBuffer[j];
//                     break;
//                 }
//             }
//             break;
//         }
//     }

//     // ?????????????,?????
//     if (start == NULL || end == NULL || end <= start + 1)
//     {
//         return -1;
//     }

//     // ??????????????
//     uint16_t numLen = end - start - 1;
//     char numStr[16];  // ?? num ??? 15 ?
//     if (numLen >= sizeof(numStr))
//     {
//         // ??????,????
//         return -1;
//     }
//     memcpy(numStr, start + 1, numLen);
//     numStr[numLen] = '\0';

//     // ??????? atoi/strtol ????
//     char *endptr;
//     long val = strtol(numStr, &endptr, 10);
//     if (*endptr != '\0')
//     {
//         // ???????,????
//         return -1;
//     }

//     return (int32_t)val;
// }
// // ���廷�λ������ͽ��ջ�����
// ringbuffer_t usart_rb;
// uint8_t usart_read_buffer[BUUFER_SIZE];

// // void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// // {
// //   if (huart->Instance == USART1)
// //   {
// //     uart_rx_ticks = uwTick;
// //     uart_rx_index++;
// //     HAL_UART_Receive_IT(&huart1, &uart_rx_buffer[uart_rx_index], 1);
// //   }
// // }

// /**
//  * @brief UART DMA�������ɻص�����
//  *        �����յ�������д�뻷�λ�������������DMA������
//  * @param huart UART����
//  * @param Size ���յ������ݴ�С
//  * @retval None
//  */
// void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
// {
// //    printf("dma data:%s\r\n", uart_rx_dma_buffer);
//     // �������λ�����δ��
//     if(!ringbuffer_is_full(&usart_rb))
//     {
//         // ��DMA�������е�����д�뻷�λ�����
//         ringbuffer_write(&usart_rb, uart_rx_dma_buffer , Size);
//     }
//     // ����DMA������
//     memset(uart_rx_dma_buffer, 0, sizeof(uart_rx_dma_buffer));
// 		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart_rx_dma_buffer, BUUFER_SIZE);
// }

// /**
//  * @brief  ����UART���ջ������е����ݡ�
//  *         ������100ms��û�н��յ��µ����ݣ������ջ�������
//  * @param  None
//  * @retval None
//  */
// // ����UART���ջ������е�����
// void uart_proc(void)
// {
//     // // ������������Ϊ0��˵��û��������Ҫ������ֱ�ӷ���
//     // if(uart_rx_index == 0) return;

//     // // ����������һ�ν��յ����ݵ������Ѿ�����100ms
//     // if(uwTick - uart_rx_ticks > 100) // 100ms��û���յ��µ�����
//     // {
//     //     printf("uart data: %s\n", uart_rx_buffer);

//     //     // ���ս��ջ���������������������
//     //     memset(uart_rx_buffer, 0, uart_rx_index);
//     //     uart_rx_index = 0;
        
//     //     // ��UART���ջ�����ָ������Ϊ���ջ���������ʼλ��
//     //     huart1.pRxBuffPtr = uart_rx_buffer;
//     // }

//     // �������λ�����Ϊ�գ�ֱ�ӷ���
//     if(ringbuffer_is_empty(&usart_rb)) return;
    
//     // �ӻ��λ�������ȡ���ݵ���ȡ������
//     ringbuffer_read(&usart_rb, usart_read_buffer, usart_rb.itemCount);
// //    parse_first_frame(usart_read_buffer,sizeof(usart_read_buffer)-1,sensors);
// //		for(int i=0;i<8;i++)
// //		{printf("%f\n\r",sensors[i]);}
// 		num=ParseNumFromUsartBuffer(usart_read_buffer,sizeof(usart_read_buffer));
//     // ��ӡ��ȡ�������е�����
//     printf("ringbuffer data: %s\n", usart_read_buffer);
    
//     // ���ն�ȡ������
//     memset(usart_read_buffer, 0, sizeof(uint8_t) * BUUFER_SIZE);
// }

#include "uart_app.h"
// #include <cstdio>

volatile unsigned char uart_data = 0;
uint8_t uart_index = 0;
uint32_t uart_ticks = 0;
uint8_t uart_rx_buf[32];
uint8_t uart_rx_len = 0;
uint8_t uart_rx_flag = 0;
uint8_t uart_rx_state = 0; // 0:等待帧头 1:接收数据

extern unsigned char Digtal;
extern uint8_t black_line_count;

// 在中断服务函数中调用
void uart_parse_byte(uint8_t byte)
{
    switch(uart_rx_state)
    {
        case 0: // 等待帧头
            if(byte == 'A')
            {
                uart_rx_state = 1;
                uart_rx_len = 0;
            }
            break;
        case 1: // 接收数据
            if(byte == 'B')
            {
                uart_rx_buf[uart_rx_len] = '\0'; // 字符串结束符
                uart_rx_flag = 1; // 一帧数据接收完成
                uart_rx_state = 0;
            }
            else
            {
                if(uart_rx_len < 31)
                {
                    uart_rx_buf[uart_rx_len++] = byte;
                }
                else
                {
                    // 数据溢出，丢弃本帧
                    uart_rx_state = 0;
                }
            }
            break;
        default:
            uart_rx_state = 0;
            break;
    }
}

//重定向fputc函数
int fputc(int ch, FILE *stream)
{
    while( DL_UART_isBusy(UART_0_INST) == true );
    DL_UART_Main_transmitData(UART_0_INST, ch);
    return ch;
}

//重定向fputs函数
int fputs(const char* restrict s, FILE* restrict stream) {

    uint16_t char_len=0;
    while(*s!=0)
    {
        while( DL_UART_isBusy(UART_0_INST) == true );
        DL_UART_Main_transmitData(UART_0_INST, *s++);
        char_len++;
    }
    return char_len;
}
int puts(const char* _ptr)
{
 return 0;
}

//串口发送单个字符
void uart0_send_char(char ch)
{
    //当串口0忙的时候等待，不忙的时候再发送传进来的字符
    while( DL_UART_isBusy(UART_0_INST) == true );
    //发送单个字符
    DL_UART_Main_transmitData(UART_0_INST, ch);
}
//串口发送字符串
void uart0_send_string(char* str)
{
    //当前字符串地址不在结尾 并且 字符串首地址不为空
    while(*str!=0&&str!=0)
    {
        //发送字符串首地址中的字符，并且在发送完成之后首地址自增
        uart0_send_char(*str++);
    }
}

// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
// 	if(huart->Instance == USART1)
// 	{
// 		uart_index++;
// 		uart_ticks = uwTick;
// 		HAL_UART_Receive_IT(huart,(uint8_t *)&uart_buf[uart_index],1);
// 	}
// }

//串口的中断服务函数
void UART_0_INST_IRQHandler(void)
{
    //如果产生了串口中断
    switch( DL_UART_getPendingInterrupt(UART_0_INST) )
    {
        case DL_UART_IIDX_RX://如果是接收中断
			uart_ticks = uwTick;
            //将发送过来的数据保存在变量中
            uart_data = DL_UART_Main_receiveData(UART_0_INST);
            //将保存的数据再发送出去
            uart0_send_char(uart_data);	
            // uart_parse_byte(uart_data); // 解析数据
            break;

        default://其他的串口中断
            break;
    }
}



void uart_proc(void)
{
    // if(uart_rx_flag)
    // {
    //     uart_rx_flag = 0;
    //     // // 这里 uart_rx_buf 就是你要的数字字符串
    //     // // 例如可以转成整数
    //     // int value = atoi(uart_rx_buf);
    //     // uart0_send_char(uart_rx_buf);
    //     // 你可以在这里处理 value
    // }
    uart0_send_string("\r\n");
    printf("AAA");

}

