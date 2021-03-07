#include "AnimatedSprite.h"
#include <iostream>
using namespace Game2D;

AnimatedSprite::AnimatedSprite()
{
	looping = false;
	playDirection = Forward;
	playing = false;
	currentFrame = 0;
	frameTime = 0;
	elapsedTime = 0.0f;
}

AnimatedSprite::AnimatedSprite(Sprite s)
{
	AnimatedSprite();

	anim.push_back(s);
}

bool AnimatedSprite::update(float timePassed)
{
	if(playing)
	{
		elapsedTime += timePassed;
		if(elapsedTime > frameTime)
		{
			elapsedTime -= frameTime;
			//move to next frame
			int temp = 0;
			temp = ((looping ? 1 : 0) << 1) + (playDirection ? 1 : 0);
			//the 2's bit is used to see if we are looping the 1's bit is used to see what direction we are playing
			//this allows us to use a switch statement which makes the code look nicer
			switch (temp)
			{
				case 0://No looping,	backwards
					if (currentFrame != 0) { currentFrame--; }//keep going until we reach the start
					else { return true; }
					break;
				case 1://No looping,	forwards
					if (currentFrame < anim.size() - 1) { currentFrame++; }//only advance frames untill we reach the end
					else { return true; }
					break;
				case 2://Looping,		backwards
					if (currentFrame-- == 0) currentFrame = anim.size() - 1;//we are at the start go to the end
					break;
				case 3://Looping,		forwards
					if (++currentFrame == anim.size()) currentFrame = 0;//we've reached the end go to start
					break;
				default:
					std::cerr << "Somehow the animated sprite state is invalid" << std::endl;
					break;
			}
		}
	}
	else
	{
		elapsedTime = 0.0f;
	}

	return false;
}

void AnimatedSprite::draw() const
{
	if (currentFrame < anim.size()) {
		anim.at(currentFrame).draw();
	} else {
		std::cerr << "Tried to draw invalid frame (" << currentFrame << ") max " << anim.size() << std::endl;
	}
}