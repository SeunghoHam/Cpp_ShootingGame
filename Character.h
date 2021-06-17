#pragma once
#include "GameBase.h"
#include "GameData.h"
class Character : public GameBase
{
	// ¸â¹öÇÔ¼ö
public:
	Character();
	~Character();
	VOID Draw(VOID);

	Image GetImage(VOID);
	VOID SetImage(Image pImage);

	Proper GetProper(VOID);
	VOID SetProper(Proper pProper);

	DWORD GetOldTime();
	VOID SetOldTime(DWORD pOldTime);

	BOOL Collision(Image A, Image B);
protected:
	DWORD _dwOldTime;
	Image _image;
	Proper _proper;
};

