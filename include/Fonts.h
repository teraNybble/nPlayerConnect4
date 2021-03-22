#ifndef FONT_H
#define FONT_H

#include "freetype.h"
#include <map>

#include <iomanip>

#ifndef GAME2D_FONT_PATHS
#define GAME2D_FONT_PATHS


#ifdef _WIN32 //Windows
//#include <Windows.h>
constexpr const char* _SysFont = "C:/Windows/Fonts/arial.ttf";
#endif
#ifdef  __unix__ //Linux
constexpr const char* _SysFont = "/usr/share/fonts/noto/NotoSans-Medium.ttf";
#endif

#endif // !GAME2D_FONT_PATHS

namespace Game2D
{
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
		//static std::map<float, freetype::font_data> fonts;
		static std::map<float, Game2D::Freetype> fonts;
		static int screenHeight;
		static bool inited;
	public:
		//~Font() { std::cout << "fontDestructor\n"; fonts.clear(); }
		//inline static void clear() { fonts.clear(); std::cout << fonts.size() << "\n"; }

		~Font(){
			for(auto& it : fonts){
				it.second.clean();
			}
		}

		inline static void insert(float h) {
			Game2D::Freetype temp;
			//std::pair<float, Game2D::Freetype> test(h,temp);
			//fonts.insert(h,temp);
			fonts.emplace(h,temp);
		}
		inline static void init(int screenHeight) {
			Font::screenHeight = screenHeight;
			//inited = false;
		}
		inline static void initFonts() {
			float projectionMatMine[4][4];
			glGetFloatv(GL_PROJECTION_MATRIX, &projectionMatMine[0][0]);
			glPushAttrib(GL_TRANSFORM_BIT);
			GLint	viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			//gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
			glOrtho(viewport[0], viewport[2], viewport[1], viewport[3], 0, 100);
			//gluOrtho2D(left, right, bottom, top);
			glPopAttrib();
			//!

			float projectionMatScreen[4][4];
			glGetFloatv(GL_PROJECTION_MATRIX, &projectionMatScreen[0][0]);
			for (auto& it : fonts) {
				float temp = it.first;
				//std::cout << temp << " " << projectionMatMine[1][1] << " " << projectionMatMine[3][1] << " " << projectionMatScreen[1][1] << "\n";
				temp = (((temp * projectionMatMine[1][1]) + (projectionMatMine[3][1]*0)) / projectionMatScreen[1][1]);
				//if this function has been called then clean the font before reiniting it
				//it.second.clean();
				it.second.init(_SysFont, temp/*it.first/* * (screenHeight / 480)*/);
			}
			inited = true;
		}
		inline static const Freetype& getFont(float h) {
			if (!inited) { std::cerr << "Error: accesing fonts before initalisation" << std::endl; }
			return fonts.find(h)->second;
		}

	};
}

#endif // !FONT_H