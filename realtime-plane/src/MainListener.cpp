#include "MainListener.h"
#include "World.h"
#include "Camera.h"

#include <iostream>

MainListener::MainListener( World *world, TranslateCamera *cam) :
 mWorld(world), mTranslateCamera(cam)
{
	x = 0;
}

// On every frame, call the appropriate managers
bool MainListener::frameStarted(const Ogre::FrameEvent &evt)
{
	//mElapsedTime += evt.timeSinceLastFrame;
    //mAnimationState->addTime(evt.timeSinceLastFrame);


	float time = evt.timeSinceLastFrame;
	if (time > 0.5)
	{
		time = 0.5;
	}
	mWorld->Think(time);
    mTranslateCamera->Think(time);
	// Call think methods on any other managers / etc you want to add

	bool keepGoing = true;

	return keepGoing;
}
