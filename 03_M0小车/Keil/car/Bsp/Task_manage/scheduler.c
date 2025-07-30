//#include "scheduler.h"

//uint8_t task_num = 0;

//typedef struct
//{
//	void (*func_proc)(void);
//	uint32_t rate_ms;
//	uint32_t last_ms;
//}task_t;

//static task_t task[]=
//{
//	{oled_proc,100,0},
////	{button_ticks,5,0},
//	{key_proc,10,0}
//};

//void scheduler_init(void)
//{
//	task_num = sizeof(task) / sizeof(task_t);
//}

//void scheduler_run(void)
//{
//	for(uint8_t i=0;i<task_num;i++)
//	{
//		uint32_t now_time = uwTick;
//		if(now_time >= task[i].last_ms + task[i].rate_ms)
//		{
//			task[i].last_ms = now_time;
//			task[i].func_proc();
//		}
//	}
//}


