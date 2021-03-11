#include "Engine.h"
#include <iostream>
#include <iomanip>


GLFWwindow* Engine::window;
int Engine::screenWidth = 1280;
int Engine::screenHeight = 720;
Game2D::Pos2 Engine::mousePos;
Game2D::KeyState::State Engine::mouseState;
Engine::State Engine::currentState;
MainMenu Engine::mainMenu;
ConnectMenu Engine::connectMenu;
Game2D::Colour Engine::playerColour;
Client* Engine::client;
//Server* Engine::server;
uint16_t Engine::serverPort;
bool Engine::serverLoop;
bool Engine::startServer;
bool Engine::stopServer;
bool Engine::heatBeat;

Engine::Engine()
{
}

void Engine::resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	screenWidth = width;
	screenHeight = height;

	Game2D::Font::init(height);
	Game2D::Font::initFonts();
	Game2D::ScreenCoord::init(width, height);
	Game2D::ScreenCoord::alignCentre();

	mainMenu.resize();
	//connectMenu.resize();
}

void Engine::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_BACKSPACE){
		if(action == GLFW_REPEAT || action == GLFW_RELEASE) {
			connectMenu.backspace();
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

void Engine::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.118f, 0.118f, 0.118f,1.0f);
	//glClearColor(1, 1, 0.118f, 1.0f);

	glLoadIdentity();

	//draw things here
	switch (currentState) {
		case MENU:
			mainMenu.draw();
			break;
		case CONNECT:
			connectMenu.draw();
			break;
		case PLAYING_MULTI:
			client->draw();
			break;
		case PLAYING_SOLO:
			break;
		case WIN:
			break;
		case TIE:
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
	Game2D::Font::initFonts();


	Game2D::ScreenCoord::init(screenWidth, screenHeight);

	mainMenu.init();
	mainMenu.resize();
	connectMenu.init();
	connectMenu.resize();

	playerColour = Game2D::Colour::Red;

	//client->init();

	currentState = MENU;
	serverLoop = true;
	startServer = false;
	stopServer = false;
	heatBeat = false;
}

void Engine::processKeys()
{

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
					currentState = PLAYING_SOLO;
					break;

			}
			break;
		case CONNECT:
			switch (connectMenu.processMouse(mousePos,mouseState)) {
				case 1://back
					//if(server) { delete server; server = nullptr; }
					if(client && client->isConnected()) { client->disconnect(); }
					currentState = MENU;
					break;
				case 2://connect to server (either self host or online)
					if(connectMenu.getHost()){
						//the user is a host so start the server
						serverPort = connectMenu.getPort();
						startServer = true;
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
			/*if(server){
				//check to see if all the connections are still connected
				server->heartBeat();
				server->update();
			}
			//server.update();*/
			heatBeat = true;
			switch (client->processMouse(mousePos,mouseState)) {
				case 1://back
					client->disconnect();
					//stop the server
					stopServer = true;
					currentState = CONNECT;
					break;
			}
			break;
		case PLAYING_SOLO:
			break;
		case WIN:
			break;
		case TIE:
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

	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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


	Game2D::ScreenCoord::init(screenWidth, screenHeight);
	Game2D::ScreenCoord::alignCentre();

	return true;

}

int Engine::mainLoop()
{
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
					server = new Server(serverPort);
					server->start();
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
						//server->stop();
						delete server;
						server = nullptr;
					}
					stopServer = false;
				}
				if(server){
					server->update();
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

	serverLoop = false;
	if(serverThread.joinable()) { serverThread.join();}

	//if(server) { delete server; }

	glfwTerminate();

	return 0;
}