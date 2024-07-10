#include "oled_layout.h"
#include "OLED.h"
#include "main.h"

void OLED_ClearScreen(void)
{
    OLED_Clear();
}

void OLED_DispSoftwareVersion(void)
{    
    OLED_Print(0, 1, SOFT_VERSION);
}    
     
void OLED_DispChipTemperature(void)
{    
    OLED_Print(2, 1, "Chip:");
    OLED_PrintNumber(2, 1+40, 29); 
}    
     
void OLED_DispEnvironmentParameter(void)
{
    OLED_Print(4, 1, "H:"); 
    OLED_PrintNumber(4, 1+16, 78); 
    OLED_Print(4, 48, "T:");   
    OLED_PrintNumber(4, 48+16, 29);     
}   
    
void OLED_DispLedStatus(uint8_t r, uint8_t g, uint8_t b)
{    
    OLED_Print(6, 1, "R:");
    OLED_PrintNumber(6, 1+16, r);
    OLED_Print(6, 44, "G:");
    OLED_PrintNumber(6, 44+16, g);
    OLED_Print(6, 88, "B:");
    OLED_PrintNumber(6, 88+16, b);
}    
     
void OLED_DispIP(const char *ip)
{    
    OLED_Print(0, 1, "IP:");
    OLED_Print(0, 25, (char*)ip);
}    
void OLED_DispSoftAP(const char *ssid, const char *passwd)
{    
    OLED_Print(2, 1, "ssid:");
    OLED_Print(2, 41, (char*)ssid);
	OLED_Print(4, 1, "passwd:");
    OLED_Print(4, 54, (char*)passwd);
}   


void OLED_DispPort(const char *port)
{
    OLED_Print(2, 1, "Port:");
    OLED_Print(2, 41, (char*)port);
}

void OLED_DispLogo(void)
{
    OLED_Print(6, 1, "www.100ask.net");
}

