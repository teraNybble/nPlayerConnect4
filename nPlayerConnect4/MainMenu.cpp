#include "MainMenu.h"

void MainMenu::init()
{
	//
	Game2D::Sprite r;
	r.setColour(Game2D::Colour::Red);
	r.setRect(Game2D::Rect(-35,-40,5,5));
	Game2D::Sprite g;
	g.setColour(Game2D::Colour::Green);
	g.setRect(Game2D::Rect(-35,-40,5,5));
	Game2D::Sprite b;
	b.setColour(Game2D::Colour::Blue);
	b.setRect(Game2D::Rect(-35,-40,5,5));

	playersPlus.setRect(Game2D::Rect(-35,-40,5,5));
	playersPlus.addStateSprites(r,g,b,b,r);
	playersPlus.setFrameTime(1);
	playersPlus.alignToDrawableObject();

	r.setPos(Game2D::Pos2(-41,-40));
	g.setPos(Game2D::Pos2(-41,-40));
	b.setPos(Game2D::Pos2(-41,-40));
	playersMinus.setRect(Game2D::Rect(-41,-40,5,5));
	playersMinus.addStateSprites(r,g,b,b,r);
	playersMinus.setFrameTime(1);
	playersMinus.alignToDrawableObject();

	numPlayers = 2;

	r.setPos(Game2D::Pos2(-5, -40));
	g.setPos(Game2D::Pos2(-5, -40));
	b.setPos(Game2D::Pos2(-5, -40));
	boardWidthMinus.setRect(Game2D::Rect(-5, -40, 5, 5));
	boardWidthMinus.addStateSprites(r, g, b, b, r);
	boardWidthMinus.alignToDrawableObject();

	r.setPos(Game2D::Pos2(1, -40));
	g.setPos(Game2D::Pos2(1, -40));
	b.setPos(Game2D::Pos2(1, -40));
	boardWidthPlus.setRect(Game2D::Rect(1, -40, 5, 5));
	boardWidthPlus.addStateSprites(r, g, b, b, r);
	boardWidthPlus.alignToDrawableObject();

	r.setPos(Game2D::Pos2(12, -34));
	g.setPos(Game2D::Pos2(12, -34));
	b.setPos(Game2D::Pos2(12, -34));
	boardHeightMinus.setRect(Game2D::Rect(12, -34, 5, 5));
	boardHeightMinus.addStateSprites(r, g, b, b, r);
	boardHeightMinus.alignToDrawableObject();

	r.setPos(Game2D::Pos2(12, -28));
	g.setPos(Game2D::Pos2(12, -28));
	b.setPos(Game2D::Pos2(12, -28));
	boardHeightPlus.setRect(Game2D::Rect(12, -28, 5, 5));
	boardHeightPlus.addStateSprites(r, g, b, b, r);
	boardHeightPlus.alignToDrawableObject();

	r.setRect(Game2D::Rect(55, -40,10,5));
	g.setRect(Game2D::Rect(55, -40, 10, 5));
	b.setRect(Game2D::Rect(55, -40, 10, 5));
	start.setRect(Game2D::Rect(55, -40, 10, 5));
	start.addStateSprites(r,g,b,b,r);
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
	if (start.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		return 1;
	}

	return 0;
}

void MainMenu::draw()
{
	//std::cout << "drawing\n";
	playersPlus.draw();
	playersMinus.draw();
	boardWidthPlus.draw();
	boardWidthMinus.draw();
	boardHeightPlus.draw();
	boardHeightMinus.draw();
	start.draw();
	Game2D::Colour(0, 0, 0).draw();
	freetype::print(Font::getFont(36), -40, -35, "%d", numPlayers);
	freetype::print(Font::getFont(26), -8, -33.5, "%d x %d", boardWidth,boardHeight);
}