//***************HC-SR04超声波传感器****************************
const int TrigPin = 3;  //SD1/S1 (RX GPIO3)
const int EchoPin = 15;  //D8 GPIO15
float duration; //声波传输时间
float distance; //距离

//****************DHT11温湿度传感器*****************************
#include <SimpleDHT.h>
const int DHT11_PIN = D0; //接D0 GPIO16
byte temperature = 0; //温度
byte humidity = 0;    //湿度
String thStr = "null"; //温湿度字符串
SimpleDHT11 dht11(DHT11_PIN);

//**************HX711压力称重**********************************
#include "HX711.h"
const int LOADCELL_DOUT_PIN = D4; // D4 GPIO2
const int LOADCELL_SCK_PIN = 3; // RX GPIO3
HX711 loadcell;
const long LOADCELL_DIVIDER = 604105; //校准参数, 以kg为单位校准的
float weight = 0; //读取的重量

//******************1.44寸TFT显示屏****************************
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h> 
#include <SPI.h>
#define TFT_CS     D1   //D1 GPIO5
#define TFT_RST    D2   //D2 GPIO4
#define TFT_DC     D3   //D3 GPIO0
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
int i = 0;

void setup() {
  Serial.begin(9600); //设置输出串口波特率
  Serial.println("初始化中...");
  pinMode(TrigPin, OUTPUT); //初始超声波传感器,设置trigPin引脚为输出
  pinMode(EchoPin, INPUT); // 设置echoPin引脚为输入
  delay(500);
  
  tft.initR(INITR_144GREENTAB); //初始1.44寸显示屏
  tft.fillScreen(ST7735_BLACK); //刷屏, 设置背景黑色
  delay(500);
  
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); //初始称重传感器
  loadcell.set_scale(LOADCELL_DIVIDER);
  loadcell.tare();  //毛皮重量
  delay(2000);
}

void loop() {
  tft.fillScreen(ST7735_BLACK); //刷屏, 重新显示
  
  printToTFT(20, 10, 1, ST7735_RED, "num: "+String(i)); //打印显示自增数字
  i++;
  delay(500);

  distance = getDistance(); //获取超声波的距离
  printToTFT(20, 20, 1, ST7735_RED, "Distance: "+String(distance,1)+"cm"); //打印显示距离
  delay(500);
  
  weight = getWeight();  //获取在传感器上的重物重量 
  printToTFT(20, 30, 1, ST7735_RED, "Weight: "+String(getWeight(), 3)+"kg"); //打印显示重量
  delay(500);  //延时500ms

  thStr = getTemperatureAndHumidity(); //获取温湿度传感器的值
  printToTFT(20, 40, 1, ST7735_RED, "T-H: "+thStr); //打印显示温湿度
  delay(500);  //延时500ms
}

void printToTFT(int x, int y, int textSize, uint16_t color, String text){ //打印到TTF显示屏的函数
  tft.setCursor(x, y);         //设置光标的位置
  tft.setTextSize(textSize);   //文字大小
  tft.setTextColor(color);     //文字颜色
  tft.print(text);             //打印要显示的内容
}

float getWeight(){ //称重函数, 获取重量
    if (loadcell.wait_ready_timeout(3000)) { //非阻塞模式
        return loadcell.get_units(10);
    } else {
        return weight; //如果延迟3s未获取到值, 就返回上次成功获取到的值
    }
}

float getDistance(){ //获取CH-SR04超声波的距离
  digitalWrite(TrigPin, LOW); // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);// Sets the trigPin on HIGH state for 10 ms
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  duration = pulseIn(EchoPin, HIGH); //读取声波来回的时间    
  return duration*0.034/2.0; //时间*声速 / 2得到距离
 }

 String getTemperatureAndHumidity(){ //获取DHT11的温度和湿度
  int waitTime = 0;
  while(dht11.read(&temperature, &humidity, NULL) != SimpleDHTErrSuccess){ //如果读取失败
      delay(100); waitTime+=100; //等待100ms再重新读取
      if(waitTime > 2000 ){ //如果超过2秒未获取到
      return thStr; //返回上次成功的读数值, 避免阻塞
    }
  }
  return String((int)temperature) + "*c " + String((int)humidity) + "H";
 }