
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#define TFT_CS     D1
#define TFT_RST    D2  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     D3

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

int i = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Hello! ST7735 TFT Test Hello World");
  // Use this initializer (uncomment) if you're using a 1.44" TFT
  tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

  Serial.println("Initialized");

  tft.fillScreen(ST7735_BLACK);
  delay(500);

  tft.setTextColor(ST7735_RED);
  tft.setCursor(20,10);
  tft.setTextSize(1);
  tft.print("Hello World!");
  tft.print(i);
}

void loop() {
  tft.fillScreen(ST7735_BLACK); //刷屏, 重新显示
  tft.setCursor(20,10);         //设置光标的位置
  tft.setTextSize(1);
  tft.print("Hello World! ");
  tft.print(i);
  delay(1000);
  i++;
}
