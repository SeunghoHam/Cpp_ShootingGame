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

	EnemyMissile m_EnemyMissile[ENEMY_MISSILE]; // 미사일 버퍼 들어갈 부분	
	INT EnemyIndex; // 적 인덱스
	DWORD StartTime; // 게임 시작 시간
	DWORD GroupAppearTime; // 그룹 출현 시간

	GroupEnemy();
	~GroupEnemy();

	VOID Init();
	VOID Update();
	VOID Draw();

};

