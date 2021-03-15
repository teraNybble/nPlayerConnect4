#include "Lobby.h"

void Lobby::init()
{	
	playerList.clear();
	winningPlayer = -2;
	m_menuTex = ImageLoder::loadPNG("Images/menu.png");
	m_circleTex = ImageLoder::loadPNG("Images/circle.png");

	Game2D::Sprite normalSprite, hoverSprite, clickSprite, disabledSprite;
	Game2D::Rect tempRect = Game2D::Rect(15,-40,10,5);
	//Game2D::Rect tempTexRect;

	disabledSprite.setTextureCoords(Game2D::Rect(0.75f,0.500f,0.25f,0.125f));
	normalSprite.setTextureCoords(Game2D::Rect(0.75f,0.375f,0.25f,0.125f));
	hoverSprite.setTextureCoords(Game2D::Rect(0.75f,0.250f,0.25f,0.125f));
	clickSprite.setTextureCoords(Game2D::Rect(0.75f,0.125f,0.25f,0.125f));

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	disabledSprite.setColour(Game2D::Colour::White);
	normalSprite.setColour(Game2D::Colour::White);
	hoverSprite.setColour(Game2D::Colour::White);
	clickSprite.setColour(Game2D::Colour::White);

	backButton.setRect(tempRect);
	backButton.addStateSprites(normalSprite,hoverSprite,clickSprite,clickSprite,normalSprite);
	backButton.alignToDrawableObject();

	tempRect = Game2D::Rect(8.5,30,5,5);

	normalSprite.setTextureCoords(Game2D::Rect(0.375f,0.0f,0.125f,0.125f));
	hoverSprite.setTextureCoords(Game2D::Rect(0.500f,0.0f,0.125f,0.125f));
	clickSprite.setTextureCoords(Game2D::Rect(0.625f,0.0f,0.125f,0.125f));

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	colourAccept.setRect(tempRect);
	colourAccept.addStateSprites(normalSprite, hoverSprite, clickSprite, clickSprite, normalSprite);
	colourAccept.alignToDrawableObject();

	tempRect = Game2D::Rect(-15,-40,10,5);

	disabledSprite.setRect(tempRect);
	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	disabledSprite.setTextureCoords(Game2D::Rect(0.0f,0.500f,0.25f,0.125f));
	normalSprite.setTextureCoords(Game2D::Rect(0.0f,0.375f,0.25f,0.125f));
	hoverSprite.setTextureCoords(Game2D::Rect(0.0f,0.250f,0.25f,0.125f));
	clickSprite.setTextureCoords(Game2D::Rect(0.0f,0.125f,0.25f,0.125f));

	startButton.setRect(tempRect);
	startButton.addStateSprites(normalSprite,hoverSprite,clickSprite,clickSprite,disabledSprite);
	startButton.alignToDrawableObject();

	disabledSprite.setTextureCoords(Game2D::Rect(0.75f,0.500f,0.25f,0.125f));
	normalSprite.setTextureCoords(Game2D::Rect(0.75f,0.375f,0.25f,0.125f));
	hoverSprite.setTextureCoords(Game2D::Rect(0.75f,0.250f,0.25f,0.125f));
	clickSprite.setTextureCoords(Game2D::Rect(0.75f,0.125f,0.25f,0.125f));

	tempRect = Game2D::Rect(11,40,1,2);

	normalSprite.setTextureCoords(Game2D::Rect(0.0f,0.0f,0.0f,0.0f));
	hoverSprite.setTextureCoords(Game2D::Rect(0.0f,0.0f,0.0f,0.0f));
	clickSprite.setTextureCoords(Game2D::Rect(0.0f,0.0f,0.0f,0.0f));

	disabledSprite.setRect(tempRect);
	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	//redSlider = Game2D::Slider(Game2D::Rect(6,40,10,2));
	redSlider.setRect(Game2D::Rect(6, 40, 10, 2));
	redSlider.setButtonStateSprites(normalSprite,normalSprite,normalSprite,normalSprite,normalSprite);

	tempRect = Game2D::Rect(11,37,1,2);

	disabledSprite.setRect(tempRect);
	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	//greenSlider = Game2D::Slider(Game2D::Rect(6,37,10,2));
	greenSlider.setRect(Game2D::Rect(6, 37, 10, 2));
	greenSlider.setButtonStateSprites(normalSprite,normalSprite,normalSprite,normalSprite,normalSprite);

	tempRect = Game2D::Rect(11,34,1,2);

	disabledSprite.setRect(tempRect);
	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	//blueSlider = Game2D::Slider(Game2D::Rect(6,34,10,2));
	blueSlider.setRect(Game2D::Rect(6, 34, 10, 2));
	blueSlider.setButtonStateSprites(normalSprite,normalSprite,normalSprite,normalSprite,normalSprite);

	exampleColour.setRect(Game2D::Rect(6,45,5,5));
	exampleColour.setColour(Game2D::Colour::Red);

	redSlider.setValue(1.0f);
	greenSlider.setValue(0.0f);
	blueSlider.setValue(0.0f);
	

	//-------------------------------
	tempRect = Game2D::Rect(1.25,-45,2.5,2.5);
	//tempTexRect = Game2D::Rect(0, 0, 0.125f, 0.125f);
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
	//-------------------------------
	//*/
	lineLength = 4;
	boardWidth = 7;
	boardHeight = 6;

	delayTime = 1000;//ms
	arrowDown = false;

	arrowButtons.clear();
	arrowButtons.push_back(&boardWidthPlus);
	arrowButtons.push_back(&boardWidthMinus);
	arrowButtons.push_back(&boardHeightPlus);
	arrowButtons.push_back(&boardHeightMinus);
	arrowButtons.push_back(&lineLengthPlus);
	arrowButtons.push_back(&lineLengthMinus);

	arrowFuncs.clear();
	arrowFuncs.push_back(
		[&](){
			boardWidth++;
			boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
													   boardDimLabels.text.c_str(), boardWidth, boardHeight);
		}
	);
	arrowFuncs.push_back(
		[&](){
			if (--boardWidth < lineLength) { boardWidth = lineLength; }
			boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
													   boardDimLabels.text.c_str(), boardWidth, boardHeight);
		}
	);
	arrowFuncs.push_back(
		[&](){
			boardHeight++;
			boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
													   boardDimLabels.text.c_str(), boardWidth, boardHeight);
		}
	);
	arrowFuncs.push_back(
		[&](){
			if (--boardHeight < lineLength) { boardHeight = lineLength; }
			boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
													   boardDimLabels.text.c_str(), boardWidth, boardHeight);
		}
	);

	arrowFuncs.push_back(
		[&](){
			lineLength++;
			connectLengthLabels.width = freetype::getLength(Game2D::Font::getFont(connectLengthLabels.fontSize), connectLengthLabels.text.c_str(), lineLength);
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
				boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
														   boardDimLabels.text.c_str(), boardWidth, boardHeight);
			}
		}
	);
	arrowFuncs.push_back(
		[&](){
			if(lineLength > 0){
				lineLength--;
				connectLengthLabels.width = freetype::getLength(Game2D::Font::getFont(connectLengthLabels.fontSize), connectLengthLabels.text.c_str(), lineLength);
			}
		}
	);
	
	resize();
}

void Lobby::resize()
{
	boardDims.fontSize = 3;
	boardDims.text = "Board size";
	boardDims.width = freetype::getLength(Game2D::Font::getFont(boardDims.fontSize), boardDims.text.c_str());

	boardDimLabels.fontSize = 4;
	boardDimLabels.text = "%d x %d";
	boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize), boardDimLabels.text.c_str(), boardWidth, boardHeight);

	connectLength.fontSize = 3;
	connectLength.text = "Connect length";
	connectLength.width = freetype::getLength(Game2D::Font::getFont(connectLength.fontSize), connectLength.text.c_str());

	connectLengthLabels.fontSize = 4;
	connectLengthLabels.text = "%d";
	connectLengthLabels.width = freetype::getLength(Game2D::Font::getFont(connectLengthLabels.fontSize), connectLengthLabels.text.c_str(), lineLength);
}

int Lobby::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState)
{
	//as the start button is aligned to the right of the screen the mouse coordinats need to be aligned right as well
	Game2D::Pos2 mousePosAlignedRight = Game2D::Pos2((mousePos.x - Game2D::ScreenCoord::getAspectRatio() * 50), mousePos.y);

	//as the start button is aligned to the right of the screen the mouse coordinats need to be aligned right as well
	Game2D::Pos2 mousePosAlignedLeft = Game2D::Pos2((mousePos.x + Game2D::ScreenCoord::getAspectRatio() * 50), mousePos.y);

	if(backButton.update(mousePosAlignedLeft,mouseState,1) == Game2D::ClickableObject::CLICK){
		return 1;
	}

	if(colourAccept.update(mousePosAlignedLeft,mouseState,1) == Game2D::ClickableObject::CLICK) {
		return 2;
	}

	redSlider.update(mousePosAlignedLeft,mouseState,1);
	greenSlider.update(mousePosAlignedLeft,mouseState,1);
	blueSlider.update(mousePosAlignedLeft,mouseState,1);
	//tempSlider.update(mousePos,mouseState,1);
	//std::cout << tempSlider.getValue() << "\n";

	//std::cout << Game2D::Colour(redSlider.getValue(),greenSlider.getValue(),blueSlider.getValue()) << "\n";

	exampleColour.setColour(Game2D::Colour(redSlider.getValue(),greenSlider.getValue(),blueSlider.getValue()));

	if(isHost) {
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
						if(i < 4){
							return 4;
						} else {
							return 5;
						}
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
/*
		Game2D::ClickableObject::ClickState tempClickState = boardWidthPlus.update(mousePos, mouseState, 1);
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
					boardWidth++;
					boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
															   boardDimLabels.text.c_str(), boardWidth, boardHeight);
					return 4;
				} else {
					return -1;
				}
			}
		} else if(tempClickState == Game2D::ClickableObject::CLICK) {
		//if (boardWidthPlus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
			boardWidth++;
			boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
													   boardDimLabels.text.c_str(), boardWidth, boardHeight);
			return 4;
		}
		if (boardWidthMinus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
			if (--boardWidth < lineLength) {
				boardWidth = lineLength;
			}
			boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
													   boardDimLabels.text.c_str(), boardWidth, boardHeight);
			return 4;
		}
		if (boardHeightPlus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
			boardHeight++;
			boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
													   boardDimLabels.text.c_str(), boardWidth, boardHeight);
			return 4;
		}
		if (boardHeightMinus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
			if (--boardHeight < lineLength) {
				boardHeight = lineLength;
			}
			boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
													   boardDimLabels.text.c_str(), boardWidth, boardHeight);
			return 4;
		}
		if(lineLengthMinus.update(mousePos,mouseState,1) == Game2D::ClickableObject::CLICK){
			if(lineLength > 0){
				lineLength--;
				connectLengthLabels.width = freetype::getLength(Game2D::Font::getFont(connectLengthLabels.fontSize), connectLengthLabels.text.c_str(), lineLength);
			}
			return 5;
		}
		if(lineLengthPlus.update(mousePos,mouseState,1) == Game2D::ClickableObject::CLICK){
			lineLength++;
			connectLengthLabels.width = freetype::getLength(Game2D::Font::getFont(connectLengthLabels.fontSize), connectLengthLabels.text.c_str(), lineLength);
			if(boardHeight < lineLength) {
				boardHeight = lineLength;
				boardWidth = lineLength;
				boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
														   boardDimLabels.text.c_str(), boardWidth, boardHeight);
			}
			if(boardWidth < lineLength) {
				boardHeight = lineLength;
				boardWidth = boardHeight;
				boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize),
														   boardDimLabels.text.c_str(), boardWidth, boardHeight);
			}
			return 5;
		}*/
	}

	//only allow the host to start the game
	if(isHost) {
		//allow the game to start when there are 2 or more people
		playerList.size() > 1 ? startButton.enable() : startButton.disable();
		if (startButton.update(mousePosAlignedRight, mouseState, 1) == Game2D::ClickableObject::CLICK) {
			return 3;
		}
	}

	return -1;
}

void Lobby::setPlayerColour(int id, Game2D::Colour colour)
{
	std::pair<std::map<int,Game2D::Colour>::iterator,bool> ret;
	ret = playerList.insert(std::pair<int,Game2D::Colour>(id,colour));
	//if the insert function returned false the player already exsists
	if(!ret.second){
		ret.first->second = colour;
	}
}

void Lobby::removePlayer(int id)
{
	playerList.erase(playerList.find(id));
}

void Lobby::draw()
{
	glBindTexture(GL_TEXTURE_2D, m_menuTex);

	Game2D::ScreenCoord::alignLeft();
	backButton.draw();
	colourAccept.draw();
	redSlider.draw();
	greenSlider.draw();
	blueSlider.draw();
	exampleColour.draw();

	Game2D::ScreenCoord::alignCentre();
	//calculate the width of the player list
	Game2D::Sprite tempSprite;
	//tempSlider.draw();

	if(isHost){
		boardWidthPlus.draw();
		boardWidthMinus.draw();
		boardHeightPlus.draw();
		boardHeightMinus.draw();
		lineLengthPlus.draw();
		lineLengthMinus.draw();
	}

	//get the width of all the players plus spacing and divied by two so they will all be aligned to the centre
	float startX = ((float)(((playerList.size() - 1) * 7.5) + (playerList.size()-1))/2.0f);
	tempSprite.setRect(Game2D::Rect(-startX,0,7.5,7.5));
	tempSprite.setTextureCoords(Game2D::Rect(0,0,1,1));

	glBindTexture(GL_TEXTURE_2D, m_circleTex);

	//std::cout << playerList.size() << "\n";
	for(auto it : playerList){
		tempSprite.setColour(it.second);
		tempSprite.draw();
		tempSprite.move(Game2D::Pos2(tempSprite.getRect().width+1,0));
	}
	glBindTexture(GL_TEXTURE_2D, m_menuTex);


	Game2D::ScreenCoord::alignRight();
	//only show the host the start button
	if(isHost) {
		startButton.draw();
	}

	Game2D::ScreenCoord::alignCentre();
	Game2D::Colour::White.draw();
	freetype::print(Game2D::Font::getFont(boardDims.fontSize), (boardDims.width/-2.0f), -35, boardDims.text.c_str());
	freetype::print(Game2D::Font::getFont(boardDimLabels.fontSize), (boardDimLabels.width/-2.0f), -41, boardDimLabels.text.c_str(), boardWidth,boardHeight);
	freetype::print(Game2D::Font::getFont(connectLength.fontSize), (connectLength.width/-2.0f) + 35.5, -35, connectLength.text.c_str());
	freetype::print(Game2D::Font::getFont(connectLengthLabels.fontSize), (connectLengthLabels.width / -2.0f) + 35.5, -41, connectLengthLabels.text.c_str(), lineLength);
	if(winningPlayer == -1){
		float width = freetype::getLength(Game2D::Font::getFont(4),"Tie");
		freetype::print(Game2D::Font::getFont(4),-width/2.0,40,"Tie");
	} else if(winningPlayer >= 0) {
		float width = freetype::getLength(Game2D::Font::getFont(4),"Player %d wins",winningPlayer+1);
		freetype::print(Game2D::Font::getFont(4),-width/2.0,40,"Player %d wins",winningPlayer+1);
	}
}