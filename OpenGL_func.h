#pragma once


#ifndef WIDTH
#define WIDTH 675		// window's width
#endif
#ifndef HEIGHT
#define HEIGHT 810		// window's height
#endif

#define GRID_WHOLE_WIDTH GRID_WIDTH+6
#define GRID_WHOLE_HEIGHT GRID_HEIGHT

#define MENU_COUNT 4
#define GAME_END_MENU_COUNT 3
#define PAUSE_MENU_COUNT 4
#define INIT_TERRITORY_LENGTH 3

#include "GL/glut.h"
#include "extern.h"
#include "Character.h"
#include "Zombie.h"
#include "Grid.h"
#include "Shape.h"
#include <string>
#include <Windows.h>

enum { MAINMENU, IN_GAME, GAME_OVER, GAME_WIN, PAUSE };
enum { EASY, HARD, LUNATIC, MAINMENU_QUIT };
enum { RESTART, BACK_MAIN, QUIT, RESUME };

void init(int DIFFICULTY);
void reset_game();
void processIdle();
void renderBitmapCharacter(float x, float y, void *font, string str);
void renderScene();
void processSpecialKey(int key, int x, int y);
void processNormalKey(unsigned char key, int x, int y);
void resize(int width, int height);