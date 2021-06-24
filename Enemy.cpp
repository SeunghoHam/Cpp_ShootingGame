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

VOID Enemy::SetPositionY(FLOAT y)
{
	_image.position.y = y;
}

VOID Enemy::SetVisible(BOOL visible)
{
	_image.visible = visible;
}

VOID Enemy::Init()
{
	srand(time(NULL)); // 이거 어디서 쓰는지 찾아봐야댐
	nType = 1;
	D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Resources/Enemy.png",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0,
		D3DFORMAT::D3DFMT_UNKNOWN, D3DPOOL::D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, 0, 0, 0, 0, &_image.texture);
	D3DXGetImageInfoFromFile(L"Resources/Enemy.png", &_image.img_info);
	_image.visible = TRUE;
	_image.rect = { 0,0,(LONG)_image.img_info.Width, (LONG)_image.img_info.Height };
	_image.center = { _image.img_info.Width * 0.5f, _image.img_info.Height * 0.5f, 0 };
	_image.position =  { 800,300,0 };
	_image.collisionRange = 20.0f;
	_proper.Hp = 2;
	_proper.Speed = 5;
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
		_image.position.x -= _proper.Speed; // y -> x로 변경 오른쪽에서 왼쪽으로 적 이동
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
