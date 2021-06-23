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

VOID Explode::Init(std::wstring _filename)
{
    D3DXCreateTextureFromFileEx(g_pd3dDevice, _filename.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
        1, 0, D3DFORMAT::D3DFMT_UNKNOWN, D3DPOOL::D3DPOOL_MANAGED,
        D3DX_FILTER_NONE, 0, 0, 0, 0, &_image.texture);

    D3DXGetImageInfoFromFile(_filename.c_str(), &_image.img_info);

    // Explode 스프라이트 상세설정
    FrameIndex = 0;
    FrameCount = 6;
    FrameWidth = (LONG)_image.img_info.Width / FrameCount;
    FrameHeight = (LONG)_image.img_info.Height;

    FrameOldTime = timeGetTime();
    FrameAniTime = 100;

    _image.visible = FALSE;
    _image.rect = { 0,0,FrameWidth, FrameHeight };
    _image.center = { _image.img_info.Width / 6 * 0.5f, _image.img_info.Height / 6 *0.5f, 0 };
    _image.position = { 0, -100, 0 };

    StayTime = 100 * 6;
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
        _pSprite->Draw(_image.texture, &_image.rect, &_image.center, &_image.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, 
            _image.alpha));
        // 이거 안보이면 0xfffffffff 으로 바꿔야할듯
    }
    return VOID();
}
