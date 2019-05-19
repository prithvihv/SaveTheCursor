#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
class mouseHandler
{
	
public:
	static int x;
	static int y;
	mouseHandler();
	static void onMouse(int x,int y);
	~mouseHandler();
};

