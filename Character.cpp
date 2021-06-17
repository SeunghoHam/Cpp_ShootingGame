#include "Character.h"

Character::Character()
{
	_dwOldTime = 0;
	_image.alpha = 0;
}

Character::~Character()
{

}
VOID Character::Draw(VOID) // 그림그리기
{
	if (_image.visible == TRUE)
	{
		_pSprite->Draw(_image.texture, &_image.rect, &_image.center, &_image.position, 
			D3DXCOLOR(1.0f, 1.0f, 1.0f, _image.alpha));

		return VOID();
	}
}

Image Character::GetImage(VOID) // 이미지를 반환시킨다.
{
	return _image;
}
VOID Character::SetImage(Image pImage) // 이미지를 설정한다.
{
	_image = pImage;
}

Proper Character::GetProper(VOID) // 속성을 받아온다.
{
	return _proper;
}

VOID Character::SetProper(Proper pProper) // 속성을 설정한다.
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

