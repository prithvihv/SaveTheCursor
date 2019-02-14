class Environment {
public:
	int tl_X, tl_Y, br_X, br_Y;
	Environment(int xtl, int ytl, int xbr, int ybr);
	static void render(Environment *self);
};