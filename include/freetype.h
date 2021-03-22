#ifndef GAME2D_FREETYPE_H
#define GAME2D_FREETYPE_H

#pragma warning(disable : 4786)
#pragma warning(disable : 4996)

#include <vector>
#include "glew.h"
#include <iostream>
#include <memory>
// FreeType Headers
#ifndef FREETYPE_H

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#endif
namespace Game2D{
class Freetype
{
public:
#ifdef _WIN32 //Windows
	static constexpr const char* _SysFont = "C:/Windows/Fonts/arial.ttf";
#elif __unix__ //Linux
	static constexpr const char* _SysFont = "/usr/share/fonts/noto/NotoSans-Medium.ttf";
#endif
private:
	float h;
	std::unique_ptr<GLuint[]> textures;
	GLuint list_base;

	inline int next_p2(int a){
		int rval = 1;
		while (rval < a) { rval <<= 1; }
		return rval;
	}

	/// A fairly straight forward function that pushes
	/// a projection matrix that will make object world
	/// coordinates identical to window coordinates.
	inline static void pushScreenCoordinateMatrix() {
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
	}

	/// Pops the projection matrix without changing the current
	/// MatrixMode.
	inline static void pop_projection_matrix() {
		glPushAttrib(GL_TRANSFORM_BIT);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPopAttrib();
	}

	void make_dlist(FT_Face face, char ch, GLuint list_base, GLuint* texBase);
public:
	Freetype() = default;
	Freetype(const Freetype& ft){
		textures = std::unique_ptr<GLuint[]>(ft.textures.get());
	}
	~Freetype();

	void init(const char* filename, unsigned int h);

	void clean();

	static float print(const Freetype& font, float x, float y, const char* fmt, ...);
	static float getLength(const Freetype& font, const char* fmt, ...);
	static inline float getHeight(const Freetype& ft_font)
	{
		float h = ft_font.h / .63f;
		float projectionMatMine[4][4];
		glGetFloatv(GL_PROJECTION_MATRIX, &projectionMatMine[0][0]);

		//pushScreenCoordinateMatrix();
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

		glPushAttrib(GL_TRANSFORM_BIT);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPopAttrib();

		h = h * projectionMatScreen[1][1];
		h = (h - projectionMatMine[3][1]) / projectionMatMine[1][1];

		return h;
	}
};
}

#endif //FREETYPE_H
