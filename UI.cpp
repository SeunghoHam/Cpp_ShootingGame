#include "Ui.h"
extern LPDIRECT3DDEVICE9 g_pd3dDevice;
extern INT g_Score;


VOID Ui::Init()
{
    D3DXCreateFont(g_pd3dDevice, 40, 0, FW_HEAVY, 1, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        L"Impact", &font);
    return VOID();
}

VOID Ui::Update()
{
    return VOID();
}

VOID Ui::Draw()
{
    char string[100];
    RECT rt = { 10,40,0,0 };
    wsprintfA(string, "SCORE : %d", g_Score);
    font->DrawTextA(GameBase::_pSprite, string, -1, &rt,
        DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
    return VOID();
}

VOID Ui::Release()
{
    _pSprite->Release();
    return VOID();
}
