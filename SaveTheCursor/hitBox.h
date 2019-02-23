#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Point.h"
class hitBox
{
public:
	Point topLeft;
	Point bottomRight;
	int PADDING;
	hitBox(GLfloat coords[][2],int padding);
	hitBox(float TL_X, float TL_Y, float BR_X, float BR_Y, int padding);
	void updateHitBox(GLfloat coords[3][2]);
	void updateHitBox(float TL_X, float TL_Y, float BR_X, float BR_Y);
	bool collisionCheck(float X, float Y);
	bool collisionCheck(Point TL, Point BR);
	bool collisionCheck(hitBox* otherHitBox);
	static void DebugerRender(hitBox *self);
	~hitBox();
};

