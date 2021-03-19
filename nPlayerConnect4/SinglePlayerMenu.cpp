#include "SinglePlayerMenu.h"

void SinglePlayerMenu::init()
{
	mainMenuTex = ImageLoder::loadPNG("Images/menu.png");

	Game2D::Sprite normalSprite, hoverSprite, clickSprite, disabledSprite;
	Game2D::Rect tempRect = Game2D::Rect(15, -40, 10, 5);

	disabledSprite.setTextureCoords(Game2D::Rect(0.75f, 0.500f, 0.25f, 0.125f));
	normalSprite.setTextureCoords(Game2D::Rect(0.75f, 0.375f, 0.25f, 0.125f));
	hoverSprite.setTextureCoords(Game2D::Rect(0.75f, 0.250f, 0.25f, 0.125f));
	clickSprite.setTextureCoords(Game2D::Rect(0.75f, 0.125f, 0.25f, 0.125f));

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	disabledSprite.setColour(Game2D::Colour::White);
	normalSprite.setColour(Game2D::Colour::White);
	hoverSprite.setColour(Game2D::Colour::White);
	clickSprite.setColour(Game2D::Colour::White);

	backButton.setRect(tempRect);
	backButton.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	backButton.alignToDrawableObject();

	tempRect = Game2D::Rect(-15, -40, 10, 5);

	disabledSprite.setRect(tempRect);
	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	disabledSprite.setTextureCoords(Game2D::Rect(0.0f, 0.500f, 0.25f, 0.125f));
	normalSprite.setTextureCoords(Game2D::Rect(0.0f, 0.375f, 0.25f, 0.125f));
	hoverSprite.setTextureCoords(Game2D::Rect(0.0f, 0.250f, 0.25f, 0.125f));
	clickSprite.setTextureCoords(Game2D::Rect(0.0f, 0.125f, 0.25f, 0.125f));

	startButton.setRect(tempRect);
	startButton.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, disabledSprite);
	startButton.alignToDrawableObject();

	tempRect = Game2D::Rect(1.25, -45, 2.5, 2.5);
	normalSprite.setTextureCoords(Game2D::Rect(0, 0, 0.125f, 0.125f));
	hoverSprite.setTextureCoords(Game2D::Rect(0.125f, 0, 0.125f, 0.125f));
	clickSprite.setTextureCoords(Game2D::Rect(0.250f, 0, 0.125f, 0.125f));

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	boardWidthPlus.setRect(tempRect);
	boardWidthPlus.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	boardWidthPlus.alignToDrawableObject();

	tempRect = Game2D::Rect(37,-45,2.5,2.5);

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	lineLengthPlus.setRect(tempRect);
	lineLengthPlus.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	lineLengthPlus.alignToDrawableObject();

	tempRect = Game2D::Rect(-37, -45, 2.5, 2.5);

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	playersPlus.setRect(tempRect);
	playersPlus.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	playersPlus.alignToDrawableObject();

	tempRect = Game2D::Rect(-1.25, -45, 2.5, 2.5);

	normalSprite.flipX();
	hoverSprite.flipX();
	clickSprite.flipX();

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	boardWidthMinus.setRect(tempRect);
	boardWidthMinus.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	boardWidthMinus.alignToDrawableObject();

	tempRect = Game2D::Rect(34.5,-45,2.5,2.5);

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	lineLengthMinus.setRect(tempRect);
	lineLengthMinus.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	lineLengthMinus.alignToDrawableObject();

	tempRect = Game2D::Rect(-39.5, -45, 2.5, 2.5);

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	playersMinus.setRect(tempRect);
	playersMinus.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	playersMinus.alignToDrawableObject();

	tempRect = Game2D::Rect(12, -40, 2.5, 2.5);

	normalSprite.rotate(90);
	hoverSprite.rotate(90);
	clickSprite.rotate(90);

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	boardHeightMinus.setRect(tempRect);
	boardHeightMinus.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	boardHeightMinus.alignToDrawableObject();

	tempRect = Game2D::Rect(12, -37.5, 2.5, 2.5);

	normalSprite.flipX();
	hoverSprite.flipX();
	clickSprite.flipX();

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	boardHeightPlus.setRect(tempRect);
	boardHeightPlus.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	boardHeightPlus.alignToDrawableObject();

	lineLength = 4;
	boardWidth = 7;
	boardHeight = 6;
	numPlayers = 2;

	delayTime = 1000;//ms
	arrowDown = false;

	arrowButtons.clear();
	arrowButtons.push_back(&playersPlus);
	arrowButtons.push_back(&playersMinus);
	arrowButtons.push_back(&boardWidthPlus);
	arrowButtons.push_back(&boardWidthMinus);
	arrowButtons.push_back(&boardHeightPlus);
	arrowButtons.push_back(&boardHeightMinus);
	arrowButtons.push_back(&lineLengthPlus);
	arrowButtons.push_back(&lineLengthMinus);

	arrowFuncs.clear();
	arrowFuncs.push_back(
			[&](){
				numPlayers++;
				playerCount.width = Game2D::Freetype::getLength(Game2D::Font::getFont(playerCount.fontSize), playerCount.text.c_str(), numPlayers);
			}
	);
	arrowFuncs.push_back(
			[&](){
				if(numPlayers > 2){
					numPlayers--;
					playerCount.width = Game2D::Freetype::getLength(Game2D::Font::getFont(playerCount.fontSize), playerCount.text.c_str(), numPlayers);
				}
			}
	);
	arrowFuncs.push_back(
			[&](){
				boardWidth++;
				boardDimLabels.width = Game2D::Freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
																   boardDimLabels.text.c_str(), boardWidth, boardHeight);
			}
	);
	arrowFuncs.push_back(
			[&](){
				if (--boardWidth < lineLength) { boardWidth = lineLength; }
				boardDimLabels.width = Game2D::Freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
																   boardDimLabels.text.c_str(), boardWidth, boardHeight);
			}
	);
	arrowFuncs.push_back(
			[&](){
				boardHeight++;
				boardDimLabels.width = Game2D::Freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
																   boardDimLabels.text.c_str(), boardWidth, boardHeight);
			}
	);
	arrowFuncs.push_back(
			[&](){
				if (--boardHeight < lineLength) { boardHeight = lineLength; }
				boardDimLabels.width = Game2D::Freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
																   boardDimLabels.text.c_str(), boardWidth, boardHeight);
			}
	);

	arrowFuncs.push_back(
			[&](){
				lineLength++;
				connectLengthLabels.width = Game2D::Freetype::getLength(Game2D::Font::getFont(connectLengthLabels.fontSize), connectLengthLabels.text.c_str(), lineLength);
				bool recalculateTextLength = false;
				if(boardHeight < lineLength) {
					boardHeight = lineLength;
					recalculateTextLength = true;
				}
				if(boardWidth < lineLength) {
					boardWidth = lineLength;
					recalculateTextLength = true;
				}
				if(recalculateTextLength){
					boardDimLabels.width = Game2D::Freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
																	   boardDimLabels.text.c_str(), boardWidth, boardHeight);
				}
			}
	);
	arrowFuncs.push_back(
			[&](){
				if(lineLength > 0){
					lineLength--;
					connectLengthLabels.width = Game2D::Freetype::getLength(Game2D::Font::getFont(connectLengthLabels.fontSize), connectLengthLabels.text.c_str(), lineLength);
				}
			}
	);

	resize();
}

void SinglePlayerMenu::resize()
{
	Game2D::ScreenCoord::alignCentre();

	noPlayers.fontSize = 3;
	noPlayers.text = "No. Players";
	noPlayers.width = Game2D::Freetype::getLength(Game2D::Font::getFont(noPlayers.fontSize), noPlayers.text.c_str());
	boardDims.fontSize = 3;
	boardDims.text = "Board size";
	boardDims.width = Game2D::Freetype::getLength(Game2D::Font::getFont(boardDims.fontSize), boardDims.text.c_str());

	playerCount.fontSize = 4;
	playerCount.text = "%d";
	playerCount.width = Game2D::Freetype::getLength(Game2D::Font::getFont(playerCount.fontSize), playerCount.text.c_str(), numPlayers);

	boardDimLabels.fontSize = 4;
	boardDimLabels.text = "%d x %d";
	boardDimLabels.width = Game2D::Freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize), boardDimLabels.text.c_str(), boardWidth, boardHeight);

	connectLength.fontSize = 3;
	connectLength.text = "Connect length";
	connectLength.width = Game2D::Freetype::getLength(Game2D::Font::getFont(connectLength.fontSize), connectLength.text.c_str());

	connectLengthLabels.fontSize = 4;
	connectLengthLabels.text = "%d";
	connectLengthLabels.width = Game2D::Freetype::getLength(Game2D::Font::getFont(connectLengthLabels.fontSize), connectLengthLabels.text.c_str(), lineLength);
}

int SinglePlayerMenu::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState)
{
	for(int i = 0; i < arrowButtons.size(); i++){
		Game2D::ClickableObject::ClickState tempClickState = arrowButtons[i]->update(mousePos,mouseState,1);
		if(tempClickState == Game2D::ClickableObject::MOUSEDOWN){
			if(!arrowDown) {
				timer.start();
				delayCount = delayTime;
				arrowDown = true;
				return -1;
			} else {
				if(timer.elapsedTime<Game2D::Timer::miliseconds>() >= delayCount){
					delayCount *= 0.9;
					timer.start();

					arrowFuncs[i]();
					//if i is less than 4 then we are changing board detentions else we are changing the connect length
					return -1;
				} else {
					return -1;
				}
			}
		} else if(tempClickState == Game2D::ClickableObject::CLICK) {
			arrowDown = false;
			arrowFuncs[i]();
			//if i is less than 4 then we are changing board detentions else we are changing the connect length
			if(i < 4){
				return 4;
			} else {
				return 5;
			}
		} else if(mouseState == Game2D::KeyState::UP && arrowDown) {
			arrowDown = false;
			return 5;
		}
	}
	//as the start button is aligned to the right of the screen the mouse coordinats need to be aligned right as well
	Game2D::Pos2 mousePosAlignedRight = Game2D::Pos2((mousePos.x - Game2D::ScreenCoord::getAspectRatio() * 50), mousePos.y);
	//as the start button is aligned to the right of the screen the mouse coordinats need to be aligned right as well
	Game2D::Pos2 mousePosAlignedLeft = Game2D::Pos2((mousePos.x + Game2D::ScreenCoord::getAspectRatio() * 50), mousePos.y);


	if (startButton.update(mousePosAlignedRight, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		return 2;
	}
	if (backButton.update(mousePosAlignedLeft, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		return 1;
	}

	return 0;
}

void SinglePlayerMenu::draw() const
{
	glBindTexture(GL_TEXTURE_2D, mainMenuTex);

	Game2D::ScreenCoord::alignLeft();
	backButton.draw();
	Game2D::ScreenCoord::alignCentre();
	playersPlus.draw();
	playersMinus.draw();
	boardHeightPlus.draw();
	boardHeightMinus.draw();
	boardWidthPlus.draw();
	boardWidthMinus.draw();
	lineLengthPlus.draw();
	lineLengthMinus.draw();
	Game2D::ScreenCoord::alignRight();
	startButton.draw();

	Game2D::ScreenCoord::alignCentre();
	Game2D::Colour::White.draw();
	Game2D::Freetype::print(Game2D::Font::getFont(playerCount.fontSize), (playerCount.width / -2.0f) - 38, -41, playerCount.text.c_str(), numPlayers);
	Game2D::Freetype::print(Game2D::Font::getFont(noPlayers.fontSize), (noPlayers.width / -2.0f) - 38, -35, noPlayers.text.c_str());
	Game2D::Freetype::print(Game2D::Font::getFont(boardDims.fontSize), (boardDims.width / -2.0f), -35, boardDims.text.c_str());
	Game2D::Freetype::print(Game2D::Font::getFont(boardDimLabels.fontSize), (boardDimLabels.width / -2.0f), -41, boardDimLabels.text.c_str(), boardWidth, boardHeight);
	Game2D::Freetype::print(Game2D::Font::getFont(connectLength.fontSize), (connectLength.width/-2.0f) + 35.5, -35, connectLength.text.c_str());
	Game2D::Freetype::print(Game2D::Font::getFont(connectLengthLabels.fontSize), (connectLengthLabels.width / -2.0f) + 35.5, -41, connectLengthLabels.text.c_str(), lineLength);
}