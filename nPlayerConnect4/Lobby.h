#ifndef LOBBY_H
#define LOBBY_H

#include <freetype.h>
#include <Button.h>
#include "Fonts.h"
#include "ImageLoder.h"
#include "ScreenCoord.h"
#include "FontInfo.h"
#include <map>
#include <Slider.h>

class Lobby
{
private:
	GLuint m_menuTex;
	GLuint m_circleTex;

	TextInfo connectText;
	TextInfo hostText;

	Game2D::Button backButton;
	Game2D::Button colourAccept;
	Game2D::Button startButton;

	std::map<int,Game2D::Colour> playerList;

	bool isHost;
	int winningPlayer;

	Game2D::Slider redSlider;
	Game2D::Slider greenSlider;
	Game2D::Slider blueSlider;
	Game2D::Sprite exampleColour;

protected:
public:
	void init();

	inline void reset() {
		playerList.clear();
	}

	void resize();

	void update();
	int processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState);

	inline void setHost(bool host = false) { isHost = host; }

	void setPlayerColour(int id, Game2D::Colour colour);
	void removePlayer(int id);
	Game2D::Colour getColour() const {
		return Game2D::Colour(redSlider.getValue(),greenSlider.getValue(),blueSlider.getValue());
	}

	//set to -1 for a tie
	void setWinningPlayer(int playerNo) { winningPlayer = playerNo; }

	void draw();
};


#endif //LOBBY_H
