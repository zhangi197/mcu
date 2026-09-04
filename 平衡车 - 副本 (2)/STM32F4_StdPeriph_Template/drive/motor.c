#include "motor.h"
#include "pwm.h"

void motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(MOTOR_DIR_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = MOTOR_DIR_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(MOTOR_DIR_PORT, &GPIO_InitStructure);

	pwm_Init();
	motor_Stop();
}

void motor_Setpwm(int16_t pwm)
{
	uint16_t duty;

	if (pwm > 100)
	{
		pwm = 100;
	}
	else if (pwm < -100)
	{
		pwm = -100;
	}

	if (pwm < 0)
	{
		GPIO_ResetBits(MOTOR_DIR_PORT, MOTOR_DIR_PIN);
		duty = (uint16_t)(-pwm);
	}
	else
	{
		GPIO_SetBits(MOTOR_DIR_PORT, MOTOR_DIR_PIN);
		duty = (uint16_t)pwm;
	}

	pwm_SetCompare(duty);
}

void motor_Stop(void)
{
	pwm_SetCompare(0);
}
