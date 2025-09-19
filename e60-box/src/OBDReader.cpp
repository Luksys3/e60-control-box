#include "OBDReader.h"

#include <CAN.h> // The OBD2 library depends on the CAN library
#include <OBD2.h>

#define CAN_CS 4
#define CAN_INT 3

OBDReader::OBDReader() {};

void OBDReader::setup()
{
	Serial.println(F("OBD2 data printer"));

	CAN.setPins(CAN_CS, CAN_INT);

	bool began = false;
	for (int i = 0; i < 2; i++)
	{
		Serial.print(F("Attempting to connect to OBD2 CAN bus ... "));

		if (!OBD2.begin())
		{
			Serial.println(F("failed!"));

			delay(1000);
		}
		else
		{
			Serial.println(F("success"));
			began = true;
			break;
		}
	}

	if (began)
	{
		Serial.println();
		Serial.print("VIN = ");
		Serial.println(OBD2.vinRead());
		Serial.print("ECU Name = ");
		Serial.println(OBD2.ecuNameRead());
		Serial.println();
	}

	// TODO: pull CS down? I want to stop CAN communication so that SD card would work
	// OBD2.end();
	// digitalWrite(CAN_CS, HIGH); // release CAN
}