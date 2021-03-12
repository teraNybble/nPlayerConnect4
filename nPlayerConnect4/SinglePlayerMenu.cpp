#include "SinglePlayerMenu.h"

void SinglePlayerMenu::init()
{
	mainMenuTex = ImageLoder::loadPNG("Images/menu.png");
	//m_circleTex = ImageLoder::loadPNG("Images/circle.png");

	Game2D::Sprite normalSprite, hoverSprite, clickSprite, disabledSprite;
	Game2D::Rect tempRect = Game2D::Rect(15, -40, 10, 5);
	//Game2D::Rect tempTexRect;

	disabledSprite.setTextureCoords(Game2D::Rect(0.75f, 0.500f, 0.25f, 0.125f));
	normalSprite.setTextureCoords(Game2D::Rect(0.75f, 0.375f, 0.25f, 0.125f));
	hoverSprite.setTextureCoords(Game2D::Rect(0.75f, 0.250f, 0.25f, 0.125f));
	clickSprite.setTextureCoords(Game2D::Rect(0.75f, 0.125f, 0.25f, 0.125f));

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	disabledSprite.setColour(Game2D::Colour::White);
	normalSprite.setColour(Game2D::Colour::White);
	hoverSprite.setColour(Game2D::Colour::White);
	clickSprite.setColour(Game2D::Colour::White);

	backButton.setRect(tempRect);
	backButton.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	backButton.alignToDrawableObject();

	tempRect = Game2D::Rect(-15, -40, 10, 5);

	disabledSprite.setRect(tempRect);
	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	disabledSprite.setTextureCoords(Game2D::Rect(0.0f, 0.500f, 0.25f, 0.125f));
	normalSprite.setTextureCoords(Game2D::Rect(0.0f, 0.375f, 0.25f, 0.125f));
	hoverSprite.setTextureCoords(Game2D::Rect(0.0f, 0.250f, 0.25f, 0.125f));
	clickSprite.setTextureCoords(Game2D::Rect(0.0f, 0.125f, 0.25f, 0.125f));

	startButton.setRect(tempRect);
	startButton.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, disabledSprite);
	startButton.alignToDrawableObject();

	//-------------------------------
	tempRect = Game2D::Rect(1.25, -45, 2.5, 2.5);
	//tempTexRect = Game2D::Rect(0, 0, 0.125f, 0.125f);
	normalSprite.setTextureCoords(Game2D::Rect(0, 0, 0.125f, 0.125f));
	hoverSprite.setTextureCoords(Game2D::Rect(0.125f, 0, 0.125f, 0.125f));
	clickSprite.setTextureCoords(Game2D::Rect(0.250f, 0, 0.125f, 0.125f));

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	boardWidthPlus.setRect(tempRect);
	boardWidthPlus.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	boardWidthPlus.alignToDrawableObject();

	tempRect = Game2D::Rect(-37, -45, 2.5, 2.5);

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	playersPlus.setRect(tempRect);
	playersPlus.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	playersPlus.alignToDrawableObject();

	tempRect = Game2D::Rect(-1.25, -45, 2.5, 2.5);

	normalSprite.flipX();
	hoverSprite.flipX();
	clickSprite.flipX();

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	boardWidthMinus.setRect(tempRect);
	boardWidthMinus.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	boardWidthMinus.alignToDrawableObject();

	tempRect = Game2D::Rect(-39.5, -45, 2.5, 2.5);

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	playersMinus.setRect(tempRect);
	playersMinus.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	playersMinus.alignToDrawableObject();

	tempRect = Game2D::Rect(12, -40, 2.5, 2.5);

	normalSprite.rotate(90);
	hoverSprite.rotate(90);
	clickSprite.rotate(90);

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	boardHeightMinus.setRect(tempRect);
	boardHeightMinus.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	boardHeightMinus.alignToDrawableObject();

	tempRect = Game2D::Rect(12, -37.5, 2.5, 2.5);

	normalSprite.flipX();
	hoverSprite.flipX();
	clickSprite.flipX();

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	boardHeightPlus.setRect(tempRect);
	boardHeightPlus.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	boardHeightPlus.alignToDrawableObject();
	//-------------------------------
	//*/
	lineLength = 4;
	boardWidth = 7;
	boardHeight = 6;
	numPlayers = 2;

	resize();
}

void SinglePlayerMenu::resize()
{
	Game2D::ScreenCoord::alignCentre();

	noPlayers.fontSize = 3;
	noPlayers.text = "No. Players";
	noPlayers.width = freetype::getLength(Game2D::Font::getFont(noPlayers.fontSize), noPlayers.text.c_str());
	//freetype::print(Font::getFont(26), -10, -20, "Board size");
	boardDims.fontSize = 3;
	boardDims.text = "Board size";
	boardDims.width = freetype::getLength(Game2D::Font::getFont(boardDims.fontSize), boardDims.text.c_str());

	playerCount.fontSize = 4;
	playerCount.text = "%d";
	playerCount.width = freetype::getLength(Game2D::Font::getFont(playerCount.fontSize), playerCount.text.c_str(), numPlayers);

	boardDimLabels.fontSize = 4;
	boardDimLabels.text = "%d x %d";
	boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize), boardDimLabels.text.c_str(), boardWidth, boardHeight);
}

int SinglePlayerMenu::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState)
{
	if (playersPlus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		numPlayers++;
		playerCount.width = freetype::getLength(Game2D::Font::getFont(playerCount.fontSize), playerCount.text.c_str(), numPlayers);
		//std::cout << playerCount.width << "\n";
	}
	if (playersMinus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		if (--numPlayers < 2) {
			numPlayers = 2;
		}
		playerCount.width = freetype::getLength(Game2D::Font::getFont(playerCount.fontSize), playerCount.text.c_str(), numPlayers);
		//std::cout << playerCount.width << "\n";
	}
	if (boardWidthPlus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		boardWidth++;
		boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize), boardDimLabels.text.c_str(), boardWidth, boardHeight);
	}
	if (boardWidthMinus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		if (--boardWidth < lineLength) {
			boardWidth = lineLength;
		}
		boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize), boardDimLabels.text.c_str(), boardWidth, boardHeight);
	}
	if (boardHeightPlus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		boardHeight++;
		boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize), boardDimLabels.text.c_str(), boardWidth, boardHeight);
	}
	if (boardHeightMinus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		if (--boardHeight < lineLength) {
			boardHeight = lineLength;
		}
		boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize), boardDimLabels.text.c_str(), boardWidth, boardHeight);
	}
	//as the start button is aligned to the right of the screen the mouse coordinats need to be aligned right as well
	Game2D::Pos2 mousePosAlignedRight = Game2D::Pos2((mousePos.x - Game2D::ScreenCoord::getAspectRatio() * 50), mousePos.y);
	if (startButton.update(mousePosAlignedRight, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		return 4;
	}
	if (backButton.update(mousePosAlignedRight, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		return 3;
	}

	return 0;
}

void SinglePlayerMenu::draw() const
{
	glBindTexture(GL_TEXTURE_2D, mainMenuTex);
	playersPlus.draw();
	playersMinus.draw();
	boardHeightPlus.draw();
	boardHeightMinus.draw();
	boardWidthPlus.draw();
	boardWidthMinus.draw();

	Game2D::Colour::White.draw();
	freetype::print(Game2D::Font::getFont(playerCount.fontSize), (playerCount.width / -2.0f) - 38, -41, playerCount.text.c_str(), numPlayers);
	freetype::print(Game2D::Font::getFont(noPlayers.fontSize), (noPlayers.width / -2.0f) - 38, -35, noPlayers.text.c_str());
	freetype::print(Game2D::Font::getFont(boardDims.fontSize), (boardDims.width / -2.0f), -35, boardDims.text.c_str());
	freetype::print(Game2D::Font::getFont(boardDimLabels.fontSize), (boardDimLabels.width / -2.0f), -41, boardDimLabels.text.c_str(), boardWidth, boardHeight);
}