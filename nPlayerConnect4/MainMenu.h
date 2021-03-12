#ifndef MAINMENU_H
#define MAINMENU_H

#include <Button.h>
#include "Fonts.h"
#include "ImageLoder.h"
#include "ScreenCoord.h"
#include "FontInfo.h"
#include "Version.h"

class MainMenu
{
private:
	Game2D::Button quit;
	Game2D::Button start;
	Game2D::Button host;
	Game2D::Button join;
	GLuint mainMenuTex;
	TextInfo title;
	TextInfo version;
public:
	void init();

	void resize();

	void update();
	int processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState);

	void draw();
};


#endif //MAINMENU_H
