#pragma once
#include "Character.h"
class HitEffect : public Character
{
public:
	DWORD StartTime;
	DWORD StayTime;

	HitEffect();
	~HitEffect();
	VOID Setvisible(BOOL visible);
	VOID SetPosition(D3DXVECTOR3 position);
	VOID Init();
	VOID Update();
	VOID Draw();
};

