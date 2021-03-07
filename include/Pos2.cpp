#include "Pos2.h"
using namespace Game2D;

Pos2::Pos2()
{
	x = y = 0;
}

Pos2::Pos2(float x, float y)
{
	this->x = x;
	this->y = y;
}
/*
std::ostream& operator<<(std::ostream& os, const Pos2& p)
{
	return os << p.x << ", " << p.y;
}
*/