#include "GroupEnemy.h"
#include "Explode.h" // GroupEnemy���� �����ϴ� Enemy���� Explode ����Ʈ�� �����Ų��.
#include <time.h>
extern LPDIRECT3DDEVICE9 g_pd3dDevice;
Explode explode;
Enemy Star;

GroupEnemy::GroupEnemy() // ������
{
}

GroupEnemy::~GroupEnemy() // �Ҹ���
{
}

VOID GroupEnemy::Init()
{
	EnemyIndex = 0;
	StartTime = timeGetTime();
	for (INT i = 0; i < ENEMY_NUM; i++)
	{
		Enemy[i].Init();
		Enemy[i].SetAppearTime(1000 * (i + 1));
		Enemy[i].SetHp(0);
	}

	for (INT i = 0; i < ENEMY_MISSILE; i++)
	{
		m_EnemyMissile[i].Init();
	}
	explode.Init();
	return VOID();
}

VOID GroupEnemy::Update()
{
	DWORD CurTime = timeGetTime();


	// 50 ~ 550 ������ ������ ��ǥ ���ϱ�
	srand((unsigned int)time(NULL)); 
	int num = rand();
	// �� ����
	for (INT i = EnemyIndex; i < ENEMY_NUM; i++)
	{
		if (Enemy[i].GetProper().Hp == 0)
		{
			if (CurTime - StartTime > Enemy[i].GetAppearTime())
			{
				Enemy[i].SetHp(5);
				Enemy[i].SetPositionY((int)num % 500 + 50);
				EnemyIndex++;
			}
			else
				break;
		}
	}
	// �� �̵�
	for (INT i = 0; i < EnemyIndex; i++)
	{
		if (Enemy[i].GetProper().Hp > 0)
		{
			Enemy[i].Update(); // ���� ������Ʈ ��Ų��. Enemy.Update
			// �̻��� �߻�
			if (CurTime - Enemy[i].GetMissileOldTime() > Enemy[i].GetMissileFireTime())
			{
				Enemy[i].SetMissileOldTime(CurTime);
				for (INT j = 0; j < ENEMY_MISSILE; j++)
				{
					if (m_EnemyMissile[j].nLife == 0) // EnemyMissile �浹��
					{
						m_EnemyMissile[j].nLife = 1;
						m_EnemyMissile[j]._image.position = Enemy[i].GetImage().position;
						m_EnemyMissile[j].MoveTime = 1000 / 30;
						m_EnemyMissile[j].OldTime = CurTime;
						break;
					}
				}
			}
		}
	}

	// �̻��� ������Ʈ
	for (INT i = 0; i < ENEMY_MISSILE; i++)
	{
		if (m_EnemyMissile[i].nLife == 1)
		{
			m_EnemyMissile[i].Update(); // EnemyMissile.Update
		}
	}

	// ���� ������Ʈ
	explode.Update();
	return VOID();
}

VOID GroupEnemy::Draw()
{
	for (INT i = 0; i < EnemyIndex; i++)
	{
		if (Enemy[i].GetProper().Hp > 0) // ���� ü���� 1 �̻�
		{
			Enemy[i].Draw();
		}
	}

	for (INT i = 0; i < ENEMY_MISSILE; i++)
	{
		if (m_EnemyMissile[i].nLife == 1) 
		{
			m_EnemyMissile[i].Draw();
		}
	}
	explode.Draw();
	return VOID();
}

VOID EnemyMissile::Init()
{
	D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Resources/EnemyMissile.png", -2, -2, 1, 0,
		D3DFORMAT::D3DFMT_UNKNOWN, D3DPOOL::D3DPOOL_MANAGED, D3DX_FILTER_NONE, 0, 0, 0, 0, &_image.texture);
	D3DXGetImageInfoFromFile(L"Resources/EnemyMissile.png", &_image.img_info);

	_image.visible = TRUE;
	_image.rect = { 0,0,(LONG)_image.img_info.Width, (LONG)_image.img_info.Height };
	_image.center = { _image.img_info.Width * 0.5f, _image.img_info.Height * 0.5f , 0};
	_image.position = { SCREEN_WIDTH + 100, 0 ,0 };

	nLife = 0;
	return VOID();
}

VOID EnemyMissile::Update()
{
	DWORD CurTime = timeGetTime();
	if (CurTime - OldTime > MoveTime)
	{
		OldTime = CurTime;
		_image.position.x -= 10.0f; // EnemyMissile �� �߻�ӵ�
		if (_image.position.x < 0)
		{
			nLife = 0;
		}
	}
	return VOID();
}

VOID EnemyMissile::Draw()
{
	if (nLife == 1)
	{
		_pSprite->Draw(_image.texture, &_image.rect, &_image.center, &_image.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, _image.alpha));

	}
	return VOID();
}
