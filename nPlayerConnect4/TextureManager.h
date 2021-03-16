#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <vector>
#include <glew.h>
#include <iostream>

class TextureManager
{
private:
	static inline std::vector<GLuint> textures;
public:
	static GLuint getText(size_t i) { 
		try {
			return textures.at(i);
		} catch (std::exception e) {
			//std::cerr << e.what() << "\n";
			std::cerr << i << " out of range " << textures.size() << "\n";
			return -1;
		}
	}
	static void loadTex(const char* path);
};

#endif