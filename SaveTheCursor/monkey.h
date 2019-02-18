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
	const int NO_OF_VERTEX = 3;
	int MAX_MONKEY_SPEED = 10;
	const GLfloat HEIGHT = 33.54101966;
	const GLfloat BASEWIDTH = 30;
	int monkeyDirection = 1;
	float monkeySpeed = 1.0;
	Environment* envRef;
	SideLocation currentPoistion;
	GLfloat Coordinate[3][2];
	int testVarible = 0;
	Monkey(Environment* env);
	static void render(Monkey *self);
	void monkeyMove();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	bool checkBounderies1(Coordinates coord, int limit);
	bool checkBounderies2(Coordinates coord, int limit);
	void updateSpeed();
};