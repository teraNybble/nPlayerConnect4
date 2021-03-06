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
#include <Timer.h>
#include <functional>

//TODO V1.0.0
//TODO V1.1.0
//TODO add ban functionality
//TODO add fall back font and location?
//TODO add chess clock feature
//TODO V1.2.0
//TODO add ability to spectate online

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
	Game2D::Button kickButton;

	std::map<int,Game2D::Colour> playerList;

	bool isHost;
	int winningPlayer;

	Game2D::Slider redSlider;
	Game2D::Slider greenSlider;
	Game2D::Slider blueSlider;
	float alpha;
	Game2D::Sprite exampleColour;

	unsigned int boardWidth;
	Game2D::Button boardWidthPlus;
	Game2D::Button boardWidthMinus;
	unsigned int boardHeight;
	Game2D::Button boardHeightPlus;
	Game2D::Button boardHeightMinus;

	unsigned int lineLength;
	Game2D::Button lineLengthPlus;
	Game2D::Button lineLengthMinus;

	TextInfo boardDims;
	TextInfo boardDimLabels;

	TextInfo connectLength;
	TextInfo connectLengthLabels;

	Game2D::Timer timer;
	int delayTime;//ms
	int delayCount;//ms
	bool arrowDown;

	std::vector<Game2D::Button*> arrowButtons;
	std::vector<std::function<void()>> arrowFuncs;
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
		return Game2D::Colour(redSlider.getValue(),greenSlider.getValue(),blueSlider.getValue(),alpha);
	}
	inline void setColour(Game2D::Colour colour){
		redSlider.setValue(colour.getR());
		greenSlider.setValue(colour.getG());
		blueSlider.setValue(colour.getB());
		alpha = colour.getA();
	}

	inline uint32_t getConnectLength() const {return lineLength; }
	inline uint32_t getBoardWidth() const { return boardWidth; }
	inline uint32_t getBoardHeight() const { return boardHeight; }
	inline void setConnectLength(unsigned int length) {
		lineLength = length;
		connectLengthLabels.width = Game2D::Freetype::getLength(Game2D::Font::getFont(connectLengthLabels.fontSize), connectLengthLabels.text.c_str(), lineLength);

	}
	inline void setBoardWidth(unsigned int width) {
		boardWidth = width;
		boardDimLabels.width = Game2D::Freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
												   boardDimLabels.text.c_str(), boardWidth, boardHeight);

	}
	inline void setBoardHeight(unsigned int height) {
		boardHeight = height;
		boardDimLabels.width = Game2D::Freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
												   boardDimLabels.text.c_str(), boardWidth, boardHeight);

	}

	//set to -1 for a tie
	void setWinningPlayer(int playerNo) { winningPlayer = playerNo; }

	void draw();
};


#endif //LOBBY_H