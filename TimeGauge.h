#pragma once
#include "Character.h"
class TimeGauge : public Character
{
public:
	BOOL GameOver;
	Image timeGauge;
	Image timeGaugeBG;

	DWORD OldTime;
	DWORD Decrease;

	TimeGauge();
	~TimeGauge();
	VOID Init();
	VOID Update();
	VOID Draw();
	
};

