#include "Player.h"
#include "GroupEnemy.h"
#include "Explode.h"
#include "Boss.h"
#include "HitEffect.h"
extern LPDIRECT3DDEVICE9   g_pd3dDevice;
extern INT g_Score;
extern GroupEnemy g_GroupEnemy;
extern Explode explode;
extern Boss g_Boss;
HitEffect hiteffect;


Player::Player()
{

}

Player::~Player()
{

}

VOID Player::Init(VOID)
{
	// �÷��̾� �ʱ�ȭ
	D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Resources/CharacterSprite.png", -2, -2, 1, 0,
		D3DFORMAT::D3DFMT_UNKNOWN, D3DPOOL::D3DPOOL_MANAGED, D3DX_FILTER_NONE, 0, 0, 0, 0, &_image.texture);
	D3DXGetImageInfoFromFile(L"Resources/CharacterSprite.png", &_image.img_info);
	_image.visible = TRUE;

	//_image.rect = { 0,0,(LONG)_image.img_info.Width, (LONG)_image.img_info.Height };

	//_image.center = { _image.img_info.Width * 0.5f, _image.img_info.Height * 0.5f,0 };
	//_image.position = { SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.7f,0 };

	//_image.collisionRange = _image.img_info.Width / 9, _image.img_info.Height / 9;
	

	_proper.Speed = 2.0f;
	_proper.Hp = 32.0f;




	FrameIndex = 0;
	FrameCount = 9;
	FrameWidth = (LONG)_image.img_info.Width / FrameCount;
	FrameHeight = (LONG)_image.img_info.Height;

	FrameOldTime = timeGetTime();
	FrameAniTime = 100;
	_image.rect = { 0,0,FrameWidth,FrameHeight };
	_image.center = { _image.img_info.Width / 9 * 0.5f, _image.img_info.Height / 9 * 0.5f,0 };
	_image.position = { 300,300,0 };
	_image.collisionRange = 64.0f;
	// �÷��̾� �̻��� �ʱ�ȭ
	D3DXCreateTextureFromFile(g_pd3dDevice, L"Resources/playerMissile2.png", &playerMissile[0]._image.texture);
	D3DXGetImageInfoFromFile(L"Resources/playerMissile2.png", &playerMissile[0]._image.img_info);
	playerMissile[0]._image.visible = TRUE;
	playerMissile[0]._image.rect = { 0,0,(LONG)playerMissile[0]._image.img_info.Width,
											(LONG)playerMissile[0]._image.img_info.Height };
	playerMissile[0]._image.center = { playerMissile[0]._image.img_info.Width * 0.5f, playerMissile[0]._image.img_info.Height * 0.5f, 0 };
	playerMissile[0]._nLife = 0;
	playerMissile[0]._image.collisionRange = 20.0f;
	for (int i = 1; i < myMissile; i++) 
	{
		playerMissile[i] = playerMissile[0];
	}
	OldFireTime = timeGetTime();
	FireTime = 200; // �߻�ӵ� ����


	GaugeInit();
	return VOID();

	
}

VOID Player::Update(VOID)
{
	// �ִϸ��̼� ����
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
	
	// Ű���� ó��
	if (GetAsyncKeyState(VK_LEFT))
		moveLeft();
	if (GetAsyncKeyState(VK_RIGHT))
		moveRight();
	if (GetAsyncKeyState(VK_UP))
		moveUp();
	if (GetAsyncKeyState(VK_DOWN))
		moveDown();

	// �׻� ���ϰ��̱� ������ visible �Ӽ��� �ǵ��� �ʴ´�- ĳ�����̱� ������

	// �̻��� �߻�
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (CurTime - OldFireTime > FireTime) // ����ð� - ������ð� > �߻� ������
		{
			OldFireTime = CurTime;
			for (INT i = 0; i < myMissile; i++) // myMissile = playerMissile �迭�� ũ��
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
	// �̻��� �̵�
	for (INT i = 0; i < myMissile; i++)
	{
		if (playerMissile[i]._nLife == 1)
		{
			if (CurTime - playerMissile[i].OldTime > 5)
			{
				playerMissile[i].OldTime = CurTime;
				if (playerMissile[i]._image.position.x < SCREEN_WIDTH) // �Ѿ� �߻� �Ÿ� ����
				{
					playerMissile[i]._image.position.x += 5;
				}
				else
					playerMissile[i]._nLife = 0;
			}
			 // ����ִ� �̻��� �� ����� �浹
			for (INT j = 0; j < ENEMY_NUM; j++) // ���� Ȯ���� ���� for�� ������
			{
				if (playerMissile[i].Collision(playerMissile[i]._image, g_GroupEnemy.Enemy[j].GetImage()))
				{
					playerMissile[i]._nLife = 0;

					/*hiteffect.SetPosition(g_GroupEnemy.Enemy[j].GetImage().position);
					hiteffect.Setvisible(TRUE);
					hiteffect.StartTime = CurTime;*/
					
					explode.SethitEffectPosition(g_GroupEnemy.Enemy[j].GetImage().position);
					explode.SethitEffectVisible(TRUE);
					//explode.hitEffect.HitStartTime = CurTime;

					g_GroupEnemy.Enemy[j].Damaged();

					if (g_GroupEnemy.Enemy[j].GetProper().Hp <= 0)
					{
						explode.SetPosition(g_GroupEnemy.Enemy[j].GetImage().position);
						g_GroupEnemy.Enemy[j].SetPositionY(100); // �̹��� ������ ��ġ�� ������Ѽ� ����Ʈ ���� �ȳ��� �Ѵ�
						explode.SetVisible(TRUE); // ����Ʈ ���̰�
						g_Score += 1; 
						explode.StartTime = CurTime;
						explode.FrameOldTime = CurTime;
					}
				}
			}
			// ����ִ� �̻��� �� ������ �浹
			if (playerMissile[i].Collision(playerMissile[i]._image, g_Boss.GetImage()))
			{
				playerMissile[i]._nLife = 0;
				g_Boss.Damaged();
				
				// Hit Effect 
				
				


				if (g_Boss.GetProper().Hp <= 0)
				{
					for (INT j = 0; j < 30; j++)
					{
						g_Boss.BossMissile.sMissile[j].nLife = 0; // ������ ������ ������ �̻��ϵ鵵 ���������
					}
					explode.SetPosition(g_Boss.GetImage().position);
					explode.SetVisible(TRUE);

					g_Score += 10;
					explode.StartTime = CurTime;
					explode.FrameOldTime = CurTime;
				}
			}
		}
	}
	


	GaugeUpdate();
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

	GaugeDraw();
	return VOID();
}

VOID Player::Damaged()
{
	if (_proper.Hp > 0)
		_proper.Hp--;
	return VOID();
}




D3DXVECTOR3 Player::GetPosition(D3DXVECTOR3 playerPosition)
{
	playerPosition = _image.position;
	return playerPosition;
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

VOID Player::GaugeInit()
{
	D3DXCreateTextureFromFile(g_pd3dDevice, L"Resources/HpGauge.png", &HPGauge.texture);
	D3DXGetImageInfoFromFile(L"Resources/HpGauge.png", &HPGauge.img_info);
	HPGauge.rect = { (LONG)HPGauge.img_info.Width, (LONG)HPGauge.img_info.Height };
	HPGauge.visible = TRUE;
	HPGauge.center = { 0,0,0 };
	HPGauge.position = { 10, 10,0 };
	HPGauge.alpha = 1.0f;

	return VOID();
}

VOID Player::GaugeUpdate()
{
	HPGauge.rect = { 0,0,(LONG)_proper.Hp * 5 ,(LONG)HPGauge.img_info.Height};
	return VOID();
}

VOID Player::GaugeDraw()
{
	_pSprite->Draw(HPGauge.texture, &HPGauge.rect, &HPGauge.center, &HPGauge.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, HPGauge.alpha));
	return VOID();
}


VOID Player::GaugeRelease()
{
	HPGauge.texture->Release();
	return VOID();
}

