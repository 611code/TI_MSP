// #include "gray_app.h"
// #include "No_Mcu_gray.h"

// unsigned char Digtal; // ������
// uint8_t black_line_count = 0;//

// float gray_weights[8] = {-30.0f, -20.0f, -5.0f, -2.0f, 2.0f, 5.0f, 20.0f, 30.0f}; // 8 ·�Ҷ�ͨ��Ȩ�ر�

// float g_line_position_error; // ѭ�����ֵ

// void Gray_Init(void)
// {

// }

// void Gray_Task(void)
// {
// 		black_line_count = 0;
        
//     Digtal=~IIC_Get_Digtal();
// //    Uart_Printf(&huart1, "Digtal %d-%d-%d-%d-%d-%d-%d-%d\r\n",(Digtal>>0)&0x01,(Digtal>>1)&0x01,(Digtal>>2)&0x01,(Digtal>>3)&0x01,(Digtal>>4)&0x01,(Digtal>>5)&0x01,(Digtal>>6)&0x01,(Digtal>>7)&0x01);
  	
//     float weighted_sum = 0;
    

//     for(uint8_t i = 0; i < 8; i++)
//     {
//       if((Digtal>>i) & 0x01)
//       {
//         weighted_sum += gray_weights[i];
//         black_line_count++;
//       }
//     }
		
	
//     if(black_line_count > 0)
//       g_line_position_error = weighted_sum / (float)black_line_count;

// }
