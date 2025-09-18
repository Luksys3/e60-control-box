#include <Arduino.h>

#include "OneWire.h"
#include "DallasTemperature.h"

#include "SDCardStorage.h"
#include "UnderGlowManager.h"

const int ONE_WIRE_BUS = A14;

// Create a new instance of the oneWire class to communicate with any OneWire device:
OneWire oneWire(ONE_WIRE_BUS);

// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);

const int BUTTON_LED_1 = 5;
const int BUTTON_LED_2 = 9;
const int BUTTON_LED_3 = 11;
const int BUTTON_LED_4 = 13;
const int BUTTON_LED_5 = 23;
const int BUTTON_LED_6 = 25;

const int BUTTON_1 = 6;
const int BUTTON_2 = 7;
const int BUTTON_3 = 12;
const int BUTTON_4 = 20;
const int BUTTON_5 = 21;
const int BUTTON_6 = 22;

const int EXHAUST_PIN = 40;
const int REGULATOR_PIN = 34;
const int OUTSIDE_LEDS_PIN = 36;
const int INSIDE_LEDS_PIN = 38;

const int SD_CARD_CHIP_SELECT = 10;

SDCardStorage storage(10); // CS pin 10

UnderGlowManager underGlow;

void setup()
{
	Serial.begin(115200); // USB to PC for debugging

	Serial1.begin(115200); // UART1 for KT6368A
	Serial1.println("AT+NAME=E60");

	underGlow.setup();

	pinMode(EXHAUST_PIN, OUTPUT);
	pinMode(REGULATOR_PIN, OUTPUT);
	pinMode(OUTSIDE_LEDS_PIN, OUTPUT);
	pinMode(INSIDE_LEDS_PIN, OUTPUT);

	pinMode(BUTTON_LED_1, OUTPUT);
	pinMode(BUTTON_LED_2, OUTPUT);
	pinMode(BUTTON_LED_3, OUTPUT);
	pinMode(BUTTON_LED_4, OUTPUT);
	pinMode(BUTTON_LED_5, OUTPUT);
	pinMode(BUTTON_LED_6, OUTPUT);

	pinMode(BUTTON_1, INPUT_PULLUP);
	pinMode(BUTTON_2, INPUT_PULLUP);
	pinMode(BUTTON_3, INPUT_PULLUP);
	pinMode(BUTTON_4, INPUT_PULLUP);
	pinMode(BUTTON_5, INPUT_PULLUP);
	pinMode(BUTTON_6, INPUT_PULLUP);

	if (storage.begin())
	{
		Serial.println("SD card initialized!");

		storage.listFiles();

		String fileData = storage.readFileContents("S~1.JSO");
		Serial.println("File contents:");
		Serial.println(fileData);
	}
	else
	{
		Serial.println("SD card init failed!");
	}

	// Start up the library:
	sensors.begin();
}

int inds = 0;
bool exhaust_on = false;

void loop()
{
	// Forward data from Bluetooth → Serial Monitor
	if (Serial1.available())
	{
		char c = Serial1.read();
		Serial.write(c);

		if (c == 'e')
		{
			exhaust_on = true;
		}
		if (c == 'r')
		{
			exhaust_on = false;
		}
	}

	digitalWrite(EXHAUST_PIN, LOW); // exhaust_on ? HIGH : LOW);
	digitalWrite(REGULATOR_PIN, exhaust_on ? HIGH : LOW);
	digitalWrite(OUTSIDE_LEDS_PIN, LOW);
	digitalWrite(INSIDE_LEDS_PIN, LOW);

	// Send the command for all devices on the bus to perform a temperature conversion:
	sensors.requestTemperatures();

	// Fetch the temperature in degrees Celsius for device index:
	float tempC = sensors.getTempCByIndex(0); // the index 0 refers to the first device
	// Fetch the temperature in degrees Fahrenheit for device index:
	float tempF = sensors.getTempFByIndex(0);

	// Print the temperature in Celsius in the Serial Monitor:
	Serial.print("Temperature: ");
	Serial.print(tempC);
	Serial.print(" \xC2\xB0"); // shows degree symbol
	Serial.print("C  |  ");

	// Print the temperature in Fahrenheit
	Serial.print(tempF);
	Serial.print(" \xC2\xB0"); // shows degree symbol
	Serial.println(inds++);

	// Wait 1 second:
	delay(1000);
}
