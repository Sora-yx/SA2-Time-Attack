#include "pch.h"

bool pbRace = true;
bool customTime = false;

void ReadConfig(const char* path) {

	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");


	delete config;

}