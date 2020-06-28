#ifndef FONT_H
#define FONT_H

#include "freetype.h"
#include <map>
/*
#ifdef _WIN32 //Windows
constexpr const char* _SysFont = "C:/Windows/Fonts/arial.ttf";
#endif
#ifdef  __unix__ //Linux
//constexpr const char* _SysFont = "/usr/share/fonts/noto/NotoSans-Medium.ttf";
constexpr const char* _SysFont = "Fonts/NotoSans-Medium.ttf";
#endif*/

class Font
{
private:
	static std::map<unsigned int, freetype::font_data> fonts;
	static int screenHeight;
public:
	inline static void insert(unsigned int h) {
		freetype::font_data temp;
		fonts.emplace(h, temp);
	}
	inline static void init(int screenHeight) {
		Font::screenHeight = screenHeight;
	}
	inline static void initFonts() {
		for (auto& it : fonts) {
			it.second.init(_SysFont, it.first * (screenHeight / 480));
		}
	}
	inline static const freetype::font_data& getFont(unsigned int h) {
		return fonts.find(h)->second;
	}

};

#endif // !FONT_H