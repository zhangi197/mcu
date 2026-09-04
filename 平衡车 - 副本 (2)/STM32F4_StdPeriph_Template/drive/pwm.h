#ifndef __PWM_H
#define __PWM_H

#include "stm32f4xx.h"

void pwm_Init(void);
void pwm_SetCompare(uint16_t compare);

#endif
