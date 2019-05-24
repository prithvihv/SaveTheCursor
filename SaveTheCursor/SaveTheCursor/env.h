#pragma once
class Environment {
public:
	int tl_X, tl_Y, br_X, br_Y;
	Environment(int xtl, int ytl, int xbr, int ybr);
	static void render(Environment *self);
	float color[3] = {1,0.6,0};
};