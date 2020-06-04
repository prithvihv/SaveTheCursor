#include "banana.h"
#include <stdio.h>
#include <cmath>

banana* self;

banana::banana()
{
	self = this;
	this->hitB = new hitBox(self->x - 20, self->y + 20, self->x + 20, self->y - 20,10);
}

void banana::onMouse(int xp, int yp) {
	self->x = xp * 1000/ 800;
	self->y = abs(yp-600) * 1000/ 600;
	printf(" \n REAL DEAL mouse position x : %d y: %d", self->x, self->y);
}

void banana::render(banana *self) {
	self->hitB->updateHitBox(self->x - 20, self->y + 20, self->x + 20, self->y - 20);
	self->hitB->DebugerRender(self->hitB);
	glutSetCursor(GLUT_CURSOR_NONE);
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslatef(self->x - 72, self->y - 80, 0);
	glBegin(GL_LINES);    //Specify line segment geometry
	glVertex2i(55, 80);
	glVertex2i(90, 80);
	glVertex2i(60, 60);
	glVertex2i(70, 100);
	glVertex2i(55, 80);
	glVertex2i(90, 60);
	glVertex2i(70, 100);
	glVertex2i(90, 60);
	glVertex2i(60, 60);
	glVertex2i(90, 80);
	glEnd();
	glTranslatef(-self->x, -self->y, 0);
	glPopMatrix();


};


banana::~banana()
{
}




