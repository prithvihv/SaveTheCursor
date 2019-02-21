#include "env.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

Environment::Environment(int xtl, int ytl, int xbr, int ybr) {
	this->tl_X = xtl;
	this->tl_Y = ytl;
	this->br_X = xbr;
	this->br_Y = ybr;
}

void Environment::render(Environment *self) {
	glColor3f(0.6196078431372549, 0.6196078431372549, 0.6196078431372549); // white BackGround
	glRecti(self->tl_X, self->tl_Y, self->br_X, self->br_Y);
};



