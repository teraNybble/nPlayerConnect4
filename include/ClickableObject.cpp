#include "ClickableObject.h"
using namespace Game2D;

ClickableObject::ClickableObject()
{
	clickRegion = Rect();
	currentState = NONE;
	//mouseDown = false;
}

ClickableObject::ClickableObject(Rect r)
{
	clickRegion = r;
	currentState = NONE;
	//mouseDown = false;
}

void ClickableObject::alignToDrawableObject()
{
	clickRegion.pos.x -= clickRegion.width / 2.0f;
	clickRegion.pos.y -= clickRegion.height / 2.0f;
}

void ClickableObject::setDimentions(float w, float h)
{
	clickRegion.width = w;
	clickRegion.height = h;
}

ClickableObject::ClickState ClickableObject::update(Pos2 mousePos, KeyState::State state)
{
	if (currentState != DISABLED)
	{
		if (clickRegion.contains(mousePos))
		{
			if (currentState == MOUSEDOWN) {
				switch (state) {
				case Game2D::KeyState::DOWN:
					return MOUSEDOWN;
				case Game2D::KeyState::RELEASED:
				case Game2D::KeyState::UP:
					currentState = CLICK;
					return CLICK;
				default:
					break;
				}
			}
			
			switch (state)
			{
				case KeyState::State::UP:		{ currentState = HOVER; 	return HOVER; }
				case KeyState::State::DOWN:		{ currentState = MOUSEDOWN; return MOUSEDOWN; }
				case KeyState::State::RELEASED:	{ currentState = CLICK; 	return CLICK; }
			}
			
		}
		else { currentState = NONE; return NONE; }
	}
	else { currentState = DISABLED; return DISABLED; }
}