#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "./env.h"

enum Coordinates {
	X = 0, Y = 1
};

enum SideLocation
{
	TOP,
	BOTTOM,
	LSIDE,
	RSIDE,
};

enum Directions
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class Monkey {
public:
	SideLocation currentPoistion;
	GLfloat Coordinate[3][2];
	const GLfloat HEIGHT = 33.54101966;
	const GLfloat BASEWIDTH = 30;
	int testVarible = 0;
	Environment* envRef;
	Monkey(Environment* env);
	static void render(Monkey *self);
	void monkeyMove();
	void monkeyMove(Directions D);
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	bool checkBounderies(Coordinates coord, int limit);
};