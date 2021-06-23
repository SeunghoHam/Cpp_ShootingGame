#pragma once
#include<d3dx9.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// 클래스 선언들
class GameBase;

struct Image
{
	BOOL visible;
	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO img_info;
	RECT rect;
	D3DXVECTOR3 position;
	D3DXVECTOR3 center;

	FLOAT collisionRange;
	FLOAT alpha;
};

// 능력치 정보
struct Proper
{
	FLOAT Speed;
	FLOAT Hp;
	FLOAT AttackDamage;
	DWORD MoveTime; // 이동시간 간격
	DWORD OldTime; // 이전이동 시간 
};

enum DIRECT { DOWN_LEFT, LEFT, UP_LEFT };

struct Pat
{                                                                                 
	DIRECT Direct;		// 방향
	INT	Step;			// 스텝
	DWORD MoveTime;		// 이동시간 간격
	FLOAT Distance;		// 이동거리
};

struct Pat_Info
{
	INT Count; // 
	D3DXVECTOR3 StartPosition; // 패턴 시작 좌표
	Pat Pat[4]; // 패턴들을 담고 있는 정보
};