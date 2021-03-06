#ifndef FONTINFO_H
#define FONTINFO_H

#include <string>
#include <Pos2.h>

struct TextInfo
{
	std::string text;
	float width;
	unsigned int fontSize;
	Game2D::Pos2 pos;
};

#endif