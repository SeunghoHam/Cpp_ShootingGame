#include "Boss.h"
#include "Player.h" // �浹 �����Ϸ��� �����µ�
#include <time.h>

extern LPDIRECT3DDEVICE9 g_pd3dDevice;
extern Player g_Player;

Boss::Boss()
{
}

Boss::~Boss()
{
}

VOID Boss::Damaged()
{
	if (_proper.Hp > 0)
		_proper.Hp--;
}

VOID Boss::SetHp(INT hp)
{
	_proper.Hp = hp;
}

VOID Boss::SetPositionX(FLOAT x)
{
	_image.position.x = x;
}

VOID Boss::SetVisible(BOOL visible)
{
	_image.visible = visible;
}

VOID Boss::PatInit()
{
	Index = 0;
	PatInfo.Count = 0;
	// ���� �����ؼ� �����ô�~
	return VOID();
}

VOID Boss::Init(std::wstring _filename)
{
	srand(time(NULL));
	D3DXCreateTextureFromFile(g_pd3dDevice, _filename.c_str(), &_image.texture);
	D3DXGetImageInfoFromFile(_filename.c_str(), &_image.img_info);

	_image.visible = TRUE;
	_image.rect = { 0,0,(LONG)_image.img_info.Width, (LONG)_image.img_info.Height };
	_image.center = { _image.img_info.Width * 0.5f, _image.img_info.Height * 0.5f, 0 };
	_image.position = { 200, 100, 0 }; // ������ǥ
	_image.collisionRange = 100.0f; // ���� �ݸ��� ũ��

	_proper.Hp = 10; // ���� ü��
	_proper.Speed = 10;
	_proper.OldTime = timeGetTime();
	_proper.MoveTime = 1000 / 30;

	MissileInit(L"missileimagename");
	GaugeInit(L"gaugeimagename");

	return VOID();
}

VOID Boss::Update()
{
	switch (PatInfo.Pat[PatInfo.Count].Direct)
	{
	case UP: nSignX = 0; nSignY = -1; break;
	
	}
	return VOID();

	DWORD Curtime = timeGetTime();
	if (Curtime - _proper.OldTime > PatInfo.Pat[PatInfo.Count].MoveTime)
	{
		_proper.OldTime = Curtime;
		Index++;
		if (Index > PatInfo.Pat[PatInfo.Count].Step)
		{
			PatInfo.Count++;
			Index = 0;
			if (PatInfo.Count > 3)
				PatInfo.Count = 0;
		}

		_image.position.x += nSignX * PatInfo.Pat[PatInfo.Count].Distance;
		_image.position.y += nSignY * PatInfo.Pat[PatInfo.Count].Distance;
		// distnace = GameData �� ���ǵǾ� �ִ� �̵��Ÿ�
	}

	MissileUpdate();
	GaugeUpdate();
	// ���� ������Ʈ���� ���� ������Ʈ ��Ų��.
}

VOID Boss::Draw()
{
	if (_proper.Hp > 0)
	{
		_pSprite->Draw(_image.texture, &_image.rect, &_image.center, &_image.position, 0xffffffff);
	}
	MissileDraw();
	GaugeDraw();
	
	// ���� ��ο쿡�� ���� �׸���.
	return VOID();
}

VOID Boss::Release()
{
	_image.texture->Release();
	MissileRelease();
	GaugeRelease();
	return VOID();
}

VOID Boss::MissileInit(std::wstring _filename)
{
	BossMissile.FireTime = 200; // �̻��� ��ü �߻� �ð� ����
	BossMissile.MoveTime = 100; // �̻��� ��ü �̵� �ð� ����
	BossMissile.OldFireTime = timeGetTime(); // �̻��� ��ü ���� �߻� �ð�

	D3DXCreateTextureFromFile(g_pd3dDevice, _filename.c_str(), &BossMissile.sMissile[0]._image.texture);
	D3DXGetImageInfoFromFile(_filename.c_str(), &BossMissile.sMissile[0]._image.img_info);
	BossMissile.sMissile[0]._image.visible = TRUE;
	BossMissile.sMissile[0]._image.rect = { 0,0,(LONG)BossMissile.sMissile[0]._image.img_info.Width, (LONG)BossMissile.sMissile[0]._image.img_info.Height };
	BossMissile.sMissile[0]._image.center = { BossMissile.sMissile[0]._image.img_info.Width * 0.5f, _image.img_info.Height * 0.5f, 0 };
	BossMissile.sMissile[0]._image.position = { 200,100,0 };
	BossMissile.sMissile[0]._image.collisionRange = 16.0f;

	BossMissile.sMissile[0].nLife = 0;
	BossMissile.sMissile[0].OldTime = timeGetTime();
	for (INT i = 1; i < 30; i++) 
	{
		BossMissile.sMissile[i] = BossMissile.sMissile[0]; // sMissile[0] �� ����� �ý���(��������Ʈ)�� �����̻��� 30���� �����Ų��.
	}

	return VOID();
}

VOID Boss::MissileUpdate()
{
	DWORD CurTime = timeGetTime();
	INT nFireMissileCount;
	return VOID();
}

VOID Boss::MissileDraw()
{
	return VOID();
}

VOID Boss::MissileRelease()
{
	return VOID();
}

VOID Boss::GaugeInit(std::wstring _filename)
{
	return VOID();
}

VOID Boss::GaugeUpdate()
{
	return VOID();
}

VOID Boss::GaugeDraw()
{
	return VOID();
}

VOID Boss::GaugeRelease()
{
	return VOID();
}
