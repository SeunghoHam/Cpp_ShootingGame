#pragma once
#include "Character.h"
class Hit : public Character
{
public:
	Image _image;
	DWORD HitStartTime;
	DWORD HitStayTime;

};
class Explode : public Character
{
public:
	Explode();
	~Explode();

	Hit hitEffect;

	DWORD StartTime; // ����Ʈ ���� �ð�
	DWORD StayTime; // ����Ʈ ���� �ð�

	INT FrameIndex; // ������ �ε���
	INT FrameCount; // ������ ����
	INT FrameWidth; // ������ �ʺ�
	INT FrameHeight; // ������ ����

	DWORD FrameOldTime; // ���� �������� �׷��� �ð� Old
	DWORD FrameAniTime; // �������� ��ȯ�ӵ�

	

	VOID SetVisible(BOOL visible);
	VOID SetPosition(D3DXVECTOR3 position);
	VOID Init();
	VOID Update(VOID);
	VOID Draw(VOID);

	
	VOID effectInit();
	VOID effectUpdate();
	VOID effectDraw();
	VOID SethitEffectVisible(BOOL visible);
	VOID SethitEffectPosition(D3DXVECTOR3 position);
};

