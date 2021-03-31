#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <Button.h>
#include <Fonts.h>
#include "TextureManager.h"

class PauseMenu
{
private:
	Game2D::Button resume;
	Game2D::Button back;
	Game2D::Button options;
	Game2D::Button quit;
public:
	void init();

	void resize();

	int processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState);

	inline void setLobbyEnabled(bool enabled) { (enabled ? back.enable() : back.disable()); }

	void draw() const;
};


#endif //PAUSEMENU_H
