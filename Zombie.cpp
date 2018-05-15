#include "Zombie.h"


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

