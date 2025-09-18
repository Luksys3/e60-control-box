#ifndef UNDERGLOWMANAGER_H
#define UNDERGLOWMANAGER_H

#include <Arduino.h>
#include <FastLED.h>

class UnderglowManager
{
public:
	UnderglowManager();
	void setup();
	void setColor(CRGB color);

private:
	CRGB leds1[10];
	CRGB leds2[10];
	CRGB leds3[10];
	CRGB leds4[10];
};

#endif
