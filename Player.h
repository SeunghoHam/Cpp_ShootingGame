#pragma once
#include "Character.h"
#define myMissile 500
class MISSILE : public Character
{
public :
	Image _image;
	INT _nLife;
	DWORD OldTime;
};
class Player : public Character
{
public:
	Player();
	~Player();
	
	// ���� �Լ�

	MISSILE playerMissile[myMissile];
	DWORD FireTime;
	DWORD OldFireTime;

	// �߰� �Լ�

	INT FrameIndex;
	INT FrameCount;
	INT FrameWidth;
	INT FrameHeight;
	DWORD FrameOldTime;
	DWORD FrameAniTime;

	VOID Init(VOID);
	VOID Update(VOID);
	VOID MissileDraw(VOID);
	
	VOID moveLeft(VOID);
	VOID moveRight(VOID);
	VOID moveUp(VOID);
	VOID moveDown(VOID);
};

