#include "Dropdown.h"

using namespace Game2D;

Game2D::Dropdown::Dropdown()
{
	Dropdown(Rect(0, 0, 0, 0));
}

Game2D::Dropdown::Dropdown(Rect r)
{
	mainButton = Rect(r);
	down = false;
	selectedItem = -1;
}

ClickableObject::ClickState Game2D::Dropdown::update(Pos2 mousePos, KeyState::State state, float time)
{
	ClickableObject::ClickState oldState = mainButton.getState();
	ClickableObject::ClickState butState = mainButton.update(mousePos, state, time);
	if (oldState == ClickableObject::MOUSEDOWN && butState != ClickableObject::MOUSEDOWN) { butState = ClickableObject::CLICK; }
	//std::cout << butState << "\n";

	switch (butState)
	{
	case Game2D::ClickableObject::DISABLED:
		break;
	case Game2D::ClickableObject::NONE:
		break;
	case Game2D::ClickableObject::HOVER:
		break;
	case Game2D::ClickableObject::MOUSEDOWN:
		break;
	case Game2D::ClickableObject::CLICK:
		down = !down;
		break;
	default:
		break;
	}

	if (down) {
		for (auto& it : buttons) {
			if (it.update(mousePos, state, time) == ClickableObject::CLICK) {
				mainButton.setText(it.getText());
				mainButton.setFontSize(fontSize);
				selectedItem = it.getID();
				down = false;
				break;
			}
		}
	}

	return butState;
}

void Game2D::Dropdown::addLastItemCopy(std::string text)
{
	Button temp;
	if (buttons.size() == 0)
	{
		temp = mainButton;
		temp.setID(0);
	} else {
		temp = buttons.back();
		temp.setID(buttons.back().getID() + 1);
		//temp.getClickRegion();
	}
	temp.alignToDrawableObject();
	Pos2 tempPos = Pos2(temp.getClickRegion().pos.x + (1 * temp.getClickRegion().width), temp.getClickRegion().pos.y - (0 *temp.getClickRegion().height));
	temp.setPos(tempPos);
	temp.setText(text);
	temp.setFontSize(fontSize);
	temp.setAnimPoss(tempPos);
	temp.alignToDrawableObject();
	buttons.push_back(temp);
}

void Game2D::Dropdown::draw() const
{
	mainButton.draw();

	if (down) {
		for (const auto& it : buttons) {
			it.draw();
		}
	}
}
