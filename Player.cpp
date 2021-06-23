#include "Player.h"

extern LPDIRECT3DDEVICE9   g_pd3dDevice;
// 그룹 에너미
// 폭파이펙트
extern INT g_Score;

Player::Player()
{

}

Player::~Player()
{

}

VOID Player::Init(VOID)
{
	// 플레이어 초기화
	D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Resources/CharacterSprite.png", -2,-2,1,0, 
		D3DFORMAT::D3DFMT_UNKNOWN, D3DPOOL::D3DPOOL_MANAGED, D3DX_FILTER_NONE, 0, 0, 0, 0, &_image.texture);
	D3DXGetImageInfoFromFile(L"Resources/CharacterSprite.png", &_image.img_info);
	_image.visible = TRUE;
	_image.rect = { 0,0,FrameWidth,FrameHeight };
	//_image.rect = { 0,0,(LONG)_image.img_info.Width, (LONG)_image.img_info.Height };
	_image.center = { _image.img_info.Width / 3 * 0.5f, _image.img_info.Height / 3 * 0.5f,0 };
	//_image.center = { _image.img_info.Width * 0.5f, _image.img_info.Height * 0.5f,0 };
	//_image.position = { SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.7f,0 };
	
	

	_proper.Speed = 2.0f;

	FrameIndex = 0;
	FrameCount = 9;
	FrameWidth = (LONG)_image.img_info.Width / FrameCount;
	FrameHeight = (LONG)_image.img_info.Height;

	FrameOldTime = timeGetTime();
	FrameAniTime = 100;

	_image.rect = { 0,0,FrameWidth, FrameHeight };
	_image.center = { _image.img_info.Width / 3 * 0.5f, _image.img_info.Height / 3 * 0.5f, 0 };
	_image.position = { 300,300,0 };
		
	// 플레이어 미사일 초기화
	D3DXCreateTextureFromFile(g_pd3dDevice, L"Resources/playerMissile2.png", &playerMissile[0]._image.texture);
	D3DXGetImageInfoFromFile(L"Resources/playerMissile2.png", &playerMissile[0]._image.img_info);
	playerMissile[0]._image.visible = TRUE;
	playerMissile[0]._image.rect = { 0,0,(LONG)playerMissile[0]._image.img_info.Width,
											(LONG)playerMissile[0]._image.img_info.Height };
	playerMissile[0]._image.center = { playerMissile[0]._image.img_info.Width * 0.5f, playerMissile[0]._image.img_info.Height * 0.5f, 0 };
	playerMissile[0]._nLife = 0;
	playerMissile[0]._image.collisionRange = 20;
	for (int i = 1; i < myMissile; i++) 
	{
		playerMissile[i] = playerMissile[0];
	}
	OldFireTime = timeGetTime();
	FireTime = 200; // 발사속도 설정

	return VOID();
}

VOID Player::Update(VOID)
{
	// 애니메이션 관련
	DWORD CurTime = timeGetTime();
	if (CurTime - FrameOldTime > FrameAniTime)
	{
		FrameOldTime = CurTime;
		FrameIndex++;
		if (FrameIndex >= FrameCount - 1)
		{
			FrameIndex = 0;
		}
	}
	_image.rect.left = FrameIndex * FrameWidth;
	_image.rect.right = _image.rect.left + FrameWidth;
	
	// 키보드 처리
	if (GetAsyncKeyState(VK_LEFT))
		moveLeft();
	if (GetAsyncKeyState(VK_RIGHT))
		moveRight();
	if (GetAsyncKeyState(VK_UP))
		moveUp();
	if (GetAsyncKeyState(VK_DOWN))
		moveDown();
	// 항상 보일것이기 때문에 visible 속성은 건들지 않는다- 캐릭터이기 때문에

	// 미사일 발사
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (CurTime - OldFireTime > FireTime) // 현재시각 - 먼저쏜시간 > 발사 딜레이
		{
			OldFireTime = CurTime;
			for (INT i = 0; i < myMissile; i++) // myMissile = playerMissile 배열의 크기
			{
				if (playerMissile[i]._nLife == 0)
				{
					playerMissile[i]._nLife = 1;
					playerMissile[i]._image.position = _image.position;
					break;
				}
			}
		}
	}
	// 미사일 이동
	for (INT i = 0; i < myMissile; i++)
	{
		if (playerMissile[i]._nLife == 1)
		{
			if (CurTime - playerMissile[i].OldTime > 5)
			{
				playerMissile[i].OldTime = CurTime;
				if (playerMissile[i]._image.position.x < SCREEN_WIDTH) // 총알 발사 거리 제한
				{
					playerMissile[i]._image.position.x += 5;
				}
				else
					playerMissile[i]._nLife = 0;
			}
			// 살아있는 미사일 중 적기와 충돌

		}
	}
	
	return VOID();

}

VOID Player::MissileDraw(VOID)
{
	for (INT i = 0; i < myMissile; i++)
	{
		if (playerMissile[i]._nLife == 1)
		{
			_pSprite->Draw(playerMissile[i]._image.texture, 
				&playerMissile[i]._image.rect, &playerMissile[i]._image.center, &playerMissile[i]._image.position, D3DXCOLOR(1.0f,1.0f,1.0f, _image.alpha));
		}
	}
	return VOID();
}

VOID Player::moveLeft(VOID)
{
	_image.position.x -= _proper.Speed;
}

VOID Player::moveRight(VOID)
{
	_image.position.x += _proper.Speed;
}

VOID Player::moveUp(VOID)
{
	_image.position.y -= _proper.Speed;
}

VOID Player::moveDown(VOID)
{
	_image.position.y += _proper.Speed;
}

