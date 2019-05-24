#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <thread>
// Headers for game Objects
#include "Game.h"

int x = 0;
int y = 0;
Game *g = new Game(&x,&y);

void init(void)
{

	glClearColor(1, 1, 1, 1); // Set display-window color to black.
	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	glLoadIdentity();
	gluOrtho2D(0.0, 1000.0, 0.0, 1000.0);
	glMatrixMode(GL_MODELVIEW); // Set projection parameters.
	glLoadIdentity();
	//(0.35, 0.329, 0.439, 1)
	//glRotatef
}

void FrameChecks(int a) {
	
	//monkey->moveRight();
	glutTimerFunc(10, FrameChecks, 1);
	// timer is a one shoot must be reset after being called.
	//By using a timed event, your application should run about the same speed on any machine.
	glutPostRedisplay();
}

void onMouse( int xp, int yp) {
	x = xp;
	y = yp;
}

void playMusic() {
	while (true) {
		sndPlaySound("POL.wav", SND_ALIAS);
		std::this_thread::sleep_for(std::chrono::seconds(12));
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode.
	glutInitWindowPosition(50, 100); // Set top-left display-window position.
	glutInitWindowSize(800, 600); // Set display-window width and height.
	glutCreateWindow("SaveTheCursor"); // Create display window.
	init(); // Execute initialization procedure.
	glutDisplayFunc(g->render); // Send graphics to display window.
	glutPassiveMotionFunc(g->bananaMouse->onMouse);
	glutTimerFunc(100, FrameChecks, 1); // works like a set timeout recalls functions
	std::thread speedChanger(playMusic);
	
	glutMainLoop(); // Display everything and wait.
	return 1;
}