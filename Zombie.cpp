#include "Zombie.h"
#include <algorithm>


Grid RiskFloodBoard;



Zombie::Zombie(int x, int y, float r, float g, float b) : Character(x, y, r, g, b)
{

}

void Zombie::setDir(int di)
{
	if (is_backward(di))
	{
		dir = nulldir;
		return;
	}
	else
	{
		dir = di;
		return;
	}

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
	if (!is_blocked(NORTH) && y<Y)
		setDir(NORTH);
	else if (!is_blocked(SOUTH) && y>Y)
		setDir(SOUTH);
	else if (!is_blocked(EAST) && x<X)
		setDir(EAST);
	else if (!is_blocked(WEST) && x>X)
		setDir(WEST);
	else
		setDir(nulldir);
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


void Zombie::ZombieCheckRisk()//�ڱ� �ڽ��� �󸶳� ���������� üũ�ϴ� �Լ�.
{
	risk = 0;
	risk += P1.Depth_in_BR(x, y);//Boundary Rectangle �ȿ� ����� ��� �������� ����.

}


int Zombie::RiskCheckFlood(int x, int y, int dist)//Flooding�� ���� BR������ �ִ�Ż��ð� Check �Լ�.
{
	bool Way[4] = { false };
	int Min_checker = -1;
	if (!P1.is_inBR(x, y))
		return dist;
	//4���� üũ
	if (!RiskFloodBoard.isGrid(x, y + 1) && !is_blocked(x, y + 1))
		Way[0] = true;
	if (!RiskFloodBoard.isGrid(x, y - 1) && !is_blocked(x, y - 1))
		Way[1] = true;
	if (!RiskFloodBoard.isGrid(x + 1, y) && !is_blocked(x + 1, y))
		Way[2] = true;
	if (!RiskFloodBoard.isGrid(x - 1 , y) && !is_blocked(x - 1, y))
		Way[3] = true;

	return 0;
}

int Zombie::getRisk()
{
	return risk;
}


void Zombie::ZombiePathFinder()//Path�� ã�� ���
{

	//�ݰ� CLOSE �̳��� Path���� Ž���Ѵ�.
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
			//�����ϴ� Path�� �� �Ÿ��� ���� ����� ���� ã�´�.
			if (Path.isGrid(i1, i2) && distance(i1, i2)<dis)
			{
				X = i1;
				Y = i2;
				dis = distance(i1, i2);
			}
		}
	}
	if (X != -1 && Y != -1)
		ZombieMoveCloser(X, Y);//���� ����� ��ġ�� Path�� �޸���.
	else
		ZombieMoveCloser();
}
