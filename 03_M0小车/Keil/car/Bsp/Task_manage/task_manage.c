// #include "task_manage.h"


// uint8_t task_num;

// typedef struct {
// 	void (*task_name)(void);
// 	uint32_t task_rate;
// 	uint32_t last_time;

// }task_list;

// task_list task[]={
// {menu_task,0,10}

// };

// void task_init(void)
// {
// task_num=sizeof(task)/sizeof(task_list);
// }

// void task_run(void)
// {
// 	for(int i=0;i<task_num;i++)
// 	{		
// 		if(uwTick>=task[i].last_time+task[i].task_rate)
// 		{
// 			task[i].task_name();
// 			task[i].last_time=uwTick;
// 		}
// 	}
// }


