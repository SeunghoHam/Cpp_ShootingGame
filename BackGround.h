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
	FLOAT startPosition; // ��� ��������Ʈ�� ���� ��ǥ�� Protected�� ������״�.
};

