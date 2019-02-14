#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
// Headers for game Objects
#include "env.h"


// make all instances of game Objects
Environment* e1;

class Game {
public:
	bool gameOver;
	Game() {
		gameOver = false;
		e1 = new Environment(990, 10, 10, 990);
	}
	static void render(void){
		e1->render(e1);
		//quickTestLine();
	}
};

Game *g1 = new Game();

void init(void)
{
	glClearColor(0, 0, 0, 0); // Set display-window color to black.
	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	gluOrtho2D(0.0, 1000.0, 0.0, 1000.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode.
	glutInitWindowPosition(50, 100); // Set top-left display-window position.
	glutInitWindowSize(1000, 1000); // Set display-window width and height.
	glutCreateWindow("An Example OpenGL Program"); // Create display window.
	init(); // Execute initialization procedure.
	glutDisplayFunc(g1->render); // Send graphics to display window.
	glutMainLoop(); // Display everything and wait.
	return 1;
}

void quickTestLine(void) {
	glColor3f(0.0, 0.4, 0.2); // Set line segment color to green.
	glBegin(GL_LINES);
	glVertex2i(900, 150); // Specify line-segment geometry.
	glVertex2i(100, 100);
	glEnd();
	glFlush(); // Process all OpenGL routines as quickly as possible.}
}