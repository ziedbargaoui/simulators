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

class World;
class TranslateCamera;
class InputHandler;


class InputHandler : public OIS::KeyListener , public OIS::MouseListener
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

    std::map<std::string, OIS::KeyListener*> mKeyListeners;
    std::map<std::string, OIS::MouseListener*> mMouseListeners;

    std::map<std::string, OIS::KeyListener*>::iterator itKeyListener;
    std::map<std::string, OIS::MouseListener*>::iterator itMouseListener;

    std::map<std::string, OIS::KeyListener*>::iterator itKeyListenerEnd;
    std::map<std::string, OIS::MouseListener*>::iterator itMouseListenerEnd;

private:
	 bool keyPressed (const OIS::KeyEvent &e);
	 bool keyReleased (const OIS::KeyEvent &e);

	 bool mouseMoved (const OIS::MouseEvent &e);
	 bool mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
	 bool mouseReleased (const OIS::MouseEvent &e,  OIS::MouseButtonID id);

};

#endif
