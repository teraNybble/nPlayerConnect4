#include "OptionsMenu.h"

void OptionsMenu::setResolutions(float ratio)
{
	if (ratio == (float)(4.0 / 3.0)) {
		//4:3
		resolutions.clear();
		resolutions.addLastItemCopy("640 x 480");
		resolutions.addLastItemCopy("800 x 600");
		resolutions.addLastItemCopy("1024 x 768");
		resolutions.addLastItemCopy("1152 x 864");
		resolutions.addLastItemCopy("1280 x 960");
		resolutions.addLastItemCopy("1280 x 1024");
	} else if (ratio == (float)(16.0 / 9.0)) {
		//16:9
		resolutions.clear();
		resolutions.addLastItemCopy("1280 x 720");
		resolutions.addLastItemCopy("1366 x 768");
		resolutions.addLastItemCopy("1600 x 900");
		resolutions.addLastItemCopy("1920 x 1080");
	}
}

void OptionsMenu::init()
{
	play = Game2D::Button(Game2D::Rect(0, -10, 20, 10));
	apply = Game2D::Button(Game2D::Rect(-15, -40, 20, 10));
	back = Game2D::Button(Game2D::Rect(20, -40, 20, 10));

	Game2D::Rect texRect(Game2D::Rect(0, 0, 0.125f, 0.0625f));

	Game2D::AnimatedSprite playSprites(Game2D::Rect(0, -10, 20, 10));
	for (int i = 3; i >= 0; i--) {
		Game2D::Sprite tempSprite(Game2D::Rect(0, -10, 20, 10));
		tempSprite.setColour(Game2D::Colour::White);
		Game2D::Rect tempRect = texRect;
		//the play buton is the 4th sprite along
		tempRect.pos.x = 3 * texRect.width;
		tempRect.pos.y = i * texRect.height;
		tempSprite.setTextureCoords(tempRect);
		playSprites.addFrame(tempSprite);
	}
	playSprites.setFrameTime(0);
	//what frame of the animation each state starts at
	int temp[5] = { 0,1,2,3,4 };
	play.addAnims(playSprites, temp);

	Game2D::AnimatedSprite backSprites(Game2D::Rect(20, -40, 10, 5));
	for (int i = 3; i >= 0; i--) {
		Game2D::Sprite tempSprite(Game2D::Rect(20, -40, 10, 5));
		tempSprite.setColour(Game2D::Colour::White);
		Game2D::Rect tempRect = texRect;
		//the back buton is the 1st sprite along on the second row
		tempRect.pos.x = 3 * texRect.width;
		tempRect.pos.y = i * texRect.height;
		tempSprite.setTextureCoords(tempRect);
		backSprites.addFrame(tempSprite);
	}
	backSprites.setFrameTime(0);
	int tempFrames[5] = { 4,1,2,3,3 };

	back.addAnims(backSprites, tempFrames);

	Game2D::AnimatedSprite applySprites(Game2D::Rect(-15, -40, 10, 5));
	for (int i = 3; i >= 0; i--) {
		Game2D::Sprite tempSprite(Game2D::Rect(-15, -40, 10, 5));
		tempSprite.setColour(Game2D::Colour::White);
		Game2D::Rect tempRect = texRect;
		//the back buton is the 1st sprite along on the second row
		tempRect.pos.x = 6 * texRect.width;
		tempRect.pos.y = i * texRect.height;
		tempSprite.setTextureCoords(tempRect);
		applySprites.addFrame(tempSprite);
	}
	applySprites.setFrameTime(0);

	apply.addAnims(applySprites, tempFrames);
	Game2D::Rect tempRect = Game2D::Rect(-10, 10, 25, 5);
	Game2D::AnimatedSprite resolutionSprite(tempRect);
	for (int i = 0; i < 4; i++) {
		Game2D::Colour colourArr[4] = { Game2D::Colour::White, Game2D::Colour(0.90f,0.95f,1.0f), Game2D::Colour(0.90f,0.93f,0.95f), Game2D::Colour::White };
		Game2D::Sprite tempSptrie(tempRect);
		tempSptrie.setColour(colourArr[i]);
		resolutionSprite.addFrame(tempSptrie);
	}
	resolutionSprite.setFrameTime(0);

	resolutions = Game2D::Dropdown(tempRect);
	resolutions.addAnims(resolutionSprite, temp);
	resolutions.setFontSize(3);
	resolutions.addLastItemCopy("1280 x 720");
	resolutions.addLastItemCopy("1366 x 768");
	resolutions.addLastItemCopy("1600 x 900");
	resolutions.addLastItemCopy("1920 x 1080");

	tempRect = Game2D::Rect(-40, 10, 25, 5);
	Game2D::AnimatedSprite aspectSprite(tempRect);
	for (int i = 0; i < 4; i++) {
		Game2D::Colour colourArr[4] = { Game2D::Colour::White, Game2D::Colour(0.90f,0.95f,1.0f), Game2D::Colour(0.90f,0.93f,0.95f), Game2D::Colour::White };
		Game2D::Sprite tempSptrie(tempRect);
		tempSptrie.setColour(colourArr[i]);
		aspectSprite.addFrame(tempSptrie);
	}
	aspectSprite.setFrameTime(0);

	aspectRatio = Game2D::Dropdown(tempRect);
	aspectRatio.addAnims(aspectSprite, temp);
	aspectRatio.setFontSize(3);
	aspectRatio.addLastItemCopy("4:3");
	aspectRatio.addLastItemCopy("16:9");

	if (Game2D::ScreenCoord::getAspectRatio() == 4.0f/3.0f) {
		aspectRatio.setSelectedItem(0);
		setResolutions(4.0 / 3.0);
	} else {
		aspectRatio.setSelectedItem(1);
		setResolutions(16.0 / 9.0);
	}
	resolutions.setText(std::to_string(Game2D::ScreenCoord::getWidth()) + " x " +
						std::to_string(Game2D::ScreenCoord::getHeight()));


	tempRect = Game2D::Rect(20,10,5,5);
	colourblind.setRect(tempRect);

	texRect = Game2D::Rect(0,0,0.0625f,0.0625f);

	Game2D::AnimatedSprite checkBoxSprites(tempRect);
	for (int i = 0; i < 3; i++) {
		Game2D::Sprite tempSprite(tempRect);
		tempSprite.setColour(Game2D::Colour::White);
		Game2D::Rect tempRect = texRect;
		//the back buton is the 1st sprite along on the second row
		tempRect.pos.x = (i+6) * texRect.width;
		tempRect.pos.y = 0 * texRect.height;
		tempSprite.setTextureCoords(tempRect);
		checkBoxSprites.addFrame(tempSprite);
	}
	checkBoxSprites.setFrameTime(0);

	colourblind.setUncheckedSprites(checkBoxSprites);

	Game2D::AnimatedSprite checkBoxSprites2(tempRect);
	for (int i = 0; i < 3; i++) {
		Game2D::Sprite tempSprite(tempRect);
		tempSprite.setColour(Game2D::Colour::White);
		Game2D::Rect tempRect = texRect;
		//the back buton is the 1st sprite along on the second row
		tempRect.pos.x = (i+9) * texRect.width;
		tempRect.pos.y = 0 * texRect.height;
		tempSprite.setTextureCoords(tempRect);
		checkBoxSprites2.addFrame(tempSprite);
	}
	checkBoxSprites2.setFrameTime(0);
//	checkBoxSprites.getSize();

	colourblind.setCheckedSprites(checkBoxSprites2);
	colourblind.setPartialcheckedSprites(checkBoxSprites2);
	colourblind.reset();
	colourblind.setState(Options::showPlayerNums);

	returnState = -1;
}

void OptionsMenu::resize()
{

}

void OptionsMenu::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState)
{
	Game2D::Pos2 leftMousePos = mousePos;
	leftMousePos.x += (50 * Game2D::ScreenCoord::getAspectRatio());
	Game2D::Pos2 rightMousePos = mousePos;
	rightMousePos.x -= (50 * Game2D::ScreenCoord::getAspectRatio());
	back.update(leftMousePos, mouseState, 1);
	apply.update(rightMousePos, mouseState, 1);
	resolutions.update(mousePos, mouseState, 1);
	aspectRatio.update(mousePos, mouseState, 1);
	colourblind.update(mousePos,mouseState,1);
	//std::cout << "\n";
}

int OptionsMenu::getResult(void(resize(float, float)))
{
	if (back.getState() == Game2D::ClickableObject::CLICK)		return 2;
	if (apply.getState() == Game2D::ClickableObject::CLICK) {
		Options::showPlayerNums = colourblind.getState();
		std::string res = resolutions.getText();
		std::string w = res.substr(0, res.find("x"));
		std::string h = res.substr(res.find("x")+1, res.size()-1);
		resize(std::stoi(w), std::stoi(h));
	}
	if (aspectRatio.getSelectedItem() != previousAspect) {
		previousAspect = aspectRatio.getSelectedItem();
		switch (previousAspect)//tecnically current aspect but this saves a function call
		{
			case 0:
				//4:3
				setResolutions(4.0 / 3.0);
				break;
			case 1:
				//16:9
				setResolutions(16.0 / 9.0);
				break;
			case 2:
				//N/A
				break;
		}
	}

	return 0;
}

void OptionsMenu::draw()
{
	glBindTexture(GL_TEXTURE_2D, TextureManager::getTexture(0));

	Game2D::ScreenCoord::alignLeft();
	back.draw();
	Game2D::ScreenCoord::alignRight();
	apply.draw();
	Game2D::ScreenCoord::alignCentre();
	colourblind.draw();

	resolutions.draw();
	aspectRatio.draw();

	Game2D::Colour::White.draw();
	Game2D::Freetype::print(Game2D::Font::getFont(2),25,10-(Game2D::Freetype::getHeight(Game2D::Font::getFont(2))/4.0f),"Show player number over pieces");
}