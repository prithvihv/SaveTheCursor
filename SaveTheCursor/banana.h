#pragma once
#include "hitBox.h"
class banana
{
public:
	hitBox* hitB;
	int x, y;
	banana();
	static void onMouse(int xp, int yp);
	static void render(banana *self);
	~banana();
};
