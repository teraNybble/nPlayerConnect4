#ifndef GAME2D_SLIDER_H
#define GAME2D_SLIDER_H

#include "Button.h"

namespace Game2D
{
	class Slider
	{
	private:
		Button button;
		Button barClickRegion;
		Rect bar;
		bool followMouse;
		bool horazontal;
	protected:
		Colour lineColour;
	public:
		Slider();
		Slider(Rect bar);

		inline void setLineColour(Colour colour) { lineColour = colour; }
		inline Colour getLineColour() const { return lineColour; }
		inline void setButtonStateSprites(Sprite normal, Sprite hover, Sprite mouseDown, Sprite click, Sprite disabled) {
			button.addStateSprites(normal,hover,mouseDown,click,disabled);
			button.alignToDrawableObject();
		}

		void setRect(Rect bar);

		void update(Pos2 mousePos, KeyState::State state, float time);

		float getValue() const;
		void setValue(float val);

		void draw() const;
	};
}

#endif //SLIDER_H
