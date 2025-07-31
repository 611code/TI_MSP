#include "app_oled.h"
#include "Bsp/Oled/hw_oled.h"
#include "Bsp/Task_manage/bsp_system.h"
extern Encoder left_encoder;
extern Encoder right_encoder;
// extern unsigned char Digtal;
extern uint8_t black_line_count;
extern unsigned char Digtal;
extern unsigned short Anolog[8];
extern unsigned short white[8];
extern unsigned short black[8];

uint8_t menu_select=0;
uint8_t Car_mode;
uint8_t adjust_mode = 0;

void menu_task(void)
{
    // if(KeyNum==1)
    // {
    //     KeyNum=0;	
    //     menu_select ^= 1;
    //     OLED_Clear();	
    // }
    if(menu_select==0)
    {
        OLED_Printf(82,0,8,"Key:%d ",KeyNum);
		OLED_Printf(0,0,8,"Yaw:%.2f ",yaw_deg);
		OLED_Printf(0,16,8,"L:%d   ",left_encoder.total_count);
		OLED_Printf(64,16,8,"R:%d   ",right_encoder.total_count);
		OLED_Printf(0,32,8,"Digtal:%d   ",Digtal);
//		//OLED_Printf(64,32,OLED_8X16,"RV:%.2f   ",rev2);
        //带MCU
		// OLED_Printf(0,48,8,"Gary:%d%d%d%d%d%d%d%d L%d",(Digtal>>0)&0x01,(Digtal>>1)&0x01,(Digtal>>2)&0x01,(Digtal>>3)&0x01,(Digtal>>4)&0x01,(Digtal>>5)&0x01,(Digtal>>6)&0x01,(Digtal>>7)&0x01,black_line_count);
        //不带MCU
        OLED_Printf(0,48,8,"Gary %d%d%d%d%d%d%d%d L%d",(Digtal>>0)&0x01,(Digtal>>1)&0x01,(Digtal>>2)&0x01,(Digtal>>3)&0x01,(Digtal>>4)&0x01,(Digtal>>5)&0x01,(Digtal>>6)&0x01,(Digtal>>7)&0x01,black_line_count);	
        OLED_Printf(64,32,8,"uwTick:%d   ",uwTick);
        OLED_Refresh();
    }

    else if(menu_select==1)
    {
        if(KeyNum==2)
        {		
            KeyNum=0;	
//			Car_mode++;
//			Car_mode=Car_mode%5;
            
            adjust_mode = 1;
            menu_select = 2;
        }
        else if(KeyNum==3)
        {
            KeyNum=0;
//			Control_mode=Car_mode;
//			pos_flag=1;

        }
        OLED_Printf(0,0,8,"Mode_select %d",Car_mode);
        OLED_Refresh();
        
    }
    else if(menu_select == 2 && adjust_mode == 1)
    {
        OLED_Printf(0,0,8,"gray adjust mode");
        no_gray_adjust();
        OLED_Printf(0,16,8,"Anolog:%d ",Anolog[0]);
        OLED_Refresh();
        if(KeyNum == 1)
        {
            KeyNum = 0;
            for(uint8_t i=0;i<8;i++)
            {
                white[i] = Anolog[i];
            }
            OLED_Printf(0,32,8,"white %d ",white[0]);	
            OLED_Refresh();
        }
        else if(KeyNum == 2)
        {
            KeyNum = 0;
            for(uint8_t i=0;i<8;i++)
            {
                black[i] = Anolog[i];
            }
            OLED_Printf(0,48,8,"black %d ",black[0]);	
            OLED_Refresh();
        }
        else if(KeyNum == 4)
        {
            KeyNum = 0;
            menu_select = 0;
            adjust_mode = 0;
        }
        
        OLED_Printf(64,32,8,"uwTick:%d   ",uwTick);
        // if(adjust_mode == 1)
        // {

        // }
    }
}
