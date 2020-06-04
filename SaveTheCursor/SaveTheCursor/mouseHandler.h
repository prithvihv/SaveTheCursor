#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
class mouseHandler
{
	
public:
	static int x;
	static int y;
	mouseHandler();
	static void onMouse(int x,int y);
	~mouseHandler();
};

