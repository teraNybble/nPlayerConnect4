#include "Engine.h"

int main()
{
	std::streambuf* coutbuff = std::cout.rdbuf();
	std::streambuf* cerrbuff = std::cerr.rdbuf();

	//redirect the cout to log.txt
	std::ofstream log("log.txt");
	std::cout.rdbuf(log.rdbuf());

	//redirect cerr to ErrorLog.txt
	std::ofstream errorLog("ErrorLog.txt");
	std::cerr.rdbuf(errorLog.rdbuf());

	Engine engine;

	int result = engine.mainLoop();

	std::cout.rdbuf(coutbuff);
	std::cerr.rdbuf(cerrbuff);

	return result;
}