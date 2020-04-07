#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = D5;
const int LOADCELL_SCK_PIN = D6;

float Weight = 0;
long HX711_Buffer = 0;
long Weight_Maopi = 0, Weight_Shiwu = 0; //毛皮, 四舍五入的重量
#define GapValue 610       ///该值需校准 每个传感器都有所不同

HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  delay(2000);    //延时一会2秒
  
  Weight_Maopi = getReadingByHX711(); //初始获取毛皮重量
}

void loop() {
 Weight = Get_Weight();  //计算放在传感器上的重物重量
 Serial.print(float(Weight/1000),3);  //串口显示重量， 3意为保留三位小数
 Serial.print(" kg\n"); //显示单位
 Serial.print("\n");  //显示单位
 delay(2000);  //延时2s 两秒读取一次传感器所受压力
}

 
long Get_Weight(){ //称重函数, 转换成重量
 Weight_Shiwu = getReadingByHX711() - Weight_Maopi;
 Weight_Shiwu = (long)((float)Weight_Shiwu/GapValue);    //AD值转换为重量（g）
 return Weight_Shiwu; 
}

long getReadingByHX711(){ //读取HX711的输入AD值
  if (scale.is_ready()) {
    return scale.read();
  } else {
    Serial.println("HX711 not found.");
    return 0;
  }
}
