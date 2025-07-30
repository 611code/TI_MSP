#ifndef __PID_USER_H__
#define __PID_USER_H__

#include "bsp_system.h"

void yaw_loop_init(void);
void speed_loop_init(void);
void pos_loop_init(void);
void line_loop_init(void);
void encoder_loop_init(void);


void yaw_loop_update(float target_yaw);
void speed_and_yaw_loop_update(float target_speed_left, float target_speed_right, float yaw_output);
int position_loop_update(float target_pos, float desired_yaw);
void speed_and_just_loop_update(float target_speed_left, float target_speed_right, float just_out );
void line_loop_update(float target_speed_left, float target_speed_right);
int position_line_loop_update(float target_pos);
void encoder_left_position_loop_update(int target_pos);
void encoder_right_position_loop_update(int target_pos);
void encoder_turn_position_loop_update(int target_pos);
void speed2_and_just_loop_update(float target_speed_left, float target_speed_right, float just_out );
void line2_loop_update(float target_speed_left, float target_speed_right);
void line3_loop_update(float target_speed_left, float target_speed_right);

#endif


