#include "KeyMap.h"
using namespace Game2D;

KeyMap::KeyMap()
{
	isDown = wasDown = false;
	currentState = KeyState::UP;
}

void KeyMap::update(int id, bool keyDown)
{
	map.find(id)->second.update(keyDown);

	KeyState::State tempState = KeyState::UP;

	//go through all the keys in the map and see what state they are in
	//if it is has been relesed that has a higher priority than if a key isn't pressed
	//and the same is true for if a key is pressed
	for(auto it = map.begin(); it != map.end(); it++)
	{
		if(it->second.getState() < tempState)
		{
			tempState = it->second.getState();
			if(tempState == KeyState::DOWN) break;//the state can't change anymore so we may as well stop
		}
	}

	currentState = tempState;

	switch (currentState)
	{
		case KeyState::UP:
			isDown = false;
			wasDown = false;
			break;
		case KeyState::RELEASED:
			isDown = false;
			wasDown = true;
			break;
		case KeyState::DOWN:
			isDown = true;
			wasDown = false;
			break;
	}
}