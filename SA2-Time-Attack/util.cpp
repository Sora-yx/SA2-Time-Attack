#include "pch.h"


int getCurrentTimeBonus() {

	if (MissionNum == 1 || MissionNum == 2)
		return 0;

	int TimeBonus = TimerSeconds + 60 * TimerMinutes;
	int penalty;


	if (TimeBonus < 60)
	{
		TimeBonus = 60;
	}

	penalty = 20 * (500 - (TimeBonus - 60));
	TimeBonus = penalty;


	return TimeBonus;
}


MinSec Get_ARank_TimeRequirement() {

	int level = CurrentLevel;

	if (level >= LevelIDs_CannonsCoreS && level <= LevelIDs_CannonsCoreK)
		level = LevelIDs_CannonsCoreS;

	if (level == LevelIDs_Route101280)
	{
		if (CurrentCharacter == Characters_Rouge)
			return Route280MissionTimes[MissionNum].ARank;
		else
			return Route101MissionTimes[MissionNum].ARank;
	}

	int arraySize = 30;

	if (MissionNum == 1)
	{
		arraySize = 34;
	}

	for (Uint8 i = 0; i < arraySize; i++) {

		if (MissionNum == 1 && level == Mission2Times[i].Level) {
			return Mission2Times[i].ARank;
		}

		if (MissionNum == 2 && level == Mission3Times[i].Level) {
			return Mission3Times[i].ARank;
		}
	}

	MinSec min = { 0, 0 };
	return min;
}

int Get_ARank_ScoreRequirement() {

	int arraySize = 30;
	int level = CurrentLevel;

	if (CurrentLevel >= LevelIDs_CannonsCoreS && CurrentLevel <= LevelIDs_CannonsCoreK)
		level = LevelIDs_CannonsCoreS;

	for (Uint8 i = 0; i < arraySize; i++) {

		if (!MissionNum && level == Mission1Scores[i].Level) {
			return Mission1Scores[i].ARank * 100;
		}

		if (MissionNum == 3 && level == Mission4Scores[i].Level) {
			return Mission4Scores[i].ARank * 100;
		}

		if (MissionNum == 4 && level == Mission5Scores[i].Level) {
			return Mission5Scores[i].ARank * 100;
		}
	}

	return NULL;
}

std::string calcCurrentRankScore(int score, short rankD, short rankC, short rankB, short rankA) {

	if (score < rankD * 100)
		return "E";

	if (score < rankC * 100)
		return "D";

	if (score < rankB * 100)
		return "C";

	if (score < rankA * 100)
		return "B";

	return "A";
}

std::string calcCurrentRankTime(MinSec time, MinSec rankD, MinSec rankC, MinSec rankB, MinSec rankA) {

	if (time.Minutes > rankD.Minutes || time.Seconds > rankD.Seconds && time.Minutes >= rankD.Minutes)
		return "E";

	if (time.Minutes > rankC.Minutes || time.Seconds > rankC.Seconds && time.Minutes >= rankC.Minutes)
		return "D";

	if (time.Minutes > rankB.Minutes || time.Seconds > rankB.Seconds && time.Minutes >= rankB.Minutes)
		return "C";

	if (time.Minutes > rankA.Minutes || time.Seconds > rankA.Seconds && time.Minutes >= rankA.Minutes)
		return "B";

	return "A";
}


std::string getCurrentRankPace() {

	std::string Rank = "E";

	if (RingCount[0] >= PerfectRings)
	{
		Rank = "A";
	}

	int bonus = getCurrentTimeBonus();
	int result = ScoreP1 + bonus;

	int arraySize = 30;

	if (MissionNum == 1)
		arraySize = 34;

	MinSec timer = { TimerMinutes, TimerSeconds };

	for (Uint8 i = 0; i < arraySize; i++) {

		if (!MissionNum && CurrentLevel == Mission1Scores[i].Level) {
			Rank = calcCurrentRankScore(result, Mission1Scores[i].DRank, Mission1Scores[i].CRank, Mission1Scores[i].BRank, Mission1Scores[i].ARank);
			break;
		}

		if (MissionNum == 1 && CurrentLevel == Mission2Times[i].Level) {
			Rank = calcCurrentRankTime(timer, Mission2Times[i].DRank, Mission2Times[i].CRank, Mission2Times[i].BRank, Mission2Times[i].ARank);
			break;
		}

		if (MissionNum == 2 && CurrentLevel == Mission3Times[i].Level) {
			Rank = calcCurrentRankTime(timer, Mission3Times[i].DRank, Mission3Times[i].CRank, Mission3Times[i].BRank, Mission3Times[i].ARank);
			break;
		}

		if (MissionNum == 3 && CurrentLevel == Mission4Scores[i].Level) {
			Rank = calcCurrentRankScore(result, Mission4Scores[i].DRank, Mission4Scores[i].CRank, Mission4Scores[i].BRank, Mission4Scores[i].ARank);
			break;
		}

		if (MissionNum == 4 && CurrentLevel == Mission5Scores[i].Level) {
			Rank = calcCurrentRankScore(result, Mission5Scores[i].DRank, Mission5Scores[i].CRank, Mission5Scores[i].BRank, Mission5Scores[i].ARank);
			break;
		}
	}


	return Rank;
}

bool isKartLevel() {
	return CurrentLevel == LevelIDs_Route101280 || CurrentLevel == LevelIDs_KartRace;
}

const char* getCurrentMission() {

	if (CurrentLevel >= LevelIDs_BigFoot && CurrentLevel != LevelIDs_Route101280)
		return nullptr;

	switch (MissionNum)
	{
	case 0:
	default:
		if (CurrentCharacter == Characters_Knuckles || CurrentCharacter == Characters_Rouge)
		{
			if (!isKartLevel() && (CurrentLevel < LevelIDs_CannonsCoreS || CurrentLevel > LevelIDs_CannonsCoreK)) {
				SetDebugFontColor(lightGreen);
				return "M1: Treasure Hunting";
			}
		}

		return "M1: Beat the Stage";
	case 1:
		SetDebugFontColor(lightOrange);
		return "M2: 100 Rings";
	case 2:
		if (!isKartLevel())
		{
			SetDebugFontColor(lightBlue);
			return "M3: Lost Chao";
		}
		SetDebugFontColor(redColor);
		return "M3: Avoid cars!";
	case 3:
		SetDebugFontColor(redColor);
		if (!isKartLevel())
		{
			return "M4: Time Attack!";
		}
		return "M4: Avoid walls!";
	case 4:
		SetDebugFontColor(purpleColor);
		return "M5: Clear Hard Mode!";
	}
}

void DisplayDebugStringFormatted(Int loc, const char* Format, ...) {
	return HelperFunctionsGlobal.DisplayDebugStringFormatted(loc, Format);
}

void SetDebugFontColor(int color) {
	return HelperFunctionsGlobal.SetDebugFontColor(color);
}

void ScaleDebugFont(int scale)
{
	float FontScale;

	if ((float)HorizontalResolution / (float)VerticalResolution > 1.33f)
		FontScale = floor((float)VerticalResolution / 480.0f);
	else
		FontScale = floor((float)HorizontalResolution / 640.0f);

	HelperFunctionsGlobal.SetDebugFontSize(FontScale * scale);
	return;
}


void initializeDebugText() {

	SetDebugFontColor(0xFFBFBFBF);
	ScaleDebugFont(16);
	return;
}
