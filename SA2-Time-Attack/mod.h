#pragma once

extern uint8_t timeAttackMode;
extern bool isTimeAttackAllowed;
extern bool isCustomTimeAllowed;
extern bool isInfoAllowed;

extern HelperFunctions HelperFunctionsGlobal;

void ReadConfig(const char* path);
void init_TimeAttack();
void initializeDebugText();
void DisplayDebugStringFormatted(Int loc, const char* Format, ...);
void TimeAttack_OnFrames();
void SetDebugFontColor(int color);
const char* getCurrentMission();

enum colorMSG {
	redColor = 0xFFFF0000,
	lightGreen = 0xFF1dcf01,
	lightBlue = 0xFF29c8e1,
	lightOrange = 0xFFec9304,
	pinkColor = 0xFFf165c8,
	greyColor = 0xFFBFBFBF,
	purpleColor = 0xFFc61bde
};