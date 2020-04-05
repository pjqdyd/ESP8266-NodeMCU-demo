
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#define TFT_CS     D1
#define TFT_RST    D2  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     D3

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);


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
  tft.setTextSize(1);
  tft.println("Hello World!");
}

void loop() {
  // put your main code here, to run repeatedly:
}
