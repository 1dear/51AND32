#ifndef __ESP_01S_Order_H
#define __ESP_01S_Order_H         //
/*一开始的启动，可能会自动连接上热点，
会有以下输出，并没有OK
WIFI CONNECTED
WIFI GOT IP
*/


#define CMD_TEST "AT"            // 测试 AT 启动
/*返回
OK*/

#define CMD_VERSION "AT+GMR"     // 查看版本信息
/*
返回
AT version:1.7.1.0(Jul 15 2019 16:58:04)
SDK version:3.0.1(78a3e33)
compile time:Feb 14 2020 09:19:42
OK
*/

// 客户端模式
#define CMD_SET_WIFI_MODE "AT+CWMODE=1"    // 选择 WIFI 应用模式
/*返回
OK
*/
#define CMD_RESET_MODULE "AT+RST"         // 重启模块

/*重启过后，会有一堆东西，然后输出ready，如果第二次连接且有wifi会自动连接， */
#define CMD_LIST_ACCESS_POINTS "AT+CWLAP" // 列出当前可用路由器接入点
#define CMD_JOIN_ACCESS_POINT "AT+CWJAP"  // 加入接入点
#define CMD_LEAVE_ACCESS_POINT "AT+CWQAP" // 退出接入点
#define CMD_TCP_CONNECT "AT+CIPSTART"     // 建立 TCP 连接服务器
#define CMD_TCP_CLOSE "AT+CIPCLOSE"       // 关闭 TCP
#define CMD_GET_LOCAL_IP "AT+CIFSR"       // 获取本地 IP 地址
#define CMD_SET_MODULE_MODE "AT+CIPMODE"  // 设置模块传输模式
/*返回
OK*/
#define CMD_SEND_DATA "AT+CIPSEND"        // 发送数据

// 服务器模式
#define CMD_SET_AP_MODE "AT+CWSAP"       // 查询和设置 AP（server） 模式下的WIFI名称、密码、加密方式
#define CMD_LIST_CONNECTED_DEVICES "AT+CWLIF" // 查看已接入设备的 IP地址
#define CMD_ENABLE_MULTI_CONNECTION "AT+CIPMUX" // 启动多连接
#define CMD_CONFIGURE_SERVER "AT+CIPSERVER"    // 配置为服务器默认端口333
#define CMD_SET_SERVER_TIMEOUT "AT+CIPSTO"     // 设置服务器超时时间
#define CMD_GET_CONNECTION_STATUS "AT+CIPSTATUS" // 获得连接状态
/*
CONNECT

OK
*/

#endif
