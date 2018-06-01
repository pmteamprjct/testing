#pragma once

#define MENU_COUNT 4
#define GAME_END_MENU_COUNT 3
#define INIT_TERRITORY_LENGTH 3

#include "GL/glut.h"
#include "extern.h"
#include "Character.h"
#include "Zombie.h"
#include "Grid.h"
#include "Shape.h"
#include <string>

enum { MAINMENU, IN_GAME, GAME_OVER, GAME_WIN, PAUSE };
enum { EASY, HARD, LUNATIC, MAINMENU_QUIT };
enum { RESTART, BACK_MAIN, QUIT };

void init(int DIFFICULTY);
void processIdle();
void renderBitmapCharacter(int x, int y, void *font, string str);
void renderScene();
void processSpecialKey(int key, int x, int y);
void processNormalKey(unsigned char key, int x, int y);