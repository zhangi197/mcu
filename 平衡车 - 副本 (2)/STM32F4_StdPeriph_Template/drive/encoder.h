#ifndef __encoder_H
#define __encoder_H

#include "stm32f4xx.h"

void encoder_Init(void);
int32_t encoder_GetValue(void);
int32_t encoder_GetSpeed(void);
void encoder_ResetValue(void);

#endif /* __encoder_H */