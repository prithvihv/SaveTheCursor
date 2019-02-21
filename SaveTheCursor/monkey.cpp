#include "env.h"
#include "monkey.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <math.h>
#include "hitBox.h"
#include "Point.h"
#include <cmath>  

Point midpoint(0, 0);

void setTimeoutToUpdateSpeed(Monkey *m) {
	while (m->monkeyMadMovement) {
		/* generate number between 300 and 1500 */
		int num = (rand() % (1500 - 300 + 1));
		std::this_thread::sleep_for(std::chrono::milliseconds(num ));
		m->updateSpeed();
	}
}

bool Monkey::lineLineIntersection(Point A, Point B, Point C, Point D)
{
	// Line AB represented as a1x + b1y = c1 
	double a1 = B.y - A.y;
	double b1 = A.x - B.x;
	double c1 = a1 * (A.x) + b1 * (A.y);

	// Line CD represented as a2x + b2y = c2 
	double a2 = D.y - C.y;
	double b2 = C.x - D.x;
	double c2 = a2 * (C.x) + b2 * (C.y);

	double determinant = a1 * b2 - a2 * b1;

	
	if (determinant != 0)
	{
		double x = (b2*c1 - b1 * c2) / determinant;
		double y = (a1*c2 - a2 * c1) / determinant;

		if (y == 0) y = 0;
		if (x == 0) x = 0;
		if ((x >= 0 && y >= 0) && (x >= this->envRef->tl_X && x <= this->envRef->br_X) && (y >= this->envRef->br_Y && y <= this->envRef->tl_Y)) {
			this->MonkeySee.x = x;
			this->MonkeySee.y = y;
			return true;
		}
	}
	// The lines are parallel. This is simplified 
	// by returning a pair of FLT_MAX 
	//FLT_MAX, FLT_MAX
	
	return false;
}

int getOpposite(int i) {
	return i == 0 ? 1 : 0;
}

int countSameDirection = 0;
void setTimeoutToUpdateDirection(Monkey *m) {
	while (m->monkeyMadMovement) {
		/* generate number between 500 and 100 */
		int num = (rand() % (100 - 50 + 1));
		std::this_thread::sleep_for(std::chrono::milliseconds(num * 100));
		int getRandomDirection = rand() % 2;
		// logic to proc reverse direction every 2th time it fails
		m->monkeyDirection = getOpposite(m->monkeyDirection);
		/*
		m->monkeyDirection == getRandomDirection ? countSameDirection++ : false; // increase same count
		if (countSameDirection < 2) {
			m->monkeyDirection = getRandomDirection;
		}
		else {
			m->monkeyDirection = getOpposite(m->monkeyDirection);
			countSameDirection = 0;
		}
		*/
	}
}

void Stopper(Monkey *m) {
	//decide whether to stop the monkey or not 
	int minTime = 500;
	int maxTime = 1500;
	int countSameDirection = 0;
	while (m->monkeyMadMovement) {
		/* generate number between minTime and maxTime */
		int num = (rand() % (maxTime - minTime + 1));
		std::this_thread::sleep_for(std::chrono::milliseconds(num));
		int getRandomDirection = (rand() % 4); // 25% it might stop
		bool randomBool = getRandomDirection == 1 ? true : false;
		// logic to proc stopper by alternating minTime and MaxTime
		randomBool == false ? countSameDirection++ : false; // increase same count
		if (countSameDirection > 3 && !randomBool && (minTime - 100) < (maxTime + 100)) {
			minTime += 100;
			maxTime -= 100;
		}
		else  if (randomBool) {
			// proc here
			countSameDirection = 0;
			minTime = 500;
			maxTime = 2000;
			m->monkeyMadMovement = false;
		}
	}
}

Monkey::Monkey(Environment *env, int *x, int *y) {
	this->envRef = env;
	this->mouseX = x;
	this->mouseY = y;
	GLfloat midpoint = (GLfloat)(env->br_X + env->tl_X) / 2;
	GLfloat initHieght = env->br_Y;
	this->Coordinate[0][0] = midpoint - BASEWIDTH / 2;
	this->Coordinate[0][1] = initHieght;
	this->Coordinate[1][0] = midpoint + BASEWIDTH / 2;
	this->Coordinate[1][1] = initHieght;
	this->Coordinate[2][0] = midpoint;
	this->Coordinate[2][1] = initHieght + HEIGHT;
	this->currentPoistion = BOTTOM;
	this->hitB = new hitBox((*this).Coordinate,this->HITBOX_PADDING);
	this->initAwesomeness();
}

float angleToCursor = 0.0;

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

SideLocation Monkey::monkeySeeWhereToLand(SideLocation lastKnowLocation,Point a,Point b) {

	Point line1P1(this->envRef->tl_X, this->envRef->br_Y);
	Point line1P2(this->envRef->br_X, this->envRef->br_Y);

	Point line2P1(this->envRef->br_X, this->envRef->br_Y);
	Point line2P2(this->envRef->br_X, this->envRef->tl_Y);

	Point line3P1(this->envRef->tl_X, this->envRef->tl_Y);
	Point line3P2(this->envRef->br_X, this->envRef->tl_Y);

	Point line4P1(this->envRef->tl_X, this->envRef->tl_Y);
	Point line4P2(this->envRef->tl_X, this->envRef->br_Y);

	bool found = false;
	if (lastKnowLocation!=BOTTOM) {
		found = this->lineLineIntersection(a, b, line1P1, line1P2);
	}
	if (found)return BOTTOM;
	if (lastKnowLocation != RSIDE) {
		found = this->lineLineIntersection(a, b, line2P1, line2P2);
	}
	if (found)return RSIDE;
	if (lastKnowLocation != TOP) {
		found = this->lineLineIntersection(a, b, line3P1, line3P2);
	}
	if (found)return TOP;
	if (lastKnowLocation != LSIDE) {
		found = this->lineLineIntersection(a, b, line4P1, line4P2);
	}
	if (found)return LSIDE;
	throw "Monkey doesnt see where to land";
}

void Monkey::render(Monkey *self) {
	printf(" \n mouse position x : %d y: %d", *self->mouseX, *self->mouseX);
	self->hitB->DebugerRender(self->hitB);
	//self->testVarible = self->testVarible + 1; y doesnt this work
	//printf("running iteration %d \n",self->testVarible);
	if (self->monkeyMadMovement) {
		self->monkeyMove();
	}
	else if (!self->monkeyMadMovement&& self->currentPoistion == FLYING) {
		// this block will only executes when below has be configured and set up
		if (!self->hitB->collisionCheck(self->MonkeySee.x, self->MonkeySee.y)) {
			int xSign = self->Coordinate[0][X] > self->MonkeySee.x ? -1 : +1;
			int ySign = self->Coordinate[0][Y] > self->MonkeySee.y ? -1 : +1;
			self->moveDirection(angleToCursor, xSign, ySign);
		}
		else {
			printf(" \n Reached point");
			self->currentPoistion = self->MonkeySeePoistion;
			self->monkeyMadMovement = true;
			self->initAwesomeness();
		}
	}
	else {
		// wait for 200 milliseconds
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		// decide whether we want to move towards cursor or not 
		if (self->decideJump()) {
			/* write logic to move to cursor */

			self->findBaseMidPoint();
			float x1 = 500;
			float y1 = 500;
			float x2 = midpoint.x;
			float y2 = midpoint.y;

			Point a(500, 500);
			Point b(x2, y2);

			self->MonkeySeePoistion = self->monkeySeeWhereToLand(self->currentPoistion, a, b);

			float m = (y2 - y1) / (x2 - x1);
			angleToCursor = atan(m);
			/*
			for (int k = 0; k < self->NO_OF_VERTEX; k++) {
				int next = k + 1 < self->NO_OF_VERTEX ? k + 1 : 0;
				// bring it to origin
				self->Coordinate[next][X] -= self->Coordinate[k][X];
				self->Coordinate[next][Y] -= self->Coordinate[k][Y];

				self->Coordinate[next][X] = self->Coordinate[next][X] * cos(angleToCursor)
					- self->Coordinate[next][Y] * sin(angleToCursor);
				self->Coordinate[next][Y] = self->Coordinate[next][X] * sin(angleToCursor)
					+ self->Coordinate[k][Y] * cos(angleToCursor);
				// go back to that point
				self->Coordinate[next][X] = self->Coordinate[next][X] + self->Coordinate[k][X];
				self->Coordinate[next][Y] = self->Coordinate[next][Y] + self->Coordinate[k][Y];
			}
			*/
			self->currentPoistion = FLYING;
		}
		else {
			self->monkeyMadMovement = true;
			self->initAwesomeness(); // recreate all threads to do various functions of MONKEY BOT
		}
	}
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(midpoint.x, midpoint.y);
	glVertex2f(500, 500);
	glEnd();

	glColor3f(0.14901960784313725, 0.2549019607843137, 0.5607843137254902);
	glBegin(GL_TRIANGLES);
	glVertex2f(self->Coordinate[0][0], self->Coordinate[0][1]);
	glVertex2f(self->Coordinate[1][0], self->Coordinate[1][1]);
	glVertex2f(self->Coordinate[2][0], self->Coordinate[2][1]);
	glEnd();
	self->hitB->updateHitBox((*self).Coordinate);
	
};

int failedJumps = 0;
bool Monkey::decideJump() {
	int getRandomDirection = (rand() % 5); // 80% it might stop and jump
	return getRandomDirection != 1 ? true : false;
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
			this->monkeyDirection == 1 ? this->moveRight() : this->moveLeft();
		}
		else {
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
			this->monkeyDirection == 1 ? this->moveLeft() : this->moveRight();
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
bool Monkey::checkBounderies1(Coordinates coord, int limit) {
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

void Monkey::findBaseMidPoint() {

	switch (this->currentPoistion)
	{
	case BOTTOM:
	case TOP:
		midpoint.x = (this->Coordinate[0][X] + this->Coordinate[1][X]) / 2;
		midpoint.y = this->Coordinate[0][Y];
		break;
	case RIGHT:
	case LEFT:
		midpoint.y = (this->Coordinate[0][Y] + this->Coordinate[1][Y]) / 2;
		midpoint.x = this->Coordinate[0][X];
		break;
	}
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

void Monkey::moveDirection(float thethe,int xSign,int ySign) {
	float  xintercept = abs(cos(thethe) * this->MONKEY_SPEED_JUMP);
	float  yintercept = abs(sin(thethe) * this->MONKEY_SPEED_JUMP);
	for (int i = 0; i < NO_OF_VERTEX; i++) {
		this->Coordinate[i][X] = this->Coordinate[i][X] + xSign * xintercept;
		this->Coordinate[i][Y] = this->Coordinate[i][Y] + ySign * yintercept;
	}
}
/*
for (k = 0; k < nVerts; k++) {
vertsRot [k].x = pivPt.x + (verts [k].x - pivPt.x) * cos (theta)
- (verts [k].y - pivPt.y) * sin (theta);
vertsRot [k].y = pivPt.y + (verts [k].x - pivPt.x) * sin (theta)
+ (verts [k].y - pivPt.y) * cos (theta);
}self->Coordinate[k][X]
*/

void Monkey::updateSpeed() {
	/* generate number between 0 and MAX_MONKEY_SPEED */
	float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / MAX_MONKEY_SPEED));
	this->monkeySpeed = r2;
}