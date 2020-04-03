### ESP8266-NodeMCU-Lua-V3 (CH340)物联网开发板代码案例

#### 开发工具:

>1.ESP8266-NodeMCU-Lua-V3开发板<br>
>2.Micro-USB数据线<br>
>3.CH341SER连接驱动<br>
>4.Arduino IDE<br>

#### 开发准备:
 1. 电脑安装对应版本的CH341SER连接驱动(注意如果开发板是CP2102版本,就安装cp210x_VCP驱动)
 2. 配置Arduino IDE: 文件>首选项>附件开发板网址(填写:http://arduino.esp8266.com/stable/package_esp8266com_index.json)
 3. 配置Arduino IDE的ESP8266插件: 工具>开发板>开发板管理器..>搜索ESP8266>安装esp8266 2.6.3
 开发板插件包
 4. 使用USB线连接电脑和ESP8266开发板, 确保在我的电脑>管理>设备管理器>端口(COM和LPT)>(有连接的设备(COM3))
 5. 配置Arduino IDE: 工具>开发板>选中NodeMCU 1.0 (ESP-12E Module)
 6. 配置Arduino IDE: 工具>端口>选中COM3 (对应设备管理器下端口连接的设备)
 7. Arduino IDE打开对应的代码进行上传烧录固件即可

#### 代码目录:
 ```
      ├─1-Init                            初始的代码
      ├─2-Blink                           控制板载的LED灯闪烁
      ├─3-AccessPoint-Wifi                开启Wifi接入点模式(开启热点)
      ├─4-Connect-Wifi                    开启Wifi无线终端模式(连接路由器wifi)
      ├─5-Connect-Wifi-Multi              开启Wifi无线终端模式(从多个中连接信号强的wifi)
      ├─6-WebServer                       开启Web服务,监听80端口
      ├─7-WebServer-Light                 开启Web服务,监听80端口,控制板载LED的亮灭
      ├─8-WebServer-Pin-State             开启Web服务,监听80端口,查看D3引脚的状态
      ├─9-WebServer-Pin-State-AutoRefresh 开启Web服务,监听80端口,查看D3引脚的状态,自动刷新
      ├─10-Flash-Write                    向闪存中写入文本文件
      ├─11-Flash-Read                     读取闪存中的文本文件
      ├─12-Flash-Append                   向闪存文件中添加字符
      ├─13-Flash-Folder-Read              读取闪存目录
      ├─14-Flash-Remove                   删除闪存中的文件
      ├─15-Flash-Info                     获取闪存信息
      ├─16-SPLFFS-File-Server             上传网页web文件到闪存,并作为Web服务
      ├─17-SPLFFS-File-Server-Pin         上传网页web文件到闪存,并作为Web服务控制引脚(板载LED)
      ├─.gitignore                        .gitignore文件
      └─README.md                         README.md文件
 ```

#### 提示
1. Arduino IDE开启串口监视器可以查看输出打印日志.
2. 通过Arduino IDE向ESP8266闪存中存入任意文件,需要安装[Arduino-ESP8266FS-Plugin插件](https://github.com/esp8266/arduino-esp8266fs-plugin)
   安装插件后重启IDE,在工具>ESP8266 Sketch Data Upload会将当前打开文件的同级data文件夹上传