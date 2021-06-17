#pragma once
#include "Character.h"
class Player : public Character
{
public:
	Player();
	~Player();
	VOID Init(VOID);
	VOID Update(VOID);
	
	VOID moveLeft(VOID);
	VOID moveRight(VOID);
	VOID moveUp(VOID);
	VOID moveDown(VOID);
};

