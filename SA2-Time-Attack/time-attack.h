#pragma once

VoidFunc(CheckAndLoadCountDown, 0x451F00);
FunctionPointer(void, LoadCountDownTimer, (char a1, char a2), 0x451EA0);
DataArray(char, PlayerLevelStatsArray, 0x1DEC638, 17640); //weird ass struct save used to get player level stats


DataPointer(char, SaveBossKartPtr, 0x1DEF428);