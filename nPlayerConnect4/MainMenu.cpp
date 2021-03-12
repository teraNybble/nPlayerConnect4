#include "MainMenu.h"

void MainMenu::init()
{
	//load the texture
	mainMenuTex = ImageLoder::loadPNG("Images/menu.png");
	//set the sprites colour

	Game2D::Rect tempRect;
	Game2D::Sprite tempNormal, tempHover, tempClick;
	tempRect = Game2D::Rect(0,-14,10,5);

	tempNormal.setTextureCoords(Game2D::Rect(0, 0.375f, 0.25f, 0.125f));
	tempHover.setTextureCoords(Game2D::Rect(0, 0.250f, 0.25f, 0.125f));
	tempClick.setTextureCoords(Game2D::Rect(0, 0.125f, 0.25f, 0.125f));

	tempNormal.setRect(tempRect);
	tempHover.setRect(tempRect);
	tempClick.setRect(tempRect);

	tempNormal.setColour(Game2D::Colour::White);
	tempHover.setColour(Game2D::Colour::White);
	tempClick.setColour(Game2D::Colour::White);

	start.setRect(tempRect);
	start.addStateSprites(tempNormal,tempHover,tempClick,tempClick,tempNormal);
	start.alignToDrawableObject();

	tempRect = Game2D::Rect(5.5,-20,10,5);
	host.setRect(tempRect);

	tempNormal.setTextureCoords(Game2D::Rect(0.25f, 0.375f, 0.25f, 0.125f));
	tempHover.setTextureCoords(Game2D::Rect(0.25f, 0.25f, 0.25f, 0.125f));
	tempClick.setTextureCoords(Game2D::Rect(0.25f, 0.125f, 0.25f, 0.125f));

	tempNormal.setRect(tempRect);
	tempHover.setRect(tempRect);
	tempClick.setRect(tempRect);

	host.addStateSprites(tempNormal,tempHover,tempClick,tempClick,tempNormal);
	host.alignToDrawableObject();

	tempRect = Game2D::Rect(-5.5,-20,10,5);
	tempNormal.setTextureCoords(Game2D::Rect(0.50f, 0.375f, 0.25f, 0.125f));
	tempHover.setTextureCoords(Game2D::Rect(0.50f, 0.25f, 0.25f, 0.125f));
	tempClick.setTextureCoords(Game2D::Rect(0.50f, 0.125f, 0.25f, 0.125f));

	tempNormal.setRect(tempRect);
	tempHover.setRect(tempRect);
	tempClick.setRect(tempRect);

	tempNormal.setColour(Game2D::Colour::White);
	tempHover.setColour(Game2D::Colour::White);
	tempClick.setColour(Game2D::Colour::White);

	join.setRect(tempRect);
	join.addStateSprites(tempNormal,tempHover,tempClick,tempClick,tempNormal);
	join.alignToDrawableObject();

	tempRect = Game2D::Rect(0,-26,10,5);
	tempNormal.setTextureCoords(Game2D::Rect(0.75f, 0.875f, 0.25f, 0.125f));
	tempHover.setTextureCoords(Game2D::Rect(0.75f, 0.75f, 0.25f, 0.125f));
	tempClick.setTextureCoords(Game2D::Rect(0.75f, 0.625f, 0.25f, 0.125f));

	tempNormal.setRect(tempRect);
	tempHover.setRect(tempRect);
	tempClick.setRect(tempRect);

	tempNormal.setColour(Game2D::Colour::White);
	tempHover.setColour(Game2D::Colour::White);
	tempClick.setColour(Game2D::Colour::White);

	quit.setRect(tempRect);
	quit.addStateSprites(tempNormal,tempHover,tempClick,tempClick,tempNormal);
	quit.alignToDrawableObject();

	resize();
}

void MainMenu::resize()
{
	Game2D::ScreenCoord::alignCentre();
	title.fontSize = 5;
	title.text = "n Player Connect 4";
	title.width = freetype::getLength(Game2D::Font::getFont(title.fontSize), title.text.c_str());

	version.fontSize = 3;
	version.text = "%d.%d.%d";
	version.width = freetype::getLength(Game2D::Font::getFont(version.fontSize),version.text.c_str(),GameVer.ver,GameVer.verMajor,GameVer.verMinor);
}

void MainMenu::update()
{
}

int MainMenu::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState)
{
	//as the start button is aligned to the right of the screen the mouse coordinats need to be aligned right as well
	Game2D::Pos2 mousePosAlignedRight = Game2D::Pos2((mousePos.x - Game2D::ScreenCoord::getAspectRatio() * 50), mousePos.y);
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

	return 0;
}

void MainMenu::draw()
{
	glBindTexture(GL_TEXTURE_2D, mainMenuTex);
	Game2D::Colour(1, 1, 1).draw();

	host.draw();
	join.draw();
	start.draw();
	quit.draw();
	Game2D::ScreenCoord::alignRight();

	freetype::print(Game2D::Font::getFont(version.fontSize),-1 - version.width , -49 ,version.text.c_str(),GameVer.ver,GameVer.verMajor,GameVer.verMinor);
	Game2D::ScreenCoord::alignCentre();

	freetype::print(Game2D::Font::getFont(title.fontSize), title.width/-2.0f, 25, title.text.c_str());
}