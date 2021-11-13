#include "pch.h"
#include "time-attack.h"

Trampoline* CheckAndLoadCountDown_t;
SaveLevelInfo* savePtr = nullptr;
uint8_t msgDelay = 0;
uint8_t inputDelay = 0;

SaveLevelInfo* GetSavePtr() {

	if (CurrentLevel == LevelIDs_Route101280)
	{
		return (SaveLevelInfo*)&SaveBossKartPtr;
	}

	if (CurrentLevel >= LevelIDs_BigFoot)
		return nullptr;

	return (SaveLevelInfo*)&PlayerLevelStatsArray[196 * CurrentLevel];
}

bool SetTimeAttack_PB() {

	if (timeAttackMode != PB || CurrentLevel >= LevelIDs_BigFoot && CurrentLevel != LevelIDs_Route101280)
		return false;

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
				return true;
			}
		}
	}

	return false;
}

bool SetTimeAttack_Goal() {

	if (timeAttackMode != Custom)
		return false;

	LoadCountDownTimer(3, 0);
	return true;
}

void FixTimerPosition() {
	
	float vanillaPos = 48.0f;
	float newPos = 74.0f;

	if (isKartLevel()) {
		MinCountdown_Sprite.posY = newPos;
		MSCountdown_Sprite.posY = newPos;
		SecCountdown_Sprite.posY = newPos;
		ColonCountdown_Sprite.posY = newPos;
		Colon2Countdown_Sprite.posY = newPos;
	}
	else {
		MinCountdown_Sprite.posY = vanillaPos;
		MSCountdown_Sprite.posY = vanillaPos;
		SecCountdown_Sprite.posY = vanillaPos;
		ColonCountdown_Sprite.posY = vanillaPos;
		Colon2Countdown_Sprite.posY = vanillaPos;
	}

	return;
}

void CheckAndLoadCountDown_r(char min, char sec) {

	FixTimerPosition();

	if (SetTimeAttack_PB() || SetTimeAttack_Goal())
		return;

	VoidFunc(original, CheckAndLoadCountDown_t->Target());
	original();
}


void DisplayBestTime(char min, char sec, char ms) {

	if (!min && !sec && !ms)
		return;

	SetDebugFontColor(lightBlue);
	DisplayDebugStringFormatted(NJM_LOCATION(2, 10), "Best Time:");
	DisplayDebugStringFormatted(NJM_LOCATION(12, 10), "%d:", min);
	DisplayDebugStringFormatted(NJM_LOCATION(14, 10), "%d.", sec);
	DisplayDebugStringFormatted(NJM_LOCATION(16, 10), " %d", ms);
}

void DisplayBestRingsAndScore(short Rings, int score, int mission) {

	if (!Rings && !score)
		return;

	SetDebugFontColor(lightOrange);

	if (Rings)
		DisplayDebugStringFormatted(NJM_LOCATION(2, 12), "Best Rings:%d", Rings);

	if (MissionNum != 1 && MissionNum != 2 && score) {
		SetDebugFontColor(lightGreen);
		DisplayDebugStringFormatted(NJM_LOCATION(2, 14), "Best Score:%d", score);
	}

	return;
}

void DisplayCustomTimeGoal(char min, char sec) {
	DisplayDebugStringFormatted(NJM_LOCATION(2, 16), "Goal:");
	DisplayDebugStringFormatted(NJM_LOCATION(12, 16), "%d:", min);
	DisplayDebugStringFormatted(NJM_LOCATION(14, 16), "%d", sec);
}

void DisplayARankRequirement(int posY) {

	if (CurrentLevel >= LevelIDs_BigFoot && CurrentLevel != LevelIDs_Route101280)
		return;


	SetDebugFontColor(pinkColor);

	DisplayDebugStringFormatted(NJM_LOCATION(2, posY), "A Rank Requirement:");

	if (CurrentLevel == LevelIDs_Route101280)
	{
		MinSec timerR = Get_ARank_TimeRequirement();

		DisplayDebugStringFormatted(NJM_LOCATION(2, posY + 1), "%d:", timerR.Minutes);
		DisplayDebugStringFormatted(NJM_LOCATION(4, posY + 1), "%d", timerR.Seconds);
	}


	if (!MissionNum || MissionNum >= 3) {

		int score = Get_ARank_ScoreRequirement();

		if (score != NULL) {
			DisplayDebugStringFormatted(NJM_LOCATION(2, posY + 1), "Score:%d", score);
		}
	}
	else {

		MinSec timer = Get_ARank_TimeRequirement();

		if (timer.Minutes != 0 || timer.Seconds != 0) {
			DisplayDebugStringFormatted(NJM_LOCATION(2, posY + 1), "%d:", timer.Minutes);
			DisplayDebugStringFormatted(NJM_LOCATION(4, posY + 1), "%d", timer.Seconds);
		}


	}

	return;
}

void DisplayCurrentTimeBonus(int posY) {

	if (CurrentLevel >= LevelIDs_BigFoot)
		return;

	int bonus = getCurrentTimeBonus();

	if (bonus > 0)
		DisplayDebugStringFormatted(NJM_LOCATION(2, posY + 4), "Time Bonus:%d", bonus);

	return;
}

void DisplayRankEstimate(int posY) {

	std::string Rank = getCurrentRankPace();
	DisplayDebugStringFormatted(NJM_LOCATION(2, posY + 6), "Rank Estimate:");
	DisplayDebugStringFormatted(NJM_LOCATION(16, posY + 6), Rank.c_str());
	return;

}

void DisplayMissionGoal() {
	const char* missionText = getCurrentMission();


	if (missionText != nullptr)
	{
		DisplayDebugStringFormatted(NJM_LOCATION(2, 8), missionText);
	}
}

void Pause_DisplayInformation() {

	if (!savePtr || GameState != GameStates_Pause)
		return;

	int mission = MissionNum;

	if (mission > 0)
		mission *= 3; //used to reach the correct mission slot in the struct

	char min = savePtr->Scores[mission].Time.Minutes;
	char sec = savePtr->Scores[mission].Time.Seconds;
	char ms = savePtr->Scores[mission].Time.Centiseconds;

	int posY = 16;

	DisplayMissionGoal();
	DisplayBestTime(min, sec, ms);
	DisplayBestRingsAndScore(savePtr->Scores[mission].Rings, savePtr->Scores[mission].Score, mission);

	SetDebugFontColor(purpleColor);
	if (timeAttackMode == Custom)
	{
		posY = 18;
		DisplayCustomTimeGoal(min, sec);
	}

	DisplayARankRequirement(posY);
	SetDebugFontColor(greyColor);
	DisplayCurrentTimeBonus(posY);
	DisplayRankEstimate(posY);
	SetDebugFontColor(greyColor);
	return;
}

void DisplayTimeAttackMode() {

	if (!msgDelay)
		return;

	SetDebugFontColor(greyColor);
	DisplayDebugStringFormatted(NJM_LOCATION(2, 3), "TIME ATTACK MODE:");

	std::string mode;

	switch (timeAttackMode)
	{
	case off:
	default:
		mode = "DISABLED";
		SetDebugFontColor(redColor);
		break;
	case PB:
		mode = "PERSONAL BEST";
		SetDebugFontColor(lightGreen);
		break;
	case Custom:
		mode = "CUSTOM TIME (GOAL)";
		SetDebugFontColor(lightBlue);
		break;
	}


	DisplayDebugStringFormatted(NJM_LOCATION(20, 3), mode.c_str());
	msgDelay--;
	SetDebugFontColor(greyColor);
	return;
}

void TimeAttack_ChangeMode() {

	if (inputDelay > 0) {
		inputDelay--;
		return;
	}

	if (GameState != 0 || GameMode != GameMode_Advertise || (ControllerPointers[0]->press & Buttons_Y) == 0)
	{
		return;
	}


	msgDelay = 120;
	inputDelay = 10;

	switch (timeAttackMode)
	{
	case off:
	default:
		timeAttackMode = PB;
		return;
	case PB:
		timeAttackMode = Custom;
		return;
	case Custom:
		timeAttackMode = off;
		return;
	}

}

void TimeAttack_OnFrames() {
	TimeAttack_ChangeMode();
	DisplayTimeAttackMode();
	Pause_DisplayInformation();
	return;
}


void init_TimeAttack() {

	CheckAndLoadCountDown_t = new Trampoline((int)CheckAndLoadCountDown, (int)CheckAndLoadCountDown + 0x5, CheckAndLoadCountDown_r);
	return;
}
