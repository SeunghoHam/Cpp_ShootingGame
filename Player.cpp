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
	D3DXCreateTextureFromFile(g_pd3dDevice, L"imagename.png", &_image.texture);
	D3DXGetImageInfoFromFile(L"imagename.png", &_image.img_info);

}