#include "Player.h"

extern LPDIRECT3DDEVICE9   g_pd3dDevice;
// �׷� ���ʹ�
// ��������Ʈ
extern INT g_Score;

Player::Player()
{

}

Player::~Player()
{

}

VOID Player::Init(VOID)
{
	// �÷��̾� �ʱ�ȭ
	D3DXCreateTextureFromFile(g_pd3dDevice, L"imagename.png", &_image.texture);
	D3DXGetImageInfoFromFile(L"imagename.png", &_image.img_info);

}