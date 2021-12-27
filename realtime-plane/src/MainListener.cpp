#include "MainListener.h"
#include "InputHandler.h"
#include "World.h"
#include "Camera.h"

#include <iostream>

MainListener::MainListener(Ogre::RenderWindow *mainWindow, InputHandler *inputManager, World *world, TranslateCamera *cam) :
mRenderWindow(mainWindow), mInputHandler(inputManager), mWorld(world), mTranslateCamera(cam)
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
	mInputHandler->Think(time);
    	mTranslateCamera->Think(time);

	// Call think methods on any other managers / etc you want to add3

    	bool keepGoing = true;

	// Ogre will shut down if a listener returns false.  We will shut everything down if
	// either the user presses escape or the main render window is closed.  Feel free to
	// modify this as you like.
	if (mInputHandler->IsKeyDown(OIS::KC_ESCAPE) || mRenderWindow->isClosed())
	{
		keepGoing = false;
	}

	if (mInputHandler->IsKeyDown(OIS::KC_ADD)) {
	    mTranslateCamera->zoom(time,true);
	}

	if (mInputHandler->IsKeyDown(OIS::KC_MINUS)) {
	    mTranslateCamera->zoom(time,false);
	}

	return keepGoing;
}
