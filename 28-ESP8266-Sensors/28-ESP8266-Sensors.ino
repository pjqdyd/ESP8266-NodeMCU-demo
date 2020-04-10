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
SimpleDHT11 dht11(DHT11_PIN);

//**************HX711压力称重**********************************
#include "HX711.h"
#define GapValue 610       ///该值需校准 每个称重传感器都有所不同
const int LOADCELL_DOUT_PIN = 1; //TX GPIO1
const int LOADCELL_SCK_PIN = D6; //D6 GPIO12
float weight = 0;
long HX711_Buffer = 0;
long weight_maopi = 0, weight_shiwu = 0; //毛皮, 四舍五入的重量
HX711 scale;

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
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); //初始称重传感器
  delay(2000);
  weight_maopi = getReadingByHX711(); //初始获取毛皮重量
}

void loop() {
  tft.fillScreen(ST7735_BLACK); //刷屏, 重新显示
  
  tft.setCursor(20,10);         //设置光标的位置
  tft.setTextSize(1);
  tft.setTextColor(ST7735_RED);
  tft.print("num: ");           //显示屏显示自增数字
  tft.print(i);
  i++;
  delay(500);

  distance = getDistance();
  tft.setCursor(20,20);         //设置光标的位置
  tft.setTextSize(1);
  tft.print("Distance: ");      //显示屏显示超声波距离
  tft.print(distance);
  tft.print("cm");               //单位cm
  delay(500);
  
  weight = getWeight();  //获取在传感器上的重物重量
  float result = float(weight/1000); //转换成KG
  tft.setCursor(20,30);         //设置光标的位置
  tft.setTextSize(1);
  tft.print("Weight: ");        //显示屏显示重量
  tft.print(result,3);
  tft.print("kg");             //单位kg
  delay(500);  //延时500ms

  tft.setCursor(20,40);         //设置光标的位置
  tft.setTextSize(1);
  tft.print("T-H: ");        //显示屏显示温度和湿度
  tft.print(getTemperatureAndHumidity());
  delay(500);  //延时500ms
}

long getWeight(){ //称重函数, 获取重量
 weight_shiwu = getReadingByHX711() - weight_maopi;
 weight_shiwu = (long)((float)weight_shiwu/GapValue); //AD值转换为重量（g）
 return weight_shiwu; 
}
long getReadingByHX711(){ //读取HX711称重传感器的输入AD值
  int waitTime = 0;
  while(!scale.is_ready()){ //如果称重传感器没有准备成功
    delay(50); waitTime+=100; //等待100ms再重新获取
    if(waitTime > 3000 ){ //如果超过3秒未获取到, 返回0, 避免阻塞
      return 0;
    }
  }
  return scale.read();
}

float getDistance(){ //获取CH-SR04超声波的距离
  digitalWrite(TrigPin, LOW); // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);// Sets the trigPin on HIGH state for 10 ms
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  duration = pulseIn(EchoPin, HIGH); //读取声波来回的时间
  distance= duration*0.034/2.0;      //时间*声速 / 2得到距离
  return distance;
 }

 String getTemperatureAndHumidity(){ //获取DHT11的温度和湿度
  byte temperature = 0;
  byte humidity = 0;
  int waitTime = 0;
  while(dht11.read(&temperature, &humidity, NULL) != SimpleDHTErrSuccess){ //如果读取失败
      delay(100); waitTime+=100; //等待100ms再重新读取
      if(waitTime > 3000 ){ //如果超过3秒未获取到, 返回空, 避免阻塞
      return "null";
    }
  }
  return String((int)temperature) + "*c " + String((int)humidity) + "H";
 }
