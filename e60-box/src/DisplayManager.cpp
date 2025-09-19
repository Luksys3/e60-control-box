#include "DisplayManager.h"

/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void testdrawline()
{
	int16_t i;

	display.clearDisplay(); // Clear display buffer

	for (i = 0; i < display.width(); i += 4)
	{
		display.drawLine(0, 0, i, display.height() - 1, SSD1306_WHITE);
		display.display(); // Update screen with each newly-drawn line
		delay(1);
	}
	for (i = 0; i < display.height(); i += 4)
	{
		display.drawLine(0, 0, display.width() - 1, i, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	delay(250);

	display.clearDisplay();

	for (i = 0; i < display.width(); i += 4)
	{
		display.drawLine(0, display.height() - 1, i, 0, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	for (i = display.height() - 1; i >= 0; i -= 4)
	{
		display.drawLine(0, display.height() - 1, display.width() - 1, i, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	delay(250);

	display.clearDisplay();

	for (i = display.width() - 1; i >= 0; i -= 4)
	{
		display.drawLine(display.width() - 1, display.height() - 1, i, 0, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	for (i = display.height() - 1; i >= 0; i -= 4)
	{
		display.drawLine(display.width() - 1, display.height() - 1, 0, i, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	delay(250);

	display.clearDisplay();

	for (i = 0; i < display.height(); i += 4)
	{
		display.drawLine(display.width() - 1, 0, 0, i, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	for (i = 0; i < display.width(); i += 4)
	{
		display.drawLine(display.width() - 1, 0, i, display.height() - 1, SSD1306_WHITE);
		display.display();
		delay(1);
	}

	delay(2000); // Pause for 2 seconds
}

DisplayManager::DisplayManager() {};

void DisplayManager::setup()
{

	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
	{
		Serial.println(F("SSD1306 allocation failed"));
		for (;;)
			; // Don't proceed, loop forever
	}
	Serial.println(F("SSD1306 SUCESS!!"));

	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(SSD1306_WHITE);
	display.setCursor(0, 0);
	display.println(F("Hello, Mega 2560 Mini!"));
	display.display();

	// // Show initial display buffer contents on the screen --
	// // the library initializes this with an Adafruit splash screen.
	// display.display();
	// delay(2000); // Pause for 2 seconds

	// // Clear the buffer
	// display.clearDisplay();

	// // Draw a single pixel in white
	// display.drawPixel(10, 10, SSD1306_WHITE);

	// // Show the display buffer on the screen. You MUST call display() after
	// // drawing commands to make them visible on screen!
	// display.display();
	// delay(2000);
	// // display.display() is NOT necessary after every single drawing command,
	// // unless that's what you want...rather, you can batch up a bunch of
	// // drawing operations and then update the screen all at once by calling
	// // display.display(). These examples demonstrate both approaches...

	// testdrawline(); // Draw many lines

	// // Invert and restore display, pausing in-between
	// display.invertDisplay(true);
	// delay(1000);
	// display.invertDisplay(false);
	// delay(1000);
}

void DisplayManager::setTemperature(float temperature)
{
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(SSD1306_WHITE);
	display.setCursor(0, 0);
	display.println(temperature);
	display.display();
}