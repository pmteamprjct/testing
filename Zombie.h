#pragma once
#include"extern.h"
#include"Character.h"
#include"Grid.h"

#ifndef ZOMBIE_SPEED
#define ZOMBIE_SPEED 2
#endif

#ifndef ZOMBIE_CLOSE
#define ZOMBIE_CLOSE GRID_WIDTH/5+GRID_HEIGHT/5
#endif


class Zombie : public Character
{
public:
	Zombie(int x, int y, float r, float g, float b);
	bool setDir(int di);
	bool is_blocked(int i);
	bool is_blocked(int x, int y);
	void ZombieMoveCloser();
	void ZombieMoveCloser(int x,int y);//(x,y)로 달린다.
	void ZombieMoveOutFromBR();
	void ZombieMoveAwayFrom(Character& P);
	void ZombiePathFinder();//Path를 찾는 모드
	void ZombieCheckRisk();
	void update_Zombie_pos();//Grid Zombie_pos를 업데이트하는 함수
	void ZombiePathAttack();
	void Zombie_Think();

	int getRisk();
	int getDist();
	int getOpp();

private:
	int risk = 0;
	int opp = 0;
	int dis = 999;
	int closestX =-1;
	int closestY = -1;
};

bool is_exist(int x, int y);
