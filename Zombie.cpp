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
		isAllBlocked &= blockedDir[i]; // 전부 막혔다면 true
	}
} //어느 방향이 막혔는지 확인하는 함수

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


void Zombie::ZombieCheckRisk()//자기 자신이 얼마나 위험한지를 체크하는 함수.
{
	risk = 0;
	risk += P1.Depth_in_BR(x, y);//Boundary Rectangle 안에 깊숙히 들어 있을수록 위험.

}


int Zombie::RiskCheckFlood(int x, int y, int dist)//Flooding을 통한 BR에서의 최단탈출시간 Check 함수.
{
	bool Way[4] = { false };
	int Min_checker = -1;
	if (!P1.is_inBR(x, y))
		return dist;
	//4방향 체크
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

void Zombie::ZombiePathFinder()//Path를 찾는 모드
{

	//반경 CLOSE 이내의 Path들을 탐색한다.
	int i1 = max(0, x - ZOMBIE_CLOSE);
	int k1 = min(GRID_WIDTH - 1, x + ZOMBIE_CLOSE);
	int i2 = max(0, y - ZOMBIE_CLOSE);
	int k2 = min(GRID_HEIGHT - 1, y + ZOMBIE_CLOSE);
	closestPath[0] = closestPath[1] = -1; // 변수 X,Y를 멤버변수 closestPath[2]로 바꿨습니다.
	distFromPath = 999; // 변수 dis를 멤버변수 distFromPath로 바꿨습니다.
	opportunity = 0;
	for (i1 = 0; i1 <= GRID_WIDTH - 1; i1++)
	{
		for (i2 = 0; i2 <= GRID_HEIGHT - 1; i2++)
		{
			//존재하는 Path들 중 거리가 가장 가까운 것을 찾는다.
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
	opportunity -= distFromPath/2; // Path의 길이 - Path로부터의 거리
}

void Zombie::ZombiePathAttack(){ // Path를 향해 돌격
	if (closestPath[0] != -1 && closestPath[1] != -1)
		ZombieMoveCloser(closestPath[0], closestPath[1]);//가장 가까운 위치의 Path로 달린다.
	else
		ZombieMoveCloser();
}

