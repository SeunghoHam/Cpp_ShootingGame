#include "HitEffect.h"

extern LPDIRECT3DDEVICE9 g_pd3dDevice;

HitEffect::HitEffect()
{
}

HitEffect::~HitEffect()
{
}

VOID HitEffect::Setvisible(BOOL visible)
{
    _image.visible = visible;
}
VOID HitEffect::SetPosition(D3DXVECTOR3 position)
{
    _image.position = position;
}
VOID HitEffect::Init()
{
    D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Resources/HitEffect.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
        1, 0, D3DFORMAT::D3DFMT_UNKNOWN, D3DPOOL::D3DPOOL_MANAGED,
        D3DX_FILTER_NONE, 0, 0, 0, 0, &_image.texture);

    D3DXGetImageInfoFromFile(L"Resources/HitEffect.png", &_image.img_info);

    _image.visible = TRUE;
    _image.rect = { 0,0, (LONG)_image.img_info.Width, (LONG)_image.img_info.Height };
    _image.center = { _image.img_info.Width * 0.5f, _image.img_info.Height * 0.5f ,0 };
    _image.position = { 30,100,0 };
    _image.alpha = 1.0f;

    StayTime = 200;
    return VOID();
}

VOID HitEffect::Update()
{
    DWORD CurTime = timeGetTime();
    //if (CurTime - StartTime > StayTime)
    //{
    //    _image.visible = FALSE;
    //}
    return VOID();
}

VOID HitEffect::Draw()
{
    if (_image.visible == TRUE)
    {
        _pSprite->Draw(_image.texture, &_image.rect, &_image.center, &_image.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, _image.alpha));
    }
    return VOID();
}
