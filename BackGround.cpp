#include "BackGround.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

VOID BackGround::Update()
{
    // 배경이 반복되게 하기
    _image.position.y += _proper.Speed;
    if (_image.position.y > startPosition + _image.img_info.Height)
        _image.position.y = startPosition;
    return VOID();
}

VOID BackGround::InitPosition(FLOAT position)
{

    startPosition = position;
    _image.position.y = position;
}
