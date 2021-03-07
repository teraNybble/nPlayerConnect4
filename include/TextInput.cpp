#include "TextInput.h"

using namespace Game2D;

TextInput::TextInput()
{
	//font.init(_SysFont,50);
	fontSize = 5;
	//text = "TEST STRING";
	maxLength = INT_MAX;
	blacklist = true;
	selected = false;
}

TextInput::TextInput(Pos2 pos)
{
	//font.init(_SysFont,12);
	fontSize = 5;
	button.setRect(Rect(pos,0,0));
	this->pos = pos;
	maxLength = INT_MAX;
	blacklist = true;
	selected = false;
}

TextInput::TextInput(Rect rect)
{
	fontSize = 5;
	button.setRect(rect);
	button.alignToDrawableObject();
	pos = Pos2(rect.pos.x - rect.width/2.0f,rect.pos.y);
	maxLength = INT_MAX;
	blacklist = true;
	selected = false;
}

TextInput::~TextInput()
{
	//font.clean();
}

void TextInput::processMouse(Pos2 mousePos, KeyState::State state, float time)
{
	ClickableObject::ClickState result = button.update(mousePos,state,time);
	switch (result) {
		case ClickableObject::ClickState::CLICK:
			selected = true;
			break;
		case ClickableObject::ClickState::NONE:
			switch (state) {
				case KeyState::State::RELEASED:
					selected = false;
					break;
			}
			break;
	}
}

void TextInput::update(unsigned int codepoint)
{
	//only process the key inputs if the input is slected
	if(selected) {
		//disallow inputs once the max length is reached
		if (text.length() >= maxLength) return;

		bool found = false;
		//check to make sure no invalid charactes are being enterd if they are dont provess them
		for (auto it : charList)
			if ((char) codepoint == it)
				found = true;

		if (found && blacklist)
			return;
		else if ((!found) && (!blacklist))
			return;

		text.push_back((char) codepoint);
	}
}

void TextInput::draw() const
{
	button.draw();
	glColor3f(1,1,1);
	float textPos = freetype::print(Font::getFont(fontSize),pos.x,pos.y,text.c_str());
	if(selected) {
		//only show the blinker if it is selected
		freetype::print(Font::getFont(fontSize * 1.2f), textPos - 1.2f, pos.y - 0, "%s",
						(blinker.elapsedTime<Timer::miliseconds>() % 1000 < 500 ? "|" : ""));
	}
}