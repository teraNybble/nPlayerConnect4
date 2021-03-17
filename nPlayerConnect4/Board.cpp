#include "Board.h"
#include "TextureManager.h"

float Board::GetSegDim()
{
	float segWidth = ((100.0f * Game2D::ScreenCoord::getAspectRatio()) / width);
	float segHeight = (100.0f / height);

	return (segWidth < segHeight ? segWidth : segHeight);
}

Board::Board() {

}

Board::~Board() 
{
	board.clear();
	clickboxes.clear();
}

void Board::setClickboxes()
{
	clickboxes.clear();

	float segDim = GetSegDim();

	float clickHeight = (segDim + 2) * height;
	for (float i = 0, x = (0 - ((segDim) * (width - 1)) / 2.0f); i < width; i++, x+=(segDim)) {
		Game2D::ClickableObject temp;
		temp.setRect(Game2D::Rect(x,0, segDim,((segDim) * (height))));
		clickboxes.push_back(temp);
		clickboxes.back().alignToDrawableObject();
	}

	float projectionMatMine[4][4];
	glGetFloatv(GL_PROJECTION_MATRIX, &projectionMatMine[0][0]);
	glPushAttrib(GL_TRANSFORM_BIT);
	GLint	viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(viewport[0], viewport[2], viewport[1], viewport[3], 0, 100);
	glPopAttrib();

	float projectionMatScreen[4][4];
	glGetFloatv(GL_PROJECTION_MATRIX, &projectionMatScreen[0][0]);

	float temp = (segDim/1.5F)*0.9;
	temp = (((temp * projectionMatMine[1][1]) + projectionMatMine[3][1]) / projectionMatScreen[1][1]);
	playerNoFont.init(_SysFont, temp);
}

void Board::initBoard()
{
	circleTex = TextureManager::getText(1);
	circleSprite.setTextureCoords(Game2D::Rect(0, 0, 1, 1));
	highlightSprite.setTextureCoords(Game2D::Rect(0, 0, 1, 1));
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
		}

		i++;
	}
	if(!newHighlight){
		nextInsertPos = Game2D::Pos2(-1,-1);
	}

	return -2;
}

void Board::resize()
{
	float projectionMatMine[4][4];
	glGetFloatv(GL_PROJECTION_MATRIX, &projectionMatMine[0][0]);
	glPushAttrib(GL_TRANSFORM_BIT);
	GLint	viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(viewport[0], viewport[2], viewport[1], viewport[3], 0, 100);
	glPopAttrib();

	float projectionMatScreen[4][4];
	glGetFloatv(GL_PROJECTION_MATRIX, &projectionMatScreen[0][0]);

	float temp = (GetSegDim()/1.5F)*0.9;
	temp = (((temp * projectionMatMine[1][1]) + projectionMatMine[3][1]) / projectionMatScreen[1][1]);
	playerNoFont.init(_SysFont, temp);
}

int Board::makeMove(int x, int playerNum, unsigned int& winningPlayer)
{
	Game2D::Pos2 pos;
	if (insertPice(x, currentPlayer, pos)) {
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
	if (lineLength < 2) { return true; }
	return (checkLine(pos) || checkRow(pos) || checkDiag(pos) || checkBackDiag(pos));
}

bool Board::checkLine(Game2D::Pos2 pos)
{
	int count = 1;

	for(int i = 1; i < width; i++){
		if(board[pos.y][i] == -1) {
			count = 1;
			continue;
		}
		if(board[pos.y][i] == board[pos.y][i-1]){
			count++;
			if(count >= lineLength){
				return true;
			}
		}
		else count = 1;
	}

	return false;
}

bool Board::checkRow(Game2D::Pos2 pos)
{
	int count = 1;

	for(int i = 1; i < height; i++){
		if(board[i][pos.x] == -1) {
			count = 1;
			continue;
		}
		if(board[i][pos.x] == board[i-1][pos.x]){
			count++;
			if(count >= lineLength){
				return true;
			}
		}
		else count = 1;
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

	int count = 1;

	for(int i = 1; i < line.size(); i++){
		if(line[i] == -1){
			count = 1;
			continue;
		}
		if(line[i] == line[i-1]){
			count++;
			if(count >= lineLength){
				return true;
			}
		}
		else count = 1;
	}

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
				return true;
			}
		}
		else count = 1;
	}

	return false;
}

bool Board::boardFull()
{
	for(int y = 0; y < height; y++)	{
		for(int x = 0; x < width; x++){
			if(board[y][x] == -1){
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

	circleSprite.setRect(Game2D::Rect(0,0,segDim*0.9f,segDim*0.9f));
	circleSprite.setColour(Game2D::Colour::Black);

	highlightSprite.setRect(Game2D::Rect(0,0,(segDim*0.9f)*1.1f,(segDim*0.9f)*1.1f));
	highlightSprite.setColour(Game2D::Colour::White);

	float x = (0 - ((segDim) * (width-1)) / 2.0f);
	float y = -50 + (segDim/2.0f)+2;

	for(int i = 0; i < width; i++){
		y = 0 - ((segDim) * ((height-1)/2.0));
		for(int j = 0; j < height; j++){
			if(board[j][i] != -1){
				circleSprite.setColour(playerColours[board[j][i]]);
			} else {
				circleSprite.setColour(Game2D::Colour::Black);
			}
			Game2D::Pos2 currentBoardPos(i,j);
			if(currentBoardPos == nextInsertPos){
				highlightSprite.setPos(Game2D::Pos2(x,y));
				highlightSprite.setColour(playerColours[currentPlayer]);
				highlightSprite.draw();
			}

			circleSprite.setPos(Game2D::Pos2(x,y));
			circleSprite.draw();

			y += segDim;// + 2;
		}
		x += segDim; //+ 2;
	}
	if(Options::showPlayerNums){
		x = (0 - ((segDim) * (width-1)) / 2.0f);
		float fontHight = (segDim/1.5f)*0.9f;
		for(int i = 0; i < width; i++){
			y = 0 - ((segDim) * ((height-1)/2.0));
			for(int j = 0; j < height; j++){
				if(board[j][i] != -1){
					float fontWidth = Game2D::Freetype::getLength(playerNoFont,"%d",board[j][i]+1);
					Game2D::Colour tempColour;
					if(board[j][i] < playerColours.size()){
						tempColour = playerColours[board[j][i]];
					} else {
						tempColour = Game2D::Colour::Black;
					}

					if(tempColour.getR()+tempColour.getG()+tempColour.getB() < 1.0){
						Game2D::Colour::White.draw();
					} else {
						Game2D::Colour::Black.draw();
					}
					Game2D::Freetype::print(playerNoFont,x-(fontWidth/2.0f),y-(fontHight/2.0f),"%d",board[j][i]+1);
				}
				y += segDim;
			}
			x += segDim;
		}
	}
	Game2D::ScreenCoord::alignLeft();
	Game2D::Colour(1, 1, 1).draw();
	Game2D::Freetype::print(Game2D::Font::getFont(5), 1, 44, "Player %d's turn", currentPlayer + 1);
	Game2D::ScreenCoord::alignCentre();
}