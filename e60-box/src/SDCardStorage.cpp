#include "SDCardStorage.h"

SDCardStorage::SDCardStorage(int chipSelectPin) : csPin(chipSelectPin) {}

bool SDCardStorage::begin()
{
	return SD.begin(csPin);
}

String SDCardStorage::readFileContents(const String &filename)
{
	if (!SD.exists(filename.c_str()))
		return "NO EXISTS";

	File file = SD.open(filename.c_str());
	if (!file)
		return "FAILED OPEN";

	String contents = "";
	while (file.available())
	{
		contents += (char)file.read();
	}
	file.close();
	return contents;
}

void SDCardStorage::listFiles()
{
	File root = SD.open("/");
	if (!root)
	{
		Serial.println("Failed to open root directory");
		return;
	}

	File entry = root.openNextFile();
	while (entry)
	{
		Serial.print(entry.name()); // may show 8.3 names
		if (entry.isDirectory())
		{
			Serial.println(" <DIR>");
		}
		else
		{
			Serial.print("  SIZE: ");
			Serial.println(entry.size());
		}
		entry.close();
		entry = root.openNextFile();
	}
	root.close();
}
