#include "env.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

Environment::Environment(int xtl, int ytl, int xbr, int ybr) {
	this->tl_X = xtl;
	this->tl_Y = ytl;
	this->br_X = xbr;
	this->br_Y = ybr;
}

void Environment::render(Environment *self) {
	glColor3fv(self->color); // white BackGround
	glRecti(self->tl_X, self->tl_Y, self->br_X, self->br_Y);
	//int getRandomDirection = (rand() % 2);
	//self->color[getRandomDirection] = self->color[getRandomDirection] > 1.000 ? self->color[getRandomDirection] - 1 : self->color[getRandomDirection] + 0.8;

};



