#include "Colour.h"
#include <algorithm>
using namespace Game2D;

Colour::Colour()
{
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}

Colour::Colour(float r, float g, float b, float a)
{
	//ensures that values are between 0 and 1
	std::clamp(r, 0.0f, 1.0f);
	std::clamp(g, 0.0f, 1.0f);
	std::clamp(b, 0.0f, 1.0f);
	std::clamp(a, 0.0f, 1.0f);
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

//define some commonly used colours to save time
const Colour Colour::Black			= Colour(0, 0, 0, 1);
const Colour Colour::White			= Colour(1, 1, 1, 1);
const Colour Colour::Transparent	= Colour(0, 0, 0, 0);
const Colour Colour::Red			= Colour(1, 0, 0, 1);
const Colour Colour::Yellow			= Colour(1, 1, 0, 1);
const Colour Colour::Green			= Colour(0, 1, 0, 1);
const Colour Colour::Cyan			= Colour(0, 1, 1, 1);
const Colour Colour::Blue			= Colour(0, 0, 1, 1);
const Colour Colour::Magenta		= Colour(1, 0, 1, 1);