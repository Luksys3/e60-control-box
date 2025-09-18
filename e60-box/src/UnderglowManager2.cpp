#include "UnderglowManager.h"

UnderglowManager::UnderglowManager() {}

const int LEDSTRIP_PIN_1 = A4;
const int LEDSTRIP_PIN_2 = A6;
const int LEDSTRIP_PIN_3 = A8;
const int LEDSTRIP_PIN_4 = A10;

void UnderglowManager::setup()
{
	FastLED.addLeds<WS2811, LEDSTRIP_PIN_1, GRB>(leds1, 10);
	FastLED.addLeds<WS2811, LEDSTRIP_PIN_2, GRB>(leds2, 10);
	FastLED.addLeds<WS2811, LEDSTRIP_PIN_3, GRB>(leds3, 10);
	FastLED.addLeds<WS2811, LEDSTRIP_PIN_4, GRB>(leds4, 10);

	FastLED.clear();
	FastLED.show();
}

void UnderglowManager::setColor(CRGB color)
{
}