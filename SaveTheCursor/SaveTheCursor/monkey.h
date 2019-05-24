#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "env.h"
#include "banana.h"
#include "hitBox.h"
#include "Point.h"

enum Coordinates {
	X = 0, Y = 1
};

enum SideLocation
{
	TOP,
	BOTTOM,
	LSIDE,
	RSIDE,
	FLYING
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
	GLfloat color[3] = { 0.14901960784313725, 0.2549019607843137, 0.5607843137254902 };
	bool monkeyMadMovement = true;
	const int NO_OF_VERTEX = 3;
	int MAX_MONKEY_SPEED = 10;
	int HITBOX_PADDING = 10;
	const GLfloat HEIGHT = 33.54101966;
	const GLfloat BASEWIDTH = 30;
	int monkeyDirection = 1;
	int *mouseX, *mouseY;
	float monkeySpeed = 1.0;
	float MONKEY_SPEED_JUMP = 30;
	hitBox* hitB;
	Environment* envRef;
	banana* bananaRef;
	SideLocation currentPoistion;
	GLfloat Coordinate[3][2];
	Point MonkeySee;
	SideLocation MonkeySeePoistion;
	int testVarible = 0;
	Monkey(Environment* env, banana* banana);
	static bool render(Monkey *self);
	void monkeyMove();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	bool checkBounderies1(Coordinates coord, int limit);
	bool checkBounderies2(Coordinates coord, int limit);
	bool decideJump();
	void updateSpeed();
	void initAwesomeness();
	void moveDirection(float thethe, int xSign, int ySign);
	void findBaseMidPoint();
	bool lineLineIntersection(Point A, Point B, Point C, Point D);
	SideLocation monkeySeeWhereToLand(SideLocation lastKnowLocation, Point A, Point B);
};