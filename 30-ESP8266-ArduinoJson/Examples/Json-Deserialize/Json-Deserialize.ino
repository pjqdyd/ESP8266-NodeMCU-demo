#include "ArduinoJson.h" //引用ArduinoJson库

//声明一个json数据
char myJson[] = "{\"myChar\":\"hello\",\"myArray\":[13,14],\"myObject\":{\"myFloat\":3.1415926}}";

void parmPass(JsonVariant parm)
{
    const char *myC = parm["myChar"];
    int myN0 = parm["myArray"][0];
    int myN1 = parm["myArray"][1];
    float myF = parm["myObject"]["myFloat"];

    Serial.println(myC);
    Serial.println(myN0);
    Serial.println(myN1);
    Serial.println(myF);
}

void setup()
{
    Serial.begin(115200);
    Serial.println();

    StaticJsonDocument<200> doc; //声明一个JsonDocument对象
    DeserializationError error = deserializeJson(doc, myJson); //反序列化JSON数据
    if (!error) //检查反序列化是否成功
    {
        parmPass(doc.as<JsonVariant>()); //将参数传递后打印输出
    }
}

void loop()
{
}
