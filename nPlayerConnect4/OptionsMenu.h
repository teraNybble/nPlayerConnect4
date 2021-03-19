#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "TextureManager.h"
#include <Button.h>
#include <Dropdown.h>
#include "Fonts.h"
#include "ImageLoder.h"
#include "ScreenCoord.h"
#include "FontInfo.h"

class OptionsMenu
{
private:
	Game2D::Button play, back, apply;
	Game2D::Dropdown resolutions;
	Game2D::Dropdown aspectRatio;
	unsigned int previousAspect;

	void setResolutions(float ratio);
public:
	void init();

	void resize();

	void update();
	void processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState);
	int getResult(void(resize(float,float)));

	void draw();
};


#endif //OPTIONSMENU_H
