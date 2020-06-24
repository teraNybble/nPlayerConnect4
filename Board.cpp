#include "Board.h"

void Board::initBoard()
{
	for(int i = 0; i < height; i++){
		std::vector<int> temp;
		for(int j = 0; j < width; j++){
			temp.push_back(-1);
		}
		board.push_back(temp);
	}

	//board[0][0] = 0;
	//board[5][6] = 0;
}

bool Board::insertPice(int x, int playerNum)
{
	for(int i = height - 1; i >=0; i--){
		
	}
}

bool Board::checkBoard()
{

}

bool Board::checkLine(Game2D::Pos2 pos)
{
	int previous = -2;
	int count = 0;

	for(int i = 1; i < width; i++){
		if(board[pos.y][i] == -1) {
			count = 0;
			continue;
		}
		if(board[pos.y][i] == board[pos.y][i-1]){
			count++;
			if(count >= lineLength){
				return true;
			}
		}
		else count = 0;
	}

	return false;
}

bool Board::checkRow(Game2D::Pos2 pos)
{
	int count = 0;

	for(int i = 1; i < width; i++){
		if(board[i][pos.x] == -1) {
			count = 0;
			continue;
		}
		if(board[i][pos.x] == board[i-1][pos.x]){
			count++;
			if(count >= lineLength){
				return true;
			}
		}
		else count = 0;
	}

	return false;
}

bool Board::checkDiag(Game2D::Pos2 pos)
{
	std::vector<int> line;

	for(int h = 0; h < height; h++){
		int w = pos.x - pos.y + h;

		if(0 <= w && w < width){
			line.push_back(board[h][w]);
		}
	}

	if(line.size() < 4)
		return false;

	int count = 0;

	for(int i = 1; i < line.size(); i++){
		if(line[i] == -1){
			count = 0;
			continue;
		}
		if(line[i] == line[i-1]){
			count++;
			if(count >= lineLength){
				return true;
			}
		}
		else count = 0;
	}
}

bool Board::checkBackDiag(Game2D::Pos2 pos)
{
	std::vector<int> line;

	for(int h = 0; h < height; h++){
		int w = pos.x + pos.y - h;

		if(0 <= w && w < width){
			line.push_back(board[h][w]);
		}
	}

	if(line.size() < 4)
		return false;

	int count = 0;

	for(int i = 1; i < line.size(); i++){
		if(line[i] == -1){
			count = 0;
			continue;
		}
		if(line[i] == line[i-1]){
			count++;
			if(count >= lineLength){
				return true;
			}
		}
		else count = 0;
	}
}

void Board::draw()
{
	float segWidth = 100.0f/width;
	float segHeight = 100.0f/height;

	float segDim = (segWidth < segHeight ? segWidth : segHeight);

	//std::cout << segWidth << "\n";

	Game2D::DrawableObject test;
	test.setRect(Game2D::Rect(0,0,segDim,segDim));
	test.setColour(Game2D::Colour::Black);
	//test.draw();
/*
	for(int x = -50; x < 50; x+= segDim+2){
		for(int y = -50; y < 50; y+=segDim+2) {
			test.setPos(Game2D::Pos2(x, y));
			test.draw();
		}
	}*/

	float x = -50;
	float y = -50 + (segWidth/2.0f)+2;

	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			if(board[j][i] != -1){
				test.setColour(Game2D::Colour::Red);
			} else {
				test.setColour(Game2D::Colour::Black);
			}
			test.setPos(Game2D::Pos2(x,y));
			test.draw();

			if((y += segWidth + 2) > 50) { y = -50 + (segWidth/2.0f)+2; }
		}
		if((x += segWidth + 2 ) > 50) { x = -50; }
	}
}