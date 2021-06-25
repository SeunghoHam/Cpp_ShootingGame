#pragma once
#include "Character.h"
#include<string>
class Explode : public Character
{
public:
	Explode();
	~Explode();

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
};

