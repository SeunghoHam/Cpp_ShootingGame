#include "BackGround.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

VOID BackGround::Update()
{
    // ����� �ݺ��ǰ� �ϱ�
    _image.position.x -= _proper.Speed;
    //if (_image.position.x < startPosition - _image.img_info.Width)
    if (_image.position.x < -800)
        _image.position.x = startPosition;
    return VOID();
}

VOID BackGround::InitPosition(FLOAT position)
{
    startPosition = position;
    //_image.position.x = position;
}
