#include "pch.h"

uint8_t timeAttackMode = 1;

void ReadConfig(const char* path) {

	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
	timeAttackMode = config->getInt("General", "time", 1);

	delete config;

}