#include<d3dx9.h>
#include"Game.h"
#include"GameData.h"
#include"GameBase.h"
#include"Character.h"
#include"BackGround.h"
#include"Player.h"
#include"Enemy.h"
#include"GroupEnemy.h"
#include"Boss.h"
#include"UI.h"

extern LPDIRECT3DDEVICE9 g_pd3dDevice;

BackGround g_BG1;
BackGround g_BG2;

Player g_Player;

GroupEnemy g_GroupEnemy;
Boss g_Boss;

UI testUI;


INT g_Score;
DWORD dwOldTime;
VOID GameInit()
{
	// 플레이어, 배경, 적, 보스 초기화(Init)
	BGInit(); // 배경 초기화

	g_Boss.Init();
	g_Boss.PatInit(); // 패턴 정보 확인 필요함 ■■■■■■■
	g_Player.Init();
	g_GroupEnemy.Init();
}

VOID GameUpdate()
{
	GameBase::t = (timeGetTime() - dwOldTime) * 0.001f;
	dwOldTime = timeGetTime();

	
	// 플레이어, 배경, 적 보스 업데이트
	BGUpdate();
	g_Player.Update();
	g_GroupEnemy.Update();
	g_Boss.Update();
}

VOID GameRender()
{
	// 배경 랜더
	g_BG1.Draw();
	g_BG2.Draw();

	// 캐릭터 랜더
	g_Player.Draw();
	g_GroupEnemy.Draw(); // Enemy Draw
	g_Boss.Draw(); // Boss Draw


	// 캐릭터 미사일 드로우
	g_Player.MissileDraw();

}

VOID GameRelease()
{
	g_Boss.Release();
	// 제거
}

VOID MissileInit()
{
	return VOID();
}

VOID BGInit()
{
	Image bgImage1;
	D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Resources/BackGround1.png", -2, -2, 1, 0,
		D3DFORMAT::D3DFMT_UNKNOWN, D3DPOOL::D3DPOOL_MANAGED, D3DX_FILTER_NONE, 0, 0, 0, 0, &bgImage1.texture);

	D3DXGetImageInfoFromFile(L"Resources/BackGround1.png", &bgImage1.img_info);
	bgImage1.visible = TRUE;
	bgImage1.rect = { 0,0,(LONG)bgImage1.img_info.Width, (LONG)bgImage1.img_info.Height };
	bgImage1.center = { 0,0,0 };
	//bgImage1.position = { (FLOAT)bgImage1.rect.left * -1 + SCREEN_WIDTH, 0, 0 };
	bgImage1.position = { 0,0,0 };
	bgImage1.alpha = 1.0f;

	Proper bgProper1;
	ZeroMemory(&bgProper1, sizeof(bgProper1));
	bgProper1.Speed = 4.0f;
	bgProper1.MoveTime = 16; // MoveTime = 이동시간 간격

	// 이미지 할당 시켜줘ㅏ야함 ex) g_SeaBG.SetImage(SeabgImage);
	g_BG1.SetImage(bgImage1);
	g_BG1.SetProper(bgProper1);
	g_BG1.InitPosition(800);

	// ********************************** //

	Image bgImage2;
	D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Resources/BackGround2.png", -2, -2, 1, 0,
		D3DFORMAT::D3DFMT_UNKNOWN, D3DPOOL::D3DPOOL_MANAGED, D3DX_FILTER_NONE, 0, 0, 0, 0, &bgImage2.texture);

	D3DXGetImageInfoFromFile(L"Resources/BackGround2.png", &bgImage2.img_info);
	bgImage2.visible = TRUE;
	bgImage2.rect = { 0,0,(LONG)bgImage2.img_info.Width, (LONG)bgImage2.img_info.Height };
	bgImage2.center = { 0,0,0 };
	bgImage2.position = { bgImage1.position.x + (FLOAT)bgImage2.rect.right,  0,0 };
	bgImage2.alpha = 1.0f;

	Proper bgProper2;
	ZeroMemory(&bgProper2, sizeof(bgProper2));
	bgProper2.Speed = 4.0f;
	bgProper2.MoveTime = 16;

	// 이미지 할당 시켜줘ㅏ야함 ex) g_SeaBG.SetImage(SeabgImage);
	g_BG2.SetImage(bgImage2);
	g_BG2.SetProper(bgProper2);
	g_BG2.InitPosition(800);
}

VOID BGUpdate()
{
	DWORD CurTime = timeGetTime();
	if (CurTime - g_BG1.GetOldTime() > g_BG1.GetProper().MoveTime)
	{
		g_BG1.SetOldTIme(CurTime);
		g_BG1.Update();
	}

	if (CurTime - g_BG2.GetOldTime() > g_BG2.GetProper().MoveTime)
	{
		g_BG2.SetOldTIme(CurTime);
		g_BG2.Update();
	}
}

VOID MissileUpdate()
{
	return VOID();
}
