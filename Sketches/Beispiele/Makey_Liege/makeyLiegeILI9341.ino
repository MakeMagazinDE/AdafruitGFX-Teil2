#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_DC 2
#define TFT_CS 15
#define TFT_RST 4
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

int posX = 125;
int posY = 120;

// 'Details_mono', 10x9px
const unsigned char makeyDetails_mono [] PROGMEM = {
	0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x15, 0x40, 0x39, 0x80, 0x4a, 0x80, 
	0x07, 0x00
};
// 'Blaetter_mono', 24x21px
const unsigned char makeyBlaetter_mono [] PROGMEM = {
	0x00, 0x78, 0x00, 0x00, 0xfe, 0x00, 0x01, 0x9f, 0x00, 0x00, 0x0f, 0x00, 0x0e, 0x07, 0x0e, 0x3f, 
	0x87, 0x3f, 0x7f, 0xc7, 0x7c, 0x41, 0xe6, 0x70, 0x00, 0x76, 0xe0, 0x00, 0x30, 0x00, 0x0f, 0x11, 
	0xf0, 0x3f, 0xc0, 0xf8, 0x79, 0xc0, 0x7c, 0x70, 0x01, 0x0c, 0xc0, 0x03, 0xc6, 0x80, 0x01, 0xc6, 
	0x00, 0x01, 0xe0, 0x00, 0x00, 0xe0, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80
};
// 'Stamm_mono', 8x16px
const unsigned char makeyStamm_mono [] PROGMEM = {
	0x01, 0x01, 0x07, 0x06, 0x00, 0x0e, 0x0c, 0x00, 0x1c, 0x38, 0x30, 0x00, 0x70, 0xe0, 0xc0, 0xc0
};
// 'Liege_mono', 40x18px
const unsigned char makeyLiege_mono [] PROGMEM = {
	0xfe, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x40, 
	0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 
	0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 
	0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0xff, 0xc0, 0xff, 0x80, 0x02, 0x00, 0x00, 0x40, 0x40, 0x06, 0x06, 0x00, 0x60, 0x60, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xfc
};
// 'Makey_mono', 24x20px
const unsigned char makeyMakey_mono [] PROGMEM = {
	0x0f, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x3f, 0xc1, 0x00, 0x2f, 0x43, 0x80, 0x3f, 0xc7, 0x80, 0x00, 
	0x1e, 0x00, 0x5f, 0xec, 0x00, 0xfe, 0x30, 0x00, 0xfd, 0x58, 0x00, 0xf8, 0xc8, 0x00, 0xfe, 0xac, 
	0x00, 0x77, 0x1f, 0x81, 0x7b, 0xf8, 0xef, 0x3d, 0xff, 0x7f, 0x0d, 0xff, 0xbf, 0x1d, 0xff, 0xbf, 
	0x00, 0x07, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0xc0
};
// 'Sonne_mono', 16x15px
const unsigned char makeySonne_mono [] PROGMEM = {
	0x01, 0x00, 0x01, 0x00, 0x24, 0x48, 0x11, 0x10, 0x07, 0xc0, 0x2f, 0xe8, 0x0f, 0xe0, 0xdf, 0xf6, 
	0x0f, 0xe0, 0x2f, 0xe8, 0x07, 0xc0, 0x11, 0x10, 0x24, 0x48, 0x01, 0x00, 0x01, 0x00
};

// 'Liege_mono2x', 80x36px
const unsigned char makeyLiege_mono2x [] PROGMEM = {
	0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf0, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x03, 
	0xff, 0xff, 0xf0, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 
	0x30, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x30, 0x00, 0x00, 0x3c, 0x00, 0x3c, 
	0x00, 0x00, 0x3c, 0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00, 0x3c, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0
};
// 'Sonne_mono2x', 32x30px
const unsigned char makeySonne_mono2x [] PROGMEM = {
	0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 
	0x0c, 0x30, 0x30, 0xc0, 0x0c, 0x30, 0x30, 0xc0, 0x03, 0x03, 0x03, 0x00, 0x03, 0x03, 0x03, 0x00, 
	0x00, 0x3f, 0xf0, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x0c, 0xff, 0xfc, 0xc0, 0x0c, 0xff, 0xfc, 0xc0, 
	0x00, 0xff, 0xfc, 0x00, 0x00, 0xff, 0xfc, 0x00, 0xf3, 0xff, 0xff, 0x3c, 0xf3, 0xff, 0xff, 0x3c, 
	0x00, 0xff, 0xfc, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x0c, 0xff, 0xfc, 0xc0, 0x0c, 0xff, 0xfc, 0xc0, 
	0x00, 0x3f, 0xf0, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x03, 0x03, 0x03, 0x00, 0x03, 0x03, 0x03, 0x00, 
	0x0c, 0x30, 0x30, 0xc0, 0x0c, 0x30, 0x30, 0xc0, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 
	0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00
};
// 'Makey_mono2x', 48x40px
const unsigned char makeyMakey_mono2x [] PROGMEM = {
	0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x00, 
	0x00, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x03, 0x00, 0x00, 0x0f, 0xff, 
	0xf0, 0x03, 0x00, 0x00, 0x0c, 0xff, 0x30, 0x0f, 0xc0, 0x00, 0x0c, 0xff, 0x30, 0x0f, 0xc0, 0x00, 
	0x0f, 0xff, 0xf0, 0x3f, 0xc0, 0x00, 0x0f, 0xff, 0xf0, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x03, 0xfc, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x00, 0x33, 0xff, 0xfc, 0xf0, 0x00, 0x00, 0x33, 0xff, 
	0xfc, 0xf0, 0x00, 0x00, 0xff, 0xfc, 0x0f, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x0f, 0x00, 0x00, 0x00, 
	0xff, 0xf3, 0x33, 0xc0, 0x00, 0x00, 0xff, 0xf3, 0x33, 0xc0, 0x00, 0x00, 0xff, 0xc0, 0xf0, 0xc0, 
	0x00, 0x00, 0xff, 0xc0, 0xf0, 0xc0, 0x00, 0x00, 0xff, 0xfc, 0xcc, 0xf0, 0x00, 0x00, 0xff, 0xfc, 
	0xcc, 0xf0, 0x00, 0x00, 0x3f, 0x3f, 0x03, 0xff, 0xc0, 0x03, 0x3f, 0x3f, 0x03, 0xff, 0xc0, 0x03, 
	0x3f, 0xcf, 0xff, 0xc0, 0xfc, 0xff, 0x3f, 0xcf, 0xff, 0xc0, 0xfc, 0xff, 0x0f, 0xf3, 0xff, 0xff, 
	0x3f, 0xff, 0x0f, 0xf3, 0xff, 0xff, 0x3f, 0xff, 0x00, 0xf3, 0xff, 0xff, 0xcf, 0xff, 0x00, 0xf3, 
	0xff, 0xff, 0xcf, 0xff, 0x03, 0xf3, 0xff, 0xff, 0xcf, 0xff, 0x03, 0xf3, 0xff, 0xff, 0xcf, 0xff, 
	0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x3f, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00
};
// 'Stamm_mono2x', 16x32px
const unsigned char makeyStamm_mono2x [] PROGMEM = {
	0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x3f, 0x00, 0x3f, 0x00, 0x3c, 0x00, 0x3c, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0xf0, 0x03, 0xf0, 0x0f, 0xc0, 0x0f, 0xc0, 0x0f, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x3f, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00
};
// 'Blaetter_mono2x', 48x42px
const unsigned char makeyBlaetter_mono2x [] PROGMEM = {
	0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfc, 
	0x00, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xc3, 0xff, 0x00, 0x00, 0x00, 0x03, 
	0xc3, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 
	0x00, 0xfc, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0x3f, 0x00, 0xfc, 0x0f, 0xff, 0xc0, 0x3f, 
	0x0f, 0xff, 0x0f, 0xff, 0xc0, 0x3f, 0x0f, 0xff, 0x3f, 0xff, 0xf0, 0x3f, 0x3f, 0xf0, 0x3f, 0xff, 
	0xf0, 0x3f, 0x3f, 0xf0, 0x30, 0x03, 0xfc, 0x3c, 0x3f, 0x00, 0x30, 0x03, 0xfc, 0x3c, 0x3f, 0x00, 
	0x00, 0x00, 0x3f, 0x3c, 0xfc, 0x00, 0x00, 0x00, 0x3f, 0x3c, 0xfc, 0x00, 0x00, 0x00, 0x0f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0x03, 0xff, 0x00, 0x00, 0xff, 
	0x03, 0x03, 0xff, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0xff, 0xc0, 0x0f, 0xff, 0xf0, 0x00, 0xff, 0xc0, 
	0x3f, 0xc3, 0xf0, 0x00, 0x3f, 0xf0, 0x3f, 0xc3, 0xf0, 0x00, 0x3f, 0xf0, 0x3f, 0x00, 0x00, 0x03, 
	0x00, 0xf0, 0x3f, 0x00, 0x00, 0x03, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x0f, 0xf0, 0x3c, 0xf0, 0x00, 
	0x00, 0x0f, 0xf0, 0x3c, 0xc0, 0x00, 0x00, 0x03, 0xf0, 0x3c, 0xc0, 0x00, 0x00, 0x03, 0xf0, 0x3c, 
	0x00, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00
};
// 'Details_mono2x', 32x18px
const unsigned char makeyDetails_mono2x [] PROGMEM = {
	0xc0, 0x30, 0x00, 0x00, 0xc0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x03, 0x33, 0x30, 0x00, 0x03, 0x33, 0x30, 0x00, 
	0x0f, 0xc3, 0xc0, 0x00, 0x0f, 0xc3, 0xc0, 0x00, 0x30, 0xcc, 0xc0, 0x00, 0x30, 0xcc, 0xc0, 0x00, 
	0x00, 0x3f, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00
};


void setup() {

  display.begin();
  display.setRotation(1);

  display.fillScreen(0x3DF8);

	//Kleiner Makey auf der Liege
	/*
	display.drawBitmap(posX,posY,makeyLiege_mono,40,18,ILI9341_WHITE);
	display.drawBitmap(posX+6,posY-4,makeyMakey_mono,24,20,0xE0E4);
	display.drawBitmap(posX+9,posY-1,makeyDetails_mono,10,9,ILI9341_WHITE);
	display.drawBitmap(posX+5,posY-17,makeyStamm_mono,8,16,0xBAE0);
	display.drawBitmap(posX-1,posY-27,makeyBlaetter_mono,24,21,0x048A);
	display.drawBitmap(posX+24,posY-20,makeySonne_mono,16,15,0xF627);
  */

	//Großer Makey auf der Liege
	display.drawBitmap(posX,posY,makeyLiege_mono2x,80,36,ILI9341_WHITE);
	display.drawBitmap(posX+12,posY-8,makeyMakey_mono2x,48,40,0xE0E4);
	display.drawBitmap(posX+18,posY-2,makeyDetails_mono2x,32,18,ILI9341_WHITE);
	display.drawBitmap(posX+10,posY-34,makeyStamm_mono2x,16,32,0xBAE0);
	display.drawBitmap(posX-2,posY-54,makeyBlaetter_mono2x,48,42,0x048A);
	display.drawBitmap(posX+48,posY-40,makeySonne_mono2x,32,30,0xF627);
	

}

void loop() {

}
