#ifndef BOARD_H
#define BOARD_H

#include <Pos2.h>
#include <Colour.h>
#include <DrawableObject.h>
#include <vector>
#include <ClickableObject.h>

class Board
{
private:
	int width, height;
	int lineLength;
	unsigned int numPlayers;
	std::vector<Game2D::Colour> playerColours;

	std::vector<std::vector<int>> board;

	std::vector<Game2D::ClickableObject> clickboxes;
	void setClickboxes();

	unsigned int currentPlayer;
public:
	inline void setBoardDims(int width, int height) { this->width = width; this->height = height; setClickboxes(); }
	inline void setLineLength(int length) { this->lineLength = length; }
	inline void setPlayerColours(std::vector<Game2D::Colour>& colours) { this->playerColours = colours; }
	inline void setNumPlayers(unsigned int num) { this->numPlayers = num; }

	void initBoard();

	int processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState);

	bool insertPice(int x, int playerNum, Game2D::Pos2& insertPos);

	bool checkBoard(Game2D::Pos2 pos);
	bool checkLine(Game2D::Pos2 pos);
	bool checkRow(Game2D::Pos2 pos);
	bool checkDiag(Game2D::Pos2 pos);
	bool checkBackDiag(Game2D::Pos2 pos);

	void draw();
};


#endif //BOARD_H
