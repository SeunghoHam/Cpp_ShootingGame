#pragma once
#include<d3dx9.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class GameBase;

struct Image
{
	BOOL visible;
	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO img_info;
	RECT rect;
	D3DXVECTOR3 center;
	D3DXVECTOR3 position;

	FLOAT collisionRange;
	FLOAT alpha;
	
};

struct Proper
{
	FLOAT Speed;
	FLOAT Hp;
	FLOAT AttackDamage;
	DWORD MoveTime; // 이동시간 간격
	DWORD OldTime; // 이전이동 시각
};

enum DIRECT {UP, UP_RIGHT, RIGHT ,DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT};

struct  Pattern
{
	DIRECT Direct;		// 방향
	INT Step;			// 스텝
	DWORD MoveTime;		// 이동시간 간격
	FLOAT Distance;		// 이동거리
};

struct Pattern_Info
{
	INT Count;			
	D3DXVECTOR3 StartPosition;	// 시작 좌표
	Pattern Pat[4];				// 패턴들을 담고 있는 정보
};