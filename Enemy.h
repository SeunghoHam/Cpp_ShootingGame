#pragma once
#include "Character.h"
#include <string>
class Enemy : public Character
{
protected:
	DWORD AppearTime; // 출현시각
	DWORD MissileFireTime; // 발사 시간 간격
	DWORD MissileOldTime; // 이전 발사 시각

public:
	int nType; // 적 종류

	Enemy();
	~Enemy();

	DWORD GetAppearTime();
	VOID SetAppearTime(DWORD time);

	DWORD GetMissileFireTime();
	VOID SetMissileFireTime(DWORD time);

	DWORD GetMissileOldTime();
	VOID SetMissileOldTime(DWORD time);

	VOID Damaged();
	VOID SetHp(INT hp);
	VOID SetPositionY(FLOAT y);

	VOID SetVisible(BOOL visible);

	VOID Init();
	VOID Update(VOID);
	VOID Draw(VOID);
	


};

