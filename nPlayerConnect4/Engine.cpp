#include "Engine.h"
#include <iostream>
#include <iomanip>
#include "TextureManager.h"

GLFWwindow* Engine::window;
int Engine::screenWidth = 1280;
int Engine::screenHeight = 720;
Game2D::Pos2 Engine::mousePos;
Game2D::KeyState::State Engine::mouseState;
Game2D::KeyState::State Engine::escState;
Engine::State Engine::currentState;
MainMenu Engine::mainMenu;
ConnectMenu Engine::connectMenu;
SinglePlayerMenu Engine::singlePlayerMenu;
OptionsMenu Engine::optionsMenu;
Board Engine::singlePlayerBoard;
unsigned int Engine::winningPlayer;
Game2D::Colour Engine::playerColour;
Client* Engine::client;
uint16_t Engine::serverPort;
bool Engine::serverLoop;
bool Engine::startServer;
bool Engine::stopServer;
bool Engine::heatBeat;
int Engine::serverError;

Engine::Engine()
{
}

void Engine::resize(float width, float height)
{
	glfwSetWindowSize(window, width, height);
	glViewport(0, 0, width, height);
	Game2D::ScreenCoord::init(width,height);
	Game2D::ScreenCoord::alignCentre();
	display();
}

void Engine::resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	screenWidth = width;
	screenHeight = height;

	Game2D::ScreenCoord::init(width, height);
	Game2D::ScreenCoord::alignCentre();

	Game2D::Font::init(height);
	Game2D::Font::initFonts();

	mainMenu.resize();
	singlePlayerBoard.resize();
	if(client) { client->resize(); }
}

void Engine::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_BACKSPACE){
		if(action == GLFW_REPEAT || action == GLFW_RELEASE) {
			connectMenu.backspace();
		}
	}
	if(key == GLFW_KEY_ESCAPE){
		if(action == GLFW_PRESS){
			escState = Game2D::KeyState::State::DOWN;
		}
		else if(action == GLFW_RELEASE){
			if(escState == Game2D::KeyState::State::DOWN) {
				escState = Game2D::KeyState::State::RELEASED;
			}
			else{
				escState = Game2D::KeyState::State::UP;
			}
		}
	}
}

void Engine::charCallback(GLFWwindow *window, unsigned int codepoint)
{
	connectMenu.processCodepoint(codepoint);
}

void Engine::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if(button == GLFW_MOUSE_BUTTON_LEFT){
		if(action == GLFW_PRESS){
			mouseState = Game2D::KeyState::State::DOWN;
		}
		else if(action == GLFW_RELEASE){
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
	mousePos = Game2D::Pos2(
			(((xpos - ((screenWidth - screenHeight) / 2.0f)) / screenHeight)*100.0f) - 50.0f,
			-(((ypos / screenHeight)*100)-50));
}

void Engine::setWindowTitle(std::string title)
{
	glfwSetWindowTitle(window,title.c_str());
}

void Engine::loadOptions()
{
	std::ifstream inFile("options.opt");

	if(!inFile){
		screenWidth = 1280;
		screenHeight = 720;
		Options::showPlayerNums = false;
	} else {
		inFile >> screenWidth;
		inFile >> screenHeight;
		inFile >> Options::showPlayerNums;

		//std::cout << screenWidth << "\n" << screenHeight << "\n" << Options::showPlayerNums << "\n";

		inFile.close();
	}
}

void Engine::writeOptions()
{
	std::ofstream outFile("options.opt");

	if(!outFile){
		std::cerr << "Error: couldn't open options file\n";
	}

	outFile << screenWidth << "\n";
	outFile << screenHeight << "\n";
	outFile << Options::showPlayerNums << "\n";

	if(outFile.is_open()){
		outFile.close();
	}
}

void Engine::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.118f, 0.118f, 0.118f,1.0f);

	glLoadIdentity();

	Game2D::Sprite temp;

	//draw things here
	switch (currentState) {
		case MENU:
			mainMenu.draw();
			break;
		case CONNECT:
			connectMenu.draw();
			break;
		case SOLO_MENU:
			singlePlayerMenu.draw();
			break;
		case PLAYING_MULTI:
			client->draw();
			break;
		case PLAYING_SOLO:
			singlePlayerBoard.draw();
			break;
		case OPTIONS:
			optionsMenu.draw();
			break;
		case WIN:
			singlePlayerBoard.draw();
			temp.setColour(Game2D::Colour(0, 0, 0, 0.5));
			temp.setRect(Game2D::Rect(0, 0, 400, 400));
			temp.draw();
			Game2D::Colour(1, 1, 1).draw();
			Game2D::ScreenCoord::alignCentre();
			Game2D::Freetype::print(Game2D::Font::getFont(5), Game2D::Freetype::getLength(Game2D::Font::getFont(5), "Player %d wins!", winningPlayer + 1) / -2.0, 20, "Player %d wins!", winningPlayer + 1);
			Game2D::Freetype::print(Game2D::Font::getFont(3), Game2D::Freetype::getLength(Game2D::Font::getFont(3), "Click to continue") /-2.0, 10, "Click to continue");
			break;
		case TIE:
			singlePlayerBoard.draw();
			temp.setColour(Game2D::Colour(0, 0, 0, 0.5));
			temp.setRect(Game2D::Rect(0, 0, 400, 400));
			temp.draw();
			Game2D::Colour(1, 1, 1).draw();
			Game2D::ScreenCoord::alignCentre();
			Game2D::Freetype::print(Game2D::Font::getFont(5), Game2D::Freetype::getLength(Game2D::Font::getFont(5), "Tie") / -2.0, 20, "Tie");
			Game2D::Freetype::print(Game2D::Font::getFont(3), Game2D::Freetype::getLength(Game2D::Font::getFont(3), "Click to continue") /-2.0, 10, "Click to continue");
			break;
		case EXIT:
			break;

	}

	glDisable(GL_BLEND);
	glFlush();
}

void Engine::init()
{
	//set callbacks
	glfwSetWindowSizeCallback(window, resizeCallback);
	glfwSetCursorPosCallback(window,mouseCallback);
	glfwSetKeyCallback(window,keyCallback);
	glfwSetCharCallback(window,charCallback);
	glfwSetMouseButtonCallback(window,mouseButtonCallback);

	//make the starting state of the mouse state to up so there aren't any unintentional clicks
	mouseState = Game2D::KeyState::State::UP;

	Game2D::Font::init(screenHeight);
	Game2D::Font::insert(40);
	Game2D::Font::insert(36);
	Game2D::Font::insert(30);
	Game2D::Font::insert(26);
	Game2D::Font::insert(20);
	Game2D::Font::insert(5);
	Game2D::Font::insert(4*1.2f);
	Game2D::Font::insert(4);
	Game2D::Font::insert(3);
	Game2D::Font::insert(2);
	Game2D::Font::initFonts();
	
	TextureManager::loadTex("Images/menu.png");
	TextureManager::loadTex("Images/circle.png");

	Game2D::ScreenCoord::init(screenWidth, screenHeight);

	//Options::showPlayerNums = false;

	mainMenu.init();
	mainMenu.resize();
	connectMenu.init();
	connectMenu.resize();
	singlePlayerMenu.init();
	singlePlayerMenu.resize();
	optionsMenu.init();
	optionsMenu.resize();

	std::vector<Game2D::Colour> playerColours = {
			Game2D::Colour::Red, Game2D::Colour::Yellow,
			Game2D::Colour::Green, Game2D::Colour::Blue,
			Game2D::Colour::Cyan, Game2D::Colour::Magenta,
			Game2D::Colour::White, Game2D::Colour(1,0.65f,0),
			Game2D::Colour(1,0.75f,0.8f),
	};

	singlePlayerBoard.setPlayerColours(playerColours);

	//playerColour = Game2D::Colour::Red;
	playerColour = Game2D::Colour(0,0,0,0);

	currentState = MENU;
	serverLoop = true;
	startServer = false;
	stopServer = false;
	heatBeat = false;
	serverError = -1;
}

void Engine::processKeys()
{
	switch (currentState) {
		case PLAYING_MULTI:
			if(client) { client->processKeyboard(escState); }
			break;
	}

	if(escState == Game2D::KeyState::State::RELEASED){
		escState = Game2D::KeyState::State::UP;
	}
}

void Engine::processMouse()
{
	switch (currentState) {
		case MENU:
			switch (mainMenu.processMouse(mousePos,mouseState)) {
				case 1://quit
					currentState = EXIT;
					break;
				case 2://join online game
					connectMenu.setHost(false);
					currentState = CONNECT;
					break;
				case 3://host online game
					connectMenu.setHost(true);
					currentState = CONNECT;
					break;
				case 4://Solo game
					currentState = SOLO_MENU;
					break;
				case 5://Options menu
					optionsMenu.setReturnState((int)MENU);
					currentState = OPTIONS;
					break;
			}
			break;
		case CONNECT:
			switch (connectMenu.processMouse(mousePos,mouseState)) {
				case 1://back
					if(client && client->isConnected()) { client->disconnect(); }
					currentState = MENU;
					break;
				case 2://connect to server (either self host or online)
					if(connectMenu.getHost()){
						//the user is a host so start the server
						serverPort = connectMenu.getPort();
						startServer = true;
						//wait to see if the server has started of failed
						while (serverError == -1) {
							if(serverError != -1) break;
						}
						if(serverError == 1) {
							serverError = -1;
							break;
						}
						serverError = -1;
					}
					if(client) {
						playerColour = client->getColour();
						delete client;
					}
					client = new Client();
					client->init();
					client->setColour(playerColour);
					client->setHost(connectMenu.getHost());
					client->connect(connectMenu.getAddress(),connectMenu.getPort());
					if(client->isConnected()) {
						currentState = PLAYING_MULTI;
					}
					break;

			}
			break;
		case PLAYING_MULTI:
			heatBeat = true;
			switch (client->processMouse(mousePos,mouseState,setWindowTitle)) {
				case 1://back
					if(client) {
						playerColour = client->getColour();
						client->leave();
					}
					//stop the server
					stopServer = true;
					currentState = CONNECT;
					break;
				case 2://Options
					optionsMenu.setReturnState(PLAYING_MULTI);
					currentState = OPTIONS;
					break;
				case 3:
					currentState = EXIT;
					break;
			}
			break;
		case SOLO_MENU:
			switch (singlePlayerMenu.processMouse(mousePos, mouseState)) {
			case 1://back
				currentState = MENU;
				break;
			case 2://start
				singlePlayerBoard.setBoardDims(singlePlayerMenu.getBoardWidth(),singlePlayerMenu.getBoardHeight());
				singlePlayerBoard.setLineLength(singlePlayerMenu.getLineLength());
				singlePlayerBoard.setNumPlayers(singlePlayerMenu.getNumPlayers());
				std::string tempString;
				tempString += std::to_string(singlePlayerMenu.getNumPlayers());
				tempString += " Player Connect ";
				tempString += std::to_string(singlePlayerMenu.getLineLength());
				setWindowTitle(tempString);
				singlePlayerBoard.initBoard();

				currentState = PLAYING_SOLO;
				break;
			}
			break;
		case PLAYING_SOLO:
			switch (singlePlayerBoard.processMouse(mousePos,mouseState,winningPlayer))
			{
				case -1:
					currentState = TIE;
					break;
				case 1:
					currentState = WIN;
					break;
			}
			break;
		case OPTIONS:
			//should allow us to process messages in the background
			if(optionsMenu.getReturnState() == PLAYING_MULTI){
				if(client) { client->processMouse(mousePos,mouseState,setWindowTitle); }
			}
			optionsMenu.processMouse(mousePos,mouseState);
			switch(optionsMenu.getResult(resize)) {
				case 2: //back
					currentState = (State)optionsMenu.getReturnState();
					break;
			}
			break;
		case WIN:
		case TIE:
			setWindowTitle("n Player Connect x");
			if (mouseState == Game2D::KeyState::DOWN) {
				currentState = SOLO_MENU;
			}
			break;
		case EXIT:
			break;
	}
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

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(screenWidth, screenHeight, "n Player Connect x", NULL, NULL);
	if (!window)
	{
		std::cerr << "failed to create window\n";
		glfwTerminate();
		return false;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	Game2D::ScreenCoord::init(screenWidth, screenHeight);
	Game2D::ScreenCoord::alignCentre();

	return true;

}

int Engine::mainLoop()
{
	loadOptions();

	if(!createWindow())
		return -1;

	glfwSwapInterval(1);

	init();

	std::thread serverThread(
		[](){
			Server* server = nullptr;
			while (serverLoop){
				if(startServer){
					if(server) { delete server; }
					try {
						server = new Server(serverPort);
						server->start();
						serverError = 0;
					} catch (std::exception e){
						std::cerr << e.what() << "\n";
						serverError = 1;
					}
					startServer = false;
				}
				if(heatBeat){
					if(server){
						server->heartBeat();
					}
					heatBeat = false;
				}
				if(stopServer) {
					if(server){
						delete server;
						server = nullptr;
					}
					stopServer = false;
				}
				if(server){
					server->update(-1,false);
				}
			}
			if(server) {delete server;}
		}
	);

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		display();

		glfwSwapBuffers(window);

		update();
		//update glfw's mouse and keyboard events
		glfwPollEvents();
		processKeys();
		processMouse();

		if(currentState == EXIT) { break; }
	}

	stopServer = true;
	serverLoop = false;

	if(client) {
		client->leave();
		delete client;
	}

	if(serverThread.joinable()) { serverThread.join();}

	glfwTerminate();

	writeOptions();

	return 0;
}