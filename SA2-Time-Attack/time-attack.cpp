#include "pch.h"
#include "time-attack.h"

Trampoline* CheckAndLoadCountDown_t;
SaveLevelInfo* savePtr = nullptr;

SaveLevelInfo* GetSavePtr() {

	if (CurrentLevel == LevelIDs_Route101280)
	{
		return (SaveLevelInfo*)&SaveBossKartPtr;
	}

	if (CurrentLevel >= LevelIDs_BigFoot)
		return nullptr;

	return (SaveLevelInfo*)&PlayerLevelStatsArray[196 * CurrentLevel];
}


void CheckAndLoadCountDown_r(char min, char sec) {


	if (pbRace)
	{
		//get player level stat information from the weird save struct.
		savePtr = GetSavePtr();

		if (savePtr) {

			char round = 0;
			char sec = savePtr->Scores->Time.Seconds;
			char min = savePtr->Scores->Time.Minutes;

			int mission = MissionNum;

			if (mission > 0)
				mission *= 3; //used to reach the correct mission slot in the struct

			if (savePtr->Scores[mission].Time.Centiseconds >= 52) //if MS are close to one second, just round them.
			{
				round = 1;
			}

			if (min < 30) { //The game set your PB to 30 min when you never played a stage, we don't want the timer to start in that case.

				if (min > 0 || sec > 0) {

					LoadCountDownTimer(savePtr->Scores[mission].Time.Minutes, savePtr->Scores[mission].Time.Seconds + round);
					return;
				}
			}
		}
	}

	VoidFunc(original, CheckAndLoadCountDown_t->Target());
	original();
}


void init_TimeAttack() {

	CheckAndLoadCountDown_t = new Trampoline((int)CheckAndLoadCountDown, (int)CheckAndLoadCountDown + 0x5, CheckAndLoadCountDown_r);
	return;
}
