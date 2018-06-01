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


	virtual void move();//dir �������� �̵��ϴ� �Լ�


	bool is_equal_pos(Character& P);
	bool is_out_of_bound(int di);
	virtual bool is_backward(int di);
	bool is_on(int i);
	bool is_closer_to(Character& P, int dir); //dir �������� �̵��ϸ� P�� ��������� �ǹ�.
	int distance(int x, int y);//(x,y)���� �Ÿ�
	int distance(Character& P);//P���� �Ÿ�
	/*int distance(Grid& g);//���� G���� ���� ����� �������� �Ÿ��� ��ȯ.
	int distance(Grid& g, int* proximate_point);*///���� G���� ���� ����� �������� �Ÿ��� ��ȯ. ���� ����� ���� proximate_point�� ����.
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
	void drawPath();//Player�� ��ǥ�� Path Grid�� ���Խ�Ų��.
	void processBR();//Player�� �����ϴ� Boundary Rectangle �����Ѵ�.
	void setBR(int E, int W, int N, int S);
	int getBRN();
	int getBRS();
	int getBRW();
	int getBRE();
	bool is_backward(int di);
	bool is_inBR(int x, int y);
	bool is_inBR(Character& P);
	bool enclosed_by_path();//�н��� �ѷ����� ���¸� true
	void move();
	void process_prev_dir();
	void flood(int x, int y);
	void FloodtoTerritory();
	void floodChecking(int BR_Start, int BR_End, int BR_Side, bool isHorizontal);
	void PathToTer();//��θ� ����� �ٲٴ� �Լ�
	int Depth_in_BR(int x, int y);//Boundary Rectangle ���� ���� ���̸� ��ȯ�ϴ� �Լ�
private:
	int BR_N;//Boundary Rectangle, North
	int BR_S;
	int BR_E;
	int BR_W;
	int prev_dir=nulldir;
	bool PREV_B_EMPTY;
};
