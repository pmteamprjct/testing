#pragma once
#include <algorithm>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>


using namespace std;

class Character;
class Player;
class Grid;
class Zombie;

extern clock_t clock_start;
extern clock_t clock_end;


extern Grid Territory;
extern Grid Path;
extern Grid Flood;
extern Grid Zombie_position;
extern Player P1;
extern int mode;
extern int menu_selection;

extern int debugger_int;
extern int zombie_move_count;
extern int score;
extern int phase;
extern int life;


extern vector<Zombie> Zombies;
