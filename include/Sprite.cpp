#include "Sprite.h"
using namespace Game2D;

Sprite::Sprite()
{
	texture = Rect();
	loadedTex = false;
}

Sprite::Sprite(Rect r) : DrawableObject(r)
{
	texture = Rect();
	loadedTex = false;
}

Sprite::Sprite(Rect r, Rect texCoords) : DrawableObject(r)
{
	texture = texCoords;
	loadedTex = true;
}

void Sprite::flipX()
{
	texture.pos.x += texture.width;
	texture.width = -texture.width;
}

void Sprite::flipY()
{
	texture.pos.y += texture.height;
	texture.height = -texture.height;
}

void Sprite::draw() const
{
	if(loadedTex)
		glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	colour.draw();

	glTranslatef(rect.pos.x, rect.pos.y, 0);
	glRotatef(rot, 0, 0, 1);

	glBegin(GL_POLYGON);
		glTexCoord2f(texture.pos.x,texture.pos.y);										glVertex2f(0 - (rect.width / 2.0f), 0 - (rect.height / 2.0f));
		glTexCoord2f(texture.pos.x, texture.pos.y + texture.height);					glVertex2f(0 - (rect.width / 2.0f), 0 + (rect.height / 2.0f));
		glTexCoord2f(texture.pos.x + texture.width, texture.pos.y + texture.height);	glVertex2f(0 + (rect.width / 2.0f), 0 + (rect.height / 2.0f));
		glTexCoord2f(texture.pos.x + texture.width, texture.pos.y);						glVertex2f(0 + (rect.width / 2.0f), 0 - (rect.height / 2.0f));
	glEnd();
	glPopMatrix();

	if(loadedTex)
		glDisable(GL_TEXTURE_2D);
}