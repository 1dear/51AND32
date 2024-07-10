#ifndef __ESP_01S_H
#define __ESP_01S_H
#define WIFI_SSID "vivoS15"
#define WIFI_PASSWORD "3430295583"
#define SERVER_ADDRESS	"192.168.98.143"
#define PORT_NUMBER 8081


#define OK 1
#define ERROR 0
void ESP_01S_Init();
void ESP_01S_SendString(char * str);
void TCP_Connect();
void TCP_CIP_SEND();

void json_DHT11(char *data,uint8_t Tvalue,uint8_t Hvalue);
void make_request(char* request,char *data);
#endif