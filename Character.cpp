#include "Character.h"
Character::Character() // 캐릭터 클래스의 생성자 함수
{
	_dwOldTime = 0;
	_image.alpha = 1.0f;
}

Character::~Character() // 캐릭터 클래스의 소멸자 함수
{

}

VOID Character::Draw(VOID)
{
	// _image = 멤버변수로 선언한 IMAGE형 변수
	if (_image.visible == TRUE)
	{
		// _pSprite = GameBase 에 정적 선언된 LPD3DXSPRITE 
		_pSprite->Draw(_image.texture, &_image.rect, &_image.center, &_image.position, D3DXCOLOR(1.0f, 1.0f, 1.0f, _image.alpha));
	}
	return VOID();
}

Image Character::GetImage(VOID)
{
	// GetImage에서는 받아온 이미지를 반환시킨다.
	return _image;
}

VOID Character::SetImage(Image pImage)
{
	// SetImage에서는 인수(pImage)를 _image 에 넣는다.
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
	// 원충돌
	FLOAT l = sqrtf((B.position.x - A.position.x) * (B.position.x - A.position.x) +
		(B.position.y - A.position.y) * (B.position.y - A.position.y));
	if (l > A.collisionRange + B.collisionRange)
		return FALSE;
	else
		return TRUE;
}