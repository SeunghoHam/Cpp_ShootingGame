#pragma once
#include "Character.h"
#include <string>

// �̻��� ������Ʈ ����
struct BOSS_MISSILE
{
	Image _image; // �̻��� ���� �̹�������
	INT nLife; // �̻��� ���� ����
	DIRECT nDirect; // �̻��� ���� ����
	DWORD OldTime; // �̻��� ���� �����̵��ð� 

};
// ��ü �̻��� ����
struct BOSS_MISSILE_INFO
{
	DWORD MoveTime; // �̻��� ��ü �̵� �ð� ����
	DWORD FireTime; // �̻��� ��ü �߻� �ð� ����
	DWORD OldFireTime; // �̻��� ��ü ���� �߻� �ð�
	BOSS_MISSILE sMissile[30]; // �ִ� ��� �̻��� ����
};

class Boss : public Character
{
public:
	INT Index;
	Pat_Info PatInfo; // ���� ����

	DIRECT Direcct;					// ���� �̵� ����
	DWORD AppearTime;				// �����ð�
	DWORD MissileFireTime;			// �̻��� �߻� �ð� ����
	DWORD MissileOldTime;			// ���� �̻��� �߻� �ð�
	INT nSignX, nSignY;				// ���� ó�� ��ȣ ����
	BOSS_MISSILE_INFO BossMissile;	// ���� �̻���
	Image BossGauge;				// ���� ������

	BOOL BossDead;

	

	Boss();
	~Boss();

	VOID Damaged();
	VOID SetHp(INT hp);
	VOID SetPositionX(FLOAT x);

	VOID SetVisible(BOOL visible);

	VOID PatInit();

	// {���� ����} [�ʱ�ȭ] [������Ʈ] [�׸���] [����] �Լ�
	VOID Init();
	VOID Turn(INT a);
	VOID Update();
	VOID Draw();
	VOID Release();

	// {���� �̻��� ����} [�ʱ�ȭ] [������Ʈ] [�׸���] [����] �Լ�
	VOID MissileInit();
	VOID MissileUpdate();
	VOID MissileDraw();
	VOID MissileRelease();


	// {���� ������ �� ����} [�ʱ�ȭ] [������Ʈ] [�׸���] [����] �Լ�
	VOID GaugeInit();
	VOID GaugeUpdate();
	VOID GaugeDraw();
	VOID GaugeRelease();
};