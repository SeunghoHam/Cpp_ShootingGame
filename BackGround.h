#pragma once
#include "Character.h"
class BackGround : public Character
{
public:
	BackGround();
	~BackGround();
	VOID Update();
	VOID InitPosition(FLOAT position);
protected:
	FLOAT startPosition; // 배경 스프라이트의 시작 좌표를 Protected로 선언시켰다.
};

