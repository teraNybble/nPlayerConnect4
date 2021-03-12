#ifndef SINGLEPLAYERMENU_H
#define SINGLEPLAYERMENU_H

#include <Button.h>
#include "Fonts.h"
#include "ImageLoder.h"
#include "ScreenCoord.h"
#include "FontInfo.h"
#include "Version.h"

class SinglePlayerMenu
{
private:
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

	Game2D::Button startButton;
	Game2D::Button backButton;

	TextInfo title;
	TextInfo noPlayers;
	TextInfo boardDims;
	TextInfo playerCount;
	TextInfo boardDimLabels;

	GLuint mainMenuTex;
public:
	void init();

	void resize();

	void update();
	int processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState);

	inline unsigned int getNumPlayers()  const { return numPlayers; }
	inline unsigned int getBoardWidth()  const { return boardWidth; }
	inline unsigned int getBoardHeight() const { return boardHeight; }
	inline unsigned int getLineLength()  const { return lineLength; }

	void draw() const;
};

#endif // !SINGLEPLAYERMENU_H