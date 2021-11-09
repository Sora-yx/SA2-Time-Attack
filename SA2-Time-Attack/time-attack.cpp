#include "pch.h"
#include "time-attack.h"

Trampoline* CheckAndLoadCountDown_t;



void CheckAndLoadCountDown_r(char min, char sec) {

	if (pbRace)
	{
		LoadCountDownTimer(3, 0);
		return;
	}


	VoidFunc(original, CheckAndLoadCountDown_t->Target());
	original();
}


void init_TimeAttack() {

	CheckAndLoadCountDown_t = new Trampoline((int)CheckAndLoadCountDown, (int)CheckAndLoadCountDown + 0x5, CheckAndLoadCountDown_r);
	return;
}
