### ESP8266-NodeMCU-Lua-V3 (CH340)物联网开发板代码案例

#### 开发工具:

>1.CH341SER连接驱动<br>
>2.Arduino IDE<br>
>3.ESP8266-NodeMCU-Lua-V3开发板<br>
>4.Micro-USB数据线<br>
>5.TFT 1.44寸液晶显示屏<br>
>6.DHT11 温湿度传感器<br>
>7.HX711 5KG压力称重传感器<br>
>8.HC-SR04 超声波距离传感器
>9.杜邦线若干<br>

#### 开发准备:
 1. 电脑安装对应版本的[CH341SER](https://github.com/juliagoda/CH341SER)连接驱动(注意如果开发板是CP2102版本,就安装cp210x_VCP驱动)
 2. 配置Arduino IDE: 文件>首选项>附件开发板网址(填写:http://arduino.esp8266.com/stable/package_esp8266com_index.json)
 3. 配置Arduino IDE的ESP8266插件: 工具>开发板>开发板管理器..>搜索ESP8266>安装esp8266 2.6.3
 开发板插件包
 4. 使用USB线连接电脑和ESP8266开发板, 确保在我的电脑>管理>设备管理器>端口(COM和LPT)>(有连接的设备(COM3))
 5. 配置Arduino IDE: 工具>开发板>选中NodeMCU 1.0 (ESP-12E Module)
 6. 配置Arduino IDE: 工具>端口>选中COM3 (对应设备管理器下端口连接的设备)
 7. Arduino IDE打开对应的代码进行上传烧录固件即可

#### 代码目录:
 ```
      ├─01-Init                            初始的代码
      ├─02-Blink                           控制板载的LED灯闪烁
      ├─03-AccessPoint-Wifi                开启Wifi接入点模式(开启热点)
      ├─04-Connect-Wifi                    开启Wifi无线终端模式(连接路由器wifi)
      ├─05-Connect-Wifi-Multi              开启Wifi无线终端模式(从多个中连接信号强的wifi)
      ├─06-WebServer                       开启Web服务,监听80端口
      ├─07-WebServer-Light                 开启Web服务,监听80端口,控制板载LED的亮灭
      ├─08-WebServer-Pin-State             开启Web服务,监听80端口,查看D3引脚的状态
      ├─09-WebServer-Pin-State-AutoRefresh 开启Web服务,监听80端口,查看D3引脚的状态,自动刷新
      ├─10-Flash-Write                     向闪存中写入文本文件
      ├─11-Flash-Read                      读取闪存中的文本文件
      ├─12-Flash-Append                    向闪存文件中添加字符
      ├─13-Flash-Folder-Read               读取闪存目录
      ├─14-Flash-Remove                    删除闪存中的文件
      ├─15-Flash-Info                      获取闪存信息
      ├─16-SPIFFS-File-Server              上传网页web文件到闪存,并作为Web服务
      ├─17-SPIFFS-File-Server-Pin          上传网页web文件到闪存,并作为Web服务控制引脚(板载LED亮灭)
      ├─18-SPIFFS-File-Server-PWM          上传网页web文件到闪存,并通过Web页面传值控制引脚的PWM(板载LED的亮度)
      ├─19-SPIFFS-File-Server-Value        上传网页web文件到闪存,并通过Web页面传多个值到ESP8266
      ├─20-SPIFFS-File-Server-Pin-A0       上传网页web文件到闪存,并通过Web页面Ajax控制板载LED,获取A0引脚的读数
      ├─21-SPIFFS-File-Server-PWM-View     上传网页web文件到闪存,并通过Jquery的视图控件控制引脚的PWM(板载LED的亮度)
      ├─22-SPIFFS-File-Server-Analog-View  上传网页web文件到闪存,并通过Jquery的仪表盘视图控件显示引脚的输入数值
      ├─23-SPIFFS-File-Server-Web-Upload   上传网页web文件到闪存,通过前端Web页面实现上传文件到闪存
      ├─24-TFT-1.44inch-Display            1.44寸TFT液晶显示屏的使用
      ├─25-DHT11                           DHT11温湿度传感器的使用
      ├─26-HX711-5KG                       HX711压力称重传感器的使用(5KG)
      ├─27-HC-SR04                         HC-SR04超声波测距传感器的使用
      ├─28-ESP8266-Sensors                 ESP8266同时整合连接1.44TFT, DHT11, HX711, HC-SR04
      ├─.gitignore                         .gitignore文件
      └─README.md                          README.md文件
 ```

#### 提示
1. Arduino IDE开启串口监视器可以查看输出打印日志(波特率:9600 = Serial.begin(9600);).
2. 通过Arduino IDE向ESP8266闪存中存入任意文件,需要安装[Arduino-ESP8266FS-Plugin插件](https://github.com/esp8266/arduino-esp8266fs-plugin)
   安装插件后重启IDE,在工具>ESP8266 Sketch Data Upload会将当前打开文件的同级data文件夹上传.
3. Arduino IDE安装库文件可以通过项目>加载库>管理库>进行搜索安装, 也可以直接将库文件复制到
   文件>首选项>项目文件夹位置/libiaries目录下.

 (基础参考: [文档](http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/))
