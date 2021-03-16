#ifndef IMAGELODER_H
#define IMAGELODER_H

#include <string>
#include "glew.h"
#include <png.h>
#include <cstring>

class ImageLoder
{

private:
	static void GLErrorReport();
	static bool loadPNGFromFile(const char *name, int& pngWidth, int& pngHeight, bool& outHasAlpha, GLubyte** outData);
public:
	static void loadExtensions();

	static GLuint loadPNG(const char* filename);
};


#endif //IMAGELODER_H