#include "mouseHandler.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <stdio.h>

static mouseHandler *self;
mouseHandler::mouseHandler()
{

}
void mouseHandler::onMouse(int x, int y) {
	//self->x = x;
	//self->y = y;
	printf(" \n mouse position x : %d y: %d", x, y);
}

mouseHandler::~mouseHandler()
{
}
