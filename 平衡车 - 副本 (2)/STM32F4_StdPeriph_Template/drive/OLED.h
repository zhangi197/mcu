/*
 * OLED.h
 * SSD1306 128x64 硬件 SPI 驱动 (STM32 标准库版)
 * 架构：统一 GRAM 缓冲，所有绘制只改内存，手动刷新
 *
 * 使用说明：
 *  1. 修改下方"用户配置区"的宏定义，匹配实际接线
 *  2. 确保工程已添加 stm32f10x_stdperiph_driver（或其他系列对应库）
 *  3. 在 main() 中先调用系统时钟配置，再调用 OLED_Init()
 *  4. 绘制完成后调用 OLED_RefreshGRAM() 刷新到屏幕
 */

#ifndef __OLED_H
#define __OLED_H

#include "stm32f4xx.h"
#include <stdint.h>

/* ===================== 用户配置区 ===================== */
/* 请根据实际接线修改以下宏定义 */

/* SPI 外设选择 (SPI1 / SPI2) */
#define OLED_SPI                SPI1
#define OLED_USE_SPI1           1

/* SPI 与 GPIO 时钟使能（根据实际端口修改） */
#define OLED_SPI_CLK_ENABLE()   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE)
#define OLED_GPIO_CLK_ENABLE()  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE)

/* CS 片选引脚 */
#define OLED_CS_PORT            GPIOA
#define OLED_CS_PIN             GPIO_Pin_4

/* DC 数据/命令引脚 */
#define OLED_DC_PORT            GPIOA
#define OLED_DC_PIN             GPIO_Pin_3

/* RES 复位引脚 */
#define OLED_RES_PORT           GPIOA
#define OLED_RES_PIN            GPIO_Pin_2

/* 屏幕参数 */
#define OLED_WIDTH              128
#define OLED_HEIGHT             64
#define OLED_PAGES              8

/* 颜色 */
#define OLED_COLOR_BLACK        0
#define OLED_COLOR_WHITE        1

/* 显示模式 */
#define OLED_MODE_NORMAL        0
#define OLED_MODE_REVERSE       1

/* 字体大小 */
#define OLED_FONT_6X8           0
#define OLED_FONT_8X16          1

/* ===================== 函数声明 ===================== */

/* 初始化与刷新 */
void OLED_Init(void);
void OLED_RefreshGRAM(void);

/* GRAM 操作（只改内存，不刷新屏幕） */
void OLED_ClearGRAM(void);
void OLED_FillGRAM(uint8_t color);

/* 直接刷新到屏幕的便捷函数 */
void OLED_ClearScreen(void);
void OLED_FillScreen(uint8_t color);

/* 显示开关与对比度 */
void OLED_DisplayOn(void);
void OLED_DisplayOff(void);
void OLED_SetContrast(uint8_t contrast);

/* 像素与图形（写 GRAM） */
void OLED_SetPixel(uint8_t x, uint8_t y, uint8_t color);
void OLED_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
void OLED_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
void OLED_DrawFillRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
void OLED_DrawBMP(uint8_t x0, uint8_t y0_page, uint8_t x1, uint8_t y1_page, const uint8_t *bmp);

/* 6x8 字体 - 像素坐标 (x: 0~127, y_page: 0~7) */
void OLED_ShowChar(uint8_t x, uint8_t y_page, char chr, uint8_t mode);
void OLED_ShowString(uint8_t x, uint8_t y_page, const char *str, uint8_t mode);
void OLED_ShowNum(uint8_t x, uint8_t y_page, int32_t num, uint8_t mode);

/* 扩展字体 - 像素坐标，支持 6x8 / 8x16 */
void OLED_ShowCharEx(uint8_t x, uint8_t y_page, char chr, uint8_t size, uint8_t mode);
void OLED_ShowStringEx(uint8_t x, uint8_t y_page, const char *str, uint8_t size, uint8_t mode);

/* 行列坐标（At = At position）(row: 0~7, col: 视字体宽度而定) */
void OLED_ShowCharAt(uint8_t row, uint8_t col, char chr, uint8_t size, uint8_t mode);
void OLED_ShowStringAt(uint8_t row, uint8_t col, const char *str, uint8_t size, uint8_t mode);
void OLED_ShowNumAt(uint8_t row, uint8_t col, int32_t num, uint8_t size, uint8_t mode);
void OLED_ShowFloatAt(uint8_t row, uint8_t col, float f, uint8_t decimal, uint8_t size, uint8_t mode);

/* 演示函数 */
void OLED_TestScreen(void);
void OLED_Demo(void);

#endif /* __OLED_H */
