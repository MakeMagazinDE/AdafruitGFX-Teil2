#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_DC 2
#define TFT_CS 15
#define TFT_RST 4
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

//Byte-Arrays HIER einfügen.


void setup() {

  display.begin();
  display.setRotation(1);

  display.fillScreen(ILI9341_BLACK);

  //Monochromes Bitmap mit transparentem Hintergrund
  display.drawBitmap(x,y,n,w,h,c);

  //Monochromes Bitmap mit opakem Hintergrund
  //display.drawBitmap(x,y,n,w,h,c,bgr);

  //RGB-Bitmap ohne Maske bzw. Transparenz
  //display.drawRGBBitmap(x,y,n,w,h);

  //RGB-Bitmap mit Maske bzw. Transparenz
  //display.drawRGBBitmap(x,y,n,m,w,h);

}

void loop() {

}
