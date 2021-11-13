#include "pch.h"

bool isTimeAttackAllowed = true;
bool isCustomTimeAllowed = true;
bool isInfoAllowed = true;

uint8_t timeAttackMode = 0;

void ReadConfig(const char* path) {

	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");


	isTimeAttackAllowed = config->getBool("General", "isTimeAttackAllowed", true);
	isCustomTimeAllowed = config->getBool("General", "isCustomTimeAllowed", true);
	isInfoAllowed = config->getBool("General", "isInfoAllowed", true);

	delete config;

	if (isTimeAttackAllowed)
		timeAttackMode = 1;

	if (isCustomTimeAllowed && !isTimeAttackAllowed)
		timeAttackMode = 2;

	return;
}