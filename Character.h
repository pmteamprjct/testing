#pragma once
#include <iostream>
#include <GL/glut.h>



#ifndef GRID_WIDTH
#define GRID_WIDTH 30
#endif

#ifndef GRID_HEIGHT
#define GRID_HEIGHT 30		
#endif



using namespace std;


enum { NORTH, EAST, SOUTH, WEST };
enum { TERRITORY, PATH, MAP_BOUND, ZOMBIE_POS };


#define nulldir -1

class Character
{
public:
	//Ctor
	Character(int x, int y, float r, float g, float b);

	//Setter-Getter
	virtual bool setDir(int di);
	void setColor(float r, float g, float b);
	void setPos(int pos_x, int pos_y);
	void ProcessBPos();
	int getX();
	int getY();
	int getbX();
	int getbY();
	int getDir();


	virtual void move();//dir 방향으로 이동하는 함수


	bool is_equal_pos(Character& P);
	bool is_out_of_bound(int di);
	virtual bool is_backward(int di);
	bool is_on(int i);
	bool is_closer_to(Character& P, int dir); //dir 방향으로 이동하면 P와 가까워짐을 의미.
	int distance(int x, int y);//(x,y)와의 거리
	int distance(Character& P);//P와의 거리
	/*int distance(Grid& g);//영역 G에서 가장 가까운 영역과의 거리를 반환.
	int distance(Grid& g, int* proximate_point);*///영역 G에서 가장 가까운 영역과의 거리를 반환. 가장 가까운 점은 proximate_point에 저장.
	void draw(int phase);

protected:
	int x = 0;
	int y = 0;
	int b_x = 0;
	int b_y = 0;
	int dir = nulldir;
	float Color[3];
};



class Player : public Character
{
public:
	Player(int x, int y, float r, float g, float b);
	void drawPath();//Player의 좌표를 Path Grid에 포함시킨다.
	void processBR();//Player를 포함하는 Boundary Rectangle 갱신한다.
	void setBR(int E, int W, int N, int S);
	int getBRN();
	int getBRS();
	int getBRW();
	int getBRE();
	bool is_backward(int di);
	bool is_inBR(int x, int y);
	bool is_inBR(Character& P);
	bool enclosed_by_path();//패스로 둘러싸인 상태면 true
	void move();
	void process_prev_dir();
	void flood(int x, int y);
	void FloodtoTerritory();
	void floodChecking(int BR_Start, int BR_End, int BR_Side, bool isHorizontal);
	void PathToTer();//경로를 영토로 바꾸는 함수
	int Depth_in_BR(int x, int y);//Boundary Rectangle 안의 점의 깊이를 반환하는 함수
private:
	int BR_N;//Boundary Rectangle, North
	int BR_S;
	int BR_E;
	int BR_W;
	int prev_dir=nulldir;
	bool PREV_B_EMPTY;
};
