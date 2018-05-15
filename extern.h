#pragma once
#include <algorithm>
#include <vector>
using namespace std;

class Character;
class Player;
class Grid;
class Zombie;

extern Grid Territory;
extern Grid Path;
extern Grid Flood;
extern Player P1;
extern int score;

extern vector<Zombie> Zombies;
