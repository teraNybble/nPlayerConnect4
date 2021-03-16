#ifndef ENGINE_H
#define ENGINE_H

#include <net.h>
#include <ScreenCoord.h>
#include <Pos2.h>
#include <Fonts.h>
#include "glew.h"
#include <GLFW/glfw3.h>
#include "Server.h"
#include "Client.h"
#include <KeyMap.h>
#include "MainMenu.h"
#include "ConnectMenu.h"
#include "SinglePlayerMenu.h"

class Engine
{
private:
	enum State { MENU, CONNECT, OPTIONS, SOLO_MENU, PLAYING_SOLO, PLAYING_MULTI, WIN, TIE, EXIT };

	static GLFWwindow* window;
	static int screenWidth, screenHeight;
	static Game2D::Pos2 mousePos;
	static Game2D::KeyState::State mouseState;

	static State currentState;

	static MainMenu mainMenu;
	static ConnectMenu connectMenu;
	static SinglePlayerMenu singlePlayerMenu;

	static Board singlePlayerBoard;
	static unsigned int winningPlayer;

	static Client* client;
	static Game2D::Colour playerColour;
	static uint16_t serverPort;
	static bool serverLoop;
	static bool startServer;
	static bool stopServer;
	static bool heatBeat;

	static void resizeCallback(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void charCallback(GLFWwindow* window, unsigned int codepoint);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

	static void setWindowTitle(std::string title);
public:
	Engine();

	static void display();
	static void init();
	static void processKeys();
	static void processMouse();
	static void update();
	static bool createWindow();

	static int mainLoop();
};


#endif //ENGINE_H
