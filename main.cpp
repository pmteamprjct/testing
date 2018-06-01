#include "Character.h"
#include "Zombie.h"
#include "Grid.h"
#include "Shape.h"
#include "OpenGL_func.h"

#ifndef WIDTH
#define WIDTH 675		// window's width
#endif
#ifndef HEIGHT
#define HEIGHT 810		// window's height
#endif



#ifndef GRID_POINT_SIZE
#define GRID_POINT_SIZE 14.5f
#endif

#ifndef PATH_POINT_SIZE
#define PATH_POINT_SIZE 8.0f
#endif



#define GRID_WHOLE_WIDTH GRID_WIDTH+6
#define GRID_WHOLE_HEIGHT GRID_HEIGHT
clock_t clock_start = clock();
clock_t clock_end;
int mode = MAINMENU;
int menu_selection = EASY;

int debugger_int = 0;
int zombie_move_count = 0;
int life = -1;
int score;
int phase = 1;

Player P1(GRID_WIDTH/2, GRID_HEIGHT/2, 1, 0, 0);
vector<Zombie> Zombies;
Grid Territory(0.5, 0, 0.5, 1,GRID_POINT_SIZE);
Grid Path(0.5, 0, 0.5, 1, PATH_POINT_SIZE);
Grid Zombie_position;
Grid Flood;



void main(int argc, char **argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(650, 50);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("KILL & CONQUER!");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, GRID_WHOLE_HEIGHT, 0, GRID_WHOLE_WIDTH);



	// register callbacks
	glutDisplayFunc(renderScene);
	glutSpecialFunc(processSpecialKey);
	glutKeyboardFunc(processNormalKey);
	glutIdleFunc(processIdle);

	// enter GLUT event processing cycle
	glutMainLoop();
}
