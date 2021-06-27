#include "Explode.h"

extern LPDIRECT3DDEVICE9 g_pd3dDevice;

Explode::Explode()
{
}

Explode::~Explode()
{
}

VOID Explode::SetVisible(BOOL visible)
{

    _image.visible = visible;
}

VOID Explode::SetPosition(D3DXVECTOR3 position)
{

    _image.position = position;
}

VOID Explode::Init()
{
    D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Resources/Explode.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
        1, 0, D3DFORMAT::D3DFMT_UNKNOWN, D3DPOOL::D3DPOOL_MANAGED,
        D3DX_FILTER_NONE, 0, 0, 0, 0, &_image.texture);
    D3DXGetImageInfoFromFile(L"Resources/Explode.png", &_image.img_info);

    // Explode 스프라이트 상세설정
    FrameIndex = 0;
    FrameCount = 6;
    FrameWidth = (LONG)_image.img_info.Width / FrameCount;
    FrameHeight = (LONG)_image.img_info.Height;

    FrameOldTime = timeGetTime();
    FrameAniTime = 80;

    _image.visible = FALSE;
    _image.rect = { 0,0,FrameWidth, FrameHeight };
    _image.center = { _image.img_info.Width / 6 * 0.5f, _image.img_info.Height / 6 *0.5f, 0 };
    _image.position = { 0, 0, 0 }; // 원래값 0, -100,0

    StayTime = 80 * 6;
    return VOID();
}

VOID Explode::Update(VOID)
{
    DWORD CurTime = timeGetTime();
    if (CurTime - FrameOldTime > FrameAniTime) // 현재시간 - 전 프레임 실행 시각 > 애니메이션 실행 시간
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
    if (CurTime - StartTime > StayTime)
    {
        _image.visible = FALSE;
    }
    return VOID();
}

VOID Explode::Draw(VOID)
{
    if (_image.visible == TRUE)
    {
        _pSprite->Draw(_image.texture, &_image.rect, &_image.center, &_image.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, _image.alpha));
    }
    return VOID();
}

VOID Explode::effectInit()
{
    D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Resources/HitEffect.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
        1, 0, D3DFORMAT::D3DFMT_UNKNOWN, D3DPOOL::D3DPOOL_MANAGED,
        D3DX_FILTER_NONE, 0, 0, 0, 0, &hitEffect._image.texture);

    D3DXGetImageInfoFromFile(L"Resources/HitEffect.png", &hitEffect._image.img_info);

    hitEffect._image.visible = FALSE;
    hitEffect._image.rect = { 0,0, (LONG)hitEffect._image.img_info.Width, (LONG)hitEffect._image.img_info.Height };
    hitEffect._image.center = { hitEffect._image.img_info.Width * 0.5f, hitEffect._image.img_info.Height * 0.5f ,0 };
    hitEffect._image.position = { 30,100,0 };
    hitEffect._image.alpha = 1.0f;

    hitEffect.HitStayTime = 200;

    return VOID();
}

VOID Explode::effectUpdate()
{
    DWORD CurTime = timeGetTime();
    if (CurTime - hitEffect.HitStartTime > hitEffect.HitStayTime)
    {
        hitEffect._image.visible = FALSE;
    }
    return VOID();
}

VOID Explode::effectDraw()
{
    if (hitEffect._image.visible == TRUE)
    {
       hitEffect._pSprite->Draw(hitEffect._image.texture, &hitEffect._image.rect, &hitEffect._image.center, &hitEffect._image.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, hitEffect._image.alpha));
    }
    return VOID();
}

VOID Explode::SethitEffectVisible(BOOL visible)
{
    hitEffect._image.visible = visible;
}

VOID Explode::SethitEffectPosition(D3DXVECTOR3 position)
{
    hitEffect._image.position = position;
}
