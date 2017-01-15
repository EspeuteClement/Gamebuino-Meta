/*
GRAHPIC TEST

= Draw to screen
- FillScreen
- Geometric shapes
- Print
-- Scaled
-- Change font
- Draw Image
-- RGB Colors
-- Indexed Colors
-- Scaled x2
-- Scaled by arbitrary number
-- Scaled by negative numbers (flipped)
-- Rotated 90/180/270�
-- Rotated by any angle 
-- Screen edge clipping
-- Transparent color (magenta)
-- blend modes

= Draw to Image
- Idem draw to screen
*/

#include <Image.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_CS		(30u)
#define TFT_RST		(0u)
#define TFT_DC		(31u)
#define SD_CS		(26u)
#define BTN_CS		(25u)
#define NEOPIX		(38u)

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Image imgRGB = Image(60, 40, ColorMode::RGB565);
Image imgIndex = Image(160, 128, ColorMode::INDEX);

const uint16_t favicon16Width = 16;
const uint16_t favicon16Height = 16;
const uint16_t favicon16[256] PROGMEM = {
	0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0x4208,0x4208,0x4208,0x4208,0xF81F,0xF81F, // row 0, 16 pixels
	0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xDEFB,0xDEFB,0x4208,0x4208,0xF81F, // row 1, 32 pixels
	0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xDEFB,0xF81F,0xDEFB,0xDEFB,0x4208,0xDEFB,0x4208,0x4208, // row 2, 48 pixels
	0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xDEFB,0xDEFB,0xDEFB,0xDEFB,0x4208,0x4208,0xDEFB,0xDEFB,0x4208, // row 3, 64 pixels
	0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xDEFB,0xDEFB,0x9471,0xDEFB,0xDEFB,0xDEFB,0x01DF,0x01DF,0xDEFB,0x4208, // row 4, 80 pixels
	0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xDEFB,0xDEFB,0x9471,0x9471,0x9471,0xDEFB,0xDEFB,0x27E0,0x27E0,0xDEFB,0x4208, // row 5, 96 pixels
	0xF81F,0xF81F,0xF81F,0xF81F,0xDEFB,0xDEFB,0x9471,0x9471,0x9471,0x9471,0x9471,0xDEFB,0xDEFB,0xDEFB,0x4208,0x4208, // row 6, 112 pixels
	0xF81F,0xF81F,0xF81F,0xDEFB,0xDEFB,0x9471,0x9471,0x9471,0x9471,0x9471,0x9471,0x9471,0xDEFB,0x4208,0x4208,0xF81F, // row 7, 128 pixels
	0xF81F,0xF81F,0xDEFB,0xDEFB,0x9471,0x9471,0x9471,0x9471,0x9471,0x9471,0x9471,0xDEFB,0xDEFB,0x4208,0xF81F,0xF81F, // row 8, 144 pixels
	0xF81F,0xF81F,0xF81F,0xDEFB,0xDEFB,0x9471,0x9471,0x9471,0x9471,0x9471,0xDEFB,0xDEFB,0x069E,0xF81F,0xF81F,0xF81F, // row 9, 160 pixels
	0x4208,0xF81F,0xDEFB,0x069E,0xDEFB,0xDEFB,0x9471,0x9471,0x9471,0xDEFB,0xDEFB,0x069E,0xF81F,0xF81F,0xF81F,0xF81F, // row 10, 176 pixels
	0x4208,0xDEFB,0xDEFB,0xDEFB,0xDEFB,0xDEFB,0xDEFB,0x9471,0xDEFB,0xDEFB,0x069E,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F, // row 11, 192 pixels
	0x4208,0xDEFB,0xDEFB,0xDEFB,0xFBA5,0xFBA5,0xDEFB,0xDEFB,0xDEFB,0x069E,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F, // row 12, 208 pixels
	0x4208,0x4208,0xDEFB,0xDEFB,0xFBA5,0xFBA5,0xDEFB,0x4208,0x4208,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F, // row 13, 224 pixels
	0xF81F,0x4208,0x4208,0xDEFB,0xDEFB,0xDEFB,0x4208,0x4208,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F, // row 14, 240 pixels
	0xF81F,0xF81F,0x4208,0x4208,0x4208,0x4208,0x4208,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F }; // row 15, 256 pixels
Image favicon = Image(favicon16Width, favicon16Height, ColorMode::RGB565, const_cast<uint16_t*>(favicon16));

uint16_t textImgIndexBuffer[32] = { 
	0x0123, 0x4567, 0x89AB, 0xCDEF,
	0x0123, 0x4567, 0x89AB, 0xCDEF,
	0x0123, 0x4567, 0x89AB, 0xCDEF,
	0x0123, 0x4567, 0x89AB, 0xCDEF,
	0xFEDC, 0xBA98, 0x7654, 0x3210,
	0xFEDC, 0xBA98, 0x7654, 0x3210,
	0xFEDC, 0xBA98, 0x7654, 0x3210,
	0xFEDC, 0xBA98, 0x7654, 0x3210,
};
Image testImgIndex = Image(16, 8, ColorMode::INDEX, textImgIndexBuffer);

void setup()
{
	tft.initR(INITR_BLACKTAB);
	tft.setRotation(1);
	tft.fillScreen(BLACK);
	tft.setColor(WHITE);
	tft.println("GRAPHIC TEST");
	tft.setColor(RED);
	tft.print("RED ");
	tft.setColor(GREEN);
	tft.print("GREEN ");
	tft.setColor(BLUE);
	tft.println("BLUE");
	delay(1500);
}

void loop()
{
	fillScreenTFT();
	
	drawTitle("IMAGE FILL RED");
	imgRGB.fillScreen(RED);
	drawImage(imgRGB, 1);

	drawTitle("DRAW RGB -> RGB");
	imgRGB.fillScreen(GRAY);
	imgRGB.drawImage(4, 4, favicon);
	drawImage(imgRGB, 1);

	drawTitle("DRAW RGB X 2 -> RGB");
	imgRGB.fillScreen(GRAY);
	imgRGB.drawImage(4, 4, favicon, favicon._width*2, favicon._height*2);
	drawImage(imgRGB, 1);

	drawTitle("DRAW RGB -> RGB X 2");
	imgRGB.fillScreen(GRAY);
	imgRGB.drawImage(4, 4, favicon);
	drawImage(imgRGB, 2);

	drawTitle("DRAW INDEX -> TFT");
	memset(imgIndex._buffer, 0x11, imgIndex.width()*imgIndex.height() / 2); //clear buffer
	uint16_t startTime = millis();
	tft.drawImage(0, 0, imgIndex);
	uint16_t endTime = millis();
	memset(imgIndex._buffer, 0x11, imgIndex.width()*imgIndex.height() / 2); //clear buffer
	imgIndex.setColor(13);
	//imgIndex.drawCircle((millis() / 10) % 160, 20, 10); //draw to indexed buffer
	imgIndex.setCursor(8, 42);
	for (uint16_t i = 0; i < 16; i++) {
		//numbers background
		imgIndex.setColor(i);
		imgIndex.fillRect(8 + i * 8, 32, 7, 7);
		//numbers
		imgIndex.setColor(i);
		if (i == 1) imgIndex.setColor(i, 0);
		if (i < 10) imgIndex.print(" ");
		imgIndex.print(i);
	}
	imgIndex.setColor(3);
	imgIndex.setCursor(10, 10);
	imgIndex.print(endTime - startTime);
	imgIndex.println("ms");
	imgIndex.setColor(11);
	imgIndex.setCursor(64, 10);
	imgIndex.print(1000 / (endTime - startTime));
	imgIndex.println("FPS");
	tft.drawImage(0, 0, imgIndex);
	delay(1500);

	memset(imgIndex._buffer, 0x11, imgIndex.width()*imgIndex.height() / 2); //clear buffer
	imgIndex.drawImage(8, 8, testImgIndex);
	tft.drawImage(0, 0, imgIndex);
	delay(1500);

	drawTitle("DRAW INDEX -> RGB x 2");
	imgRGB.fillScreen(GRAY);
	imgRGB.drawImage(4, 4, testImgIndex);
	imgRGB.setCursor(2, 16);
	for (uint16_t i = 0; i < 16; i++) {
		imgRGB.setColor(Adafruit_GFX::colorIndex[i]);
		imgRGB.print(i);
	}
	drawImage(imgRGB, 2);

}

void drawTitle(char* title) {
	tft.fillScreen(BLACK);
	tft.setCursor(2, 2);
	tft.setColor(WHITE);
	tft.println(title);
}

void fillScreenTFT() {
	tft.setColor(WHITE);
	tft.setCursor(2, 2);
	tft.fillScreen(RED);
	tft.println("FILL SCREEN RED");
	delay(500);
	tft.setCursor(2, 2);
	tft.fillScreen(GREEN);
	tft.println("FILL SCREEN GREEN");
	delay(500);
	tft.setCursor(2, 2);
	tft.fillScreen(BLUE);
	tft.println("FILL SCREEN BLUE");
	delay(500);
}

void drawImage(Image img, float scale) {
	int w = img._width * scale;
	int h = img._height * scale;
	int x = (tft._width - w) / 2;
	int y = (tft._height - h) / 2;
	tft.setColor(MAGENTA);
	tft.fillRect(x - 8, y - 8, w + 16, h + 16);
	tft.setColor(CYAN);
	//tft.println("DRAW BUFFER");
	tft.drawRect(x - 1, y - 1, w + 2, h + 2);
	tft.drawImage(x, y, img, w, h);
	delay(1500);
}
