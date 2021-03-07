#include "Rect.h"
using namespace Game2D;

Rect::Rect()
{
	pos = Pos2();
	width = height = 0;
}

Rect::Rect(Pos2 p, float width, float height)
{
	this->pos = p;
	this->width = width;
	this->height = height;
}

Rect::Rect(float x, float y, float width, float height)
{
	this->pos = Pos2(x,y);
	this->width = width;
	this->height = height;
}