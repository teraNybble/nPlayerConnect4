#include "Button.h"
#include "freetype.h"
#include "Fonts.h"
using namespace Game2D;

Button::Button() : ClickableObject()
{
	Button(Rect(0, 0, 0, 0));
}

Button::Button(Rect r) : ClickableObject(r)
{
	currentFrame = newFrame = 0;
	for (int i = 0; i < 5; i++)
		stateFrames[i] = 0;

	id = -1;

	text = "";
	fontSize = 0;
	fontColour = Colour(0, 0, 0);
	alignToDrawableObject();
}

void Button::fillFrameArray(int* a)
{
	for (int i = 0; i < 5; i++) {
		stateFrames[i] = a[i];
	}
}

void Button::addAnims(AnimatedSprite anims, int* stateFrames)
{
	buttonAnims.clearFrames();
	buttonAnims = anims;
	fillFrameArray(stateFrames);
	currentFrame = newFrame = stateFrames[getState()];

	buttonAnims.setFrame(currentFrame);
}

void Button::addStateSprites(Sprite none, Sprite hover, Sprite mouseDown, Sprite click, Sprite disable)
{
	buttonAnims.clearFrames();
	buttonAnims.setElapsedTimeToZero();

	buttonAnims.addFrame(disable);
	buttonAnims.addFrame(none);
	buttonAnims.addFrame(hover);
	buttonAnims.addFrame(mouseDown);
	buttonAnims.addFrame(click);

	//as there is no animation the sprites are located sequentially
	for(int i = 0; i < 5; i++)
		stateFrames[i] = i;

	currentFrame = newFrame = stateFrames[getState()];
}

ClickableObject::ClickState Button::update(Pos2 mousePos, KeyState::State state, float time)
{
	ClickState temp = ClickableObject::update(mousePos, state);
	currentFrame = buttonAnims.getFrame();
	newFrame = stateFrames[temp];

	if(newFrame == currentFrame)
	{
		buttonAnims.pause();
		/*might be needed to stop the elapsed time variable being wildly incorrect
		  despite all the code that sets it to zero*/
		buttonAnims.update(time);
	}
	else if(newFrame > currentFrame)
	{
		//advance until we reach the new frame
		buttonAnims.setPlayDirection(Forward);
		buttonAnims.play();
		buttonAnims.update(time);
	}
	else if(newFrame < currentFrame)
	{
		//rewind until we reach the new frame
		buttonAnims.setPlayDirection(Backward);
		buttonAnims.play();
		buttonAnims.update(time);
	}
	return  temp;
}

void Button::draw() const
{
	buttonAnims.draw();
	if (fontSize > 0) {
		fontColour.draw();
		//std::cout << getClickRegion().height << "\t";
		//std::cout << freetype::getHeight(Font::getFont(fontSize)) << "\t";
		//std::cout << (getClickRegion().height - freetype::getHeight(Font::getFont(fontSize))) << "\n";
		//std::cout << ((getClickRegion().height - freetype::getHeight(Font::getFont(fontSize))) / 2.0f) << "\n";
		//std::cout << (getClickRegion().height - (freetype::getHeight(Font::getFont(fontSize))) / 2.0f) << "\n";
		freetype::print(Font::getFont(fontSize), getClickRegion().pos.x, getClickRegion().pos.y + ((getClickRegion().height - freetype::getHeight(Font::getFont(fontSize))) / (1.0f/2.0f)), text.c_str());
	}
}