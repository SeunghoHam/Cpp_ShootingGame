#pragma once
#include "GameBase.h"
#include "GameData.h"
class Ui : public GameBase
{
public:
	//UI();
	//~UI();

	LPD3DXFONT font;
	VOID Init();
	VOID Update();
	VOID Draw();
	VOID Release();
};

