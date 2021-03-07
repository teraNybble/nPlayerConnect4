#include "Fonts.h"

using namespace Game2D;

std::map<float, freetype::font_data> Font::fonts;
int Font::screenHeight;
bool Font::inited = false;