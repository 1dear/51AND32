#ifndef WEB_HTML_PAGE_H_
#define WEB_HTML_PAGE_H_

#define FONT_AWESOME_PAGE  "\
<!DOCTYPE html>\
<html>\
<head>\
<meta charset='UTF-8'>\
<title>百问网智能家居控制台</title>\r\n\
<link rel=\"stylesheet\" href=\"https://cdn.staticfile.org/font-awesome/4.7.0/css/font-awesome.css\">\
<link rel=\"stylesheet\" href=\"http://pay.100ask.net:8080/html/100ask.css\">\
</head>\
<body class=\"HolyGrail\">\
  <div class=\"HolyGrail-body\">\
    <main id=\"jscode\" class=\"HolyGrail-content\"></main>\
    <nav class=\"HolyGrail-nav\">\
		<span id=\"info\"></span>\
		<span id=\"weather\"></span>\
		<p id=\"ad\" class=\"ad\"></p>\
	</nav>\
  </div>\
<script>\
room_ayyy = ['客厅','主卧','次卧','客房','厨房','厕所'];\
room_dev_arry =[\
[['box','r1-1-off','fa-lightbulb-o','灯'],['box','r1-2-off','fa-modx','风扇'],['box','r1-3-off','fa-snowflake-o','空调'],['box','r1-4-off','fa-tv','电视机']],\
[['box','r2-1-off','fa-lightbulb-o','灯'],['box','r2-2-off','fa-snowflake-o','空调'],['box','r2-3-off','fa-modx','风扇']],\
[['box','r3-1-off','fa-lightbulb-o','灯'],['box','r3-2-off','fa-snowflake-o','空调'],['box','r3-3-off','fa-modx','风扇']],\
[['box','r4-1-off','fa-lightbulb-o','灯'],['box','r4-2-off','fa-snowflake-o','空调'],['box','r4-3-off','fa-modx','风扇']],\
[['box','r5-1-off','fa-lightbulb-o','灯'],['box','r5-2-off','fa-recycle','排气扇'],['box','r5-3-off','fa-recycle','抽油烟机']],\
[['box','r6-1-off','fa-lightbulb-o','灯'],['box','r6-2-off','fa-recycle','排气扇'],['box','r6-3-off','fa-bathtub','热水器']]];\
</script>\
<script src=\"http://pay.100ask.net:8080/html/100ask.js\"></script>\
</body>\
</html>\
"


#define FONT_AWESOME_PAGE1  "\
<!DOCTYPE html>\
<html>\
<head>\
<meta charset=\"utf-8\">\
<title>百问网智能家居控制台</title>\
<link rel=\"stylesheet\" href=\"https://cdn.staticfile.org/font-awesome/4.7.0/css/font-awesome.css\">\
<link rel=\"stylesheet\" href=\"http://pay.100ask.net:8080/html/100ask.css\">\
</head>\
<body class=\"HolyGrail\">\
  <div class=\"HolyGrail-body\">\
    <main id=\"jscode\" class=\"HolyGrail-content\"></main>\
    <nav class=\"HolyGrail-nav\">\
		<span id=\"info\"></span>\
		<span id=\"weather\"></span>\
		<p id=\"ad\" class=\"ad\"></p>\
	</nav>\
  </div>\
"

#if 1
#define FONT_AWESOME_PAGE2  "\
<script>\
room_ayyy = [' '];\
room_dev_arry =[\
[['box','dev1-off','fa-lightbulb-o','白灯'],['box','dev2-off','fa-lightbulb-o','蓝灯'],['box','dev3-off','fa-lightbulb-o','绿灯'],['box','dev4-off','fa-modx','风扇'],['box','dev5-off','fa-home','离开']]];\
</script>\
"
#endif

#define FONT_AWESOME_PAGE3  "\
<script src=\"http://pay.100ask.net:8080/html/100ask.js\"></script>\
</body>\
</html>\
"


/* 
 * web配网页面html代码
 */
#define HOME_WIFI_SET_PAGE "\
<!DOCTYPE html>\r\n\
<html><head><title>百问网WEB配网</title>\r\n\
<meta charset='UTF-8'>\r\n\
<meta name='viewport' content='width=device-width, initial-scale=1.0'/>\r\n\
<style type='text/css'>\r\n\
.login-page {\r\n\
  width: 360px;\r\n\
  padding: 8% 0 0;\r\n\
  margin: auto;}\r\n\
.form {\r\n\
  position: relative;\r\n\
  z-index: 1;\r\n\
  background: #FFFFFF;\r\n\
  max-width: 360px;\r\n\
  margin: 0 auto 100px;\r\n\
  padding: 45px;\r\n\
  text-align: center;\r\n\
  box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);}\r\n\
.form input {\r\n\
  font-family: 'Roboto', sans-serif;\r\n\
  outline: 0;\r\n\
  background: #f2f2f2;\r\n\
  width: 100%;\r\n\
  border: 0;\r\n\
  margin: 0 0 15px;\r\n\
  padding: 15px;\r\n\
  box-sizing: border-box;\r\n\
  font-size: 14px;}\r\n\
.form button {\r\n\
  font-family: 'Roboto', sans-serif;\r\n\
  text-transform: uppercase;\r\n\
  outline: 0;\r\n\
  background: #4CAF50;\r\n\
  width: 100%;\r\n\
  border: 0;\r\n\
  padding: 15px;\r\n\
  color: #FFFFFF;\r\n\
  font-size: 14px;\r\n\
  -webkit-transition: all 0.3 ease;\r\n\
  transition: all 0.3 ease;\r\n\
  cursor: pointer;}\r\n\
.form button:hover,.form button:active,.form button:focus {\r\n\
  background: #43A047;}\r\n\
.form .message {\r\n\
  margin: 15px 0 0;\r\n\
  color: #b3b3b3;\r\n\
  font-size: 12px;}\r\n\
body {\r\n\
  background: #76b852;}\r\n\
</style>\r\n\
<body><div class='login-page'>\r\n\
	<div class='form'>\r\n\
		<form name='input' action='/' method='POST'>\r\n\
			<input name='ssid' placeholder='WiFi名称(SSID)'>\r\n\
			<input name='password' type='password' placeholder='WiFi密码(PASSWORD)'>\r\n\
			<input name='n' type='hidden'>\r\n\
			<button type='submit'>保存</button>\r\n\
			<p class='message'>Copyright © 2019-2021 深圳百问网科技有限公司 All Rights Reserved.<br/><a href=\"www.100ask.org\">www.100ask.org</a></p>\r\n\
		</form>\r\n\
    </div></div>\r\n\
</body>\r\n\
</html>\r\n\
";

#if 0
/* 
 * 初级版web配网页面html代码
 */
#define HOME_WIFI_SET_PAGE "\
<!DOCTYPE html>\r\n\
<html lang='en'>\r\n\
<head>\r\n\
  <meta charset='UTF-8'>\r\n\
  <meta name='viewport' content='width=device-width, initial-scale=1.0'>\r\n\
  <title>Document</title>\r\n\
</head>\r\n\
<body style=\"background-color:#8bc16d;\">\r\n\
  <form name='input' action='/' method='POST'>\r\n\
        wifi名称: <br>\r\n\
        <input type='text' name='ssid'><br>\r\n\
        wifi密码:<br>\r\n\
        <input type='text' name='password'><br>\r\n\
        <input type='submit' value='保存'>\r\n\
    </form>\r\n\
</body>\r\n\
</html>\r\n\
";

/* 
 * 高级版web配网页面html代码
 */
#define HOME_WIFI_SET_PAGE "\
<html>\
<head>\
<title>百问网WIFI配网</title>\
<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>\
<meta name='viewport' content='width=device-width, initial-scale=1.0, user-scalable=no, minimum-scale=1.0, maximum-scale=1.0'/>\
<head>\
<link rel=\"stylesheet\" href=\"http://pay.100ask.net:8080/html/100ask_wifi_set.css\">\
</head>\
<script src=\"http://pay.100ask.net:8080/html/100ask_wifi_set.js\"></script>\
</head>\
<body>\
	<div class='login-page'>\
		<div class='form'>\
			<input id='name' placeholder='WiFi名称 (SSID)'>\
			<input type='password' id='pass' placeholder='WiFi密码 (PASSWORD)'>\
			<button onclick='javascript:sendSetWifi();'>连接</button>\
			<p class='message'>Copyright © 2019-2021 深圳百问网科技有限公司 All Rights Reserved.<br/><a href=\"www.100ask.org\">www.100ask.org</a></p>\
		</div>\
	</div>\
</body>\
</html>\
";	

#endif
#endif /* WEB_HTML_PAGE_H_ */
