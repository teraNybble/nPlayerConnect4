#include "KeyState.h"
using namespace Game2D;

KeyState::KeyState()
{
	isDown = false;
	wasDown = false;
	currentState = UP;
}

void KeyState::update(bool keyDown)
{
	if(keyDown)
	{
		isDown = true;
		wasDown = false;
		currentState = DOWN;
	}
	else if(/*!keyDown && */isDown)
	{
		isDown = false;
		wasDown = true;
		currentState = RELEASED;
	}
	else
	{
		isDown = false;
		wasDown = false;
		currentState = UP;
	}
}