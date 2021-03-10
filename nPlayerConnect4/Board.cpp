#include "Board.h"

float Board::GetSegDim()
{
	float segWidth = ((100.0f * Game2D::ScreenCoord::getAspectRatio()) / width) - 2;
	float segHeight = (100.0f / height) - 2;

	//std::cout << segWidth << " x " << segHeight << "\n";

	return (segWidth < segHeight ? segWidth : segHeight);
}

Board::Board() {

}

void Board::setClickboxes()
{
	clickboxes.clear();

	float segDim = GetSegDim();

	float clickHeight = (segDim + 2) * height;
	for (float i = 0, x = (0 - ((segDim + 2) * (width - 1)) / 2.0f); i < width; i++, x+=(segDim +2)) {
		Game2D::ClickableObject temp;
		//std::cout << "Adding click object at:\t" << Game2D::Rect(x,0, segDim,((segDim + 2) * (height - 1)) + 2) << "\n";
		temp.setRect(Game2D::Rect(x,0, segDim,((segDim + 2) * (height))));
		clickboxes.push_back(temp);
		clickboxes.back().alignToDrawableObject();
	}
	//std::cout << clickboxes[0].getClickRegion().pos << "\n";
}

void Board::initBoard()
{
	circleTex = ImageLoder::loadPNG("Images/circle.png");
	circleSprite.setTextureCoords(Game2D::Rect(0, 0, 1, 1));
	highlightSprite.setTextureCoords(Game2D::Rect(0, 0, 1, 1));
	//std::cout << circleTex << "\n";
	board.clear();
	for(int i = 0; i < height; i++){
		std::vector<int> temp;
		for(int j = 0; j < width; j++){
			temp.push_back(-1);
		}
		board.push_back(temp);
	}

	currentPlayer = 0;//so it starts as player 1
	nextInsertPos = Game2D::Pos2(-1,-1);

	//board[0][0] = 0;
	//board[5][6] = 1;
}

int Board::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState, unsigned int& winningPlayer, int* x)
{
	bool newHighlight = false;
	int i = 0;
	for (auto& it : clickboxes) {
		if (it.update(mousePos, mouseState) == Game2D::ClickableObject::CLICK) {
			//if the user wants the x postion the piece was inserted in
			if(x) { *x = i; }
			return makeMove(i,currentPlayer,winningPlayer);
		}
		if(it.update(mousePos,mouseState) == Game2D::ClickableObject::HOVER){
			Game2D::Pos2 pos;
			if(insertPice(i,-1,pos)){
				newHighlight = true;
				nextInsertPos = pos;
			} else {
				nextInsertPos = Game2D::Pos2(-1,-1);
			}
		} else {
			//nextInsertPos = Game2D::Pos2(-1,-1);
		}
		//std::cout << nextInsertPos << "\n";

		i++;
	}
	if(!newHighlight){
		nextInsertPos = Game2D::Pos2(-1,-1);
	}

	return -2;
}

int Board::makeMove(int x, int playerNum, unsigned int& winningPlayer)
{
	Game2D::Pos2 pos;
	if (insertPice(x, currentPlayer, pos)) {
		//std::cout << "insert time\n";
		if (checkBoard(pos)) {
			winningPlayer = currentPlayer;
			return 1;
		} else if(boardFull()){
			return -1;
		} else {
			if (++currentPlayer >= numPlayers) {
				currentPlayer = 0;
			}
			return 0;
		}
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

bool Board::boardFull()
{
	for(int y = 0; y < height; y++)	{
		for(int x = 0; x < width; x++){
			if(board[x][y] == -1){
				return false;
			}
		}
	}

	return true;
}

void Board::draw()
{
	glBindTexture(GL_TEXTURE_2D, circleTex);

	float segDim = GetSegDim();

	//std::cout << segWidth << "\n";

	//Game2D::DrawableObject test;
	circleSprite.setRect(Game2D::Rect(0,0,segDim,segDim));
	circleSprite.setColour(Game2D::Colour::Black);

	highlightSprite.setRect(Game2D::Rect(0,0,segDim*1.1f,segDim*1.1f));
	highlightSprite.setColour(Game2D::Colour::White);

	float x = (0 - ((segDim + 2) * (width-1)) / 2.0f);// *ScreenCoord::getAspectRatio();
	//float x = -50 * ScreenCoord::getAspectRatio();
	float y = -50 + (segDim/2.0f)+2;

	for(int i = 0; i < width; i++){
		//y = -50 + (segDim / 2.0f) + 1;//old formula
		y = 0 - ((segDim+2) * ((height-1)/2.0));
		for(int j = 0; j < height; j++){
			if(board[j][i] != -1){
				circleSprite.setColour(playerColours[board[j][i]]);
			} else {
				circleSprite.setColour(Game2D::Colour::Black);
			}
			//std::cout << i << "," << j << " at " << x << "," << y << "\n";
			Game2D::Pos2 currentBoardPos(i,j);
			//std::cout << currentBoardPos << "\t" << nextInsertPos << "\n";
			if(currentBoardPos == nextInsertPos){
				//std::cout << "Drawing Highlight\n";
				highlightSprite.setPos(Game2D::Pos2(x,y));
				highlightSprite.setColour(playerColours[currentPlayer]);
				highlightSprite.draw();
			}

			circleSprite.setPos(Game2D::Pos2(x,y));
			circleSprite.draw();

			y += segDim + 2;
			//if ((y += segWidth + 2) > 50) { std::cout << y <<"\n"; y = -51 + (segWidth / 2.0f) + 2; }
		}
		x += segDim + 2;
		//if((x += segWidth + 2 ) > 50) { x = -50; }
	}
	Game2D::ScreenCoord::alignLeft();
	Game2D::Colour(1, 1, 1).draw();
	freetype::print(Game2D::Font::getFont(5), 1, 44, "Player %d's turn", currentPlayer + 1);
	Game2D::ScreenCoord::alignCentre();
	//test.setColour(Game2D::Colour(0, 1, 1, 0.5f));
	//std::cout << ((segHeight + 2) * (height-1)) << "\n";
	//test.setRect(Game2D::Rect(0, 0, segWidth, 2+(segHeight + 2) * (height - 1)));
	//test.setRect(clickboxes.begin()->getClickRegion());
	//std::cout << clickboxes.begin()->getClickRegion() << "\n";
	//test.draw();
}