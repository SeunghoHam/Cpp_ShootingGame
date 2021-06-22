#include "Enemy.h"
#include<time.h>

extern LPDIRECT3DDEVICE9 g_pd3dDevice;

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

DWORD Enemy::GetAppearTime()
{
	// AppearTime = 출현시각
	return AppearTime;
}

VOID Enemy::SetAppearTime(DWORD time)
{
	AppearTime = time;
}

DWORD Enemy::GetMissileFireTime()
{
	return MissileFireTime;
}

VOID Enemy::SetMissileFireTime(DWORD time)
{
	MissileFireTime = time;
}

DWORD Enemy::GetMissileOldTime()
{
	return MissileOldTime;
}

VOID Enemy::SetMissileOldTime(DWORD time)
{
	MissileOldTime = time;
}

VOID Enemy::Damaged()
{
	if (_proper.Hp > 0)
	{
		_proper.Hp--;
	}
}

VOID Enemy::SetHp(INT hp)
{
	_proper.Hp = hp;
}

VOID Enemy::SetPositionX(FLOAT x)
{
	_image.position.x = x;
}

VOID Enemy::SetVisible(BOOL visible)
{
	_image.visible = visible;
}

VOID Enemy::Init(std::wstring _filename)
{
	//srand(time(NULL)); // 이거 어디서 쓰는지 찾아봐야댐
	nType = 1;
	D3DXCreateTextureFromFile(g_pd3dDevice, _filename.c_str(), &_image.texture);
	D3DXGetImageInfoFromFile(_filename.c_str(), &_image.img_info);
	_image.visible = TRUE;
	_image.rect = { 0,0,(LONG)_image.img_info.Width, (LONG)_image.img_info.Height };
	_image.center = { _image.img_info.Width * 0.5f, _image.img_info.Height * 0.5f, 0 };
	_image.position =  { 0,-100,0 };
	_image.collisionRange = 20.0f;
	_proper.Hp = 2;
	_proper.Speed = 10;
	_proper.OldTime = timeGetTime();
	_proper.MoveTime = 1000 / 30;


	MissileFireTime = 1000;
	MissileOldTime = timeGetTime();
	return VOID();
}

VOID Enemy::Update(VOID)
{

	DWORD CurTime = timeGetTime();
	if (CurTime - _proper.OldTime > _proper.MoveTime)
	{
		_proper.OldTime = CurTime;
		_image.position.y += _proper.Speed;
	}
	return VOID();
}

VOID Enemy::Draw(VOID)
{
	if (_proper.Hp > 0)
	{
		_pSprite->Draw(_image.texture, &_image.rect, &_image.center, &_image.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, _image.alpha));
	}
	return VOID();
}
