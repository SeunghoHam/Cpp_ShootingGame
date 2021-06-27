#include "TimeGauge.h"
extern LPDIRECT3DDEVICE9 g_pd3dDevice;
TimeGauge::TimeGauge()
{
}

TimeGauge::~TimeGauge()
{
}

VOID TimeGauge::Init()
{
    D3DXCreateTextureFromFile(g_pd3dDevice, L"Resources/TimeGauge.png", &timeGauge.texture);
    D3DXGetImageInfoFromFile(L"Resources/TimeGauge.png", &timeGauge.img_info);
    timeGauge.rect = { 0,0,(LONG)timeGauge.img_info.Width, (LONG)timeGauge.img_info.Height };
    timeGauge.center = { 0,0,0 };
    timeGauge.position = { 20, 530, 0 };


    D3DXCreateTextureFromFile(g_pd3dDevice, L"Resources/TimeGaugeBG.png", &timeGaugeBG.texture);
    D3DXGetImageInfoFromFile(L"Resources/TimeGaugeBG.png", &timeGaugeBG.img_info);
    timeGaugeBG.rect = { 0,0,(LONG)timeGaugeBG.img_info.Width, (LONG)timeGaugeBG.img_info.Height };
    timeGaugeBG.center = { 0,0,0 };
    timeGaugeBG.position = { 20, 530, 0 };
    _proper.Hp = 320;
    Decrease = 2000;
    OldTime = timeGetTime();

    GameOver = FALSE;
    return VOID();
}

VOID TimeGauge::Update()
{
    timeGauge.rect = { 0,0, (LONG)_proper.Hp * 1, (LONG)timeGauge.img_info.Height };


    DWORD CurTime = timeGetTime();
    if (CurTime - OldTime > Decrease)
    {
        OldTime = CurTime;
        _proper.Hp-= 16.0f;
        if (_proper.Hp <= 0.0f)
        {
            GameOver = TRUE;
        }
        
    }
    return VOID();

    OldTime = CurTime;
}

VOID TimeGauge::Draw()
{
    _pSprite->Draw(timeGaugeBG.texture, &timeGaugeBG.rect, &timeGaugeBG.center, &timeGaugeBG.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, _image.alpha));
    _pSprite->Draw(timeGauge.texture, &timeGauge.rect, &timeGauge.center, &timeGauge.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, _image.alpha));
    
    return VOID();
}
