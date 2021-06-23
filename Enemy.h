#pragma once
#include "Character.h"
#include <string>
class Enemy : public Character
{
protected:
	DWORD AppearTime; // �����ð�
	DWORD MissileFireTime; // �߻� �ð� ����
	DWORD MissileOldTime; // ���� �߻� �ð�

public:
	int nType; // �� ����

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

