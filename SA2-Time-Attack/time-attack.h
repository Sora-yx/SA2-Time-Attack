#pragma once

enum timeAttackModeE {
	off,
	PB,
	Custom
};

struct CountDownStruct {
	char idk[8];
	float idkF;
	float posX;
	float posY;
	float posZ;
	float idkF2;
	int color;
};

VoidFunc(CheckAndLoadCountDown, 0x451F00);
FunctionPointer(void, LoadCountDownTimer, (char a1, char a2), 0x451EA0);
DataArray(char, PlayerLevelStatsArray, 0x1DEC638, 17640); //weird ass struct save used to get player level stats


DataPointer(char, SaveBossKartPtr, 0x1DEF428);

DataPointer(CountDownStruct, MinCountdown_Sprite, 0x173CA50);
DataPointer(CountDownStruct, ColonCountdown_Sprite, 0x173CA70);
DataPointer(CountDownStruct, SecCountdown_Sprite, 0x173CA90);
DataPointer(CountDownStruct, Colon2Countdown_Sprite, 0x173CAB0);
DataPointer(CountDownStruct, MSCountdown_Sprite, 0x173CAD0);
