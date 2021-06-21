#pragma once
#include "Character.h"

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
	

	DWORD FireTime;
	DWORD OldFireTime;

	VOID Init(VOID);
	VOID Update(VOID);
	VOID MissileDraw(VOID);
	
	VOID moveLeft(VOID);
	VOID moveRight(VOID);
	VOID moveUp(VOID);
	VOID moveDown(VOID);
};

