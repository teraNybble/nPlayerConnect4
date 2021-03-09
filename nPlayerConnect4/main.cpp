#include "Engine.h"

int main()
{
	if(tempVer2 > tempVer) {
		std::cout << "Yay1\n";
	}

	if(tempVer2 >= tempVer) {
		std::cout << "Yay2\n";
	}

	Engine engine;

	return engine.mainLoop();
}