#include "Character.h"
Character::Character() // ĳ���� Ŭ������ ������ �Լ�
{
	_dwOldTime = 0;
	_image.alpha = 1.0f;
}

Character::~Character() // ĳ���� Ŭ������ �Ҹ��� �Լ�
{

}

VOID Character::Draw(VOID)
{
	// _image = ��������� ������ IMAGE�� ����
	if (_image.visible == TRUE)
	{
		// _pSprite = GameBase �� ���� ����� LPD3DXSPRITE 
		_pSprite->Draw(_image.texture, &_image.rect, &_image.center, &_image.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, _image.alpha));
	}
	return VOID();
}

Image Character::GetImage(VOID)
{
	// GetImage������ �޾ƿ� �̹����� ��ȯ��Ų��.
	return _image;
}

VOID Character::SetImage(Image pImage)
{
	// SetImage������ �μ�(pImage)�� _image �� �ִ´�.
	_image = pImage;
}

Proper Character::GetProper(VOID)
{
	return _proper;
}

VOID Character::SetProper(Proper pProper)
{
	_proper = pProper;
}

DWORD Character::GetOldTime()
{
	return _dwOldTime;
}

VOID Character::SetOldTIme(DWORD pOldTime)
{
	_dwOldTime = pOldTime;
}

BOOL Character::Collision(Image A, Image B)
{
	// ���浹
	FLOAT l = sqrtf((B.position.x - A.position.x) * (B.position.x - A.position.x) +
		(B.position.y - A.position.y) * (B.position.y - A.position.y));
	if (l > A.collisionRange + B.collisionRange)
		return FALSE;
	else
		return TRUE;
}