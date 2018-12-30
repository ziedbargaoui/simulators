#ifndef __InputHandler_h_
#define __InputHandler_h_

#include <OIS/OIS.h>
#include <Ogre.h>
#include "OgreRenderWindow.h"

//#include "InputManager.h"
#include "OIS/OISEvents.h"
#include "OIS/OISInputManager.h"
#include "OIS/OISKeyboard.h"
#include "OIS/OISMouse.h"
//#include "OIS/OISJoystick.h"


class World;
class TranslateCamera;
class InputHandler;


class InputHandler // : public OIS::MouseListener, public OIS::KeyListener
{
public:

	InputHandler(Ogre::RenderWindow* win);
	~InputHandler();
	void Think(float time);

	bool IsKeyDown(OIS::KeyCode key);
	bool WasKeyDown(OIS::KeyCode key);

protected:
	OIS::InputManager* mInputManager;
	Ogre::RenderWindow *mRenderWindow;
	OIS::Keyboard *mPreviousKeyboard;
	OIS::Keyboard *mCurrentKeyboard;
	char mOldKeys[256];

};

#endif
