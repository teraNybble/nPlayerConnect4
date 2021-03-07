#include "DrawableObject.h"
using namespace Game2D;

DrawableObject::DrawableObject()
{
	rect = Rect();
	colour = Colour();
	rot = 0;
}

DrawableObject::DrawableObject(Rect rec)
{
	rect = rec;
	colour = Colour(0, 0, 0);
	rot = 0;
}

void DrawableObject::setDimentions(float w, float h)
{
	rect.width = w;
	rect.height = h;
}

void DrawableObject::draw() const
{
	glPushMatrix();
	colour.draw();

	glTranslatef(rect.pos.x, rect.pos.y, 0);
	glRotatef(rot, 0, 0, 1);

	glBegin(GL_POLYGON);
	glVertex2f(0 - (rect.width / 2.0f), 0 - (rect.height / 2.0f));
	glVertex2f(0 - (rect.width / 2.0f), 0 + (rect.height / 2.0f));
	glVertex2f(0 + (rect.width / 2.0f), 0 + (rect.height / 2.0f));
	glVertex2f(0 + (rect.width / 2.0f), 0 - (rect.height / 2.0f));
	glEnd();
	glPopMatrix();
}