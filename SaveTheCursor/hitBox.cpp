#include "hitBox.h"
#include "Point.h"
#include <cmath> 
#include <GL/glew.h>
#include <GL/freeglut.h>
hitBox::hitBox(float TL_X, float TL_Y, float BR_X, float BR_Y,int padding) {
	this->PADDING = padding;
	this->bottomRight.x = BR_X;
	this->bottomRight.y = BR_Y;
	this->topLeft.x = TL_X;
	this->topLeft.y = TL_Y;
}

void hitBox::updateHitBox(float TL_X, float TL_Y, float BR_X, float BR_Y) {

	this->bottomRight.x = BR_X;
	this->bottomRight.y = BR_Y;
	this->topLeft.x = TL_X;
	this->topLeft.y = TL_Y;
}

void hitBox::updateHitBox(GLfloat coords[3][2]) {
	/*
	// Centroid stuff
	float x = (coords[0][0] + coords[1][0] + coords[2][0]) / 3;
	float y = (coords[2][0] + coords[2][1] + coords[3][1]) / 3;
	float width = (coords[0][0] + coords[1][0]) / 2;
	*/
	this->topLeft.x = coords[0][0];
	this->bottomRight.y = coords[1][1];
	this->bottomRight.x = 0;
	this->topLeft.y = 0;

	for (int i = 0;i < 3;i++) {
		// find max X
		if (this->bottomRight.x < coords[i][0]) {
			this->bottomRight.x = coords[i][0];
		}
		// find min X
		if (this->topLeft.x > coords[i][0]) {
			this->topLeft.x = coords[i][0];
		}
		// find max Y
		if (this->topLeft.y < coords[i][1]) {
			this->topLeft.y = coords[i][1];
		}
		// find min Y
		if (this->bottomRight.y > coords[i][1]) {
			this->bottomRight.y = coords[i][1];
		}

	}
	this->updateHitBox(this->topLeft.x - this->PADDING, this->topLeft.y + this->PADDING, this->bottomRight.x + this->PADDING , this->bottomRight.y - this->PADDING);
}

// this is for 1D image
bool hitBox::collisionCheck(float X, float Y) {
	if (X >= this->topLeft.x  &&  this->bottomRight.x >= X) {
		if (Y >= this->bottomRight.y &&  this->topLeft.y >= Y) {
			return true;
		}
	}
	return false;
}

// this is for a box
bool hitBox::collisionCheck(Point TL, Point BR) {
	bool found = false;
	for (int i = 0;i < 3 ; i++) {
		found = this->collisionCheck(TL.x, TL.y);
		if (found) {
			return true;
		}
		found = this->collisionCheck(TL.x, BR.y);
		if (found) {
			return true;
		}
		found = this->collisionCheck(BR.x, BR.y);
		if (found) {
			return true;
		}
		found = this->collisionCheck(BR.x, TL.y);
		if (found) {
			return true;
		}
	}
	//complete this function
	return false;
}

bool hitBox::collisionCheck(hitBox* otherHitBox) {
	bool found = false;
	for (int i = 0;i < 3; i++) {
		found = this->collisionCheck(otherHitBox->topLeft.x, otherHitBox->topLeft.y);
		if (found) {
			return true;
		}
		found = this->collisionCheck(otherHitBox->topLeft.x, otherHitBox->bottomRight.y);
		if (found) {
			return true;
		}
		found = this->collisionCheck(otherHitBox->bottomRight.x, otherHitBox->bottomRight.y);
		if (found) {
			return true;
		}
		found = this->collisionCheck(otherHitBox->bottomRight.x, otherHitBox->topLeft.y);
		if (found) {
			return true;
		}
	}
	//complete this function
	return false;
}

void hitBox::DebugerRender(hitBox *self) {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(self->topLeft.x, self->bottomRight.y);
	glVertex2f(self->bottomRight.x, self->bottomRight.y);
	glVertex2f(self->bottomRight.x, self->topLeft.y);
	glVertex2f(self->topLeft.x, self->topLeft.y);
	glEnd();
}

hitBox::hitBox(GLfloat coords[][2], int padding) {
	this->PADDING = padding;
	/*
	// Centroid stuff
	float x = (coords[0][0] + coords[1][0] + coords[2][0]) / 3;
	float y = (coords[2][0] + coords[2][1] + coords[3][1]) / 3;
	float width = (coords[0][0] + coords[1][0]) / 2;
	*/
	this->topLeft.x = 10000000;
	this->bottomRight.y = 10000000;

	for (int i = 0;i < 3;i++) {
		// find max X
		if (this->bottomRight.x < coords[i][0]) {
			this->bottomRight.x = coords[i][0];
		}
		// find min X
		if (this->topLeft.x > coords[i][0]) {
			this->topLeft.x = coords[i][0];
		}
		// find max Y
		if (this->topLeft.y < coords[i][1]) {
			this->topLeft.y = coords[i][1];
		}
		// find min Y
		if (this->bottomRight.y > coords[i][1]) {
			this->bottomRight.y = coords[i][1];
		}
	}
}

hitBox::~hitBox()
{
}
