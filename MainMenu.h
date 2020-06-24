#ifndef MAINMENU_H
#define MAINMENU_H

#include <Button.h>

class MainMenu
{
private:
	Game2D::Button playersPlus;
	Game2D::Button playersMinus;
	int numPlayers;
public:
	void init();

	void update();
	void processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState);

	void draw();
};


#endif //MAINMENU_H
