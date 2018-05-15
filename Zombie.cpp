#include "Zombie.h"
#include <algorithm>

Zombie::Zombie(int x, int y, float r, float g, float b) : Character(x, y, r, g, b)
{

}


void Zombie::ZombieMoveCloser()
{
	if (!is_blocked(NORTH) && is_closed(P1, NORTH))
		setDir(NORTH);
	else if (!is_blocked(SOUTH) && is_closed(P1, SOUTH))
		setDir(SOUTH);
	else if (!is_blocked(EAST) && is_closed(P1, EAST))
		setDir(EAST);
	else if (!is_blocked(WEST) && is_closed(P1, WEST))
		setDir(WEST);
	else
		setDir(nulldir);
}

void Zombie::ZombieMoveCloser(int X, int Y)
{
	if (!is_blocked(NORTH) && getY()<Y)
		setDir(NORTH);
	else if (!is_blocked(SOUTH) && getY()>Y)
		setDir(SOUTH);
	else if (!is_blocked(EAST) && getX()<X)
		setDir(EAST);
	else if (!is_blocked(WEST) && getX()>X)
		setDir(WEST);
	else
		setDir(nulldir);
}


void Zombie::ZombieCheckRisk()
{

}


void Zombie::ZombiePathFinder()//Path를 찾는 모드
{

	//반경 CLOSE 이내의 Path들을 탐색한다.
	int i1 = max(0, x - ZOMBIE_CLOSE);
	int k1 = min(GRID_WIDTH - 1, x + ZOMBIE_CLOSE);
	int i2 = max(0, y - ZOMBIE_CLOSE);
	int k2 = min(GRID_HEIGHT - 1, y + ZOMBIE_CLOSE);
	int X = -1;
	int Y = -1;
	int dis = 999;
	for (i1 = 0; i1 <= GRID_WIDTH - 1; i1++)
	{
		for (i2 = 0; i2 <= GRID_HEIGHT - 1; i2++)
		{
			//존재하는 Path들 중 거리가 가장 가까운 것을 찾는다.
			if (Path.isGrid(i1, i2) && distance(i1, i2)<dis)
			{
				X = i1;
				Y = i2;
				dis = distance(i1, i2);
			}
		}
	}
	if (X != -1 && Y != -1)
		ZombieMoveCloser(X, Y);//가장 가까운 위치의 Path로 달린다.
	else
		ZombieMoveCloser();
}
