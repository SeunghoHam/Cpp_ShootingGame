#pragma once
#include"Enemy.h"

#define ENEMY_NUM 50
#define ENEMY_MISSILE 200

class EnemyMissile : public Character
{
public:
	Image _image;
	INT nLife;
	DWORD OldTime;
	DWORD MoveTime;
	VOID Init();
	VOID Update();
	VOID Draw();
};

class GroupEnemy
{
public:
	Enemy Enemy[ENEMY_NUM];

	EnemyMissile m_EnemyMissile[ENEMY_MISSILE]; // �̻��� ���� �� �κ�	
	INT EnemyIndex; // �� �ε���
	DWORD StartTime; // ���� ���� �ð�
	DWORD GroupAppearTime; // �׷� ���� �ð�

	GroupEnemy();
	~GroupEnemy();

	VOID Init();
	VOID Update();
	VOID Draw();

};

