#ifndef __PID_H
#define __PID_H

typedef struct
{
    float ki;
    float kp;
    float kd;

    float target;
    float actual;

    float err0;
    float err1;
    float errint;

    float inte_max;
    float out_min;
    float out_max;
} PID_t;

void  PID_init(PID_t *pid, float ki, float kp, float kd, float inte, float out_min, float out_max);
float PID_updata(PID_t *pid);

#endif
