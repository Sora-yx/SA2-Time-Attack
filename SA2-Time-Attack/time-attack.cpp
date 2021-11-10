#include "pch.h"
#include "time-attack.h"

Trampoline* CheckAndLoadCountDown_t;
SaveLevelInfo* savePtr = nullptr;


void CheckAndLoadCountDown_r(char min, char sec) {

	if (pbRace)
	{
		savePtr = (SaveLevelInfo*)&levelThing[196 * CurrentLevel];
		int mission = MissionNum;

		if (mission > 0)
			mission *= 3;

		if (savePtr) {

			if (savePtr->Scores->Time.Minutes > 0 || savePtr->Scores->Time.Seconds > 0) {
				LoadCountDownTimer(savePtr->Scores[mission].Time.Minutes, savePtr->Scores[mission].Time.Seconds);
				return;
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
