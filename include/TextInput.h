#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <limits>
#include "Fonts.h"
#include "Sprite.h"
#include "Timer.h"
#include "Button.h"

#define _arrLength(arr) (sizeof(arr)/sizeof(*arr))

namespace Game2D
{
	class TextInput
	{
	private:
		Pos2 pos;
		//freetype::font_data font;
		//freetype::font_data blinkerFont;
		float fontSize;
		std::string text;
		Timer blinker;
		std::vector<char> charList;
		//Sprite background;
		unsigned int maxLength;
		constexpr static const char numbers[] = "0123456789";
		constexpr static const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		constexpr static const char special[] = "!\"£$%^&*()_-=+*/[]{};:'";
		bool blacklist;

		Button button;
		bool selected;
	public:
		TextInput();
		TextInput(Pos2 pos);
		TextInput(Rect rect);

		~TextInput();

		inline void addNumbersToList() { charList.insert(charList.begin(), numbers, numbers + _arrLength(numbers)); }
		inline void addLettersToList() { charList.insert(charList.begin(), letters, letters + _arrLength(letters)); }
		inline void addSpecialToList() { charList.insert(charList.begin(), special, special + _arrLength(special)); }
		inline void addCharToList(char c) { charList.push_back(c); }

		inline void setCharListModeBlacklist() { blacklist = true; }
		inline void setCharListModeWhitelist() { blacklist = false; }

		inline void init(float size = 12.0f) { fontSize = size; Font::insert(size); Font::insert(size*1.2f); /*Font::initFonts();*/}
		inline void setBackGroundSprites(Sprite normal, Sprite hover, Sprite mouseDown, Sprite click, Sprite disable){
			button.addStateSprites(normal,hover,mouseDown,click,disable);
		}

		inline void setPos(Pos2 p) { pos = p; }
		inline void setRect(Rect r) { button.setRect(r); pos = Pos2(r.pos.x - r.width/2.0f,(r.pos.y - (r.height-fontSize)/2.0f)); button.alignToDrawableObject(); }
		inline void setMaxLength(unsigned int max) { maxLength = max; }
		inline void setText(std::string text) { this->text = text; }
		inline void setSelected(bool selected) { this->selected = selected; }

		void processMouse(Pos2 mosePos,KeyState::State state, float time);
		void update(unsigned int codepoint);
		inline void backspace()	{ if (selected && text.size() > 0) text.pop_back(); }

		inline std::string getText() const { return text; }
		void draw() const;
	};
}

#endif //TEXTINPUT_H