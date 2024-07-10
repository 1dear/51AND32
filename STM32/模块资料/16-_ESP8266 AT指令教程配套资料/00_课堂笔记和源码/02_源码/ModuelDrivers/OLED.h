#ifndef OLED_H
#define OLED_H

#include "stm32f1xx_hal.h"

#define OLED_ADDRESS    0x78        // DC#=0, address=0b0111 1000
extern void OLED_Init(void);
extern void OLED_Clear(void);
extern void OLED_PutChar(int page, int col, char c);
extern void OLED_Print(int page, int col, char *str);
extern void OLED_PutNumber(int page, int col, int num);
extern void OLED_PrintNumber(int page, int col, uint8_t num);

#endif

