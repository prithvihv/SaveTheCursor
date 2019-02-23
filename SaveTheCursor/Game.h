#pragma once
#include "env.h"
#include "monkey.h"
#include "banana.h"
class Game
{
public:
	int* x;
	int* y;
	bool gameOver;
	// make all instances of game Objects
	Environment* e1;
	Monkey* monkey;
	banana* bananaMouse;
	static void render();
	Game(int* xpostion, int* yposition);
};

