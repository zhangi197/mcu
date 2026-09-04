#include "pid.h"                         // 引入 PID_t 结构体和 PID 函数声明

// 将 value 限制在 min 和 max 之间，防止数值超过允许范围
static float limit(float value, float min, float max)
{
    if (value > max)                     // 如果 value 大于上限
        return max;                       // 返回上限
    else if (value < min)                // 如果 value 小于下限
        return min;                       // 返回下限
    else                                  // 如果 value 在范围内
        return value;                     // 返回原始值
}

// 初始化 PID 参数和运行过程中需要保存的状态
// ki：积分系数，kp：比例系数，kd：微分系数
// inte：积分累计上限，out_min/out_max：PID 输出上下限
void PID_init(PID_t *pid, float ki, float kp, float kd, float inte, float out_min, float out_max)
{
    pid->ki = ki;                         // 保存积分系数
    pid->kp = kp;                         // 保存比例系数
    pid->kd = kd;                         // 保存微分系数

    pid->target = 0;                      // 目标值
    pid->actual = 0;                      // 实际值

    pid->err0 = 0;                        // 当前误差，当前目标值减实际值
    pid->err1 = 0;                        // 上一次误差，用于计算误差变化量
    pid->errint = 0;                      // 误差累计值，也就是积分项的输入

    pid->inte_max = inte;                 // 限制误差累计值，防止积分饱和
    pid->out_min = out_min;               // 限制 PID 最小输出
    pid->out_max = out_max;               // 限制 PID 最大输出
}

// 执行一次 PID 计算，返回本次应该输出给电机的控制量
float PID_updata(PID_t *pid)
{
    float out;                            // 保存未限幅前的 PID 计算结果

    pid->err1 = pid->err0;                // 先保存上一次误差
    pid->err0 = pid->target - pid->actual; // 计算当前误差：目标值 - 实际值

    pid->errint += pid->err0;             // 将当前误差累加到积分值
    pid->errint = limit(pid->errint, -pid->inte_max, pid->inte_max); // 积分限幅

    out = pid->kp * pid->err0            // 比例项：当前误差乘以 kp
        + pid->ki * pid->errint           // 积分项：累计误差乘以 ki
        + pid->kd * (pid->err0 - pid->err1); // 微分项：误差变化量乘以 kd

    return limit(out, pid->out_min, pid->out_max); // 输出限幅
}
