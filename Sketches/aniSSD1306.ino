#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);


uint8_t fps = 30;
unsigned long previousTime = 0;
uint8_t currentFrame = 0;

//Byte-Arrays HIER einfügen.


void animation() {

  unsigned long currentTime = millis();
  
  if(currentTime - previousTime >= 1000/fps){
    if(currentFrame < 27){
      display.drawBitmap(48,15,makeyallArray[currentFrame],32,35,1,0);
      display.display();
      currentFrame += 1;
      currentTime = previousTime;
    } else {
      currentFrame = 0;
    }
  }

}

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC,0x03C);
  display.clearDisplay();
  display.display();

}

void loop() {

	animation();

}
