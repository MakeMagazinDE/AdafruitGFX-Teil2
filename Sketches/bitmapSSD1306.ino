#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);

//Byte-Arrays HIER einfügen.


void setup() {

  display.begin(SSD1306_SWITCHCAPVCC,0x03C);
  display.clearDisplay();

  //Monochromes Bitmap mit transparentem Hintergrund
  display.drawBitmap(x,y,n,w,h,c);

  //Monochromes Bitmap mit opakem Hintergrund
  //display.drawBitmap(x,y,n,w,h,c,bgr);

  display.display();

}

void loop() {

}
