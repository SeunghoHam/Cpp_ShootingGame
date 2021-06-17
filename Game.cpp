#include<d3dx9.h>
#include"Game.h"
#include"GameData.h"
#include "Player.h"
extern LPDIRECT3DDEVICE9 g_pd3dDevice;

Player g_Player;

VOID GameInit()
{
	g_Player.Init();

}
