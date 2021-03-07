#include "Slider.h"

using namespace Game2D;

Slider::Slider()
{
	Slider(Rect(0,0,0,0));
}

Slider::Slider(Rect bar)
{
	this->bar = bar;
	//if the bar is wider than it is tall assume it is a horazontal bar
	horazontal = (bar.width>bar.height);
	if(horazontal){
		button.setRect(Rect(bar.pos,1,bar.height));
	} else {
		button.setRect(Rect(bar.pos,bar.height,1));
	}

	lineColour = Colour::White;

	followMouse = false;
}

void Slider::update(Pos2 mousePos, KeyState::State state, float time)
{
	if(button.update(mousePos,state,time) == ClickableObject::MOUSEDOWN){
		followMouse = true;

	} else if (state != KeyState::State::DOWN){
		followMouse = false;
	}

	if(followMouse){
		if(horazontal) {
			Game2D::Pos2 pos;
			pos.x = mousePos.x;
			//clamp the slider to the bar
			if(pos.x < (bar.pos.x - (bar.width/2.0f))) { pos.x = (bar.pos.x - (bar.width/2.0f)); }
			if(pos.x > (bar.pos.x + (bar.width/2.0f))) { pos.x = (bar.pos.x + (bar.width/2.0f)); }
			pos.y = button.getClickRegion().pos.y;
			//buttons aren't aligned the same way as everything else
			pos.x -= button.getClickRegion().width/2.0f;
			button.setPos(pos);
			pos.y += button.getClickRegion().height/2.0f;
			pos.x += button.getClickRegion().width/2.0f;
			button.setAnimPoss(pos);
		} else {
			Game2D::Pos2 pos;
			pos.y = mousePos.y;
			if(pos.y < (bar.pos.y - (bar.height/2.0f))) { pos.y = (bar.pos.y - (bar.height/2.0f)); }
			if(pos.y > (bar.pos.y + (bar.height/2.0f))) { pos.y = (bar.pos.y + (bar.height/2.0f)); }
			pos.x = button.getClickRegion().pos.x;
			pos.y -= button.getClickRegion().height/2.0f;
			button.setPos(pos);
			pos.x += button.getClickRegion().width/2.0f;
			pos.y += button.getClickRegion().height/2.0f;
			button.setAnimPoss(pos);
		}
	}
}

float Slider::getValue() const
{
	if(horazontal){
		return (button.getClickRegion().pos.x - (bar.pos.x-(bar.width/2.0f)))/bar.width;
	} else {
		return (button.getClickRegion().pos.y - (bar.pos.y-(bar.height/2.0f)))/bar.height;
	}
}

void Slider::setValue(float val)
{
	if(horazontal){
		Game2D::Pos2 pos;
		pos.x = (val * bar.width) + (bar.pos.x - (bar.width/2.0f));
		//clamp the slider to the bar
		if(pos.x < (bar.pos.x - (bar.width/2.0f))) { pos.x = (bar.pos.x - (bar.width/2.0f)); }
		if(pos.x > (bar.pos.x + (bar.width/2.0f))) { pos.x = (bar.pos.x + (bar.width/2.0f)); }
		pos.y = button.getClickRegion().pos.y;
		pos.x -= button.getClickRegion().width/2.0f;
		button.setPos(pos);
		pos.y += button.getClickRegion().height/2.0f;
		pos.x += button.getClickRegion().width/2.0f;
		button.setAnimPoss(pos);
	} else {
		Game2D::Pos2 pos;
		pos.y = (val * bar.height) + (bar.pos.y - (bar.height/2.0f));
		if(pos.y < (bar.pos.y - (bar.height/2.0f))) { pos.y = (bar.pos.y - (bar.height/2.0f)); }
		if(pos.y > (bar.pos.y + (bar.height/2.0f))) { pos.y = (bar.pos.y + (bar.height/2.0f)); }
		pos.x = button.getClickRegion().pos.x;
		pos.y -= button.getClickRegion().height/2.0f;
		button.setPos(pos);
		pos.x += button.getClickRegion().width/2.0f;
		pos.y += button.getClickRegion().height/2.0f;
		button.setAnimPoss(pos);
	}
}

void Slider::draw() const
{
	glPushMatrix();
		lineColour.draw();

		//glTranslatef(bar.pos.x, bar.pos.y, 0);

		glBegin(GL_LINES);
			if(horazontal){
				glVertex2f(bar.pos.x-(bar.width/2.0f),bar.pos.y);
				glVertex2f(bar.pos.x+(bar.width/2.0f),bar.pos.y);
			} else {
				glVertex2f(bar.pos.x,bar.pos.y-(bar.height/2.0f));
				glVertex2f(bar.pos.x,bar.pos.y+(bar.height/2.0f));
			}
		glEnd();
	glPopMatrix();

	button.draw();
}
