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

VOID Boss::Init()
{
	srand(time(NULL));
	D3DXCreateTextureFromFile(g_pd3dDevice, L"Resources/Boss.png", &_image.texture);
	D3DXGetImageInfoFromFile(L"Resources/Boss.png", &_image.img_info);

	_image.visible = TRUE;
	_image.rect = { 0,0,(LONG)_image.img_info.Width, (LONG)_image.img_info.Height };
	_image.center = { _image.img_info.Width * 0.5f, _image.img_info.Height * 0.5f, 0 };
	//_image.center = { 0,0,0 };
	_image.position = { 570, 300, 0 }; // ������ǥ
	_image.collisionRange = 40.0f; // ���� �ݸ��� ũ��

	_proper.Hp = 10; // ���� ü��
	_proper.Speed = 10;
	_proper.OldTime = timeGetTime();
	_proper.MoveTime = 1000 / 30;

	MissileInit();
	GaugeInit();

	return VOID();
}

VOID Boss::Update()
{
	switch (PatInfo.Pat[PatInfo.Count].Direct)
	{
	case DOWN_LEFT:		nSignX = -1; nSignY = 0;	break;
	case LEFT:			nSignX = -1; nSignY = 0;	break;
	case UP_LEFT:		nSignX = -1; nSignY = -1;	break;
	
	}


	DWORD Curtime = timeGetTime();
	/*if (Curtime - _proper.OldTime > PatInfo.Pat[PatInfo.Count].MoveTime)
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
	}*/

	MissileUpdate();
	GaugeUpdate();
	// ���� ������Ʈ���� ���� ������Ʈ ��Ų��.

	return VOID();
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

VOID Boss::MissileInit()
{
	BossMissile.FireTime = 200; // �̻��� ��ü �߻� �ð� ����
	BossMissile.MoveTime = 100; // �̻��� ��ü �̵� �ð� ����
	BossMissile.OldFireTime = timeGetTime(); // �̻��� ��ü ���� �߻� �ð�

	D3DXCreateTextureFromFile(g_pd3dDevice, L"Resources/Star.png", &BossMissile.sMissile[0]._image.texture);
	D3DXGetImageInfoFromFile(L"Resources/Star.png", &BossMissile.sMissile[0]._image.img_info);
	BossMissile.sMissile[0]._image.visible = TRUE;
	BossMissile.sMissile[0]._image.rect = { 0,0,(LONG)BossMissile.sMissile[0]._image.img_info.Width, (LONG)BossMissile.sMissile[0]._image.img_info.Height };
	BossMissile.sMissile[0]._image.center = { BossMissile.sMissile[0]._image.img_info.Width * 0.5f, _image.img_info.Height * 0.5f, 0 };
	BossMissile.sMissile[0]._image.position = { 570,100,0 };
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
	INT nFireMissileCount =0;

	// �� �߻�
	if (CurTime - BossMissile.OldFireTime > BossMissile.FireTime)
	{
		BossMissile.OldFireTime = CurTime;
		nFireMissileCount = 0;
		for (INT i = 0; i < 30; i++)
		{
			if (BossMissile.sMissile[i].nLife == 0)
			{
				BossMissile.sMissile[i]._image.position.x = _image.position.x; // + 100;
				BossMissile.sMissile[i]._image.position.y = _image.position.y;
				BossMissile.sMissile[i].nLife = 1;
				BossMissile.sMissile[i].nDirect = (DIRECT)(DOWN_LEFT - nFireMissileCount);
				BossMissile.sMissile[i].OldTime = CurTime;
				nFireMissileCount++;
				//PatInfo.Count++;
				if (nFireMissileCount > 2) // ������ �̻��� �ִ� �߻� ����
				{
					break;
				}
			}
		}
	}

	// �̻��� �̵�
	for (INT i = 0; i < 30; i++)
	{
		if (BossMissile.sMissile[i].nLife == 1)
		{
			switch (BossMissile.sMissile[i].nDirect) {
			case DOWN_LEFT:		nSignX = -1; nSignY = 1;	break;
			case LEFT:			nSignX = -1; nSignY = 0;	break;
			case UP_LEFT:		nSignX = -1; nSignY = -1;	break;
			}



			BossMissile.sMissile[i]._image.position.x += nSignX *1.3f;
			BossMissile.sMissile[i]._image.position.y += nSignY * 1.3f;

			//BossMissile.sMissile[i]._image.position.x += nSignX * PatInfo.Pat[PatInfo.Count].Distance;
			//BossMissile.sMissile[i]._image.position.y += nSignY * PatInfo.Pat[PatInfo.Count].Distance;


			// ���� ������ ���� ��� �̻��� ����� 0
			if (BossMissile.sMissile[i]._image.position.x < 0) 
				BossMissile.sMissile[i].nLife = 0;

			// �̵� ���� �̻��� �� �浹
			if (g_Player.Collision(g_Player.GetImage(), BossMissile.sMissile[i]._image)) // Collision(A,B) A �� B�� �浹
			{
				//BossMissile.sMissile[i].nLife = 0; // �浹 ���J��
				//BossMissile.sMissile[i]._image.position.x = 1000;
			}
		}
		
	}
	return VOID();
}

VOID Boss::MissileDraw()
{
	for (INT i = 0; i < 30; i++) {
		if (BossMissile.sMissile[i].nLife == 1) {
			_pSprite->Draw(BossMissile.sMissile[i]._image.texture,
				&BossMissile.sMissile[i]._image.rect,
				&BossMissile.sMissile[i]._image.center,
				&BossMissile.sMissile[i]._image.position, D3DXCOLOR(1.0f,1.0f,1.0f,_image.alpha));
		}
	}
	return VOID();
}

VOID Boss::MissileRelease()
{
	for (INT i = 0; i < 30; i++) {
		BossMissile.sMissile[i]._image.texture->Release();
	}
	return VOID();
}

VOID Boss::GaugeInit()
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
