#pragma once
#include<d3dx9.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Ŭ���� �����
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

// �ɷ�ġ ����
struct Proper
{
	FLOAT Speed;
	FLOAT Hp;
	FLOAT AttackDamage;
	DWORD MoveTime; // �̵��ð� ����
	DWORD OldTime; // �����̵� �ð� 
};

enum DIRECT { DOWN_LEFT, LEFT, UP_LEFT };

struct Pat
{                                                                                 
	DIRECT Direct;		// ����
	INT	Step;			// ����
	DWORD MoveTime;		// �̵��ð� ����
	FLOAT Distance;		// �̵��Ÿ�
};

struct Pat_Info
{
	INT Count; // 
	D3DXVECTOR3 StartPosition; // ���� ���� ��ǥ
	Pat Pat[4]; // ���ϵ��� ��� �ִ� ����
};