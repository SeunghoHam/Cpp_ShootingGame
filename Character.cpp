#include "Character.h"

Character::Character()
{
	_dwOldTime = 0;
	_image.alpha = 0;
}

Character::~Character()
{

}
VOID Character::Draw(VOID) // �׸��׸���
{
	if (_image.visible == TRUE)
	{
		_pSprite->Draw(_image.texture, &_image.rect, &_image.center, &_image.position, 
			D3DXCOLOR(1.0f, 1.0f, 1.0f, _image.alpha));

		return VOID();
	}
}

Image Character::GetImage(VOID) // �̹����� ��ȯ��Ų��.
{
	return _image;
}
VOID Character::SetImage(Image pImage) // �̹����� �����Ѵ�.
{
	_image = pImage;
}

Proper Character::GetProper(VOID) // �Ӽ��� �޾ƿ´�.
{
	return _proper;
}

VOID Character::SetProper(Proper pProper) // �Ӽ��� �����Ѵ�.
{
	_proper = pProper;
}

DWORD Character::GetOldTime()
{
	return _dwOldTime;
}

VOID Character::SetOldTime(DWORD pOldTime)
{
	_dwOldTime = pOldTime;
}

BOOL Character::Collision(Image A, Image B)
{
	FLOAT I = sqrtf((B.position.x - A.position.x) * (B.position.x - A.position.x) + 
		(B.position.y - A.position.y) * (B.position.y - A.position.y));

	if (I > A.collisionRange + B.collisionRange)
		return FALSE;
	else
		return TRUE;
}

