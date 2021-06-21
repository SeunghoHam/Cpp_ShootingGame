#include"Game.h"
#include"GameData.h"
#include"GameBase.h"

extern LPDIRECT3DDEVICE9 g_pd3dDevice;

INT g_Score;
DWORD dwOldTime;
VOID GameInit()
{
	// �÷��̾�, ���, ��, ���� �ʱ�ȭ(Init)
	BGInit();
}

VOID GameUpdate()
{
	GameBase::t = (timeGetTime() - dwOldTime) * 0.001f;
	dwOldTime = timeGetTime();

	// �÷��̾�, ���, �� ���� ������Ʈ
}

VOID GameRender()
{
	// ��� ����

	// ĳ���� ����
}

VOID GameRelease()
{
	// ����
}

VOID MissileInit()
{
	return VOID();
}

VOID BGInit()
{
	Image bgImage;
	D3DXCreateTextureFromFileEx(g_pd3dDevice, L"filename.png", -2, -2, 1, 0,
		D3DFORMAT::D3DFMT_UNKNOWN, D3DPOOL::D3DPOOL_MANAGED, D3DX_FILTER_NONE, 0, 0, 0, 0, &bgImage.texture);

	D3DXGetImageInfoFromFile(L"imagename.png", &bgImage.img_info);
	bgImage.visible = TRUE;
	bgImage.rect = { 0,0,(LONG)bgImage.img_info.Width, (LONG)bgImage.img_info.Height };
	bgImage.center = { 0,0,0 };
	bgImage.position = { 0, (FLOAT)bgImage.rect.bottom * -1 + SCREEN_HEIGHT, 0 };
	bgImage.alpha = 1.0f;

	Proper bgProper;
	ZeroMemory(&bgProper, sizeof(bgProper));
	bgProper.Speed = 1.0f;
	bgProper.MoveTime = 16;

	// �̹��� �Ҵ� �����ि���� ex) g_SeaBG.SetImage(SeabgImage);
}

VOID BGUpdate()
{
	DWORD CurTime = timeGetTime();
	//if(CurTime - )
}

VOID MissileUpdate()
{
	return VOID();
}
