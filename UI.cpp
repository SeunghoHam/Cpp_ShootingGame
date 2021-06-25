#include "UI.h"
extern LPDIRECT3DDEVICE9 g_pd3dDevice;
extern INT g_Score;


VOID UI::Init()
{
    D3DXCreateFont(g_pd3dDevice, 40, 0, FW_HEAVY, 1, FALSE, // 40 = width, 0 = height
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        DEFAULT_CHARSET, DEFAULT_PITCH | FF_DONTCARE,
        L"Impact", &font);
    return VOID();
}

VOID UI::Update()
{
    return VOID();
}

VOID UI::Draw()
{
    char string[100];
    RECT rt = { 10,10,0,0 };
    wsprintfA(string, "SCORE : %d", g_Score);
    font->DrawTextA(GameBase::_pSprite, string, -1, &rt, // rt = rect
        DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0));
    return VOID();
}

VOID UI::Release()
{
    return VOID();
}
