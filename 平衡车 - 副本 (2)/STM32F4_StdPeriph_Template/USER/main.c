#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "encoder.h"
#include "oled.h"
#include "motor.h"
#include "timer1.h"
#include "pid.h"
#include "adc.h"

#define middle_angle 2048
#define middle_rance 500

uint8_t keynum;
uint8_t flash; 
uint16_t num1,num2;
volatile uint16_t runstate; 
volatile int32_t ANGLE;
volatile int32_t speed,location;

PID_t angle_pid={
.kp=1.9,
.ki=0,
.kd=0,

.out_max=100,
.out_min=-100,
.inte_max=1000,
.target=middle_angle,


};

 PID_t location_pid=
 {
    .kp=0.6,
    .ki=0,
    .kd=0,
    .out_max=100,
    .out_min=-100,
    .inte_max=1000,
    .target=0

 };
int main(void)
{
    LED_Init();   
    KEY_Init();   
    OLED_Init(); 
    motor_Init();
    encoder_Init();
    adc_Init();

    timer1_Init();
    
    while (1)
    {
        
        if(key_check(key_down))
       {
         runstate=!runstate;
       }
       OLED_ShowStringAt(0, 0,"angle", OLED_FONT_6X8, OLED_MODE_NORMAL);
       OLED_ShowStringAt(1, 0,"kp", OLED_FONT_6X8, OLED_MODE_NORMAL);
       OLED_ShowFloatAt(1, 3, angle_pid.kp,2, OLED_FONT_6X8  ,OLED_MODE_NORMAL);
       OLED_ShowStringAt(2, 0,"ki", OLED_FONT_6X8, OLED_MODE_NORMAL);
       OLED_ShowFloatAt(2, 3, angle_pid.ki,2, OLED_FONT_6X8  ,OLED_MODE_NORMAL);
       OLED_ShowStringAt(3, 0,"kd", OLED_FONT_6X8, OLED_MODE_NORMAL);
       OLED_ShowFloatAt(3, 3, angle_pid.kp,2, OLED_FONT_6X8  ,OLED_MODE_NORMAL);
     


       OLED_ShowStringAt(0, 9,"loc", OLED_FONT_6X8, OLED_MODE_NORMAL);
       OLED_ShowFloatAt(1, 9, location_pid.kp,2, OLED_FONT_6X8  ,OLED_MODE_NORMAL);
       OLED_ShowFloatAt(2, 9, angle_pid.ki,2, OLED_FONT_6X8,OLED_MODE_NORMAL);
       OLED_ShowFloatAt(3, 9, angle_pid.kp,2, OLED_FONT_6X8,OLED_MODE_NORMAL);
       OLED_RefreshGRAM();
        // keynum = key_get_num();
        // if(keynum==1)
        // {
        //     flash=!flash;
        // }
        // if(flash)
        // {
        //     if((timer1_GetTick() % 1000) < 500)
        //     {
        //         LED_On();
        //     }
        //     else
        //     {
        //         LED_Off();
        //     }
        // }
        // else
        // {
        //     LED_Off();
        // }
    }


    }



void timer1_UserHandler(void)
{
    static uint16_t count1,count2;
     key_tick();//非阻塞方式按键
     ANGLE=adc_ReadMillivolts();
     speed=encoder_GetSpeed();
     location+=speed;
 if(!(ANGLE>middle_angle-middle_rance && ANGLE<middle_angle+middle_rance))
    {
    runstate=0;

            }
        if(runstate)
{
          count1++;//内环角度环分频
            if(count1>=5)
  {
    count1=0;
    angle_pid.actual=ANGLE;
    motor_Setpwm((int16_t)PID_updata(&angle_pid));
        }

    /*外环位置环分频*/
  count2++;
if(count2>=50)
{
    count2=0;
    location_pid.actual=location;
    angle_pid.target=middle_angle + PID_updata(&location_pid);


}
    

}
else 
{
 motor_Stop();
}

}

