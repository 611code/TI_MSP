#include "multi_button_user.h"
#include "multi_button.h"
#include "bsp_system.h"

// /*user_add_header_file*/

// //#include "Beeper.h"
// /*user_add*/
// uint8_t KeyNum;
// /*user_add_define*/
// #define ENCODER_MODE 0
// /*user_add_define*/

// /*user_add_handle*/
// struct Button key1;
// struct Button key2;
// struct Button key3;
// struct Button key4;

// /*user_add_handle*/

// /*user_add_param*/

// /*user_add_param*/

// /*user_add_funtion*/
// void user_keyBSP_init(void)
// {



// 	button_init(&key1, read_key1_gpio ,	  0, 	1);
// 	button_init(&key2, read_key2_gpio ,  	0,  2);
// 	button_init(&key3, read_key3_gpio ,	  0, 	3);
// 	button_init(&key4, read_key4_gpio ,  	0,  4);	
	
	

// 	button_attach(&key1, SINGLE_CLICK, key1_single_click_Handler);
// 	button_attach(&key1, DOUBLE_CLICK, key1_double_click_Handler);
// 	button_attach(&key1, LONG_PRESS_START, key1_long_click_Handler);

// 	button_attach(&key2, SINGLE_CLICK, key2_single_click_Handler);
// 	button_attach(&key2, DOUBLE_CLICK, key2_double_click_Handler);
// 	button_attach(&key2, LONG_PRESS_START, key2_long_click_Handler);
	
// 	button_attach(&key3, SINGLE_CLICK, key3_single_click_Handler);
// 	button_attach(&key3, DOUBLE_CLICK, key3_double_click_Handler);
// 	button_attach(&key3, LONG_PRESS_START, key3_long_click_Handler);

// 	button_attach(&key4, SINGLE_CLICK, key4_single_click_Handler);
// 	button_attach(&key4, DOUBLE_CLICK, key4_double_click_Handler);
// 	button_attach(&key4, LONG_PRESS_START, key4_long_click_Handler);

// 	button_start(&key1);
// 	button_start(&key2);
// 	button_start(&key3);
// 	button_start(&key4);
// }

// uint8_t read_key1_gpio(uint8_t key)
// {
// 	if(DL_GPIO_readPins(KEY_PIN_K1_PORT, KEY_PIN_K1_PIN) == 0)
// 		return 1;
// 	else
// 		return 0;
// }
// uint8_t read_key2_gpio(uint8_t key)
// {
// 	return (uint8_t)DL_GPIO_readPins(KEY_PIN_K2_PORT, KEY_PIN_K2_PIN);
// }
// uint8_t read_key3_gpio(uint8_t key)
// {
// 	return (uint8_t)DL_GPIO_readPins(KEY_PIN_K3_PORT, KEY_PIN_K3_PIN);
// }
// uint8_t read_key4_gpio(uint8_t key)
// {
// 	return (uint8_t)DL_GPIO_readPins(KEY_PIN_K4_PORT, KEY_PIN_K4_PIN);
// }



// /*user_add_funtion*/

// void key1_single_click_Handler(void *btn)
// {
// 	KeyNum = 1;
// }
// void key1_double_click_Handler(void *btn)
// {
// 	KeyNum = 11;
// }
// void key1_long_click_Handler(void *btn)
// {
// 	KeyNum = 21;
// }

// void key2_single_click_Handler(void *btn)
// {
// 	KeyNum = 2;
// }
// void key2_double_click_Handler(void *btn)
// {
// 	KeyNum = 12;
// }
// void key2_long_click_Handler(void *btn)
// {
// 	KeyNum = 22;
// }

// void key3_single_click_Handler(void *btn)
// {
// 	KeyNum = 3;
// }
// void key3_double_click_Handler(void *btn)
// {
// 	KeyNum = 13;
// }
// void key3_long_click_Handler(void *btn)
// {
// 	KeyNum = 23;
// }

// void key4_single_click_Handler(void *btn)
// {
// 	KeyNum = 4;
// }
// void key4_double_click_Handler(void *btn)
// {
// 	KeyNum = 14;
// }
// void key4_long_click_Handler(void *btn)
// {
// 	KeyNum = 24;
// }


uint8_t key_val = 0;
uint8_t key_old = 0;
uint8_t key_down = 0;
uint8_t key_up = 0;
uint8_t KeyNum = 0;



uint8_t key_read(void)
{
	uint8_t temp = 0;
	if (DL_GPIO_readPins(KEY_PIN_K1_PORT, KEY_PIN_K1_PIN) == 0)
		temp = 1;
	if (DL_GPIO_readPins(KEY_PIN_K2_PORT, KEY_PIN_K2_PIN) == 0)
		temp = 2;
	if (DL_GPIO_readPins(KEY_PIN_K3_PORT, KEY_PIN_K3_PIN) == 0)
		temp = 3;
	if (DL_GPIO_readPins(KEY_PIN_K4_PORT, KEY_PIN_K4_PIN) == 0)
		temp = 4;
	return temp;
}

void key_proc(void)
{
	key_val = key_read();
	key_down = key_val & (key_val ^ key_old);
	key_up = ~key_val & (key_val ^ key_old);
	key_old = key_val;
	if (key_down)
	{
		switch (key_down)
		{
			case 1: // KEY_CENTER ??
				KeyNum=1;	
                // menu_select ^= 1;
				if(menu_select != 2)menu_select ^= 1;
				OLED_Clear();
				break;
			case 2: // KEY_RIGHT ??
				KeyNum = 2;
				break;
			case 3: // KEY_DOWN -
				KeyNum = 3;
				break;
			case 4: // KEY_LEFT - ?????
				KeyNum = 4;
				break;
		}
	}
}


