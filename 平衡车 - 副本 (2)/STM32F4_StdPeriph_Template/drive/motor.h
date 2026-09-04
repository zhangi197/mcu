#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f4xx.h"

/* Change these three macros to match the motor driver's DIR input. */
#define MOTOR_DIR_PORT       GPIOB
#define MOTOR_DIR_PIN        GPIO_Pin_0
#define MOTOR_DIR_GPIO_CLK   RCC_AHB1Periph_GPIOB

void motor_Init(void);
void motor_Setpwm(int16_t pwm);
void motor_Stop(void);

#endif
