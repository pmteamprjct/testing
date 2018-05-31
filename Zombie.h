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
	int getRisk();
	void setDir(int di);
	int getDist();
	int getOpp();
	void CheckDir();
	void ZombieMoveCloser();
	void ZombieMoveCloser(int X,int Y);//���� ����� ��ġ�� Path�� �޸���.
	void ZombieMoveOutFromBR();
	void ZombieMoveAwayFrom(Character& P);
	void ZombiePathFinder();//Path�� ã�� ���
	void ZombiePathAttack(); // PathFinder���� �и�
	void ZombieCheckRisk();
	int RiskCheckFlood(int x, int y, int dist);
private:
	int risk=0;
	int opportunity = 0;
	int distFromPath = 999;
	int closestPath[2];
	bool blockedDir[4];
	bool isAllBlocked;

};

