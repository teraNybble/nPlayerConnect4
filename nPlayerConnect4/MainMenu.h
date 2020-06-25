#ifndef MAINMENU_H
#define MAINMENU_H

#include <Button.h>

class MainMenu
{
private:
	Game2D::Button playersPlus;
	Game2D::Button playersMinus;
	unsigned int numPlayers;

	Game2D::Button start;
public:
	void init();

	void update();
	int processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState);

	inline unsigned int getNumPlayers() { return numPlayers; }

	void draw();
};


#endif //MAINMENU_H
