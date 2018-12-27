#ifndef __MainListener_h_
#define __MainListener_h_

#include "Ogre.h"
#include "OgreFrameListener.h"


// Forward declaration of classes
namespace Ogre
{
	class RenderWindow;
}

class InputHandler;
class World;
class TranslateCamera;

class MainListener : public Ogre::FrameListener
{
public:
	MainListener(World *world, TranslateCamera *cam);

	bool frameStarted(const Ogre::FrameEvent &evt);

	//bool frameRenderingQueued(const Ogre::FrameEvent& evt);


protected:
	World *mWorld;
    TranslateCamera *mTranslateCamera;
	int x;
};

#endif
