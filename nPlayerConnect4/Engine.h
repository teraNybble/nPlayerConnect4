#ifndef ENGINE_H
#define ENGINE_H

#include "glew.h"
#include <GLFW/glfw3.h>
#include <map>
#include <KeyMap.h>
#include "Board.h"
#include "MainMenu.h"

class Engine
{
public:
	enum State { MENU, PLAYING, WIN, EXIT };
private:
	static GLFWwindow* window;
	static int screenWidth, screenHeight;
	static Game2D::Pos2 mousePos;
	static Game2D::KeyState::State mouseState;

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

	static Board board;
	static MainMenu mainMenu;
	static State currentState;
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