#pragma once
#include "Character.h"
class DrawEnd : public Character
{
public:
	Image Failed;
	Image Success;
	VOID FailedInit();
	VOID FailedDraw();

	VOID SuccessInit();
	VOID SuccessDraw();
};

