#include "Zombie.h"
#include <algorithm>


Zombie::Zombie(int x, int y, float r, float g, float b) : Character(x, y, r, g, b)
{

}

bool Zombie::setDir(int di)
{
	if (is_blocked(di))
	{
		dir = nulldir;
		return false;
	}
	else
	{
		dir = di;
		return true;
	}

}

bool Zombie::is_blocked(int x, int y)
{
	if (Territory.isGrid(x, y) || x <= 0 || y <= 0 || x >= GRID_WIDTH || y >= GRID_HEIGHT)
		return true;
	return false;
}
bool Zombie::is_blocked(int i)
{
	if (is_out_of_bound(i))
		return true;
	switch (i)
	{
	case NORTH:
		if (Territory.isGrid(x, y + 1))
			return true;
		return false;
	case SOUTH:
		if (Territory.isGrid(x, y - 1))
			return true;
		return false;
	case WEST:
		if (Territory.isGrid(x - 1, y))
			return true;
		return false;
	case EAST:
		if (Territory.isGrid(x + 1, y))
			return true;
		return false;
	}
}

bool is_exist(int x, int y)
{
	for (int i = 0; i < Zombies.size(); i++)
	{
		if (x == Zombies[i].getX() && y == Zombies[i].getY())
			return true;
	}
	return false;
}





void Zombie::ZombieMoveCloser()
{
	bool is_dir_selected = false;
	if (!is_dir_selected && is_closer_to(P1, NORTH))
		is_dir_selected = setDir(NORTH);
	if (!is_dir_selected && is_closer_to(P1, SOUTH))
		is_dir_selected = setDir(SOUTH);
	if (!is_dir_selected && is_closer_to(P1, EAST))
		is_dir_selected = setDir(EAST);
	if (!is_dir_selected && is_closer_to(P1, WEST))
		is_dir_selected = setDir(WEST);
}



void Zombie::ZombieMoveCloser(int X, int Y)
{
	bool is_dir_selected = false;
	if (!is_dir_selected && y<Y)
		is_dir_selected = setDir(NORTH);
	if (!is_dir_selected && y>Y)
		is_dir_selected = setDir(SOUTH);
	if (!is_dir_selected && x<X)
		is_dir_selected = setDir(EAST);
	if (!is_dir_selected && x>X)
		is_dir_selected =setDir(WEST);
}

void Zombie::ZombieMoveAwayFrom(Character& P)
{
	if (!is_blocked(NORTH) && y>P.getY())
		setDir(NORTH);
	else if (!is_blocked(SOUTH) && y<P.getY())
		setDir(SOUTH);
	else if (!is_blocked(EAST) && x>P.getX())
		setDir(EAST);
	else if (!is_blocked(WEST) && x<P.getX())
		setDir(WEST);
	else
		setDir(nulldir);
}


void Zombie::ZombieMoveOutFromBR()
{
	int d = P1.Depth_in_BR(x, y);
	if (!is_blocked(NORTH) && P1.Depth_in_BR(x, y + 1) < d)
		setDir(NORTH);
	else if (!is_blocked(SOUTH) && P1.Depth_in_BR(x, y - 1) < d)
		setDir(SOUTH);
	else if (!is_blocked(EAST) && P1.Depth_in_BR(x + 1, y) < d)
		setDir(EAST);
	else if (!is_blocked(WEST) && P1.Depth_in_BR(x - 1, y) < d)
		setDir(WEST);
	else
		setDir(nulldir);



}


void Zombie::ZombieCheckRisk()//자기 자신이 얼마나 위험한지를 체크하는 함수.
{
	risk = 0;
	risk += P1.Depth_in_BR(x, y);//Boundary Rectangle 안에 깊숙히 들어 있을수록 위험.

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
	opp = 0;
	dis = 999;
	for (i1 = 0; i1 <= GRID_WIDTH - 1; i1++)
	{
		for (i2 = 0; i2 <= GRID_HEIGHT - 1; i2++)
		{
			//존재하는 Path들 중 거리가 가장 가까운 것을 찾는다.
			if (Path.isGrid(i1, i2)) {
				opp++;
				if(distance(i1, i2) < dis)
				{
					X = i1;
					Y = i2;
					dis = distance(i1, i2);
				}
			}
		}
	}
	closestX = X;
	closestY = Y;
	opp -= dis / 2;
}

void Zombie::ZombiePathAttack() {
	if (closestX != -1 && closestY != -1)
		ZombieMoveCloser(closestX, closestY);//가장 가까운 위치의 Path로 달린다.
	else
		ZombieMoveCloser();
}

void Zombie::update_Zombie_pos()
{
	Zombie_position.setPoint(x, y, true);
}
//Grid Zombie_pos를 업데이트하는 함수


int Zombie::getRisk()
{
	return risk;
}

int Zombie::getDist() {
	return dis;
}

int Zombie::getOpp() {
	return opp;
}


void Zombie::Zombie_Think()
{
	int k = Zombies.size();
	ZombieCheckRisk();
	ZombiePathFinder();

	if (dis < 6 || opp >= 5) {
		ZombiePathAttack();
		return;
	}
	else if (getRisk() < 30)
	{
		ZombiePathAttack();
		for (int j = 0; j < k; j++)
		{
			if (&Zombies[j] == this)
				continue;
			if (distance(Zombies[j]) < 7)
			{
				ZombieMoveAwayFrom(Zombies[j]);
				break;
			}
		}
	}
	else
	{
		ZombieMoveOutFromBR();
	}

}



