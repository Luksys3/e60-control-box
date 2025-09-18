#ifndef SDCARDSTORAGE_H
#define SDCARDSTORAGE_H

#include <Arduino.h>
#include <SD.h>

class SDCardStorage
{
public:
	SDCardStorage(int chipSelectPin);

	bool begin();
	String readFileContents(const String &filename);
	void listFiles();

private:
	int csPin; // Chip select pin for SD card
};

#endif
