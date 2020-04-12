
#include "ArduinoJson.h"

void setup()
{
    Serial.begin(9600);
    Serial.println();

    StaticJsonDocument<200> doc; //声明一个JsonDocument对象
    // DynamicJsonDocument doc(200); //声明一个JsonDocument对象

    doc["myChar"] = "hello"; //添加一个字符串对象节点

    JsonArray myA = doc.createNestedArray("myArray"); //添加一个数组节点
    myA.add(true);                                    //使用add方式添加数据到JsonArray
    myA.add(false);

    JsonObject myO = doc.createNestedObject("myObject"); //添加一个对象节点
    myO["myNumber"] = 1234567890;                        //使用[]添加数据到JsonObject

    serializeJson(doc, Serial); //序列化JSON数据（压缩形式），并从Serial输出
    // 以下三行输出结果同上面一行
    // char myDoc[measureJson(doc) + 1];
    // serializeJson(doc, myDoc, measureJson(doc) + 1);
    // Serial.println(myDoc);

    Serial.println();
    Serial.println();

    serializeJsonPretty(doc, Serial); //序列化JSON数据（展开形式），并从Serial输出
    // 以下三行输出结果同上面一行
    // char myDocP[measureJsonPretty(doc) + 1];
    // serializeJsonPretty(doc, myDocP, measureJsonPretty(doc) + 1);
    // Serial.println(myDocP);
}

void loop()
{
}
