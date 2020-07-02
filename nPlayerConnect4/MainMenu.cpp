#include "MainMenu.h"

void MainMenu::init()
{
	//load the texture
	mainMenuTex = ImageLoder::loadPNG("Images/menu.png");
	//set the sprites colour
	arrow.setColour(Game2D::Colour::White);
	arrowHover.setColour(Game2D::Colour::White);
	arrowClick.setColour(Game2D::Colour::White);
	//set the texture coords
	arrow.setTextureCoords(Game2D::Rect(0, 0, 0.25f, 0.25f));
	arrowHover.setTextureCoords(Game2D::Rect(0.25f, 0, 0.25f, 0.25f));
	arrowClick.setTextureCoords(Game2D::Rect(0.50f, 0, 0.25f, 0.25f));

	//set the sprites sizes an positions
	arrow.setRect(Game2D::Rect(-35, -40, 5, 5));
	arrowHover.setRect(Game2D::Rect(-35, -40, 5, 5));
	arrowClick.setRect(Game2D::Rect(-35, -40, 5, 5));

	playersPlus.setRect(Game2D::Rect(-35,-40,5,5));
	playersPlus.addStateSprites(arrow,arrowHover,arrowClick,arrowClick,arrow);
	playersPlus.alignToDrawableObject();

	arrow.setPos(Game2D::Pos2(1, -40));
	arrowHover.setPos(Game2D::Pos2(1, -40));
	arrowClick.setPos(Game2D::Pos2(1, -40));

	boardWidthPlus.setRect(Game2D::Rect(1, -40, 5, 5));
	boardWidthPlus.addStateSprites(arrow, arrowHover, arrowClick, arrowClick, arrow);
	boardWidthPlus.alignToDrawableObject();

	arrow.setPos(Game2D::Pos2(-41, -40));
	arrowHover.setPos(Game2D::Pos2(-41, -40));
	arrowClick.setPos(Game2D::Pos2(-41, -40));
	
	arrow.flipX();
	arrowHover.flipX();
	arrowClick.flipX();

	playersMinus.setRect(Game2D::Rect(-41, -40, 5, 5));
	playersMinus.addStateSprites(arrow, arrowHover, arrowClick, arrowClick, arrow);
	playersMinus.alignToDrawableObject();

	arrow.setPos(Game2D::Pos2(-5, -40));
	arrowHover.setPos(Game2D::Pos2(-5, -40));
	arrowClick.setPos(Game2D::Pos2(-5, -40));

	boardWidthMinus.setRect(Game2D::Rect(-5, -40, 5, 5));
	boardWidthMinus.addStateSprites(arrow, arrowHover, arrowClick, arrowClick, arrow);
	boardWidthMinus.alignToDrawableObject();

	arrow.rotate(90);
	arrowHover.rotate(90);
	arrowClick.rotate(90);

	arrow.setPos(Game2D::Pos2(12, -34));
	arrowHover.setPos(Game2D::Pos2(12, -34));
	arrowClick.setPos(Game2D::Pos2(12, -34));

	boardHeightMinus.setRect(Game2D::Rect(12, -34, 5, 5));
	boardHeightMinus.addStateSprites(arrow, arrowHover, arrowClick, arrowClick, arrow);
	boardHeightMinus.alignToDrawableObject();

	arrow.setPos(Game2D::Pos2(12, -28));
	arrowHover.setPos(Game2D::Pos2(12, -28));
	arrowClick.setPos(Game2D::Pos2(12, -28));

	arrow.flipX();
	arrowHover.flipX();
	arrowClick.flipX();

	boardHeightPlus.setRect(Game2D::Rect(12, -28, 5, 5));
	boardHeightPlus.addStateSprites(arrow, arrowHover, arrowClick, arrowClick, arrow);
	boardHeightPlus.alignToDrawableObject();

	numPlayers = 2;

	
	startSprite.setTextureCoords(Game2D::Rect(0, 0.75f, 0.50f, 0.25f));
	startHover.setTextureCoords(Game2D::Rect(0, 0.50f, 0.50f, 0.25f));
	startClick.setTextureCoords(Game2D::Rect(0, 0.25f, 0.50f, 0.25f));

	startSprite.setRect(Game2D::Rect(-15, -40, 20, 10));
	startHover.setRect(Game2D::Rect(-15, -40, 20, 10));
	startClick.setRect(Game2D::Rect(-15, -40, 20, 10));

	startSprite.setColour(Game2D::Colour::White);
	startHover.setColour(Game2D::Colour::White);
	startClick.setColour(Game2D::Colour::White);

	start.setRect(Game2D::Rect(-15, -40, 20, 10));
	start.addStateSprites(startSprite,startHover,startClick,startClick,startSprite);
	start.alignToDrawableObject();
	
	//font.init("C:/Windows/Fonts/arial.ttf", 36);
	lineLength = 4;
	boardWidth = 7;
	boardHeight = 6;
}

void MainMenu::update()
{
}

int MainMenu::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState)
{
	if(playersPlus.update(mousePos,mouseState,1) == Game2D::ClickableObject::ClickState::CLICK){
		numPlayers++;
	}
	if(playersMinus.update(mousePos,mouseState,1) == Game2D::ClickableObject::ClickState::CLICK) {
		if(--numPlayers < 2){
			numPlayers = 2;
		}
	}
	if (boardWidthPlus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		boardWidth++;
	}
	if (boardWidthMinus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		if (--boardWidth < lineLength) {
			boardWidth = lineLength;
		}
	}
	if (boardHeightPlus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		boardHeight++;
	}
	if (boardHeightMinus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		if (--boardHeight < lineLength) {
			boardHeight = lineLength;
		}
	}
	//as the start button is aligned to the right of the screen the mouse coordinats need to be aligned right as well
	Game2D::Pos2 mousePosAlignedRight = Game2D::Pos2((mousePos.x - ScreenCoord::getAspectRatio() * 50), mousePos.y);
	if (start.update(mousePosAlignedRight, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		return 1;
	}

	return 0;
}

void MainMenu::draw()
{
	glBindTexture(GL_TEXTURE_2D, mainMenuTex);
	//std::cout << "drawing\n";
	Game2D::Colour(1, 1, 1).draw();
	playersMinus.draw();
	playersPlus.draw();
	
	boardWidthPlus.draw();
	boardWidthMinus.draw();
	boardHeightPlus.draw();
	boardHeightMinus.draw();
	
	ScreenCoord::alignRight();
	start.draw();


	ScreenCoord::alignCentre();

	Game2D::Colour(0, 0, 0).draw();
	freetype::print(Font::getFont(36), -40, -35, "%d", numPlayers);
	freetype::print(Font::getFont(26), -8, -33.5, "%d x %d", boardWidth,boardHeight);
	freetype::print(Font::getFont(26), -50, -20, "No. Players");
	freetype::print(Font::getFont(26), -10, -20, "Board size");
	freetype::print(Font::getFont(40), -30, 25, "N player connect 4");
}