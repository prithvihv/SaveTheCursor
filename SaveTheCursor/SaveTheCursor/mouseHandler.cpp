#include "mouseHandler.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>

static mouseHandler *self;
mouseHandler::mouseHandler()
{

}
void mouseHandler::onMouse(int x, int y) {
	//self->x = x;
	//self->y = y;
	printf(" \n WRONG PLACE mouse position x : %d y: %d", x, y);
}

mouseHandler::~mouseHandler()
{
}
