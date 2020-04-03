/**********************************************************************
注意: 上传前需要点击Arduino IDE的工具>ESP8266 Sketch Data Upload进行将本文件同级data文件夹上传

程序目的/Purpose          : 
此程序用于演示如何通过网页控制LED引脚以及将A0引脚读数实时显示于网页中。
-----------------------------------------------------------------------
修订历史/Revision History  
日期/Date    作者/Author      参考号/Ref    修订说明/Revision Description
20200210      CYNO朔           0.02          改正了plane -> plain
20200211      CYNO朔           0.03          一致性调整
***********************************************************************/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <FS.h>

ESP8266WiFiMulti wifiMulti;     // 建立ESP8266WiFiMulti对象,对象名称是 'wifiMulti'

ESP8266WebServer esp8266_server(80);    // 建立网络服务器对象，该对象用于响应HTTP请求。监听端口（80）

void setup() {
  Serial.begin(9600);          // 启动串口通讯
  Serial.println("");

  pinMode(LED_BUILTIN, OUTPUT);   // 初始化NodeMCU控制板载LED引脚为OUTPUT
  digitalWrite(LED_BUILTIN, HIGH);// 初始化LED引脚状态
  
  wifiMulti.addAP("ssid_from_AP_1", "your_password_for_AP_1"); // 将需要连接的一系列WiFi ID和密码输入这里
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2"); // ESP8266-NodeMCU再启动后会扫描当前网络
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3"); // 环境查找是否有这里列出的WiFi ID。如果有
  Serial.println("Connecting ...");                            // 则尝试使用此处存储的密码进行连接。

  int i = 0;  
  while (wifiMulti.run() != WL_CONNECTED) { // 尝试进行wifi连接。
    delay(1000);
    Serial.print(i++); Serial.print(' ');
  }
  
  // WiFi连接成功后将通过串口监视器输出连接成功信息 
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // 通过串口监视器输出连接的WiFi名称
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // 通过串口监视器输出ESP8266-NodeMCU的IP

  if(SPIFFS.begin()){                       // 启动闪存文件系统
    Serial.println("SPIFFS Started.");
  } else {
    Serial.println("SPIFFS Failed to Start.");
  }     
 
  esp8266_server.on("/setLED", handleLED);
  esp8266_server.on("/readADC", handleADC);  
  
  esp8266_server.onNotFound(handleUserRequest); // 处理其它网络请求

  // 启动网站服务
  esp8266_server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  esp8266_server.handleClient();
}


void handleLED() {
 String ledState = "OFF";
 String LED_State = esp8266_server.arg("LEDstate"); //参考xhttp.open("GET", "setLED?LEDstate="+led, true);
 Serial.println(LED_State);
 
 if(LED_State == "1"){
  digitalWrite(LED_BUILTIN,LOW); //LED 点亮
  ledState = "ON"; //反馈参数
 } else {
  digitalWrite(LED_BUILTIN,HIGH); //LED 熄灭
  ledState = "OFF"; //反馈参数
 }
 
 esp8266_server.send(200, "text/plain", ledState); //发送网页
}

void handleADC() {
 int a = analogRead(A0);
 String adcValue = String(a);
 
 esp8266_server.send(200, "text/plain", adcValue); //发送模拟输入引脚到客户端ajax请求
}
 
// 处理用户浏览器的HTTP访问
void handleUserRequest() {         
     
  // 获取用户请求资源(Request Resource）
  String reqResource = esp8266_server.uri();
  Serial.print("reqResource: ");
  Serial.println(reqResource);
  
  // 通过handleFileRead函数处处理用户请求资源
  bool fileReadOK = handleFileRead(reqResource);

  // 如果在SPIFFS无法找到用户访问的资源，则回复404 (Not Found)
  if (!fileReadOK){                                                 
    esp8266_server.send(404, "text/plain", "404 Not Found"); 
  }
}

bool handleFileRead(String resource) {            //处理浏览器HTTP访问

  if (resource.endsWith("/")) {                   // 如果访问地址以"/"为结尾
    resource = "/index.html";                     // 则将访问地址修改为/index.html便于SPIFFS访问
  } 
  
  String contentType = getContentType(resource);  // 获取文件类型
  
  if (SPIFFS.exists(resource)) {                     // 如果访问的文件可以在SPIFFS中找到
    File file = SPIFFS.open(resource, "r");          // 则尝试打开该文件
    esp8266_server.streamFile(file, contentType);// 并且将该文件返回给浏览器
    file.close();                                // 并且关闭文件
    return true;                                 // 返回true
  }
  return false;                                  // 如果文件未找到，则返回false
}

// 获取文件类型
String getContentType(String filename){
  if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}
