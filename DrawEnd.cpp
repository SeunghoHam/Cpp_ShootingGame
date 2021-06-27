#include "DrawEnd.h"
extern LPDIRECT3DDEVICE9 g_pd3dDevice;


VOID DrawEnd::FailedInit()
{
	D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Resources/FAILED.png", -2, -2, 1, 0,
		D3DFORMAT::D3DFMT_UNKNOWN, D3DPOOL::D3DPOOL_MANAGED, D3DX_FILTER_NONE, 0, 0, 0, 0, &Failed.texture);

	D3DXGetImageInfoFromFile(L"Resources/FAILED.png", &Failed.img_info);
	Failed.visible = TRUE;
	Failed.center = { 0,0,0 };
	Failed.rect = { 0,0 ,(LONG)Failed.img_info.Width, (LONG)Failed.img_info.Height };
	Failed.position = { 0,0,0 };
	Failed.alpha = 1.0f;
	
    return VOID();
}

VOID DrawEnd::FailedDraw()
{
	_pSprite->Draw(Failed.texture, &Failed.rect, &Failed.center, &Failed.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, Failed.alpha));
	return VOID();
}



VOID DrawEnd::SuccessInit()
{
	D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Resources/SUCCESS.png", -2, -2, 1, 0,
		D3DFORMAT::D3DFMT_UNKNOWN, D3DPOOL::D3DPOOL_MANAGED, D3DX_FILTER_NONE, 0, 0, 0, 0, &Success.texture);
	D3DXGetImageInfoFromFile(L"Resources/SUCCESS.png", &Success.img_info);
	Success.visible = TRUE;
	Success.center = { 0,0,0 };
	Success.rect = { 0,0 ,(LONG)Success.img_info.Width, (LONG)Success.img_info.Height };
	Success.position = { 0,0,0 };
	Success.alpha = 1.0f;

	
    return VOID();
}

VOID DrawEnd::SuccessDraw()
{
	_pSprite->Draw(Success.texture, &Success.rect, &Success.center, &Success.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, Success.alpha));
}

