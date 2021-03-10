#include "MainMenu.h"

void MainMenu::init()
{
	//load the texture
	mainMenuTex = ImageLoder::loadPNG("Images/menu.png");
	//set the sprites colour
	arrow.setColour(Game2D::Colour::White);
	arrowHover.setColour(Game2D::Colour::White);
	arrowClick.setColour(Game2D::Colour::White);
	//set the texture coords
	arrow.setTextureCoords(Game2D::Rect(0, 0, 0.125f, 0.125f));
	arrowHover.setTextureCoords(Game2D::Rect(0.125f, 0, 0.125f, 0.125f));
	arrowClick.setTextureCoords(Game2D::Rect(0.250f, 0, 0.125f, 0.125f));

	//set the sprites sizes an positions
	arrow.setRect(Game2D::Rect(-35, -40, 5, 5));
	arrowHover.setRect(Game2D::Rect(-35, -40, 5, 5));
	arrowClick.setRect(Game2D::Rect(-35, -40, 5, 5));

	playersPlus.setRect(Game2D::Rect(-35,-40,5,5));
	playersPlus.addStateSprites(arrow,arrowHover,arrowClick,arrowClick,arrow);
	playersPlus.alignToDrawableObject();

	arrow.setPos(Game2D::Pos2(1, -40));
	arrowHover.setPos(Game2D::Pos2(1, -40));
	arrowClick.setPos(Game2D::Pos2(1, -40));

	boardWidthPlus.setRect(Game2D::Rect(1, -40, 5, 5));
	boardWidthPlus.addStateSprites(arrow, arrowHover, arrowClick, arrowClick, arrow);
	boardWidthPlus.alignToDrawableObject();

	arrow.setPos(Game2D::Pos2(-41, -40));
	arrowHover.setPos(Game2D::Pos2(-41, -40));
	arrowClick.setPos(Game2D::Pos2(-41, -40));

	arrow.flipX();
	arrowHover.flipX();
	arrowClick.flipX();

	playersMinus.setRect(Game2D::Rect(-41, -40, 5, 5));
	playersMinus.addStateSprites(arrow, arrowHover, arrowClick, arrowClick, arrow);
	playersMinus.alignToDrawableObject();

	arrow.setPos(Game2D::Pos2(-5, -40));
	arrowHover.setPos(Game2D::Pos2(-5, -40));
	arrowClick.setPos(Game2D::Pos2(-5, -40));

	boardWidthMinus.setRect(Game2D::Rect(-5, -40, 5, 5));
	boardWidthMinus.addStateSprites(arrow, arrowHover, arrowClick, arrowClick, arrow);
	boardWidthMinus.alignToDrawableObject();

	arrow.rotate(90);
	arrowHover.rotate(90);
	arrowClick.rotate(90);

	arrow.setPos(Game2D::Pos2(12, -34));
	arrowHover.setPos(Game2D::Pos2(12, -34));
	arrowClick.setPos(Game2D::Pos2(12, -34));

	boardHeightMinus.setRect(Game2D::Rect(12, -34, 5, 5));
	boardHeightMinus.addStateSprites(arrow, arrowHover, arrowClick, arrowClick, arrow);
	boardHeightMinus.alignToDrawableObject();

	arrow.setPos(Game2D::Pos2(12, -28));
	arrowHover.setPos(Game2D::Pos2(12, -28));
	arrowClick.setPos(Game2D::Pos2(12, -28));

	arrow.flipX();
	arrowHover.flipX();
	arrowClick.flipX();

	boardHeightPlus.setRect(Game2D::Rect(12, -28, 5, 5));
	boardHeightPlus.addStateSprites(arrow, arrowHover, arrowClick, arrowClick, arrow);
	boardHeightPlus.alignToDrawableObject();

	numPlayers = 2;

	Game2D::Rect tempRect;

	startSprite.setTextureCoords(Game2D::Rect(0, 0.375f, 0.25f, 0.125f));
	startHover.setTextureCoords(Game2D::Rect(0, 0.250f, 0.25f, 0.125f));
	startClick.setTextureCoords(Game2D::Rect(0, 0.125f, 0.25f, 0.125f));

	startSprite.setRect(Game2D::Rect(-15, -40, 10, 5));
	startHover.setRect(Game2D::Rect(-15, -40, 10, 5));
	startClick.setRect(Game2D::Rect(-15, -40, 10, 5));

	startSprite.setColour(Game2D::Colour::White);
	startHover.setColour(Game2D::Colour::White);
	startClick.setColour(Game2D::Colour::White);

	start.setRect(Game2D::Rect(-15, -40, 10, 5));
	start.addStateSprites(startSprite,startHover,startClick,startClick,startSprite);
	start.alignToDrawableObject();

	tempRect = Game2D::Rect(-15,-25,10,5);
	host.setRect(tempRect);

	//borrowing the start sprite for the host button sprites
	startSprite.setTextureCoords(Game2D::Rect(0.25f, 0.375f, 0.25f, 0.125f));
	startHover.setTextureCoords(Game2D::Rect(0.25f, 0.25f, 0.25f, 0.125f));
	startClick.setTextureCoords(Game2D::Rect(0.25f, 0.125f, 0.25f, 0.125f));

	startSprite.setRect(tempRect);
	startHover.setRect(tempRect);
	startClick.setRect(tempRect);

	host.addStateSprites(startSprite,startHover,startClick,startClick,startSprite);
	host.alignToDrawableObject();

	tempRect = Game2D::Rect(-15,-10,10,5);
	Game2D::Sprite tempNormal, tempHover, tempClick;
	//borrowing the start sprites for the join button sprites
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
	//join.addStateSprites(startSprite,startHover,startClick,startClick,startSprite);
	join.alignToDrawableObject();

	//font.init("C:/Windows/Fonts/arial.ttf", 36);
	lineLength = 4;
	boardWidth = 7;
	boardHeight = 6;

	resize();
}

void MainMenu::resize()
{
	Game2D::ScreenCoord::alignCentre();
	//TextInfo title;
	title.fontSize = 5;
	title.text = "N player connect 4";
	title.width = freetype::getLength(Game2D::Font::getFont(title.fontSize), title.text.c_str());
	//freetype::print(Font::getFont(26), -50, -20, "No. Players");
	noPlayers.fontSize = 4;
	noPlayers.text = "No. Players";
	noPlayers.width = freetype::getLength(Game2D::Font::getFont(noPlayers.fontSize), noPlayers.text.c_str());
	//freetype::print(Font::getFont(26), -10, -20, "Board size");
	boardDims.fontSize = 4;
	boardDims.text = "Board size";
	boardDims.width = freetype::getLength(Game2D::Font::getFont(boardDims.fontSize), boardDims.text.c_str());

	playerCount.fontSize = 4;
	playerCount.text = "%d";
	playerCount.width = freetype::getLength(Game2D::Font::getFont(playerCount.fontSize), playerCount.text.c_str(),numPlayers);

	boardDimLabels.fontSize = 4;
	boardDimLabels.text = "%d x %d";
	boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize), boardDimLabels.text.c_str(), boardWidth, boardHeight);

}

void MainMenu::update()
{
}

int MainMenu::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState)
{
	if(playersPlus.update(mousePos,mouseState,1) == Game2D::ClickableObject::ClickState::CLICK){
		numPlayers++;
		playerCount.width = freetype::getLength(Game2D::Font::getFont(playerCount.fontSize), playerCount.text.c_str(), numPlayers);
		//std::cout << playerCount.width << "\n";
	}
	if(playersMinus.update(mousePos,mouseState,1) == Game2D::ClickableObject::ClickState::CLICK) {
		if(--numPlayers < 2){
			numPlayers = 2;
		}
		playerCount.width = freetype::getLength(Game2D::Font::getFont(playerCount.fontSize), playerCount.text.c_str(), numPlayers);
		//std::cout << playerCount.width << "\n";
	}
	if (boardWidthPlus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		boardWidth++;
		boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize), boardDimLabels.text.c_str(), boardWidth, boardHeight);
	}
	if (boardWidthMinus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		if (--boardWidth < lineLength) {
			boardWidth = lineLength;
		}
		boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize), boardDimLabels.text.c_str(), boardWidth, boardHeight);
	}
	if (boardHeightPlus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		boardHeight++;
		boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize), boardDimLabels.text.c_str(), boardWidth, boardHeight);
	}
	if (boardHeightMinus.update(mousePos, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		if (--boardHeight < lineLength) {
			boardHeight = lineLength;
		}
		boardDimLabels.width = freetype::getLength(Game2D::Font::getFont(boardDimLabels.fontSize), boardDimLabels.text.c_str(), boardWidth, boardHeight);
	}
	//as the start button is aligned to the right of the screen the mouse coordinats need to be aligned right as well
	Game2D::Pos2 mousePosAlignedRight = Game2D::Pos2((mousePos.x - Game2D::ScreenCoord::getAspectRatio() * 50), mousePos.y);
	if (start.update(mousePosAlignedRight, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		return 4;
	}
	if (join.update(mousePosAlignedRight, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		return 2;
	}
	if (host.update(mousePosAlignedRight, mouseState, 1) == Game2D::ClickableObject::ClickState::CLICK) {
		return 3;
	}

	return 0;
}

void MainMenu::draw()
{
	glBindTexture(GL_TEXTURE_2D, mainMenuTex);
	//std::cout << "drawing\n";
	Game2D::Colour(1, 1, 1).draw();
	playersMinus.draw();
	playersPlus.draw();

	boardWidthPlus.draw();
	boardWidthMinus.draw();
	boardHeightPlus.draw();
	boardHeightMinus.draw();

	Game2D::ScreenCoord::alignRight();
	start.draw();
	host.draw();
	join.draw();

	Game2D::ScreenCoord::alignCentre();

	//Game2D::Colour(0, 0, 0).draw();
	//std::cout << noPlayers.width << "\t" << (noPlayers.width / -2.0f) << "\n";
	freetype::print(Game2D::Font::getFont(playerCount.fontSize),(playerCount.width / -2.0f) - 38, -35, playerCount.text.c_str(), numPlayers);
	freetype::print(Game2D::Font::getFont(boardDimLabels.fontSize), (boardDimLabels.width/-2.0f)-2, -33.5, boardDimLabels.text.c_str(), boardWidth,boardHeight);
	freetype::print(Game2D::Font::getFont(noPlayers.fontSize), (noPlayers.width/-2.0f)-38, -20, noPlayers.text.c_str());
	freetype::print(Game2D::Font::getFont(boardDims.fontSize), (boardDims.width/-2.0f)+1, -20, boardDims.text.c_str());
	//std::cout << title.width << "\t" << title.width / -2.0f << "\n";
	//std::cout << freetype::getLength(Font::getFont(title.fontSize), title.text.c_str()) << "\n";
	//freetype::print(Font::getFont(title.fontSize), -30, 25, title.text.c_str());
	freetype::print(Game2D::Font::getFont(title.fontSize), title.width/-2.0f, 25, title.text.c_str());
}