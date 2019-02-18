#include "./env.h"
#include "./monkey.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>

void setTimeoutToUpdateSpeed(Monkey *m) {
	while (true) {
		/* generate number between 300 and 1500 */
		int num = (rand() % (1500 - 300 + 1));
		std::this_thread::sleep_for(std::chrono::milliseconds(num * 10));
		m->updateSpeed();
	}
}

int getOpposite(int i) {
	return i == 0 ? 1 : 0;
}

void setTimeoutToUpdateDirection(Monkey *m) {
	int countSameDirection = 0;
	while (true) {
		/* generate number between 500 and 1000 */
		int num = (rand() % (1000 - 500 + 1));
		std::this_thread::sleep_for(std::chrono::milliseconds(num * 10));
		int getRandomDirection = (rand() % 2);
		// logic to proc reverse direction every 3th time it fails
		m->monkeyDirection == getRandomDirection ? countSameDirection++ : false; // increase same count
		if (countSameDirection < 5) {
			m->monkeyDirection = getRandomDirection;
		}
		else {
			m->monkeyDirection = getOpposite(m->monkeyDirection);
			countSameDirection = 0;
		}
		
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
	// creating thread for updating speed Randomly
	std::thread speedChanger(setTimeoutToUpdateSpeed, this);
	speedChanger.detach();
	// creating thread for updating directions Randomly
	std::thread directionChanger(setTimeoutToUpdateDirection, this);
	directionChanger.detach();
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
	bool moveSide1;
	bool moveSide2;
	switch (this->currentPoistion)
	{
	case BOTTOM:
		moveSide1 = checkBounderies1(X, this->envRef->br_X);//Bottom_moveRightSide
		moveSide2 = checkBounderies2(X, this->envRef->tl_X);//Bottom_moveLeftSide
 
		if (moveSide1 &&moveSide2) {
			this->monkeyDirection==1?this->moveRight():this->moveLeft();
		}else {
			if (!moveSide1) {
				// bottom right corner going to right side
				this->Coordinate[0][0] = this->envRef->br_X;
				this->Coordinate[0][1] = this->envRef->br_Y;
				this->Coordinate[1][0] = this->envRef->br_X;
				this->Coordinate[1][1] = this->envRef->br_Y + BASEWIDTH;
				this->Coordinate[2][0] = this->envRef->br_X - HEIGHT;
				this->Coordinate[2][1] = this->envRef->br_Y + BASEWIDTH / 2;
				this->currentPoistion = RSIDE;
			}
			else {
				// bottom left corner going to left side
				this->Coordinate[0][0] = this->envRef->tl_X;
				this->Coordinate[0][1] = this->envRef->br_Y;
				this->Coordinate[1][0] = this->envRef->tl_X;
				this->Coordinate[1][1] = this->envRef->br_Y + BASEWIDTH;
				this->Coordinate[2][0] = this->envRef->tl_X + HEIGHT;
				this->Coordinate[2][1] = this->envRef->br_Y + BASEWIDTH / 2;
				this->currentPoistion = LSIDE;
			}
		}
		break;
	case RSIDE:
		moveSide1 = checkBounderies1(Y, this->envRef->tl_Y);//RSIDE_moveTopSide
		moveSide2 = checkBounderies2(Y, this->envRef->br_Y);//RSIDE_moveBottomSide
		if (moveSide1 &&moveSide2) {
			this->monkeyDirection == 1 ? this->moveUp() : this->moveDown();
		}
		else {
			if (!moveSide1) {
				// top right corner going to TOP side
				this->Coordinate[0][0] = this->envRef->br_X;
				this->Coordinate[0][1] = this->envRef->tl_Y;
				this->Coordinate[1][0] = this->envRef->br_X - BASEWIDTH;
				this->Coordinate[1][1] = this->envRef->tl_Y;
				this->Coordinate[2][0] = this->envRef->br_X - BASEWIDTH / 2;
				this->Coordinate[2][1] = this->envRef->tl_Y - HEIGHT;
				this->currentPoistion = TOP;
			}
			else {
				// bottom right corner going to Bottom side
				this->Coordinate[0][0] = this->envRef->br_X;
				this->Coordinate[0][1] = this->envRef->br_Y;
				this->Coordinate[1][0] = this->envRef->br_X - BASEWIDTH;
				this->Coordinate[1][1] = this->envRef->br_Y;
				this->Coordinate[2][0] = this->envRef->br_X - BASEWIDTH / 2;
				this->Coordinate[2][1] = this->envRef->br_Y + HEIGHT;
				this->currentPoistion = BOTTOM;
			}
		}
		break;
	case TOP:
		 moveSide2 = checkBounderies1(X, this->envRef->br_X);//TOP_moveLeftSide
		moveSide1 = checkBounderies2(X, this->envRef->tl_X);//TOP_moveRightSide
		if (moveSide1 && moveSide2) {
			//inverted
			this->monkeyDirection == 1 ?  this->moveLeft() : this->moveRight();
		}
		else {
			if (!moveSide1) {
				// top left corner going to left side
				this->Coordinate[0][0] = this->envRef->tl_X;
				this->Coordinate[0][1] = this->envRef->tl_Y;
				this->Coordinate[1][0] = this->envRef->tl_X;
				this->Coordinate[1][1] = this->envRef->tl_Y - BASEWIDTH;
				this->Coordinate[2][0] = this->envRef->tl_X + HEIGHT;
				this->Coordinate[2][1] = this->envRef->tl_Y - BASEWIDTH / 2;
				this->currentPoistion = LSIDE;
			}
			else {
				// top right corner going to right side
				this->Coordinate[0][0] = this->envRef->br_X;
				this->Coordinate[0][1] = this->envRef->tl_Y;
				this->Coordinate[1][0] = this->envRef->br_X;
				this->Coordinate[1][1] = this->envRef->tl_Y - BASEWIDTH;
				this->Coordinate[2][0] = this->envRef->br_X - HEIGHT;
				this->Coordinate[2][1] = this->envRef->tl_Y - BASEWIDTH / 2;
				this->currentPoistion = RSIDE;
			}
		}
		break;
	case LSIDE:
		moveSide2 = checkBounderies1(Y, this->envRef->tl_Y);//LSIDE_moveToBottom
		moveSide1 = checkBounderies2(Y, this->envRef->br_Y);//LSIDE_moveToTop
		if (moveSide1 && moveSide2) {
			// inverted
			this->monkeyDirection == 1 ? this->moveDown() : this->moveUp();
		}
		else {
			if (!moveSide1) {
				// left bottom corner going to bottom
				this->Coordinate[0][0] = this->envRef->tl_X;
				this->Coordinate[0][1] = this->envRef->br_Y;
				this->Coordinate[1][0] = this->envRef->tl_X + BASEWIDTH;
				this->Coordinate[1][1] = this->envRef->br_Y;
				this->Coordinate[2][0] = this->envRef->tl_X + BASEWIDTH / 2;
				this->Coordinate[2][1] = this->envRef->br_Y + HEIGHT;
				this->currentPoistion = BOTTOM;
			}
			else {
				// left bottom corner going to bottom
				this->Coordinate[0][0] = this->envRef->tl_X;
				this->Coordinate[0][1] = this->envRef->tl_Y;
				this->Coordinate[1][0] = this->envRef->tl_X + BASEWIDTH;
				this->Coordinate[1][1] = this->envRef->tl_Y;
				this->Coordinate[2][0] = this->envRef->tl_X + BASEWIDTH / 2;
				this->Coordinate[2][1] = this->envRef->tl_Y - HEIGHT;
				this->currentPoistion = TOP;
			}
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