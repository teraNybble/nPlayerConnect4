#include "ConnectMenu.h"
#include "TextureManager.h"

ConnectMenu::ConnectMenu()
{
	isHost = false;

	//address = "127.0.0.1";//default address to local host
	//port = "60000";//default port to 60000
}

void ConnectMenu::setHost(bool host){
	//std::cout << "Setting host\n";
	isHost = host;
	Game2D::Sprite normalSprite, hoverSprite, clickSprite;
	if(isHost) {
		//if the player is self hosting set the connect ip to localhost
		address.setText("127.0.0.1");
	}
}

void ConnectMenu::init()
{
	//m_menuTex = ImageLoder::loadPNG("Images/menu.png");
	m_menuTex = TextureManager::getText(0);

	connectText.fontSize = 5;
	connectText.pos = Game2D::Pos2(0,35);
	connectText.text = "Connect";
	connectText.width = freetype::getLength(Game2D::Font::getFont(connectText.fontSize), connectText.text.c_str());

	hostText.fontSize = 5;
	hostText.pos = Game2D::Pos2(0,35);
	hostText.text = "Host";
	hostText.width = freetype::getLength(Game2D::Font::getFont(connectText.fontSize), connectText.text.c_str());

	Game2D::Sprite normalSprite, hoverSprite, clickSprite;
	Game2D::Rect tempRect = Game2D::Rect(15,-40,10,5);

	normalSprite.setTextureCoords(Game2D::Rect(0.75f,0.375f,0.25f,0.125f));
	hoverSprite.setTextureCoords(Game2D::Rect(0.75f,0.250f,0.25f,0.125f));
	clickSprite.setTextureCoords(Game2D::Rect(0.75f,0.125f,0.25f,0.125f));

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	normalSprite.setColour(Game2D::Colour::White);
	hoverSprite.setColour(Game2D::Colour::White);
	clickSprite.setColour(Game2D::Colour::White);

	backButton.setRect(tempRect);
	backButton.addStateSprites(normalSprite,hoverSprite,clickSprite,clickSprite,normalSprite);
	backButton.alignToDrawableObject();

	tempRect = Game2D::Rect(-15,-40,10,5);

	normalSprite.setTextureCoords(Game2D::Rect(0.50f,0.375f,0.25f,0.125f));
	hoverSprite.setTextureCoords(Game2D::Rect(0.50f,0.250f,0.25f,0.125f));
	clickSprite.setTextureCoords(Game2D::Rect(0.50f,0.125f,0.25f,0.125f));

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	connectButton.setRect(tempRect);
	connectButton.addStateSprites(normalSprite,hoverSprite,clickSprite,clickSprite,normalSprite);
	connectButton.alignToDrawableObject();

	tempRect = Game2D::Rect(0,0,45,8);

	normalSprite.setColour(Game2D::Colour::Black);
	hoverSprite.setColour(Game2D::Colour::Black);
	clickSprite.setColour(Game2D::Colour::Black);

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	//address.setPos(Game2D::Pos2(-24,0));
	address.setRect(tempRect);
	address.setBackGroundSprites(normalSprite,normalSprite,normalSprite,normalSprite,normalSprite);
	address.init(4);
	address.setCharListModeWhitelist();
	address.addNumbersToList();
	address.addCharToList('.');
	address.setText("127.0.0.1");//default to local host

	tempRect = Game2D::Rect(0,-10,45,8);

	normalSprite.setRect(tempRect);
	hoverSprite.setRect(tempRect);
	clickSprite.setRect(tempRect);

	//address.setPos(Game2D::Pos2(-24,0));
	port.setRect(tempRect);
	port.setBackGroundSprites(normalSprite,normalSprite,normalSprite,normalSprite,normalSprite);
	port.init(4);
	port.setCharListModeWhitelist();
	port.addNumbersToList();
	//address.addCharToList('.');
	port.setText("60000");//default to port 60000
}


void ConnectMenu::resize()
{
	connectText.width = freetype::getLength(Game2D::Font::getFont(connectText.fontSize), connectText.text.c_str());
	hostText.width = freetype::getLength(Game2D::Font::getFont(hostText.fontSize), hostText.text.c_str());
}

int ConnectMenu::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState)
{
	//as the start button is aligned to the right of the screen the mouse coordinats need to be aligned right as well
	Game2D::Pos2 mousePosAlignedRight = Game2D::Pos2((mousePos.x - Game2D::ScreenCoord::getAspectRatio() * 50), mousePos.y);

	//as the start button is aligned to the right of the screen the mouse coordinats need to be aligned right as well
	Game2D::Pos2 mousePosAlignedLeft = Game2D::Pos2((mousePos.x + Game2D::ScreenCoord::getAspectRatio() * 50), mousePos.y);

	if(!isHost) {
		address.processMouse(mousePos,mouseState,1);
	} /*else {
		//if the player is self hosting set the connect ip to localhost
		address.setText("127.0.0.1");
	}*/
	port.processMouse(mousePos,mouseState,1);

	if(backButton.update(mousePosAlignedLeft,mouseState,1) == Game2D::ClickableObject::CLICK){
		return 1;
	}

	if(connectButton.update(mousePosAlignedRight,mouseState,1) == Game2D::ClickableObject::CLICK){
		return 2;
	}

	return -1;
}

void ConnectMenu::processCodepoint(unsigned int codepoint)
{
	address.update(codepoint);
	port.update(codepoint);
}

void ConnectMenu::draw()
{
	glBindTexture(GL_TEXTURE_2D, m_menuTex);

	Game2D::ScreenCoord::alignLeft();
	backButton.draw();

	Game2D::ScreenCoord::alignRight();
	connectButton.draw();

	Game2D::ScreenCoord::alignCentre();
	if(!isHost) {
		address.draw();
	}
	//rebind the menu textures as address would have bound the font textures
	glBindTexture(GL_TEXTURE_2D, m_menuTex);
	port.draw();

	if(isHost){
		freetype::print(Game2D::Font::getFont(hostText.fontSize), (hostText.width/-2.0f),
				hostText.pos.y,hostText.text.c_str());
	} else {
		freetype::print(Game2D::Font::getFont(connectText.fontSize), (connectText.width / -2.0f),
						connectText.pos.y, connectText.text.c_str());
	}

	if(!isHost) { freetype::print(Game2D::Font::getFont(4),-30,-2,"IP:"); }
	freetype::print(Game2D::Font::getFont(4),-35,-12,"Port:");
}