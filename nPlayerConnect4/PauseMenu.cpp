#include "PauseMenu.h"

void PauseMenu::init()
{
	Game2D::Rect tempRect;
	Game2D::Sprite tempNormal, tempHover, tempClick, tempDisable;

	tempRect = Game2D::Rect(0,-22,10,5);
	tempNormal.setTextureCoords(Game2D::Rect(0.500f, 0.1875f, 0.125f, 0.0625f));
	tempHover.setTextureCoords(Game2D::Rect(0.500f, 0.1250f, 0.125f, 0.0625f));
	tempClick.setTextureCoords(Game2D::Rect(0.500f, 0.0625f, 0.125f, 0.0625f));

	tempNormal.setRect(tempRect);
	tempHover.setRect(tempRect);
	tempClick.setRect(tempRect);

	tempNormal.setColour(Game2D::Colour::White);
	tempHover.setColour(Game2D::Colour::White);
	tempClick.setColour(Game2D::Colour::White);
	tempDisable.setColour(Game2D::Colour::White);

	quit.setRect(tempRect);
	quit.addStateSprites(tempNormal,tempHover,tempClick,tempClick,tempNormal);
	quit.alignToDrawableObject();

	tempRect = Game2D::Rect(0,-16,10,5);

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

	tempRect = Game2D::Rect(0,-10,10,5);

	tempDisable.setTextureCoords(Game2D::Rect(0.875f, 0.2500f, 0.125f, 0.0625f));
	tempNormal.setTextureCoords(Game2D::Rect(0.875f, 0.1875f, 0.125f, 0.0625f));
	tempHover.setTextureCoords(Game2D::Rect(0.875f, 0.1250f, 0.125f, 0.0625f));
	tempClick.setTextureCoords(Game2D::Rect(0.875f, 0.0625f, 0.125f, 0.0625f));

	tempDisable.setRect(tempRect);
	tempNormal.setRect(tempRect);
	tempHover.setRect(tempRect);
	tempClick.setRect(tempRect);

	tempNormal.setColour(Game2D::Colour::White);
	tempHover.setColour(Game2D::Colour::White);
	tempClick.setColour(Game2D::Colour::White);

	back.setRect(tempRect);
	back.addStateSprites(tempNormal,tempHover,tempClick,tempClick,tempDisable);
	back.alignToDrawableObject();

	tempRect = Game2D::Rect(0,-4,10,5);

	tempNormal.setTextureCoords(Game2D::Rect(0.375f, 0.1875f, 0.125f, 0.0625f));
	tempHover.setTextureCoords(Game2D::Rect(0.375f, 0.1250f, 0.125f, 0.0625f));
	tempClick.setTextureCoords(Game2D::Rect(0.375f, 0.0625f, 0.125f, 0.0625f));

	tempNormal.setRect(tempRect);
	tempHover.setRect(tempRect);
	tempClick.setRect(tempRect);

	tempNormal.setColour(Game2D::Colour::White);
	tempHover.setColour(Game2D::Colour::White);
	tempClick.setColour(Game2D::Colour::White);

	resume.setRect(tempRect);
	resume.addStateSprites(tempNormal,tempHover,tempClick,tempClick,tempNormal);
	resume.alignToDrawableObject();
}

void PauseMenu::resize()
{
	//
}

int PauseMenu::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState)
{
	if(resume.update(mousePos,mouseState,1) == Game2D::ClickableObject::CLICK){
		return 1;
	}
	if(options.update(mousePos,mouseState,1) == Game2D::ClickableObject::CLICK){
		return 2;
	}
	if(quit.update(mousePos,mouseState,1) == Game2D::ClickableObject::CLICK){
		return 3;
	}
	if(back.update(mousePos,mouseState,1) == Game2D::ClickableObject::CLICK){
		return 4;
	}

	return 0;
}

void PauseMenu::draw() const
{
	glBindTexture(GL_TEXTURE_2D,TextureManager::getTexture(0));
	Game2D::Sprite tempSprite(Game2D::Rect(0, 0, 200, 200));
	tempSprite.setColour(Game2D::Colour(0, 0, 0, 0.5f));
	tempSprite.draw();
	//draw the pause menu buttons
	resume.draw();
	back.draw();
	options.draw();
	quit.draw();
	Game2D::Colour::White.draw();
	float width = Game2D::Freetype::getLength(Game2D::Font::getFont(5), "Paused");
	Game2D::Freetype::print(Game2D::Font::getFont(5), -width / 2.0, 35, "Paused");

}