#include "MainMenu.h"
#include "TextureManager.h"

void MainMenu::init()
{
	mainMenuTex = TextureManager::getTexture(0);
	//set the sprites colour

	Game2D::Rect tempRect;
	Game2D::Sprite tempNormal, tempHover, tempClick;
	tempRect = Game2D::Rect(0,-14,21,5);

	tempNormal.setTextureCoords(Game2D::Rect(0, 0.4375f, 0.2625f, 0.0625f));
	tempHover.setTextureCoords(Game2D::Rect(0, 0.3750f, 0.2625f, 0.0625f));
	tempClick.setTextureCoords(Game2D::Rect(0, 0.3125f, 0.2625f, 0.0625f));

	tempNormal.setRect(tempRect);
	tempHover.setRect(tempRect);
	tempClick.setRect(tempRect);

	tempNormal.setColour(Game2D::Colour::White);
	tempHover.setColour(Game2D::Colour::White);
	tempClick.setColour(Game2D::Colour::White);

	start.setRect(tempRect);
	start.addStateSprites(tempNormal,tempHover,tempClick,tempClick,tempNormal);
	start.alignToDrawableObject();

	tempRect = Game2D::Rect(0,27.5,58,6);

	tempNormal.setRect(tempRect);
	tempHover.setRect(tempRect);
	tempClick.setRect(tempRect);

	tempNormal.setColour(Game2D::Colour::Black);
	tempHover.setColour(Game2D::Colour::Red);
	tempClick.setColour(Game2D::Colour::Blue);

	gravButt.setRect(tempRect);
	gravButt.addStateSprites(tempNormal,tempHover,tempClick,tempClick,tempNormal);
	gravButt.alignToDrawableObject();

	tempRect = Game2D::Rect(5.5,-20,10,5);

	tempNormal.setTextureCoords(Game2D::Rect(0.125f, 0.1875f, 0.125f, 0.0625f));
	tempHover.setTextureCoords(Game2D::Rect(0.125f, 0.1250f, 0.125f, 0.0625f));
	tempClick.setTextureCoords(Game2D::Rect(0.125f, 0.0625f, 0.125f, 0.0625f));

	tempNormal.setRect(tempRect);
	tempHover.setRect(tempRect);
	tempClick.setRect(tempRect);

	tempNormal.setColour(Game2D::Colour::White);
	tempHover.setColour(Game2D::Colour::White);
	tempClick.setColour(Game2D::Colour::White);

	host.setRect(tempRect);
	host.addStateSprites(tempNormal,tempHover,tempClick,tempClick,tempNormal);
	host.alignToDrawableObject();

	tempRect = Game2D::Rect(-5.5,-20,10,5);
	tempNormal.setTextureCoords(Game2D::Rect(0.250f, 0.1875f, 0.125f, 0.0625f));
	tempHover.setTextureCoords(Game2D::Rect(0.250f, 0.1250f, 0.125f, 0.0625f));
	tempClick.setTextureCoords(Game2D::Rect(0.250f, 0.0625f, 0.125f, 0.0625f));

	tempNormal.setRect(tempRect);
	tempHover.setRect(tempRect);
	tempClick.setRect(tempRect);

	tempNormal.setColour(Game2D::Colour::White);
	tempHover.setColour(Game2D::Colour::White);
	tempClick.setColour(Game2D::Colour::White);

	join.setRect(tempRect);
	join.addStateSprites(tempNormal,tempHover,tempClick,tempClick,tempNormal);
	join.alignToDrawableObject();

	tempRect = Game2D::Rect(5.5,-26,10,5);
	tempNormal.setTextureCoords(Game2D::Rect(0.500f, 0.1875f, 0.125f, 0.0625f));
	tempHover.setTextureCoords(Game2D::Rect(0.500f, 0.1250f, 0.125f, 0.0625f));
	tempClick.setTextureCoords(Game2D::Rect(0.500f, 0.0625f, 0.125f, 0.0625f));

	tempNormal.setRect(tempRect);
	tempHover.setRect(tempRect);
	tempClick.setRect(tempRect);

	tempNormal.setColour(Game2D::Colour::White);
	tempHover.setColour(Game2D::Colour::White);
	tempClick.setColour(Game2D::Colour::White);

	quit.setRect(tempRect);
	quit.addStateSprites(tempNormal,tempHover,tempClick,tempClick,tempNormal);
	quit.alignToDrawableObject();

	tempRect = Game2D::Rect(-5.5,-26,10,5);

	tempNormal.setTextureCoords(Game2D::Rect(0.625f, 0.1875f, 0.125f, 0.0625f));
	tempHover.setTextureCoords(Game2D::Rect(0.625f, 0.1250f, 0.125f, 0.0625f));
	tempClick.setTextureCoords(Game2D::Rect(0.625f, 0.0625f, 0.125f, 0.0625f));

	tempNormal.setRect(tempRect);
	tempHover.setRect(tempRect);
	tempClick.setRect(tempRect);

	tempNormal.setColour(Game2D::Colour::White);
	tempHover.setColour(Game2D::Colour::White);
	tempClick.setColour(Game2D::Colour::White);

	options.setRect(tempRect);
	options.addStateSprites(tempNormal,tempHover,tempClick,tempClick,tempNormal);
	options.alignToDrawableObject();

	gravity = true;

	resize();
}

void MainMenu::resize()
{
	Game2D::ScreenCoord::alignCentre();
	title.fontSize = 5;
	if(gravity){
		title.text = "n Player Connect x";
	} else {
		title.text = "n Player x Sized Naughts & Crosses";
	}
	title.width = Game2D::Freetype::getLength(Game2D::Font::getFont(title.fontSize), title.text.c_str());

	gravButt.setRect(Game2D::Rect(0,27.5,title.width,6));
	gravButt.alignToDrawableObject();

	version.fontSize = 3;
	version.text = "%d.%d.%d";
	version.width = Game2D::Freetype::getLength(Game2D::Font::getFont(version.fontSize),version.text.c_str(),GameVer.ver,GameVer.verMajor,GameVer.verMinor);
}

void MainMenu::update()
{
}

int MainMenu::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState)
{
	//as the start button is aligned to the right of the screen the mouse coordinats need to be aligned right as well
	Game2D::Pos2 mousePosAlignedRight = Game2D::Pos2((mousePos.x - Game2D::ScreenCoord::getAspectRatio() * 50), mousePos.y);
	if (options.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		return 5;
	}
	if (start.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		return 4;
	}
	if (join.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		return 2;
	}
	if (host.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		return 3;
	}
	if(quit.update(mousePos,mouseState,1) == Game2D::ClickableObject::ClickState::CLICK){
		return 1;
	}
	if(gravButt.update(mousePos,mouseState,1) == Game2D::ClickableObject::ClickState::CLICK){
		gravity = !gravity;
		resize();
		return 6;
	}

	return 0;
}

void MainMenu::draw()
{
	glBindTexture(GL_TEXTURE_2D, mainMenuTex);
	Game2D::Colour(1, 1, 1).draw();

	//gravButt.draw(); //only drawn for debugging
	host.draw();
	join.draw();
	start.draw();
	quit.draw();
	options.draw();
	Game2D::ScreenCoord::alignRight();

	Game2D::Freetype::print(Game2D::Font::getFont(version.fontSize),-1 - version.width , -49 ,version.text.c_str(),GameVer.ver,GameVer.verMajor,GameVer.verMinor);
	Game2D::ScreenCoord::alignCentre();

	Game2D::Freetype::print(Game2D::Font::getFont(title.fontSize), title.width/-2.0f, 25, title.text.c_str());
}