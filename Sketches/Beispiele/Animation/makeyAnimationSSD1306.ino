#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);


uint8_t fps = 30;
unsigned long previousTime = 0;
uint8_t currentFrame = 0;

// '38', 32x35px
const unsigned char makey38 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xbc, 0x7d, 0xf4, 0x2f, 0xbe, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0xfd, 0xe5, 0xa7, 0xbe, 0x39, 0xf5, 0xaf, 0x9c, 0x39, 0xf8, 0x1f, 0x9c, 
	0x7d, 0xfc, 0x3f, 0xbe, 0x7c, 0xff, 0xff, 0x3e, 0x7c, 0x00, 0x00, 0x3e, 0x7c, 0x7c, 0x3e, 0x3e, 
	0x00, 0x7c, 0x3e, 0x00, 0x7c, 0x7c, 0x3e, 0x3e, 0x3c, 0x00, 0x00, 0x3c, 0x1c, 0x7c, 0x3e, 0x38, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '37', 32x35px
const unsigned char makey37 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xbc, 0x7d, 0xf4, 0x2f, 0xbe, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0xfd, 0xe5, 0xa7, 0xbe, 0x79, 0xf5, 0xaf, 0x9c, 0x7d, 0xf8, 0x1f, 0xbe, 
	0x7d, 0xfc, 0x3f, 0xbe, 0x7c, 0xff, 0xff, 0x3e, 0x7c, 0x00, 0x00, 0x3e, 0x7c, 0x7c, 0x3e, 0x3e, 
	0x3c, 0x7c, 0x3e, 0x3c, 0x1c, 0x7c, 0x3e, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '36', 32x35px
const unsigned char makey36 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xbc, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x7d, 0xe5, 0xa7, 0xbe, 0x7d, 0xf5, 0xaf, 0xbe, 0x7d, 0xf8, 0x1f, 0xbe, 
	0x7d, 0xfc, 0x3f, 0xbe, 0x7c, 0xff, 0xff, 0x3c, 0x3c, 0x00, 0x00, 0x38, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '35', 32x35px
const unsigned char makey35 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xbc, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x7d, 0xe5, 0xa7, 0xbe, 0x7d, 0xf5, 0xaf, 0xbe, 0x7d, 0xf8, 0x1f, 0xbe, 
	0x7d, 0xfc, 0x3f, 0xbc, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '34', 32x35px
const unsigned char makey34 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xbc, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x7d, 0xe5, 0xa7, 0xbe, 0x7d, 0xf5, 0xaf, 0xbe, 0x7d, 0xf8, 0x1f, 0xbe, 
	0x7d, 0xfc, 0x3f, 0xbc, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '33', 32x35px
const unsigned char makey33 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xbc, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0xfd, 0xe5, 0xa7, 0xbe, 0x7d, 0xf5, 0xaf, 0xbe, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '32', 32x35px
const unsigned char makey32 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xbc, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0xfd, 0xe5, 0xa7, 0xbe, 0x7d, 0xf5, 0xaf, 0xbe, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '31', 32x35px
const unsigned char makey31 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x7d, 0xfc, 0x3f, 0xbe, 
	0xfd, 0xf8, 0x1f, 0xbe, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x3d, 0xe5, 0xa7, 0xbc, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '30', 32x35px
const unsigned char makey30 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x7d, 0xfc, 0x3f, 0xbe, 
	0xfd, 0xf8, 0x1f, 0xbe, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x3d, 0xe5, 0xa7, 0xbc, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '29', 32x35px
const unsigned char makey29 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x7c, 0x00, 0x00, 0x3c, 0x7c, 0xff, 0xff, 0x3e, 0x7d, 0xfc, 0x3f, 0xbe, 
	0x7d, 0xf8, 0x1f, 0xbe, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x3d, 0xe5, 0xa7, 0xbc, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '28', 32x35px
const unsigned char makey28 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x7c, 0x00, 0x00, 0x3c, 0x7c, 0xff, 0xff, 0x3e, 0x7d, 0xfc, 0x3f, 0xbe, 
	0x7d, 0xf8, 0x1f, 0xbe, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x3d, 0xe5, 0xa7, 0xbc, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '27', 32x35px
const unsigned char makey27 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x3c, 0x67, 0xe6, 0x38, 
	0x7c, 0x7f, 0xfe, 0x3c, 0x7c, 0x00, 0x00, 0x3e, 0x7c, 0xff, 0xff, 0x3e, 0x7d, 0xfc, 0x3f, 0xbe, 
	0x7d, 0xf8, 0x1f, 0xbe, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x3d, 0xe5, 0xa7, 0xbc, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '26', 32x35px
const unsigned char makey26 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x1c, 0x1f, 0xf8, 0x38, 0x3c, 0x3f, 0xfc, 0x3c, 0x7c, 0x67, 0xe6, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 
	0x7c, 0x7f, 0xfe, 0x3e, 0x7c, 0x00, 0x00, 0x3e, 0x7c, 0xff, 0xff, 0x3e, 0x79, 0xfc, 0x3f, 0x9c, 
	0xfd, 0xf8, 0x1f, 0xbe, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0x7c, 0x05, 0xa0, 0x3e, 0x3d, 0xe5, 0xa7, 0xbc, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '25', 32x35px
const unsigned char makey25 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x03, 0xc0, 0x38, 0x3c, 0x0f, 0xf0, 0x3c, 
	0x7c, 0x1f, 0xf8, 0x3e, 0x00, 0x3f, 0xfc, 0x00, 0x7c, 0x67, 0xe6, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 
	0x7c, 0x7f, 0xfe, 0x3e, 0x7c, 0x00, 0x00, 0x3e, 0x38, 0xff, 0xff, 0x1c, 0x39, 0xfc, 0x3f, 0x9c, 
	0xfd, 0xf8, 0x1f, 0xbe, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbe, 
	0x7c, 0x05, 0xa0, 0x3e, 0x3d, 0xe5, 0xa7, 0xbc, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '24', 32x35px
const unsigned char makey24 [] PROGMEM = {
	0x1c, 0x00, 0x00, 0x38, 0x3c, 0x00, 0x00, 0x3c, 0x7c, 0x03, 0xc0, 0x3e, 0x00, 0x0f, 0xf0, 0x00, 
	0x7c, 0x1f, 0xf8, 0x3e, 0x7c, 0x3f, 0xfc, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 
	0x7c, 0x7f, 0xfe, 0x3e, 0x38, 0x00, 0x00, 0x1c, 0x38, 0xff, 0xff, 0x1c, 0x39, 0xfc, 0x3f, 0x9c, 
	0xfd, 0xf8, 0x1f, 0xbf, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbe, 0x7d, 0xe6, 0x67, 0xbe, 
	0x3c, 0x05, 0xa0, 0x3c, 0x1d, 0xe5, 0xa7, 0xb8, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '23', 32x35px
const unsigned char makey23 [] PROGMEM = {
	0x1c, 0x00, 0x00, 0x38, 0x3c, 0x00, 0x00, 0x3c, 0x7c, 0x03, 0xc0, 0x3e, 0x00, 0x0f, 0xf0, 0x00, 
	0x7c, 0x1f, 0xf8, 0x3e, 0x7c, 0x3f, 0xfc, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 
	0x7c, 0x7f, 0xfe, 0x3e, 0x38, 0x00, 0x00, 0x1c, 0x38, 0xff, 0xff, 0x1c, 0x39, 0xfc, 0x3f, 0x9c, 
	0xfd, 0xf8, 0x1f, 0xbf, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbe, 0x7d, 0xe6, 0x67, 0xbe, 
	0x3c, 0x05, 0xa0, 0x3c, 0x1d, 0xe5, 0xa7, 0xb8, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '22', 32x35px
const unsigned char makey22 [] PROGMEM = {
	0x1c, 0x00, 0x00, 0x38, 0x3c, 0x00, 0x00, 0x3c, 0x7c, 0x03, 0xc0, 0x3e, 0x00, 0x0f, 0xf0, 0x00, 
	0x7c, 0x1f, 0xf8, 0x3e, 0x7c, 0x3f, 0xfc, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 
	0x7c, 0x7f, 0xfe, 0x3e, 0x38, 0x00, 0x00, 0x1c, 0x38, 0xff, 0xff, 0x1c, 0x39, 0xfc, 0x3f, 0x9c, 
	0xfd, 0xf8, 0x1f, 0xbf, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbe, 0x7d, 0xe6, 0x67, 0xbe, 
	0x3c, 0x05, 0xa0, 0x3c, 0x1d, 0xe5, 0xa7, 0xb8, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '21', 32x35px
const unsigned char makey21 [] PROGMEM = {
	0x1c, 0x00, 0x00, 0x38, 0x3c, 0x00, 0x00, 0x3c, 0x7c, 0x03, 0xc0, 0x3e, 0x00, 0x0f, 0xf0, 0x00, 
	0x7c, 0x1f, 0xf8, 0x3e, 0x7c, 0x3f, 0xfc, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 
	0x7c, 0x7f, 0xfe, 0x3e, 0x38, 0x00, 0x00, 0x1c, 0x38, 0xff, 0xff, 0x1c, 0x39, 0xfc, 0x3f, 0x9c, 
	0xfd, 0xf8, 0x1f, 0xbf, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbe, 0x7d, 0xe6, 0x67, 0xbe, 
	0x3c, 0x05, 0xa0, 0x3c, 0x1d, 0xe5, 0xa7, 0xb8, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '20', 32x35px
const unsigned char makey20 [] PROGMEM = {
	0x1c, 0x00, 0x00, 0x38, 0x3c, 0x00, 0x00, 0x3c, 0x7c, 0x03, 0xc0, 0x3e, 0x00, 0x0f, 0xf0, 0x00, 
	0x7c, 0x1f, 0xf8, 0x3e, 0x7c, 0x3f, 0xfc, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 
	0x7c, 0x7f, 0xfe, 0x3e, 0x38, 0x00, 0x00, 0x1c, 0x38, 0xff, 0xff, 0x1c, 0x39, 0xfc, 0x3f, 0x9c, 
	0xfd, 0xf8, 0x1f, 0xbf, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbe, 0x7d, 0xe6, 0x67, 0xbe, 
	0x3c, 0x05, 0xa0, 0x3c, 0x1d, 0xe5, 0xa7, 0xb8, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '19', 32x35px
const unsigned char makey19 [] PROGMEM = {
	0x1c, 0x00, 0x00, 0x38, 0x3c, 0x00, 0x00, 0x3c, 0x7c, 0x03, 0xc0, 0x3e, 0x00, 0x0f, 0xf0, 0x00, 
	0x7c, 0x1f, 0xf8, 0x3e, 0x7c, 0x3f, 0xfc, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 
	0x7c, 0x7f, 0xfe, 0x3e, 0x38, 0x00, 0x00, 0x1c, 0x38, 0xff, 0xff, 0x1c, 0x39, 0xfc, 0x3f, 0x9c, 
	0xfd, 0xf8, 0x1f, 0xbf, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbe, 0x7d, 0xe6, 0x67, 0xbe, 
	0x3c, 0x05, 0xa0, 0x3c, 0x1d, 0xe5, 0xa7, 0xb8, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '18', 32x35px
const unsigned char makey18 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x03, 0xc0, 0x38, 0x3c, 0x0f, 0xf0, 0x3c, 
	0x7c, 0x1f, 0xf8, 0x3e, 0x00, 0x3f, 0xfc, 0x00, 0x7c, 0x67, 0xe6, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 
	0x7c, 0x7f, 0xfe, 0x3e, 0x7c, 0x00, 0x00, 0x3e, 0x38, 0xff, 0xff, 0x1c, 0x39, 0xfc, 0x3f, 0x9c, 
	0xfd, 0xf8, 0x1f, 0xbe, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbe, 
	0x7c, 0x05, 0xa0, 0x3e, 0x3d, 0xe5, 0xa7, 0xbc, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '17', 32x35px
const unsigned char makey17 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x1c, 0x1f, 0xf8, 0x38, 0x3c, 0x3f, 0xfc, 0x3c, 0x7c, 0x67, 0xe6, 0x3e, 0x7c, 0x67, 0xe6, 0x3e, 
	0x7c, 0x7f, 0xfe, 0x3e, 0x7c, 0x00, 0x00, 0x3e, 0x7c, 0xff, 0xff, 0x3e, 0x79, 0xfc, 0x3f, 0x9c, 
	0xfd, 0xf8, 0x1f, 0xbe, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0x7c, 0x05, 0xa0, 0x3e, 0x3d, 0xe5, 0xa7, 0xbc, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '16', 32x35px
const unsigned char makey16 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x3c, 0x67, 0xe6, 0x38, 
	0x7c, 0x7f, 0xfe, 0x3c, 0x7c, 0x00, 0x00, 0x3e, 0x7c, 0xff, 0xff, 0x3e, 0x7d, 0xfc, 0x3f, 0xbe, 
	0x7d, 0xf8, 0x1f, 0xbe, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x3d, 0xe5, 0xa7, 0xbc, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '15', 32x35px
const unsigned char makey15 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x7c, 0x00, 0x00, 0x3c, 0x7c, 0xff, 0xff, 0x3e, 0x7d, 0xfc, 0x3f, 0xbe, 
	0x7d, 0xf8, 0x1f, 0xbe, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x3d, 0xe5, 0xa7, 0xbc, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '14', 32x35px
const unsigned char makey14 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x7c, 0x00, 0x00, 0x3c, 0x7c, 0xff, 0xff, 0x3e, 0x7d, 0xfc, 0x3f, 0xbe, 
	0x7d, 0xf8, 0x1f, 0xbe, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x3d, 0xe5, 0xa7, 0xbc, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '13', 32x35px
const unsigned char makey13 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x7d, 0xfc, 0x3f, 0xbe, 
	0xfd, 0xf8, 0x1f, 0xbe, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x3d, 0xe5, 0xa7, 0xbc, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '10', 32x35px
const unsigned char makey10 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xbc, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0xfd, 0xe5, 0xa7, 0xbe, 0x7d, 0xf5, 0xaf, 0xbe, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '11', 32x35px
const unsigned char makey11 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xbc, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0xfd, 0xe5, 0xa7, 0xbe, 0x7d, 0xf5, 0xaf, 0xbe, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '9', 32x35px
const unsigned char makey9 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xbc, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x7d, 0xe5, 0xa7, 0xbe, 0x7d, 0xf5, 0xaf, 0xbe, 0x7d, 0xf8, 0x1f, 0xbe, 
	0x7d, 0xfc, 0x3f, 0xbc, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '12', 32x35px
const unsigned char makey12 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x7d, 0xfc, 0x3f, 0xbe, 
	0xfd, 0xf8, 0x1f, 0xbe, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x3d, 0xe5, 0xa7, 0xbc, 0x01, 0xf5, 0xaf, 0x80, 0x01, 0xf8, 0x1f, 0x80, 
	0x01, 0xfc, 0x3f, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '8', 32x35px
const unsigned char makey8 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xbc, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x7d, 0xe5, 0xa7, 0xbe, 0x7d, 0xf5, 0xaf, 0xbe, 0x7d, 0xf8, 0x1f, 0xbe, 
	0x7d, 0xfc, 0x3f, 0xbc, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '6', 32x35px
const unsigned char makey6 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xbc, 0x7d, 0xf4, 0x2f, 0xbe, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0xfd, 0xe5, 0xa7, 0xbe, 0x79, 0xf5, 0xaf, 0x9c, 0x7d, 0xf8, 0x1f, 0xbe, 
	0x7d, 0xfc, 0x3f, 0xbe, 0x7c, 0xff, 0xff, 0x3e, 0x7c, 0x00, 0x00, 0x3e, 0x7c, 0x7c, 0x3e, 0x3e, 
	0x3c, 0x7c, 0x3e, 0x3c, 0x1c, 0x7c, 0x3e, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '5', 32x35px
const unsigned char makey5 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xbc, 0x7d, 0xf4, 0x2f, 0xbe, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0xfd, 0xe5, 0xa7, 0xbe, 0x39, 0xf5, 0xaf, 0x9c, 0x39, 0xf8, 0x1f, 0x9c, 
	0x7d, 0xfc, 0x3f, 0xbe, 0x7c, 0xff, 0xff, 0x3e, 0x7c, 0x00, 0x00, 0x3e, 0x7c, 0x7c, 0x3e, 0x3e, 
	0x00, 0x7c, 0x3e, 0x00, 0x7c, 0x7c, 0x3e, 0x3e, 0x3c, 0x00, 0x00, 0x3c, 0x1c, 0x7c, 0x3e, 0x38, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '7', 32x35px
const unsigned char makey7 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xbc, 0xfd, 0xf4, 0x2f, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x7d, 0xe5, 0xa7, 0xbe, 0x7d, 0xf5, 0xaf, 0xbe, 0x7d, 0xf8, 0x1f, 0xbe, 
	0x7d, 0xfc, 0x3f, 0xbe, 0x7c, 0xff, 0xff, 0x3c, 0x3c, 0x00, 0x00, 0x38, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3e, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '4', 32x35px
const unsigned char makey4 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xb8, 0x7d, 0xf4, 0x2f, 0xbc, 0xfd, 0xe6, 0x67, 0xbe, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0x39, 0xe5, 0xa7, 0x9c, 0x39, 0xf5, 0xaf, 0x9c, 0x39, 0xf8, 0x1f, 0x9c, 
	0x7d, 0xfc, 0x3f, 0xbe, 0x7c, 0xff, 0xff, 0x3e, 0x7c, 0x00, 0x00, 0x3e, 0x7c, 0x7c, 0x3e, 0x3e, 
	0x7c, 0x7c, 0x3e, 0x3e, 0x00, 0x7c, 0x3e, 0x00, 0x7c, 0x00, 0x00, 0x3e, 0x3c, 0x7c, 0x3e, 0x3c, 
	0x1c, 0xfc, 0x3f, 0x38, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '3', 32x35px
const unsigned char makey3 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xb8, 0x7d, 0xf4, 0x2f, 0xbc, 0xfd, 0xe6, 0x67, 0xbe, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0xfd, 0xe5, 0xa7, 0xbf, 0x39, 0xf5, 0xaf, 0x9c, 0x39, 0xf8, 0x1f, 0x9c, 
	0x39, 0xfc, 0x3f, 0x9c, 0x7c, 0xff, 0xff, 0x3e, 0x7c, 0x00, 0x00, 0x3e, 0x7c, 0x7c, 0x3e, 0x3e, 
	0x7c, 0x7c, 0x3e, 0x3e, 0x7c, 0x7c, 0x3e, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x7c, 0x3e, 0x3e, 
	0x3c, 0xfc, 0x3f, 0x3c, 0x1c, 0xfc, 0x3f, 0x38, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '1', 32x35px
const unsigned char makey1 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xb8, 0x7d, 0xf4, 0x2f, 0xbc, 0xfd, 0xe6, 0x67, 0xbe, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0xfd, 0xe5, 0xa7, 0xbf, 0x39, 0xf5, 0xaf, 0x9c, 0x39, 0xf8, 0x1f, 0x9c, 
	0x39, 0xfc, 0x3f, 0x9c, 0x7c, 0xff, 0xff, 0x3e, 0x7c, 0x00, 0x00, 0x3e, 0x7c, 0x7c, 0x3e, 0x3e, 
	0x7c, 0x7c, 0x3e, 0x3e, 0x7c, 0x7c, 0x3e, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x7c, 0x3e, 0x3e, 
	0x3c, 0xfc, 0x3f, 0x3c, 0x1c, 0xfc, 0x3f, 0x38, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '2', 32x35px
const unsigned char makey2 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xb8, 0x7d, 0xf4, 0x2f, 0xbc, 0xfd, 0xe6, 0x67, 0xbe, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0xfd, 0xe5, 0xa7, 0xbf, 0x39, 0xf5, 0xaf, 0x9c, 0x39, 0xf8, 0x1f, 0x9c, 
	0x39, 0xfc, 0x3f, 0x9c, 0x7c, 0xff, 0xff, 0x3e, 0x7c, 0x00, 0x00, 0x3e, 0x7c, 0x7c, 0x3e, 0x3e, 
	0x7c, 0x7c, 0x3e, 0x3e, 0x7c, 0x7c, 0x3e, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x7c, 0x3e, 0x3e, 
	0x3c, 0xfc, 0x3f, 0x3c, 0x1c, 0xfc, 0x3f, 0x38, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};
// '0', 32x35px
const unsigned char makey0 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 
	0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0xfc, 0x3f, 0x80, 
	0x3d, 0xf8, 0x1f, 0xb8, 0x7d, 0xf4, 0x2f, 0xbc, 0xfd, 0xe6, 0x67, 0xbe, 0xfd, 0xe6, 0x67, 0xbf, 
	0xfc, 0x05, 0xa0, 0x3f, 0xfd, 0xe5, 0xa7, 0xbf, 0x39, 0xf5, 0xaf, 0x9c, 0x39, 0xf8, 0x1f, 0x9c, 
	0x39, 0xfc, 0x3f, 0x9c, 0x7c, 0xff, 0xff, 0x3e, 0x7c, 0x00, 0x00, 0x3e, 0x7c, 0x7c, 0x3e, 0x3e, 
	0x7c, 0x7c, 0x3e, 0x3e, 0x7c, 0x7c, 0x3e, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x7c, 0x3e, 0x3e, 
	0x3c, 0xfc, 0x3f, 0x3c, 0x1c, 0xfc, 0x3f, 0x38, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfe, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x7f, 0x80, 0x03, 0xfe, 0x7f, 0xc0
};


// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 22464)
const int makeyallArray_LEN = 39;
const unsigned char* makeyallArray[39] = {
	makey0,
	makey1,
	makey2,
	makey3,
	makey4,
	makey5,
	makey6,
	makey7,
	makey8,
	makey9,
	makey10,
	makey11,
	makey12,
	makey13,
	makey14,
	makey15,
	makey16,
	makey17,
	makey18,
	makey19,
	makey20,
	makey21,
	makey22,
	makey23,
	makey24,
	makey25,
	makey26,
	makey27,
	makey28,
	makey29,
	makey30,
	makey31,
	makey32,
	makey33,
	makey34,
	makey35,
	makey36,
	makey37,
	makey38
};



void animation() {

  unsigned long currentTime = millis();
  
  if(currentTime - previousTime >= 1000/fps){
    if(currentFrame < 39){
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