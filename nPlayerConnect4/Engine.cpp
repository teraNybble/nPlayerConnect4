#include "Engine.h"
#include <iostream>
#include <iomanip>

GLFWwindow* Engine::window;
int Engine::screenWidth = 1280;
int Engine::screenHeight = 720;
Board Engine::board;
MainMenu Engine::mainMenu;
Game2D::Pos2 Engine::mousePos;
Game2D::KeyState::State Engine::mouseState;
Engine::State Engine::currentState;
unsigned int Engine::winningPlayer;

Engine::Engine()
{
	//screenWidth = 1280;
	//screenHeight = 720;
}

void Engine::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

void Engine::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	/*if(mouseState == Game2D::KeyState::State::RELEASED){
		mouseState = Game2D::KeyState::State::UP;
	}*/
	if(button == GLFW_MOUSE_BUTTON_LEFT){
		if(action == GLFW_PRESS){
			mouseState = Game2D::KeyState::State::DOWN;
			//std::cout << "leftdown\n";
		}
		else if(action == GLFW_RELEASE){
			//std::cout << "leftup\n";
			if(mouseState == Game2D::KeyState::State::DOWN) {
				mouseState = Game2D::KeyState::State::RELEASED;
			}
			else{
				mouseState = Game2D::KeyState::State::UP;
			}
		}
	}
}

void Engine::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	//(((xpos - ((screenWidth - screenHeight) / 2.0f)) / screenHeight)*100.0f) - 50.0f
	mousePos = Game2D::Pos2(
			(((xpos - ((screenWidth - screenHeight) / 2.0f)) / screenHeight)*100.0f) - 50.0f,
			-(((ypos / screenHeight)*100)-50));
}

void Engine::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.118f, 0.118f, 0.118f,1.0f);
	//glClearColor(1, 1, 0.118f, 1.0f);

	glLoadIdentity();

	Game2D::Sprite temp;

	//draw stuff goes hear
	switch (currentState)
	{
	case Engine::MENU:
		mainMenu.draw();
		break;
	case Engine::WIN:
		board.draw();
		temp.setColour(Game2D::Colour(0, 0, 0, 0.5));
		temp.setRect(Game2D::Rect(0, 0, 400, 400));
		temp.draw();
		Game2D::Colour(1, 1, 1).draw();
		freetype::print(Font::getFont(40), (((((screenWidth - screenHeight) / 2.0f)) / screenHeight) * 100.0f) - 63.5f, 20, "Player %d wins!", winningPlayer + 1);
		break;
	case Engine::PLAYING:
		board.draw();
		break;
	case Engine::EXIT:
		break;
	default:
		break;
	}
	//board.draw();
	//mainMenu.draw();

	glDisable(GL_BLEND);
	glFlush();
}

void Engine::init()
{
	//set callbacks
	glfwSetCursorPosCallback(window,mouseCallback);
	glfwSetKeyCallback(window,keyCallback);
	glfwSetMouseButtonCallback(window,mouseButtonCallback);

	mouseState = Game2D::KeyState::State::UP;

	std::vector<Game2D::Colour> playerColours = {
		Game2D::Colour::Red, Game2D::Colour::Yellow,
		Game2D::Colour::Green, Game2D::Colour::Blue,
		Game2D::Colour::Cyan, Game2D::Colour::Magenta,
	};

	board.setBoardDims(7,6);
	board.setPlayerColours(playerColours);
	board.initBoard();
	mainMenu.init();


	Font::init(screenHeight);
	Font::insert(40);
	Font::insert(36);
	Font::insert(30);
	Font::insert(26);
	Font::initFonts();


	ScreenCoord::init(screenWidth, screenHeight);
}

void Engine::processKeys()
{

}

void Engine::processMouse()
{
	switch (currentState)
	{
	case Engine::MENU:
		switch (mainMenu.processMouse(mousePos, mouseState)) {
		case 1:
			board.setNumPlayers(mainMenu.getNumPlayers());
			board.setLineLength(4);
			board.setBoardDims(mainMenu.getBoardWidth(), mainMenu.getBoardHeight());
			board.initBoard();//reset the board
			currentState = PLAYING;
			break;
		}
		break;
	case Engine::PLAYING:
		switch (board.processMouse(mousePos,mouseState,winningPlayer))
		{
		case 1:
			std::cout << "WIN\n";
			currentState = WIN;
			break;
		}
		break;
	case Engine::WIN:
		if (mouseState == Game2D::KeyState::DOWN) {
			currentState = MENU;
		}
		break;
	case Engine::EXIT:
		break;
	default:
		break;
	}
	//std::cout << currentState << "\n";
}

void Engine::update()
{
	if(mouseState == Game2D::KeyState::State::RELEASED) {
		mouseState = Game2D::KeyState::State::UP;
	}
}

bool Engine::createWindow()
{
	if (!glfwInit())
	{
		std::cerr << "failed to init glfw with error: 0x" << std::hex << std::setw(8) << std::setfill('0') << glfwGetError(NULL) << "\n";
		return false;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(screenWidth, screenHeight, "N Player Connect 4", NULL, NULL);
	if (!window)
	{
		std::cerr << "failed to create window\n";
		glfwTerminate();
		return false;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	ScreenCoord::init(screenWidth, screenHeight);
	ScreenCoord::alignCentre();
	//ScreenCoord::alignLeft();

	/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//set screen coords
	//glOrtho(0, 100.0f * (screenWidth / (float)screenHeight), 0, 100, 0, 100);
	glOrtho(((-50.0f * (screenWidth / (float)screenHeight))), ((50.0f * (screenWidth / (float)screenHeight))), -50, 50, 0, 100);
	//ScreenCoord::alignCentre();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/
	//TODO add in input class
	//input.setWindow(window);
	return true;

}

int Engine::mainLoop()
{
	if(!createWindow())
		return -1;

	glfwSwapInterval(1);

	init();

	while(!glfwWindowShouldClose(window))
	{
		//lastCycleTime = gameTimer.restartTimer();
		glClear(GL_COLOR_BUFFER_BIT);
		display();

		glfwSwapBuffers(window);

		update();
		//update glfw's mouse and keyboard events
		glfwPollEvents();
		processKeys();
		processMouse();

		//if(currentState == QUITTING) break;
	}

	glfwTerminate();
	return 0;
}