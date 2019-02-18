#include "./env.h"
#include "./monkey.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>

void setTimeoutToUpdateSpeed(Monkey *m) {
	/* generate number between 0 and 1500 */
	while (true) {
		int num = (rand() % (1500 + 1));
		std::this_thread::sleep_for(std::chrono::milliseconds(num * 10));
		m->updateSpeed();
	}
}

Monkey::Monkey(Environment *env){
	// init randomizing speed

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
	std::thread speedChanger(setTimeoutToUpdateSpeed, this);
	speedChanger.detach();
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

// checks upper limit
bool Monkey::checkBounderies1(Coordinates coord,int limit) {
	for (int i = 0; i < NO_OF_VERTEX;i++) {
		if (this->Coordinate[i][coord] > limit) {
			return false;
		}
	}
	return true;
}

// checks lower limit
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
		this->Coordinate[i][0] += monkeySpeed;
	}
}

void Monkey::moveLeft() {
	for (int i = 0; i < NO_OF_VERTEX; i++) {
		this->Coordinate[i][0] -= monkeySpeed;
	}
}

void Monkey::moveUp() {
	for (int i = 0; i < NO_OF_VERTEX; i++) {
		this->Coordinate[i][1] += monkeySpeed;
	}
}

void Monkey::moveDown() {
	for (int i = 0; i < NO_OF_VERTEX; i++) {
		this->Coordinate[i][1] -= monkeySpeed;
	}
}

void Monkey::updateSpeed() {
	/* generate number between 0 and MAX_MONKEY_SPEED */
	float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / MAX_MONKEY_SPEED));
	this->monkeySpeed = r2;
}