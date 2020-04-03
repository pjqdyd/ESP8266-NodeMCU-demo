/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : 3_4_8_SPIFFS_File_Upload_Server
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : CYNO朔
日期/Date（YYYYMMDD）     : 20200211
程序目的/Purpose          : 建立网络服务器，允许用户通过网页将文件上传到SPIFFS
-----------------------------------------------------------------------
修订历史/Revision History  
日期/Date    作者/Author      参考号/Ref    修订说明/Revision Description
20200218     CYNO朔             0.01        一致性调整
-----------------------------------------------------------------------
本示例程序为太极创客团队制作的《零基础入门学用物联网》中示例程序。
该教程为对物联网开发感兴趣的朋友所设计和制作。如需了解更多该教程的信息，请参考以下网页：
http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/
***********************************************************************/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <FS.h>  

ESP8266WiFiMulti wifiMulti;     // 建立ESP8266WiFiMulti对象,对象名称是 'wifiMulti'

ESP8266WebServer esp8266_server(80);    // 建立网络服务器对象，该对象用于响应HTTP请求。监听端口（80）      

File fsUploadFile;              // 建立文件对象用于闪存文件上传

void setup() {
  Serial.begin(9600);        
  Serial.println("");

  wifiMulti.addAP("ssid_from_AP_1", "your_password_for_AP_1"); // 将需要连接的一系列WiFi ID和密码输入这里
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2"); // ESP8266-NodeMCU再启动后会扫描当前网络
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3"); // 环境查找是否有这里列出的WiFi ID。如果有
  Serial.println("Connecting ...");                            // 则尝试使用此处存储的密码进行连接。

  int i = 0;  
  while (wifiMulti.run() != WL_CONNECTED) { // 尝试进行wifi连接。
    delay(1000);
    Serial.print(i++); Serial.print('.');
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
  
  esp8266_server.on("/upload.html",   // 如果客户端通过upload页面
                    HTTP_POST,        // 向服务器发送文件(请求方法POST)
                    respondOK,        // 则回复状态码 200 给客户端
                    handleFileUpload);// 并且运行处理文件上传函数

  esp8266_server.onNotFound(handleUserRequest);

  esp8266_server.begin();                           // 启动网站服务
  Serial.println("HTTP server started");
}

void loop() {
  esp8266_server.handleClient();
}

// 处理上传文件函数
void handleFileUpload(){  
  
  HTTPUpload& upload = esp8266_server.upload();
  
  if(upload.status == UPLOAD_FILE_START){                     // 如果上传状态为UPLOAD_FILE_START
    
    String filename = upload.filename;                        // 建立字符串变量用于存放上传文件名
    if(!filename.startsWith("/")) filename = "/" + filename;  // 为上传文件名前加上"/"
    Serial.println("File Name: " + filename);                 // 通过串口监视器输出上传文件的名称

    fsUploadFile = SPIFFS.open(filename, "w");            // 在SPIFFS中建立文件用于写入用户上传的文件数据
    
  } else if(upload.status == UPLOAD_FILE_WRITE){          // 如果上传状态为UPLOAD_FILE_WRITE      
    
    if(fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize); // 向SPIFFS文件写入浏览器发来的文件数据
      
  } else if(upload.status == UPLOAD_FILE_END){            // 如果上传状态为UPLOAD_FILE_END 
    if(fsUploadFile) {                                    // 如果文件成功建立
      fsUploadFile.close();                               // 将文件关闭
      Serial.println(" Size: "+ upload.totalSize);        // 通过串口监视器输出文件大小
      esp8266_server.sendHeader("Location","/success.html");  // 将浏览器跳转到/success.html（成功上传页面）
      esp8266_server.send(303);                               // 发送相应代码303（重定向到新页面） 
    } else {                                              // 如果文件未能成功建立
      Serial.println("File upload failed");               // 通过串口监视器输出报错信息
      esp8266_server.send(500, "text/plain", "500: couldn't create file"); // 向浏览器发送相应代码500（服务器错误）
    }    
  }
}

//回复状态码 200 给客户端
void respondOK(){
  esp8266_server.send(200);
}

// 处理用户浏览器的HTTP访问
void handleUserRequest(){
                              
  // 获取用户请求网址信息
  String webAddress = esp8266_server.uri();
  
  // 通过handleFileRead函数处处理用户访问
  bool fileReadOK = handleFileRead(webAddress);

  // 如果在SPIFFS无法找到用户访问的资源，则回复404 (Not Found)
  if (!fileReadOK){                                                 
    esp8266_server.send(404, "text/plain", "404 Not Found"); 
  }
}

bool handleFileRead(String path) {            //处理浏览器HTTP访问

  if (path.endsWith("/")) {                   // 如果访问地址以"/"为结尾
    path = "/index.html";                     // 则将访问地址修改为/index.html便于SPIFFS访问
  } 
  
  String contentType = getContentType(path);  // 获取文件类型
  
  if (SPIFFS.exists(path)) {                     // 如果访问的文件可以在SPIFFS中找到
    File file = SPIFFS.open(path, "r");          // 则尝试打开该文件
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
