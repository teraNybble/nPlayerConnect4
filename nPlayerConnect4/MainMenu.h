#ifndef MAINMENU_H
#define MAINMENU_H

#include <Button.h>
#include "Fonts.h"
#include "ImageLoder.h"
#include "ScreenCoord.h"
//#include "freetype.h"

class MainMenu
{
private:
	Game2D::Sprite arrow;
	Game2D::Sprite arrowHover;
	Game2D::Sprite arrowClick;

	Game2D::Sprite startSprite;
	Game2D::Sprite startHover;
	Game2D::Sprite startClick;

	Game2D::Button playersPlus;
	Game2D::Button playersMinus;
	unsigned int numPlayers;

	unsigned int boardWidth;
	Game2D::Button boardWidthPlus;
	Game2D::Button boardWidthMinus;
	unsigned int boardHeight;
	Game2D::Button boardHeightPlus;
	Game2D::Button boardHeightMinus;

	unsigned int lineLength;

	Game2D::Button start;
	GLuint mainMenuTex;
	//freetype::font_data font;
public:
	void init();

	void update();
	int processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState);

	inline unsigned int getNumPlayers()  const { return numPlayers; }
	inline unsigned int getBoardWidth()  const { return boardWidth; }
	inline unsigned int getBoardHeight() const { return boardHeight; }
	inline unsigned int getLineLength()  const { return lineLength; }

	void draw();
};


#endif //MAINMENU_H
