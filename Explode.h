#pragma once
#include "Character.h"
#include<string>
class Explode : public Character
{
public:
	Explode();
	~Explode();

	DWORD StartTime; // 이펙트 시작 시간
	DWORD StayTime; // 이펙트 지속 시간

	INT FrameIndex; // 프레임 인덱스
	INT FrameCount; // 프레임 개수
	INT FrameWidth; // 프레임 너비
	INT FrameHeight; // 프레임 높이

	DWORD FrameOldTime; // 이전 프레임이 그려진 시각 Old
	DWORD FrameAniTime; // 프레임의 전환속도

	VOID SetVisible(BOOL visible);
	VOID SetPosition(D3DXVECTOR3 position);
	VOID Init();
	VOID Update(VOID);
	VOID Draw(VOID);

	VOID effectInit();
	VOID effectUpdate();
	VOID effectDraw();
};

