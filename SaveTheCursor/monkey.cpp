#include "env.h"
#include "monkey.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>

void setTimeoutToUpdateSpeed(Monkey *m) {
	while (m->monkeyMadMovement) {
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
	while (m->monkeyMadMovement) {
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

void Stopper(Monkey *m) {
	//decide whether to stop the monkey or not 
	int minTime = 500;
	int maxTime = 2000;
	int countSameDirection = 0;
	while (m->monkeyMadMovement) {
		/* generate number between minTime and maxTime */
		int num = (rand() % (maxTime - minTime + 1));
		std::this_thread::sleep_for(std::chrono::milliseconds(num));
		int getRandomDirection = (rand() % 4); // 25% it might stop
		bool randomBool = getRandomDirection == 1 ? true : false;
		// logic to proc stopper by alternating minTime and MaxTime
		randomBool == false ? countSameDirection++ : false; // increase same count
		if (countSameDirection > 3 && !randomBool && (minTime-100) < (maxTime + 100)) {
			minTime += 100;
			maxTime -= 100;
		}
		else  if(randomBool){
			// proc here
			countSameDirection = 0;
			minTime = 500;
			maxTime = 2000;
			m->monkeyMadMovement = false;
		}
	}
}

Monkey::Monkey(Environment *env,int *x, int *y){
	this->envRef = env;
	this->mouseX = x;
	this->mouseY = y;
	GLfloat midpoint = (GLfloat)(env->br_X + env->tl_X) / 2;
	GLfloat initHieght = env->br_Y;
	this->Coordinate[0][0] = midpoint - BASEWIDTH/2;
	this->Coordinate[0][1] = initHieght;
	this->Coordinate[1][0] = midpoint + BASEWIDTH/2;
	this->Coordinate[1][1] = initHieght;
	this->Coordinate[2][0] = midpoint;
	this->Coordinate[2][1] = initHieght + HEIGHT;
	this->currentPoistion = BOTTOM;
	this->initAwesomeness();
}

void Monkey::initAwesomeness() {
	// creating thread for updating speed Randomly
	std::thread speedChanger(setTimeoutToUpdateSpeed, this);
	speedChanger.detach();
	// creating thread for updating directions Randomly
	std::thread directionChanger(setTimeoutToUpdateDirection, this);
	directionChanger.detach();
	// creating thread for updating directions Randomly
	std::thread StopperThread(Stopper, this);
	StopperThread.detach();
}

void Monkey::render(Monkey *self) {
	printf(" \n mouse position x : %d y: %d", *self->mouseX, *self->mouseX);
	//self->testVarible = self->testVarible + 1; y doesnt this work
	//printf("running iteration %d \n",self->testVarible);
	if (self->monkeyMadMovement) {
		self->monkeyMove();
	}
	else {
		// wait for 200 milliseconds
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		// decide whether we want to move towards cursor or not 
		if (self->decideJump()) {
			/* write logic to move to cursor */
		}
		//if not then 
		else {
			self->monkeyMadMovement = true;
			self->initAwesomeness(); // recreate all threads to do various functions of MONKEY BOT
		}
	}
	glColor3f(0.0, 0.4, 0.2);
	glBegin(GL_TRIANGLES);
	glVertex2f(self->Coordinate[0][0], self->Coordinate[0][1]);
	glVertex2f(self->Coordinate[1][0], self->Coordinate[1][1]);
	glVertex2f(self->Coordinate[2][0], self->Coordinate[2][1]);
	glEnd();
};

int failedJumps = 0;
bool Monkey::decideJump() {
	int getRandomDirection = (rand() % 2); // 50% it might stop
	return getRandomDirection == 1 ? true : false;
}

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