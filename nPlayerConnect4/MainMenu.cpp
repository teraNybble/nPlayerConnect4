#include "MainMenu.h"

void MainMenu::init()
{
	//
	Game2D::Sprite r;
	r.setColour(Game2D::Colour::Red);
	r.setRect(Game2D::Rect(-35,-40,10,10));
	Game2D::Sprite g;
	g.setColour(Game2D::Colour::Green);
	g.setRect(Game2D::Rect(-35,-40,10,10));
	Game2D::Sprite b;
	b.setColour(Game2D::Colour::Blue);
	b.setRect(Game2D::Rect(-35,-40,10,10));

	playersPlus.setRect(Game2D::Rect(-35,-40,10,10));
	playersPlus.addStateSprites(r,g,b,b,r);
	playersPlus.setFrameTime(1);
	playersPlus.alignToDrawableObject();

	r.setPos(Game2D::Pos2(-46,-40));
	g.setPos(Game2D::Pos2(-46,-40));
	b.setPos(Game2D::Pos2(-46,-40));
	playersMinus.setRect(Game2D::Rect(-46,-40,10,10));
	playersMinus.addStateSprites(r,g,b,b,r);
	playersMinus.setFrameTime(1);
	playersMinus.alignToDrawableObject();

	numPlayers = 2;

	r.setPos(Game2D::Pos2(35, -40));
	g.setPos(Game2D::Pos2(35, -40));
	b.setPos(Game2D::Pos2(35, -40));
	start.setRect(Game2D::Rect(35, -40, 10, 10));
	start.addStateSprites(r,g,b,b,r);
	start.alignToDrawableObject();
}

void MainMenu::update()
{
}

int MainMenu::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState)
{
	//std::cout << "processing mouse\n";
	//std::cout << mousePos << "\n";
	//std::cout << mouseState << "\n";
	if(playersPlus.update(mousePos,mouseState,1) == Game2D::ClickableObject::ClickState::CLICK){
		//std::cout << "update\n";
		//std::cout << "plus\n";
		numPlayers++;
		std::cout << numPlayers << "\n";
	}
	if(playersMinus.update(mousePos,mouseState,1) == Game2D::ClickableObject::ClickState::CLICK) {
		if(--numPlayers < 2){
			numPlayers = 2;
		}
		std::cout << numPlayers << "\n";
	}
	//std::cout << numPlayers << "\n";
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
	start.draw();
}