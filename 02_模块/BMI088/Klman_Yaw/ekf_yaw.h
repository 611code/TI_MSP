#ifndef EKF_YAW_H
#define EKF_YAW_H

#include <stdint.h>
#include "bsp_system.h"

// 状态维度：四元数 (q0,q1,q2,q3) + 三轴陀螺偏置 (bx,by,bz)
#define EKF_STATE_DIM    7
#define EKF_MEAS_DIM     3

// #define M_PI 3.14159265358979323846f

typedef struct {
    float x[EKF_STATE_DIM];      // [q0, q1, q2, q3, bx, by, bz]
    float P[EKF_STATE_DIM][EKF_STATE_DIM];
    float Q[EKF_STATE_DIM][EKF_STATE_DIM];
    float R[EKF_MEAS_DIM][EKF_MEAS_DIM];
} EKF_HandleTypeDef;

/**
 * @brief  初始化 EKF 结构
 * @param  ekf     EKF 句柄指针
 * @param  q_init  初始四元数 {1,0,0,0}
 * @param  P0_diag 初始 P 对角线值（规模调优）
 * @param  Q_diag  过程噪声对角线（陀螺噪声、偏置漂移）
 * @param  R_diag  加速度测量噪声对角线
 */
void EKF_Init(EKF_HandleTypeDef *ekf,
              const float q_init[4],
              const float P0_diag[EKF_STATE_DIM],
              const float Q_diag[EKF_STATE_DIM],
              const float R_diag[EKF_MEAS_DIM]);

/**
 * @brief  EKF 预测步骤：用陀螺角速度积分更新四元数
 * @param  ekf    EKF 句柄
 * @param  gyro   三轴陀螺测量 (rad/s)
 * @param  dt     本次积分时间 (s)
 */
void EKF_Predict(EKF_HandleTypeDef *ekf,
                 const float gyro[3],
                 float dt);

/**
 * @brief  EKF 更新步骤：用加速度测量修正俯仰/横滚
 * @param  ekf     EKF 句柄
 * @param  accel   三轴加速度测量 (m/s²)
 */
void EKF_Update(EKF_HandleTypeDef *ekf,
                const float accel[3]);

/**
 * @brief  从当前四元数中提取偏航角 (Yaw)
 * @param  ekf    EKF 句柄
 * @return 偏航角 (rad)
 */
float EKF_GetYaw(const EKF_HandleTypeDef *ekf);

float EKF_GetYawFiltered(const EKF_HandleTypeDef *ekf);

void Ekf_yaw_Forecast(void);

void Yaw_Task(void);

#endif // EKF_YAW_H

