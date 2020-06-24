#ifndef BOARD_H
#define BOARD_H

#include <Pos2.h>
#include <Colour.h>
#include <DrawableObject.h>
#include <vector>

class Board
{
private:
	int width, height;
	int lineLength;
	int numPlayers;
	std::vector<Game2D::Colour> playerColours;

	std::vector<std::vector<int>> board;
public:
	inline void setBoardDims(int width, int height) { this->width = width; this->height = height; }
	inline void setLineLength(int length) { this->lineLength = length; }
	inline void setPlayerColours(std::vector<Game2D::Colour>& colours) { this->playerColours = colours; }

	void initBoard();

	bool insertPice(int x, int playerNum);

	bool checkBoard();
	bool checkLine(Game2D::Pos2 pos);
	bool checkRow(Game2D::Pos2 pos);
	bool checkDiag(Game2D::Pos2 pos);
	bool checkBackDiag(Game2D::Pos2 pos);

	void draw();
};


#endif //BOARD_H
