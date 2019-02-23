#include "Game.h"
#include "env.h"
#include "monkey.h"
#include "banana.h"
#include <stdio.h>

Game *self;
Game::Game(int* xpostion, int* yposition)
{
	this->x = xpostion;
	this->y = yposition;
	this->gameOver = false;
	e1 = new Environment(10, 990, 990, 10);
	bananaMouse = new banana();
	monkey = new Monkey(e1, bananaMouse);
	self = this;
}
void Game::render(void) {
	self->e1->render(self->e1);
	self->monkey->render(self->monkey);
	self->bananaMouse->render(self->bananaMouse);
	//glBegin(GL_LINES);
	//glVertex2i(900, 150); // Specify line-segment geometry.
	//glVertex2i(100, 100);
	//glEnd();
	glFlush(); // Process all OpenGL routines as quickly as possible.}
}
	
