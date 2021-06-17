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
	DWORD MoveTime; // �̵��ð� ����
	DWORD OldTime; // �����̵� �ð�
};

enum DIRECT {UP, UP_RIGHT, RIGHT ,DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT};

struct  Pattern
{
	DIRECT Direct;		// ����
	INT Step;			// ����
	DWORD MoveTime;		// �̵��ð� ����
	FLOAT Distance;		// �̵��Ÿ�
};

struct Pattern_Info
{
	INT Count;			
	D3DXVECTOR3 StartPosition;	// ���� ��ǥ
	Pattern Pat[4];				// ���ϵ��� ��� �ִ� ����
};