#include "Zombie.h"
#include <algorithm>
#include <queue>
#include <vector>

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

void Zombie::CheckDir() {
	isAllBlocked = true;
	for (auto i : { NORTH,SOUTH,EAST,WEST }) {
		if (is_blocked(i)) 
			blockedDir[i] = true;
		else 
			blockedDir[i] =false;
		isAllBlocked &= blockedDir[i]; // ���� �����ٸ� true
	}
} //��� ������ �������� Ȯ���ϴ� �Լ�

void Zombie::ZombieMoveCloser()
{
	CheckDir();
	if (!blockedDir[NORTH] && is_closed(P1,NORTH))
		setDir(NORTH);
	else if (!blockedDir[SOUTH] && is_closed(P1, SOUTH))
		setDir(SOUTH);
	else if (!blockedDir[EAST] && is_closed(P1, EAST))
		setDir(EAST);
	else if (!blockedDir[WEST] && is_closed(P1, WEST))
		setDir(WEST);
	else
		setDir(nulldir);
}

void Zombie::ZombieMoveCloser(int X, int Y)
{
	CheckDir();
	if (!blockedDir[NORTH] && y<Y)
		setDir(NORTH);
	else if (!blockedDir[SOUTH] && y>Y)
		setDir(SOUTH);
	else if (!blockedDir[EAST] && x<X)
		setDir(EAST);
	else if (!blockedDir[WEST] && x>X)
		setDir(WEST);
	else
		setDir(nulldir);

}

void Zombie::ZombieMoveAwayFrom(Character& P)
{
	CheckDir();
	if (!blockedDir[NORTH] && y>P.getY())
		setDir(NORTH);
	else if (!blockedDir[SOUTH] && y<P.getY())
		setDir(SOUTH);
	else if (!blockedDir[EAST] && x>P.getX())
		setDir(EAST);
	else if (!blockedDir[WEST] && x<P.getX())
		setDir(WEST);
	else
		setDir(nulldir);
}


void Zombie::ZombieMoveOutFromBR()
{
	CheckDir();
	int d = P1.Depth_in_BR(x, y);
	if (!blockedDir[NORTH] && P1.Depth_in_BR(x, y + 1) < d)
		setDir(NORTH);
	else if (!blockedDir[SOUTH] && P1.Depth_in_BR(x, y - 1) < d)
		setDir(SOUTH);
	else if (!blockedDir[EAST] && P1.Depth_in_BR(x + 1, y) < d)
		setDir(EAST);
	else if (!blockedDir[WEST] && P1.Depth_in_BR(x - 1, y) < d)
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

int Zombie::getDist() {
	return distFromPath;
}

int Zombie::getOpp() {
	return opportunity;
}

void Zombie::ZombiePathFinder()//Path�� ã�� ���
{

	//�ݰ� CLOSE �̳��� Path���� Ž���Ѵ�.
	int i1 = max(0, x - ZOMBIE_CLOSE);
	int k1 = min(GRID_WIDTH - 1, x + ZOMBIE_CLOSE);
	int i2 = max(0, y - ZOMBIE_CLOSE);
	int k2 = min(GRID_HEIGHT - 1, y + ZOMBIE_CLOSE);
	closestPath[0] = closestPath[1] = -1; // ���� X,Y�� ������� closestPath[2]�� �ٲ���ϴ�.
	distFromPath = 999; // ���� dis�� ������� distFromPath�� �ٲ���ϴ�.
	opportunity = 0;
	for (i1 = 0; i1 <= GRID_WIDTH - 1; i1++)
	{
		for (i2 = 0; i2 <= GRID_HEIGHT - 1; i2++)
		{
			//�����ϴ� Path�� �� �Ÿ��� ���� ����� ���� ã�´�.
			if (Path.isGrid(i1, i2)) {
				opportunity++;
				if(distance(i1,i2)<distFromPath)
				{
					closestPath[0] = i1;
					closestPath[1] = i2;
					distFromPath = distance(i1, i2);
				}
			}
		}
	}
	opportunity -= distFromPath/2; // Path�� ���� - Path�κ����� �Ÿ�
}

void Zombie::ZombiePathAttack(){ // Path�� ���� ����
	if (closestPath[0] != -1 && closestPath[1] != -1)
		ZombieMoveCloser(closestPath[0], closestPath[1]);//���� ����� ��ġ�� Path�� �޸���.
	else
		ZombieMoveCloser();
}

