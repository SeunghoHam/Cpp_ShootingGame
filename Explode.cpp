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
    return VOID();
}

VOID Explode::Update(VOID)
{
    return VOID();
}

VOID Explode::Draw(VOID)
{
    return VOID();
}
