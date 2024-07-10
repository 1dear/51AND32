#ifndef OLED_LAYOUT_H
#define OLED_LAYOUT_H

#include "stm32f1xx_hal.h"

extern void OLED_ClearScreen(void);
extern void OLED_DispSoftwareVersion(void);
extern void OLED_DispChipTemperature(void);
extern void OLED_DispEnvironmentParameter(void);
extern void OLED_DispLedStatus(uint8_t r, uint8_t g, uint8_t b);
extern void OLED_DispIP(const char *ip);
extern void OLED_DispPort(const char *port);
extern void OLED_DispSoftAP(const char *ssid, const char *passwd);
extern void OLED_DispLogo(void);

#endif

