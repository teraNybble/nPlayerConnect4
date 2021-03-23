#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Button.h"

namespace Game2D
{
	class Checkbox
	{
	private:
		int state;
		bool triState;
		Button box;
		AnimatedSprite uncheckedSprites;
		AnimatedSprite partialcheckedSprites;
		AnimatedSprite checkedSprites;
	public:
		Checkbox() : Checkbox(Rect(0,0,0,0)) {};
		Checkbox(Rect rect);

		void setRect(Rect rect);

		int update(Pos2 mousePos, KeyState::State mouseState, float time);

		inline bool setTriState(bool triState) { this->triState; }
		inline void setState(int state) {
			this->state = state;
			if(this->state > 2) { this->state = 2; }
			if(!triState && this->state == 1) { this->state = 2;}
		}
		inline int getState() const	{ return state; };

		inline void setUncheckedSprites(AnimatedSprite animatedSprite){
			uncheckedSprites = animatedSprite;
		}
		inline void setPartialcheckedSprites(AnimatedSprite animatedSprite){
			partialcheckedSprites = animatedSprite;
		}
		inline void setCheckedSprites(AnimatedSprite animatedSprite){
			checkedSprites = animatedSprite;
		}

		inline void reset() {
			state = 0;
			int tempArr[5] = { 4,1,2,3,3 };
			box.addAnims(uncheckedSprites,tempArr);
		}

		inline int getCurrentFrame() const { box.getCurrentFrame(); }

		inline void draw() const { box.draw(); }
	};
}


#endif //CHECKBOX_H