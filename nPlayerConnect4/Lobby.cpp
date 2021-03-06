#include "Lobby.h"

void Lobby::init()
{
	playerList.clear();
	winningPlayer = -2;
	m_menuTex = ImageLoder::loadPNG("Images/menu.png");

	Game2D::Sprite normalSprite, hoverSprite, clickSprite, disabledSprite;
	Game2D::Rect tempRect = Game2D::Rect(15,-40,10,5);

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

	startButton.setRect(tempRect);
	startButton.addStateSprites(normalSprite,hoverSprite,clickSprite,clickSprite,disabledSprite);
	startButton.alignToDrawableObject();

	tempRect = Game2D::Rect(11,40,1,2);

	disabledSprite.setRect(tempRect);
	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	redSlider = Game2D::Slider(Game2D::Rect(6,40,10,2));
	redSlider.setButtonStateSprites(normalSprite,normalSprite,normalSprite,normalSprite,normalSprite);

	tempRect = Game2D::Rect(11,37,1,2);

	disabledSprite.setRect(tempRect);
	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	greenSlider = Game2D::Slider(Game2D::Rect(6,37,10,2));
	greenSlider.setButtonStateSprites(normalSprite,normalSprite,normalSprite,normalSprite,normalSprite);

	tempRect = Game2D::Rect(11,34,1,2);

	disabledSprite.setRect(tempRect);
	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	blueSlider = Game2D::Slider(Game2D::Rect(6,34,10,2));
	blueSlider.setButtonStateSprites(normalSprite,normalSprite,normalSprite,normalSprite,normalSprite);

	exampleColour.setRect(Game2D::Rect(6,45,5,5));
	exampleColour.setColour(Game2D::Colour::Red);

	redSlider.setValue(1.0f);
	greenSlider.setValue(0.0f);
	blueSlider.setValue(0.0f);
}

void Lobby::resize()
{
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


	//get the width of all the players plus spacing and divied by two so they will all be aligned to the centre
	float startX = ((float)(((playerList.size() - 1) * 7.5) + (playerList.size()-1))/2.0f);
	tempSprite.setRect(Game2D::Rect(-startX,0,7.5,7.5));
	//std::cout << playerList.size() << "\n";
	for(auto it : playerList){
		tempSprite.setColour(it.second);
		tempSprite.draw();
		tempSprite.move(Game2D::Pos2(tempSprite.getRect().width+1,0));
	}


	Game2D::ScreenCoord::alignRight();
	//only show the host the start button
	if(isHost) {
		startButton.draw();
	}

	Game2D::ScreenCoord::alignCentre();
	if(winningPlayer == -1){
		float width = freetype::getLength(Game2D::Font::getFont(4),"Tie");
		freetype::print(Game2D::Font::getFont(4),-width/2.0,40,"Tie");
	} else if(winningPlayer >= 0) {
		float width = freetype::getLength(Game2D::Font::getFont(4),"Player %d wins",winningPlayer+1);
		freetype::print(Game2D::Font::getFont(4),-width/2.0,40,"Player %d wins",winningPlayer+1);
	}
}