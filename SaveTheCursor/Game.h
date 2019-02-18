#pragma once
#include "env.h"
#include "monkey.h"
class Game
{
public:
	int* x;
	int* y;
	bool gameOver;
	// make all instances of game Objects
	Environment* e1;
	Monkey* monkey;
	static void render();
	Game(int* xpostion, int* yposition);
};

