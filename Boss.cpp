#include "Boss.h"
#include "Player.h" // 충돌 판정하려고 가져온듯
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
	PatInfo.StartPosition = { 690,300,0 };

	PatInfo.Pat[0].Direct = SEMIDOWN;
	PatInfo.Pat[0].MoveTime = 100;
	PatInfo.Pat[0].Distance = 10.0f;
	PatInfo.Pat[0].Step = 10;

	PatInfo.Pat[1].Direct = UP;
	PatInfo.Pat[1].MoveTime = 100;
	PatInfo.Pat[1].Distance = 10.0f; // Distance = 이동거리
	PatInfo.Pat[1].Step = 20; // Step 어떻게 쓰인는지 모르겠음

	PatInfo.Pat[2].Direct = DOWN;
	PatInfo.Pat[2].MoveTime = 100;
	PatInfo.Pat[2].Distance = 10.0f; 
	PatInfo.Pat[2].Step = 20; 

	// 패턴 생각해서 넣읍시다~
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
	_image.position = { 690, 300, 0 }; // 시작좌표
	_image.collisionRange = 64.0f; // 보스 콜리전 크기

	_proper.Hp = 10; // 보스 체력
	_proper.Speed = 10;
	_proper.OldTime = timeGetTime();
	_proper.MoveTime = 1000 / 30;

	BossDead = FALSE;

	MissileInit();
	GaugeInit();

	return VOID();
}

VOID Boss::Turn(INT a)
{
	_image.position.y += 50 * a;
	return VOID();
}


VOID Boss::Update()
{
	switch (PatInfo.Pat[PatInfo.Count].Direct)
	{
	case SEMIDOWN: nSignX = 0; nSignY = 1; break;
	case DOWN: nSignX = 0; nSignY = 1; break;
	case UP: nSignX = 0; nSignY = -1; break;
	//case DOWN_LEFT: nSignX = -1; nSignY = 1; break;
	//case LEFT: nSignX = -1; nSignY = 0; break;
	//case UP_LEFT: nSignX = -1; nSignY = -1; break;


	}


	DWORD Curtime = timeGetTime();

	
	if (Curtime - _proper.OldTime > PatInfo.Pat[PatInfo.Count].MoveTime)
	{
		_proper.OldTime = Curtime;
		Index++;
		if (Index > PatInfo.Pat[PatInfo.Count].Step)
		{
			PatInfo.Count++;
			Index = 1;
			if (PatInfo.Count > 2)
				PatInfo.Count = 1;
		}

		_image.position.x += nSignX * PatInfo.Pat[PatInfo.Count].Distance;
		_image.position.y += nSignY * PatInfo.Pat[PatInfo.Count].Distance;

		
		// distnace = GameData 에 정의되어 있는 이동거리
	}

	MissileUpdate();
	GaugeUpdate();

	if (_proper.Hp <= 0)
		BossDead = TRUE;
	// 보스 업데이트에서 같이 업데이트 시킨다.

	return VOID();
}

VOID Boss::Draw()
{
	if (_proper.Hp > 0)
	{
		_pSprite->Draw(_image.texture, &_image.rect, &_image.center, &_image.position, 0xffffffff);
		MissileDraw();
		GaugeDraw();
	}
	// 보스 드로우에서 같이 그린다.
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
	BossMissile.FireTime = 200; // 미사일 전체 발사 시간 간격
	BossMissile.MoveTime = 100; // 미사일 전체 이동 시간 간격
	BossMissile.OldFireTime = timeGetTime(); // 미사일 전체 이전 발사 시각

	D3DXCreateTextureFromFile(g_pd3dDevice, L"Resources/Star.png", &BossMissile.sMissile[0]._image.texture);
	D3DXGetImageInfoFromFile(L"Resources/Star.png", &BossMissile.sMissile[0]._image.img_info);
	BossMissile.sMissile[0]._image.visible = TRUE;
	BossMissile.sMissile[0]._image.rect = { 0,0,(LONG)BossMissile.sMissile[0]._image.img_info.Width, (LONG)BossMissile.sMissile[0]._image.img_info.Height };
	BossMissile.sMissile[0]._image.center = { BossMissile.sMissile[0]._image.img_info.Width * 0.5f, _image.img_info.Height * 0.5f, 0 };
	BossMissile.sMissile[0]._image.position = { 570,100,0 };
	BossMissile.sMissile[0]._image.collisionRange = 32.0f;

	BossMissile.sMissile[0].nLife = 1;
	BossMissile.sMissile[0].OldTime = timeGetTime();
	for (INT i = 1; i < 30; i++)
	{
		BossMissile.sMissile[i] = BossMissile.sMissile[0]; // sMissile[0] 에 적용된 택스쳐(스프라이트)를 보스미사일 30개에 적용시킨다.
	}

	return VOID();
}

VOID Boss::MissileUpdate()
{
	switch (PatInfo.Pat[PatInfo.Count].Direct)
	{
	//case SEMIDOWN: nSignX = 0; nSignY = 1; break;
	//case DOWN: nSignX = 0; nSignY = 1; break;
	//case UP: nSignX = 0; nSignY = -1; break;
	case DOWN_LEFT: nSignX = -1; nSignY = 0.3f; break;
	case LEFT: nSignX = -1; nSignY = 0; break;
	case UP_LEFT: nSignX = -1; nSignY = -0.3; break;


	}
	DWORD CurTime = timeGetTime();
	INT nFireMissileCount = 0;

	// 별 발사
	if (CurTime - BossMissile.OldFireTime > BossMissile.FireTime)
	{
		BossMissile.OldFireTime = CurTime;
		nFireMissileCount = 0;
		for (INT i = 0; i < 30; i++)
		{
			if (BossMissile.sMissile[i].nLife == 0)
			{
				BossMissile.sMissile[i]._image.position.x = _image.position.x + 100; // + 100;
				BossMissile.sMissile[i]._image.position.y = _image.position.y;
				BossMissile.sMissile[i].nLife = 1;
				BossMissile.sMissile[i].nDirect = (DIRECT)(DOWN_LEFT - nFireMissileCount);
				BossMissile.sMissile[i].OldTime = CurTime;
				nFireMissileCount++;
				//PatInfo.Count++;
				if (nFireMissileCount > 3) // 보스의 미사일 최대 발사 개수
				{
					break;
				}
			}
		}
	}

	// 미사일 이동
	for (INT i = 0; i < 30; i++)
	{
		if (BossMissile.sMissile[i].nLife == 1)
		{
			switch (BossMissile.sMissile[i].nDirect) {
			case DOWN_LEFT:		nSignX = -1; nSignY = 0.5f;	break;
			case LEFT:			nSignX = -1; nSignY = 0;	break;
			case UP_LEFT:		nSignX = -1; nSignY = -0.5;	break;
			}



			BossMissile.sMissile[i]._image.position.x += nSignX * 1.3f;
			BossMissile.sMissile[i]._image.position.y += nSignY * 1.3f;

			//BossMissile.sMissile[i]._image.position.x += nSignX * PatInfo.Pat[PatInfo.Count].Distance;
			//BossMissile.sMissile[i]._image.position.y += nSignY * PatInfo.Pat[PatInfo.Count].Distance;


			// 영역 밖으로 나갈 경우 미사일 생명력 0
			if (BossMissile.sMissile[i]._image.position.x < -64.0f )
				//|| BossMissile.sMissile[i]._image.position.y < 0 ||
				//BossMissile.sMissile[i]._image.position.y > SCREEN_HEIGHT)
				BossMissile.sMissile[i].nLife = 0;

			// 이동 중인 미사일 중 충돌
			if (g_Player.Collision(g_Player.GetImage(), BossMissile.sMissile[i]._image)) // Collision(A,B) A 와 B의 충돌
			
				//BossMissile.sMissile[i].nLife = 0;
				//g_Player.Damaged();
				BossMissile.sMissile[i]._image.position.x = 1000;
				// 충돌 이펙트 나오게
				
				
			}

			//if(Collision)
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
				&BossMissile.sMissile[i]._image.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, _image.alpha));
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
	D3DXCreateTextureFromFile(g_pd3dDevice, L"Resources/BossGauge.png", &BossGauge.texture);
	D3DXGetImageInfoFromFile(L"Resources/BossGauge.png", &BossGauge.img_info);
	BossGauge.rect = { 0,0, (LONG)BossGauge.img_info.Width, (LONG)BossGauge.img_info.Height };
	BossGauge.center = { 0,0,0 };
	BossGauge.position = { 600,50,0 };
	return VOID();
}

VOID Boss::GaugeUpdate()
{
	// _proper.Hp--; // hp감소
	BossGauge.rect = { 0,0, (LONG)_proper.Hp * 8, (LONG)BossGauge.img_info.Height };
	return VOID();
}

VOID Boss::GaugeDraw()
{
	_pSprite->Draw(BossGauge.texture, &BossGauge.rect, &BossGauge.center, &BossGauge.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, _image.alpha));
	return VOID();
}

VOID Boss::GaugeRelease()
{
	BossGauge.texture->Release();
	return VOID();
}
