#ifndef __DHT11_H
#define __DHT11_H
int DHT11_GetData(uint8_t *DHT11_Data, int size, uint32_t* flag);
uint32_t DHT11_Init();
#endif
