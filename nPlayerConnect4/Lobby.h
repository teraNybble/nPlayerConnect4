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


//TODO add a join button texture and a back button texture
//TODO add single player
//TODO add ability to change if from connect4 to connectx
//TODO add quit button to main menu
//TODO add pause menu to multiplayer
//TODO show player number over piece on board for colourblind people
//TODO reduce CPU load (make server wait for messages)

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

	unsigned int boardWidth;
	Game2D::Button boardWidthPlus;
	Game2D::Button boardWidthMinus;
	unsigned int boardHeight;
	Game2D::Button boardHeightPlus;
	Game2D::Button boardHeightMinus;

	unsigned int lineLength;

	TextInfo boardDims;
	TextInfo boardDimLabels;
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
	inline Game2D::Colour getColour() const {
		return Game2D::Colour(redSlider.getValue(),greenSlider.getValue(),blueSlider.getValue());
	}
	inline void setColour(Game2D::Colour colour){
		redSlider.setValue(colour.getR());
		greenSlider.setValue(colour.getG());
		blueSlider.setValue(colour.getB());
	}

	inline uint32_t getBoardWidth() const { return boardWidth; }
	inline uint32_t getBoardHeight() const { return boardHeight; }
	inline void setBoardWidth(unsigned int width) { boardWidth = width; }
	inline void setBoardHeight(unsigned int height) { boardHeight = height; }

	//set to -1 for a tie
	void setWinningPlayer(int playerNo) { winningPlayer = playerNo; }

	void draw();
};


#endif //LOBBY_H
