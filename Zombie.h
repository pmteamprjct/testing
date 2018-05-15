#pragma once
#include"extern.h"
#include"Character.h"
#include"Grid.h"

#ifndef ZOMBIE_SPEED
#define ZOMBIE_SPEED 3
#endif


class Zombie : public Character
{
public:
	Zombie(int x, int y, float r, float g, float b);
	void ZombieMoveCloser();

};

