#include "./env.h"
#include "./monkey.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <stdio.h>


Monkey::Monkey(Environment *env){
	this->envRef = env;
	GLfloat midpoint = (GLfloat)(env->br_X + env->tl_X) / 2;
	GLfloat initHieght = env->br_Y;
	this->Coordinate[0][0] = midpoint - BASEWIDTH/2;
	this->Coordinate[0][1] = initHieght;
	this->Coordinate[1][0] = midpoint + BASEWIDTH/2;
	this->Coordinate[1][1] = initHieght;
	this->Coordinate[2][0] = midpoint;
	this->Coordinate[2][1] = initHieght + HEIGHT;
	this->currentPoistion = BOTTOM;
}

void Monkey::render(Monkey *self) {
	//self->testVarible = self->testVarible + 1; y doesnt this work
	self->monkeyMove();
	//printf("running iteration %d \n",self->testVarible);
	glColor3f(0.0, 0.4, 0.2);
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
		if (checkBounderies1(X,this->envRef->br_X)) {
			this->moveRight();
		}
		else {
			this->Coordinate[0][0] = this->envRef->br_X;
			this->Coordinate[0][1] = this->envRef->br_Y;
			this->Coordinate[1][0] = this->envRef->br_X;
			this->Coordinate[1][1] = this->envRef->br_Y + BASEWIDTH;
			this->Coordinate[2][0] = this->envRef->br_X - HEIGHT;
			this->Coordinate[2][1] = this->envRef->br_Y + BASEWIDTH / 2;
			this->currentPoistion = RSIDE;
		}
		break;
	case RSIDE:
		if (checkBounderies1(Y, this->envRef->tl_Y)) {
			this->moveUp();
		}
		else {
			this->Coordinate[0][0] = this->envRef->br_X;
			this->Coordinate[0][1] = this->envRef->tl_Y;
			this->Coordinate[1][0] = this->envRef->br_X - BASEWIDTH;
			this->Coordinate[1][1] = this->envRef->tl_Y;
			this->Coordinate[2][0] = this->envRef->br_X - BASEWIDTH/2;
			this->Coordinate[2][1] = this->envRef->tl_Y - HEIGHT;
			this->currentPoistion = TOP;
		}
		break;
	case TOP:
		if (checkBounderies2(X, this->envRef->tl_X)) {
			this->moveLeft();
		}
		else {
			this->Coordinate[0][0] = this->envRef->tl_X;
			this->Coordinate[0][1] = this->envRef->tl_Y;
			this->Coordinate[1][0] = this->envRef->tl_X;
			this->Coordinate[1][1] = this->envRef->tl_Y - BASEWIDTH;
			this->Coordinate[2][0] = this->envRef->tl_X + HEIGHT;
			this->Coordinate[2][1] = this->envRef->tl_Y - BASEWIDTH/2;
			this->currentPoistion = LSIDE;
		}
		break;
	case LSIDE:
		if (checkBounderies2(Y, this->envRef->br_Y)) {
			this->moveDown();
		}
		else {
			this->Coordinate[0][0] = this->envRef->tl_X;
			this->Coordinate[0][1] = this->envRef->br_Y;
			this->Coordinate[1][0] = this->envRef->tl_X + BASEWIDTH;
			this->Coordinate[1][1] = this->envRef->br_Y;
			this->Coordinate[2][0] = this->envRef->tl_X + BASEWIDTH/2; 
			this->Coordinate[2][1] = this->envRef->br_Y + HEIGHT;
			this->currentPoistion = BOTTOM;
		}
		break;
	default:
		break;
	}
}

bool Monkey::checkBounderies1(Coordinates coord,int limit) {
	for (int i = 0; i < NO_OF_VERTEX;i++) {
		if (this->Coordinate[i][coord] > limit) {
			return false;
		}
	}
	return true;
}
bool Monkey::checkBounderies2(Coordinates coord, int limit) {
	for (int i = 0; i < NO_OF_VERTEX;i++) {
		if (this->Coordinate[i][coord] < limit) {
			return false;
		}
	}
	return true;
}


void Monkey::moveRight() {
	for (int i = 0; i < NO_OF_VERTEX; i++) {
		this->Coordinate[i][0]++;
	}
}

void Monkey::moveLeft() {
	for (int i = 0; i < NO_OF_VERTEX; i++) {
		this->Coordinate[i][0]--;
	}
}

void Monkey::moveUp() {
	for (int i = 0; i < NO_OF_VERTEX; i++) {
		this->Coordinate[i][1]++;
	}
}

void Monkey::moveDown() {
	for (int i = 0; i < NO_OF_VERTEX; i++) {
		this->Coordinate[i][1]--;
	}
}




