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

	Image HPGauge;

	VOID Init(VOID);
	VOID Update(VOID);
	VOID MissileDraw(VOID);
	VOID Damaged();

	
	
	D3DXVECTOR3 GetPosition(D3DXVECTOR3 playerPosition);

	
	VOID moveLeft(VOID);
	VOID moveRight(VOID);
	VOID moveUp(VOID);
	VOID moveDown(VOID);


	VOID GaugeInit();
	VOID GaugeUpdate();
	VOID GaugeDraw();
	VOID GaugeRelease();
};

