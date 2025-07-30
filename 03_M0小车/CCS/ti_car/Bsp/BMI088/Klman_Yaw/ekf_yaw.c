#include "ekf_yaw.h"
#include "Bsp/Task_manage/bsp_system.h"
#include <string.h>
#include <math.h>

// 低通滤波状态和参数
static float yaw_filt = 0.0f;
static const float alpha = 0.02f; // 滤波系数
static const float epsilon = 0.005f; // 抑制抖动阈值
static uint32_t t_last = 0; // 上次时间戳
float yaw_deg; // 角度变量
EKF_HandleTypeDef ekf; // EKF句柄
float gyro_sum[3]; // 陀螺仪累加
static const float Q_diag[EKF_STATE_DIM] = {
    1e-5f, 1e-5f, 1e-5f, 1e-5f,
    1e-7f, 1e-7f, 1e-7f
};
static const float R_diag[EKF_MEAS_DIM] = {5e-2f, 5e-2f, 5e-2f}; // 测量噪声
static const float P0_diag[EKF_STATE_DIM] = {
    1e-2f, 1e-2f, 1e-2f, 1e-2f,
    1e-3f, 1e-3f, 1e-3f
};

float gyro[3], accel[3], temp;

// 四元数归一化（内联）
inline static void quaternion_normalize(float q[4]) {
    float n = sqrtf(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
    for (int i = 0; i < 4; i++) q[i] /= n;
}

// EKF初始化
void EKF_Init(EKF_HandleTypeDef *ekf,
              const float q_init[4],
              const float P0_diag[EKF_STATE_DIM],
              const float Q_diag[EKF_STATE_DIM],
              const float R_diag[EKF_MEAS_DIM]) {
    memcpy(ekf->x, q_init, sizeof(float)*4);
    memset(&ekf->x[4], 0, 3 * sizeof(float)); // 偏置初始化为0

    // Covariance初始化
    for (int i = 0; i < EKF_STATE_DIM; i++) {
        for (int j = 0; j < EKF_STATE_DIM; j++) {
            ekf->P[i][j] = (i == j) ? P0_diag[i] : 0.0f;
            ekf->Q[i][j] = (i == j) ? Q_diag[i] : 0.0f;
        }
    }
    for (int i = 0; i < EKF_MEAS_DIM; i++) {
        for (int j = 0; j < EKF_MEAS_DIM; j++) {
            ekf->R[i][j] = (i == j) ? R_diag[i] : 0.0f;
        }
    }
}

// EKF预测步骤
void EKF_Predict(EKF_HandleTypeDef *ekf, const float gyro[3], float dt) {
    // 状态预测（四元数微分）
    float wx = gyro[0] - ekf->x[4];
    float wy = gyro[1] - ekf->x[5];
    float wz = gyro[2] - ekf->x[6];

    float q0 = ekf->x[0], q1 = ekf->x[1], q2 = ekf->x[2], q3 = ekf->x[3];
    // dq = 0.5 * Omega(omega) * q
    float dq[4] = {
        -0.5f * (q1*wx + q2*wy + q3*wz),
         0.5f * (q0*wx + q2*wz - q3*wy),
         0.5f * (q0*wy - q1*wz + q3*wx),
         0.5f * (q0*wz + q1*wy - q2*wx)
    };
    // 积分更新
    ekf->x[0] += dq[0] * dt;
    ekf->x[1] += dq[1] * dt;
    ekf->x[2] += dq[2] * dt;
    ekf->x[3] += dq[3] * dt;
    quaternion_normalize(ekf->x);

    // TODO: 计算雅可比F, G并更新P (可以使用CMSIS-DSP矩阵库)
}

// EKF更新步骤
void EKF_Update(EKF_HandleTypeDef *ekf, const float accel[3]) {
    // 观测修正
    float norm = sqrtf(accel[0]*accel[0] + accel[1]*accel[1] + accel[2]*accel[2]);
    float ax = accel[0] / norm, ay = accel[1] / norm, az = accel[2] / norm;

    float q0 = ekf->x[0], q1 = ekf->x[1], q2 = ekf->x[2], q3 = ekf->x[3];
    float gx = 2 * (q1 * q3 - q0 * q2);
    float gy = 2 * (q0 * q1 + q2 * q3);
    float gz = q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3;

    // 误差y = z - h(x)
    float yv[3] = { ax - gx, ay - gy, az - gz };

    // TODO: 计算H、卡尔曼增益K，并更新ekf->x和P（使用CMSIS-DSP）
}

// 获取偏航角（单位：弧度）
float EKF_GetYaw(const EKF_HandleTypeDef *ekf) {
    float q0 = ekf->x[0], q1 = ekf->x[1], q2 = ekf->x[2], q3 = ekf->x[3];
    return atan2f(2.0f * (q0 * q3 + q1 * q2), 1.0f - 2.0f * (q2 * q2 + q3 * q3));
}

// 获取滤波后的偏航角（单位：度）
float EKF_GetYawFiltered(const EKF_HandleTypeDef *ekf) {
    float yaw = EKF_GetYaw(ekf) * 180.0f / M_PI;
    float diff = yaw - yaw_filt;
    if (diff > 180.0f) diff -= 360.0f;
    if (diff < -180.0f) diff += 360.0f;

    if (fabsf(diff) < epsilon) return yaw_filt;

    yaw_filt += alpha * diff;
    if (yaw_filt > 180.0f) yaw_filt -= 360.0f;
    if (yaw_filt < -180.0f) yaw_filt += 360.0f;

    return yaw_filt;
}

// EKF预测并更新（主函数）
void Ekf_yaw_Forecast(void) {
    while (BMI088_init()) { ; }
    const float q_init[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    EKF_Init(&ekf, q_init, P0_diag, Q_diag, R_diag);

    for (int i = 0; i < 500; i++) {
        BMI088_read(gyro, accel, &temp);
        gyro_sum[0] += gyro[0];
        gyro_sum[1] += gyro[1];
        gyro_sum[2] += gyro[2];
        delay_ms(10);
    }
    ekf.x[4] = gyro_sum[0] / 500.0f;
    ekf.x[5] = gyro_sum[1] / 500.0f;
    ekf.x[6] = gyro_sum[2] / 500.0f;
}

// 偏航任务
void Yaw_Task(void) {
    uint32_t t_now = uwTick;
    float dt = (t_now - t_last) / 1000.0f;  // 时间间隔（秒）
    t_last = t_now;

    BMI088_read(gyro, accel, &temp);
    EKF_Predict(&ekf, gyro, dt);
    EKF_Update(&ekf, accel);

    float yaw = EKF_GetYaw(&ekf);
    yaw_deg = yaw * 180.0f / M_PI; // 偏航角（度）
}
