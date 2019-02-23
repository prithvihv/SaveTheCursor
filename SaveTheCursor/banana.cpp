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
	printf(" \n mouse position x : %d y: %d", self->x, self->y);
}

void banana::render(banana *self) {
	self->hitB->updateHitBox(self->x - 20, self->y + 20, self->x + 20, self->y - 20);
	self->hitB->DebugerRender(self->hitB);
};


banana::~banana()
{
}




