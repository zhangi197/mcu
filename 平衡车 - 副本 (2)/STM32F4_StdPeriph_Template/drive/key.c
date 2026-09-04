#include "key.h"

volatile uint8_t key_flag;                // 按键事件标志：按住、按下、松开
uint8_t key_num;

void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 1. 使能 GPIOA 时钟 */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    /* 2. 配置 PA15 为上拉输入 */
    GPIO_InitStructure.GPIO_Pin   = KEY_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;     /* 输入模式 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; /* 50MHz */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    /* 输入模式该字段无效 */
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;     /* 上拉：按下为低 */
    GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStructure);
}
void key_tick(void)
{
    static uint8_t count;                  // 定时器调用次数，用于降低采样频率
    static uint8_t current_state;          // 最近一次确认的按键状态
    static uint8_t previous_state;         // 上一次确认的按键状态

    count++;                               // 每进入一次函数，计数加一

    if(count >= 20)                        // 累计 20 次后才读取一次按键
    {
        count = 0;                         // 清零，开始下一轮采样计数

        previous_state = current_state;    // 保存上一次稳定状态
        current_state = key_get_state();   // 读取当前按键电平

        if(current_state == pressed)       // 当前确认是按下状态
        {
            key_flag |= key_hold;          // 置位“按住”标志
        }
        else                               // 当前确认是松开状态
        {
            key_flag &= (uint8_t)~key_hold; // 清除“按住”标志
        }

        // 从松开变为按下，只产生一次 key_down 事件
        if(current_state == pressed && previous_state == unpressed)
        {
            key_flag |= key_down;
        }

        // 从按下变为松开，只产生一次 key_up 事件
        if(current_state == unpressed && previous_state == pressed)
        {
            key_flag |= key_up;
        }

    }
}
uint8_t key_get_state(void)
{
if(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY_GPIO_PIN)==0)
{
    return pressed;
}
else
{
    return unpressed;
}
}



uint8_t key_check(uint8_t flag)
{
    if(key_flag&flag)
    {   if(flag!=key_hold)
        {
            key_flag&=~flag;
        }
        return 1;
    }
    return 0;
}

uint8_t key_get_num(void)
{
    uint8_t temp;
    if(key_num)
    {temp=key_num;
    key_num=0;
    return temp;
    }
    return 0;
}
