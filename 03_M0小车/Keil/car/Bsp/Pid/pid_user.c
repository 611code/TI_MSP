#include "pid_user.h"

#define MAX_SPEED_CM_S 2.0

extern Encoder left_encoder;
extern Encoder right_encoder;
extern float g_line_position_error;
extern float rev1;
extern float rev2;
extern float g_motor1_journey_cm;
extern float g_motor2_journey_cm;
extern int32_t last_sigma_motor1;
extern int32_t last_sigma_motor2;
extern float g_line_position_error;
extern uint8_t black_line_count;
PID_T yaw_pid;
PID_T speed_pid_left;
PID_T speed_pid_right;
PID_T pos_pid;
PID_T line_pid;
PID_T line_pid2;

PID_T encoder_pid_left;
PID_T encoder_pid_right;


PID_T speed2_pid_left;
PID_T speed2_pid_right;
float speed_output_left;
float speed_output_right;
float current_yaw;
float current_speed_left ;
float current_speed_right;
float yaw_error;
float left_speed ;
float right_speed;
float pos_speed_output = 0.0f;


void yaw_loop_init(void)
{
    // PID参数需要实测调试
    pid_init(&yaw_pid, 8.0f, 1.0f, 5.0f, 0.0f, 999.0f);
}


void speed_loop_init(void)
{
    // PID参数：kp, ki, kd, target_speed, limit（最大输出PWM）
    pid_init(&speed_pid_left, 120.0f, 20.0f, 0.0f, 0.0f, 999.0f);
		pid_init(&speed_pid_right, 120.0f, 20.0f, 0.0f, 0.0f, 999.0f);
		pid_init(&speed2_pid_left, 80.0f, 2.0f, 0.0f, 0.0f, 999.0f);
		pid_init(&speed2_pid_right, 80.0f, 2.0f, 0.0f, 0.0f, 999.0f);
}


void pos_loop_init(void)
{
    // PID参数：kp, ki, kd, target_speed, limit（最大输出PWM）
    pid_init(&pos_pid, 0.30f, 0.0f, 0.0f, 0.0f, 999.0f);
}


void line_loop_init(void)
{
    // PID参数：kp, ki, kd, target_speed, limit（最大输出PWM）
    pid_init(&line_pid, 150.0f, 0.0f, 70.0f, 0.0f, 999.0f);
    // PID参数：kp, ki, kd, target_speed, limit（最大输出PWM）
    pid_init(&line_pid2, 4.0f, 0.0f, 1.0f, 0.0f, 999.0f);
}


void encoder_loop_init(void)
{
    // PID参数：kp, ki, kd, target_speed, limit（最大输出PWM）
    pid_init(&encoder_pid_left, 3.0f, 0.0f, 2.0f, 0.0f, 999.0f);
	pid_init(&encoder_pid_right, 3.0f, 0.0f, 2.0f, 0.0f, 999.0f);
}

// 计算两个角度之间的最短差值，结果在 [-180, +180) 范围内
static float angle_error(float target_deg, float current_deg) {
    float err = target_deg - current_deg;
    if      (err >  180.0f) err -= 360.0f;
    else if (err < -180.0f) err += 360.0f;
    return err;
}


void yaw_loop_update(float target_yaw)
{
    float current_yaw = yaw_deg;  // 从IMU读取当前Yaw角

    // 处理yaw角度的±180°溢出问题（角度差需归一化）
		float angle_error = target_yaw - current_yaw;
		if (angle_error > 180.0f) angle_error -= 360.0f;
		else if (angle_error < -180.0f) angle_error += 360.0f;

		pid_set_target(&yaw_pid, 0);  // 目标是零误差
		float output = pid_calculate_incremental(&yaw_pid, angle_error);

		
		int pwm=(int)output;
    load_motor_pwm(pwm,-pwm);
}


void speed_and_yaw_loop_update(float target_speed_left, float target_speed_right, float target_yaw )
{
    // 获取当前转速
    current_speed_left = rev1;
    current_speed_right = rev2;
		
		float angle_error = target_yaw - yaw_deg;
		if (angle_error > 180.0f) angle_error -= 360.0f;
		else if (angle_error < -180.0f) angle_error += 360.0f;

		pid_set_target(&yaw_pid, 0);  // 目标是零误差
		float yaw_output = pid_calculate_incremental(&yaw_pid, angle_error);	
    // **PID 控制器计算**
    // 车速控制输出
		pid_set_target(&speed_pid_left, target_speed_left);  
	  pid_set_target(&speed_pid_right, target_speed_right); 
    speed_output_left = pid_calculate_positional(&speed_pid_left, current_speed_left);
    speed_output_right = pid_calculate_positional(&speed_pid_right, current_speed_right);


    // **差速控制**
    // 航向角控制调整左右轮差速，车速控制则调整整体速度
		left_speed = speed_output_left + yaw_output ;
		right_speed = speed_output_right - yaw_output ;
//		float left_speed = speed_output_left;
//    float right_speed = speed_output_right;

    // 确保左右轮速度在可控制范围内
    left_speed = pid_constrain(left_speed, -speed_pid_left.limit, speed_pid_left.limit);
    right_speed = pid_constrain(right_speed, -speed_pid_right.limit, speed_pid_right.limit);

    // **5. 控制电机输出**
		int pwm1=(int)left_speed;
		int pwm2=(int)right_speed;
    load_motor_pwm(pwm1, pwm2);
}

void speed_and_just_loop_update(float target_speed_left, float target_speed_right, float just_out )
{
    // 获取当前转速
    current_speed_left = rev1;
    current_speed_right = rev2;
		
    // **PID 控制器计算**
    // 车速控制输出
		pid_set_target(&speed_pid_left, target_speed_left);  
	  pid_set_target(&speed_pid_right, target_speed_right); 
    speed_output_left = pid_calculate_positional(&speed_pid_left, current_speed_left);
    speed_output_right = pid_calculate_positional(&speed_pid_right, current_speed_right);


    // **差速控制**
    // 航向角控制调整左右轮差速，车速控制则调整整体速度
		left_speed = 0.5*speed_output_left + just_out ;
		right_speed = 0.5*speed_output_right - just_out ;
//		float left_speed = speed_output_left;
//    float right_speed = speed_output_right;

    // 确保左右轮速度在可控制范围内
    left_speed = pid_constrain(left_speed, -speed_pid_left.limit, speed_pid_left.limit);
    right_speed = pid_constrain(right_speed, -speed_pid_right.limit, speed_pid_right.limit);

    // **5. 控制电机输出**
		int pwm1=(int)left_speed;
		int pwm2=(int)right_speed;
    load_motor_pwm(pwm1, pwm2);
}
void speed2_and_just_loop_update(float target_speed_left, float target_speed_right, float just_out )
{
    // 获取当前转速
    current_speed_left = rev1;
    current_speed_right = rev2;
		
    // **PID 控制器计算**
    // 车速控制输出
		pid_set_target(&speed2_pid_left, target_speed_left);  
	  pid_set_target(&speed2_pid_right, target_speed_right); 
    speed_output_left = pid_calculate_incremental(&speed2_pid_left, current_speed_left);
    speed_output_right = pid_calculate_incremental(&speed2_pid_right, current_speed_right);


    // **差速控制**
    // 航向角控制调整左右轮差速，车速控制则调整整体速度
		left_speed = speed_output_left + just_out ;
		right_speed = speed_output_right - just_out ;
//		float left_speed = speed_output_left;
//    float right_speed = speed_output_right;

    // 确保左右轮速度在可控制范围内
    left_speed = pid_constrain(left_speed, -speed_pid_left.limit, speed_pid_left.limit);
    right_speed = pid_constrain(right_speed, -speed_pid_right.limit, speed_pid_right.limit);

    // **5. 控制电机输出**
		int pwm1=(int)left_speed;
		int pwm2=(int)right_speed;
    load_motor_pwm(pwm1, pwm2);
}

// 位置环更新函数
// target_pos: 期望的目标位置（单位：cm）
// desired_yaw: 目标航向，用于下一步调用速度+航向环
int position_loop_update(float target_pos, float desired_yaw)
{
    // 1. 计算平均行程作为当前位置
    float current_pos_cm = (g_motor1_journey_cm + g_motor2_journey_cm) * 0.5f;

    // 2. 计算当前位置与目标位置的误差
    float error = target_pos - current_pos_cm;

    // 3. 如果误差在 ±1cm 以内，认为到达目标
    if (fabsf(error) <= 0.5f) {
        // 可选：到达后停止输出
        speed_and_yaw_loop_update(0.0f, 0.0f, desired_yaw);
				left_encoder.total_count=0;
				g_motor1_journey_cm=0;
				last_sigma_motor1=0;
				right_encoder.total_count=0;
				g_motor2_journey_cm=0;
				last_sigma_motor2=0;
				load_motor_pwm(0,0);
        return 1;
    }

    // 4. 更新 PID 目标并计算位置环输出（单位：cm/s）
    pid_set_target(&pos_pid, target_pos);
    pos_speed_output = pid_calculate_positional(&pos_pid, current_pos_cm);

    // 5. 限幅：防止给出的速度过大或过小
    if (pos_speed_output > MAX_SPEED_CM_S)      pos_speed_output = MAX_SPEED_CM_S;
    else if (pos_speed_output < -MAX_SPEED_CM_S) pos_speed_output = -MAX_SPEED_CM_S;

    // 6. 将位置环输出作为速度环的目标速度，调用速度+航向控制
    speed_and_yaw_loop_update(pos_speed_output,
                              pos_speed_output,
                              desired_yaw);

    return 0;
}


void line_loop_update(float target_speed_left, float target_speed_right)// 循迹环控制
{
  int line_pid_output = 0;
  
  // 使用位置式 PID 计算利用循迹环计算输出
  line_pid_output = pid_calculate_positional(&line_pid, g_line_position_error);
  
  // 输出限幅
  line_pid_output = pid_constrain(line_pid_output, -line_pid.limit, line_pid.limit);
  
//	if(black_line_count==8||black_line_count==0)
//	{
//	load_motor_pwm(0,0);
//	return;	
//	}
  // 将差值作用在速度环的目标量上
  // 将位置环输出作为速度环的目标速度，调用速度+航向控制
    speed_and_just_loop_update(target_speed_left,
                              target_speed_right,
                              -3*line_pid_output);
}
void line2_loop_update(float target_speed_left, float target_speed_right)// 循迹环控制
{
  int line_pid_output = 0;
  
  // 使用位置式 PID 计算利用循迹环计算输出
  line_pid_output = pid_calculate_positional(&line_pid, g_line_position_error);
  
  // 输出限幅
  line_pid_output = pid_constrain(line_pid_output, -line_pid.limit, line_pid.limit);
  
//	if(black_line_count==8||black_line_count==0)
//	{
//	load_motor_pwm(0,0);
//	return;	
//	}
  // 将差值作用在速度环的目标量上
  // 将位置环输出作为速度环的目标速度，调用速度+航向控制
    speed2_and_just_loop_update(target_speed_left,
                              target_speed_right,
                              -3*line_pid_output);
}

//循线环
void line3_loop_update(float target_speed_left, float target_speed_right)// 循迹环控制
{
  int line_pid_output = 0;
  
  // 使用位置式 PID 计算利用循迹环计算输出
  line_pid_output = pid_calculate_positional(&line_pid2, g_line_position_error);
  
  // 输出限幅
  line_pid_output = pid_constrain(line_pid_output, -line_pid2.limit, line_pid2.limit);
  

  // 将差值作用在速度环的目标量上
  // 将位置环输出作为速度环的目标速度，调用速度+航向控制
	left_speed = (float)target_speed_left/5.0f*1000.0f;
	right_speed = (float)target_speed_right/5.0f*1000.0f;
    // **差速控制**
    // 航向角控制调整左右轮差速，车速控制则调整整体速度
		left_speed = left_speed - line_pid_output ;
		right_speed = right_speed + line_pid_output ;
//		float left_speed = speed_output_left;
//    float right_speed = speed_output_right;

    // 确保左右轮速度在可控制范围内
    left_speed = pid_constrain(left_speed, -speed_pid_left.limit, speed_pid_left.limit);
    right_speed = pid_constrain(right_speed, -speed_pid_right.limit, speed_pid_right.limit);

    // **5. 控制电机输出**
		int pwm1=(int)left_speed;
		int pwm2=(int)right_speed;
    load_motor_pwm(pwm1, pwm2);
}


// 位置环更新函数
// target_pos: 期望的目标位置（单位：cm）
// desired_yaw: 目标航向，用于下一步调用速度+航向环
int position_line_loop_update(float target_pos)
{
    // 计算平均行程作为当前位置
    float current_pos_cm = (g_motor1_journey_cm + g_motor2_journey_cm) * 0.5f;
		
		// 2. 计算当前位置与目标位置的误差
    float error = target_pos - current_pos_cm;

    // 如果误差在 ±1cm 以内，认为到达目标
    if (fabsf(error) <= 0.5f) {
        // 可选：到达后停止输出
        speed_and_just_loop_update(0.0f, 0.0f, 0.0f);
				left_encoder.total_count=0;
				g_motor1_journey_cm=0;
				right_encoder.total_count=0;
				g_motor2_journey_cm=0;
				load_motor_pwm(0,0);
        return 1;
    }
		// 更新PID目标并计算位置环输出（单位：cm/s）
    pid_set_target(&pos_pid, target_pos);
    pos_speed_output = pid_calculate_positional(&pos_pid, current_pos_cm);
		// 3. 限幅：防止给出的速度过大或过小
    if (pos_speed_output > MAX_SPEED_CM_S)      pos_speed_output = MAX_SPEED_CM_S;
    else if (pos_speed_output < -MAX_SPEED_CM_S) pos_speed_output = -MAX_SPEED_CM_S;


    // 将位置环输出作为速度环的目标速度，调用速度+航向控制
	int line_pid_output = 0;
  
  // 使用位置式 PID 计算利用循迹环计算输出
  line_pid_output = pid_calculate_positional(&line_pid, g_line_position_error);
  
  // 输出限幅
  line_pid_output = pid_constrain(line_pid_output, -line_pid.limit, line_pid.limit);
  
  // 将差值作用在速度环的目标量上
  // 将位置环输出作为速度环的目标速度，调用速度+航向控制
    speed_and_just_loop_update(pos_speed_output,
                              pos_speed_output,
                              -line_pid_output);
		return 0;
}


void encoder_left_position_loop_update(int target_pos)
{
	int current_count=left_encoder.total_count;
	// 2. 计算当前位置与目标位置的误差
  float error = target_pos - current_count;		
  // 使用位置式 PID 计算利用循迹环计算输出
  float pos_pid_output = pid_calculate_positional(&encoder_pid_left, error);
  
  // 输出限幅
  pos_pid_output = pid_constrain(pos_pid_output, -encoder_pid_left.limit, encoder_pid_left.limit);
  
  // 将差值作用在速度环的目标量上
  // 将位置环输出作为速度环的目标速度，调用速度+航向控制
	load_motor_pwm(-pos_pid_output,0);
}
	
void encoder_right_position_loop_update(int target_pos)
{
	int current_count=right_encoder.total_count;
	// 2. 计算当前位置与目标位置的误差
  float error = target_pos - current_count;		
  // 使用位置式 PID 计算利用循迹环计算输出
  float pos_pid_output = pid_calculate_positional(&encoder_pid_right, error);
  
  // 输出限幅
  pos_pid_output = pid_constrain(pos_pid_output, -encoder_pid_right.limit, encoder_pid_right.limit);
  
  // 将差值作用在速度环的目标量上
  // 将位置环输出作为速度环的目标速度，调用速度+航向控制
	load_motor_pwm(0,-pos_pid_output);
}


void encoder_turn_position_loop_update(int target_pos)
{
	int current_count1=right_encoder.total_count;
	// 2. 计算当前位置与目标位置的误差
  float error1 = target_pos - current_count1;		
  // 使用位置式 PID 计算利用循迹环计算输出
  float pos_pid_output1 = pid_calculate_positional(&encoder_pid_right, error1);
  int current_count2=left_encoder.total_count;
	// 2. 计算当前位置与目标位置的误差
  float error2 = -target_pos - current_count2;		
  // 使用位置式 PID 计算利用循迹环计算输出
  float pos_pid_output2 = pid_calculate_positional(&encoder_pid_left, error2);
  
  // 输出限幅
  pos_pid_output2 = pid_constrain(pos_pid_output2, -encoder_pid_left.limit, encoder_pid_left.limit);
 
  // 输出限幅
  pos_pid_output1 = pid_constrain(pos_pid_output1, -encoder_pid_right.limit, encoder_pid_right.limit);
  
  // 将差值作用在速度环的目标量上
  // 将位置环输出作为速度环的目标速度，调用速度+航向控制
	load_motor_pwm(-pos_pid_output2,-pos_pid_output1);
}


