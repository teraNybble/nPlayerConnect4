#include "Board.h"

Board::Board() {
	
}

void Board::setClickboxes()
{
	clickboxes.clear();
	float segWidth = 100.0f / width;
	float segHeight = 100.0f / height;


	float clickHeight = (segHeight + 2) * height;
	for (float i = 0, x = -50; i < width; i++, x+=(segWidth+2)) {
		Game2D::ClickableObject temp;
		temp.setRect(Game2D::Rect(x,0,segWidth,((segHeight + 2) * (height - 1)) + 2));
		clickboxes.push_back(temp);
		clickboxes.back().alignToDrawableObject();
	}
	//std::cout << clickboxes[0].getClickRegion().pos << "\n";
}

void Board::initBoard()
{
	circleTex = ImageLoder::loadPNG("Images/circle.png");
	circleSprite.setTextureCoords(Game2D::Rect(0, 0, 1, 1));
	//std::cout << circleTex << "\n";
	board.clear();
	for(int i = 0; i < height; i++){
		std::vector<int> temp;
		for(int j = 0; j < width; j++){
			temp.push_back(-1);
		}
		board.push_back(temp);
	}

	//board[0][0] = 0;
	//board[5][6] = 1;
}

int Board::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState, unsigned int& winningPlayer)
{
	int i = 0;
	for (auto& it : clickboxes) {
		if (it.update(mousePos, mouseState) == Game2D::ClickableObject::CLICK) {
			//get its id
			//std::cout << "it clicked\n";
			Game2D::Pos2 pos;
			if (insertPice(i, currentPlayer, pos)) {
				//std::cout << "insert time\n";
				if (checkBoard(pos)) {
					winningPlayer = currentPlayer;
					return 1; 
				}
				else {
					if (++currentPlayer >= numPlayers) {
						currentPlayer = 0;
					}
					return 0;
				}
			}
		}

		i++;
	}

	return 0;
}

bool Board::insertPice(int x, int playerNum,Game2D::Pos2& insertPos)
{
	for(int i = height - 1; i >=0; i--){
		if (board[i][x] != -1) {
			if (i == height - 1) {
				return false;
			}
			board[i + 1][x] = playerNum;
			insertPos.x = x;
			insertPos.y = i + 1;
			return true;
		}
		if (i == 0) {
			board[i][x] = playerNum;
			insertPos.x = x;
			insertPos.y = i;
			return true;
		}
	}

	return false;
}

bool Board::checkBoard(Game2D::Pos2 pos)
{
	return (checkLine(pos) || checkRow(pos) || checkDiag(pos) || checkBackDiag(pos));
	bool temp = (checkLine(pos) || checkRow(pos) || checkDiag(pos) || checkBackDiag(pos));
	std::cout << (temp ? "true" : "false") << std::endl;
	return temp;
}

bool Board::checkLine(Game2D::Pos2 pos)
{
	//int previous = -2;
	int count = 1;

	for(int i = 1; i < width; i++){
		if(board[pos.y][i] == -1) {
			count = 1;
			continue;
		}
		if(board[pos.y][i] == board[pos.y][i-1]){
			count++;
			if(count >= lineLength){
				//std::cout << "Line\ttrue" << std::endl;
				return true;
			}
		}
		else count = 1;
	}

	//std::cout << "Line\tfalse" << std::endl;
	return false;
}

bool Board::checkRow(Game2D::Pos2 pos)
{
	int count = 1;

	for(int i = 1; i < height; i++){
		//std::cout << i << std::endl;
		if(board[i][pos.x] == -1) {
			count = 1;
			continue;
		}
		if(board[i][pos.x] == board[i-1][pos.x]){
			count++;
			//std::cout << count << "\n";
			if(count >= lineLength){
				//std::cout << "Row\ttrue" << std::endl;
				return true;
			}
		}
		else count = 1;
	}

	//std::cout << "Row\tfalse" << std::endl;
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

	int count = 1;

	for(int i = 1; i < line.size(); i++){
		if(line[i] == -1){
			count = 1;
			continue;
		}
		if(line[i] == line[i-1]){
			count++;
			if(count >= lineLength){
				//std::cout << "Diag\ttrue" << std::endl;
				return true;
			}
		}
		else count = 1;
	}

	//std::cout << "Diag\tfalse" << std::endl;
	return false;
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

	int count = 1;

	for(int i = 1; i < line.size(); i++){
		if(line[i] == -1){
			count = 1;
			continue;
		}
		if(line[i] == line[i-1]){
			count++;
			if(count >= lineLength){
				//std::cout << "BackDiag\ttrue" << std::endl;
				return true;
			}
		}
		else count = 1;
	}

	//std::cout << "backDiag\tfalse" << std::endl;
	return false;
}

void Board::draw()
{
	glBindTexture(GL_TEXTURE_2D, circleTex);

	float segWidth = 100.0f/width;
	float segHeight = 100.0f/height;

	float segDim = (segWidth < segHeight ? segWidth : segHeight);

	//std::cout << segWidth << "\n";

	//Game2D::DrawableObject test;
	circleSprite.setRect(Game2D::Rect(0,0,segDim,segDim));
	circleSprite.setColour(Game2D::Colour::Black);
	//std::cout << (circleSprite.textureLoaded() ? "True\n" : "False\n");
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
				circleSprite.setColour(playerColours[board[j][i]]);
			} else {
				circleSprite.setColour(Game2D::Colour::Black);
			}
			circleSprite.setPos(Game2D::Pos2(x,y));
			circleSprite.draw();

			if((y += segWidth + 2) > 50) { y = -50 + (segWidth/2.0f)+2; }
		}
		if((x += segWidth + 2 ) > 50) { x = -50; }
	}
	ScreenCoord::alignLeft();
	Game2D::Colour(1, 1, 1).draw();
	freetype::print(Font::getFont(26), 0, 45, "Player %d's turn", currentPlayer + 1);
	ScreenCoord::alignCentre();
	//test.setColour(Game2D::Colour(0, 1, 1, 0.5f));
	//std::cout << ((segHeight + 2) * (height-1)) << "\n";
	//test.setRect(Game2D::Rect(0, 0, segWidth, 2+(segHeight + 2) * (height - 1)));
	//test.setRect(clickboxes.begin()->getClickRegion());
	//std::cout << clickboxes.begin()->getClickRegion() << "\n";
	//test.draw();
}