#include "./env.h"
#include "./monkey.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <stdio.h>


Monkey::Monkey(Environment *env){
	this->envRef = env;
	GLfloat midpoint = (GLfloat)(env->br_X + env->tl_X) / 2;
	GLfloat initHieght = env->tl_Y;
	this->Coordinate[0][0] = midpoint - BASEWIDTH/2;
	this->Coordinate[0][1] = initHieght;
	this->Coordinate[1][0] = midpoint + BASEWIDTH/2;
	this->Coordinate[1][1] = initHieght;
	this->Coordinate[2][0] = midpoint;
	this->Coordinate[2][1] = initHieght + HEIGHT;
	this->currentPoistion = BOTTOM;
}

void Monkey::render(Monkey *self) {
	self->testVarible++;
	printf("running iteration %d \n",self->testVarible);
	glColor3f(0.0, 0.4, 0.2); // Set line segment color to green.		
	glBegin(GL_TRIANGLES);
		glVertex2f(self->Coordinate[0][0], self->Coordinate[0][1]);
		glVertex2f(self->Coordinate[1][0], self->Coordinate[1][1]);
		glVertex2f(self->Coordinate[2][0], self->Coordinate[2][1]);
	glEnd();
};

void Monkey::monkeyMove(Directions D) {
	
}

void Monkey::monkeyMove() {
	switch (this->currentPoistion)
	{
	case BOTTOM:
		if (checkBounderies(X,990)) {
		}

	default:
		break;
	}
}

bool Monkey::checkBounderies(Coordinates coord,int limit) {
	// completed functions
	for (int i = 0; i < sizeof(Coordinate);i++) {
	}
	return false;
}

void Monkey::moveRight() {
	int len = sizeof(Coordinate);
	for (int i = 0; i < len  ; i++) {
		this->Coordinate[i][0]++;
	}
}

void Monkey::moveLeft() {
	int len = sizeof(Coordinate);
	for (int i = 0; i < len; i++) {
		this->Coordinate[i][0]--;
	}
}

void Monkey::moveUp() {
	int len = sizeof(Coordinate);
	for (int i = 0; i < len; i++) {
		this->Coordinate[i][1]++;
	}
}

void Monkey::moveDown() {
	int len = sizeof(Coordinate);
	for (int i = 0; i < len; i++) {
		this->Coordinate[i][1]--;
	}
}




