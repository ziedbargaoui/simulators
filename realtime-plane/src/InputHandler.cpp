#include "InputHandler.h"
#include "Ogre.h"
#include "OgreStringConverter.h"
#include <OIS/OIS.h>
#include <stdio.h>

InputHandler::InputHandler(Ogre::RenderWindow *renderWindow) : 
	 mRenderWindow(renderWindow)
{
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	renderWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem(pl);

	mCurrentKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false /* not buffered */ ));
}


bool InputHandler::IsKeyDown(OIS::KeyCode key)
{
	return mCurrentKeyboard->isKeyDown(key);
}

bool InputHandler::WasKeyDown(OIS::KeyCode key)
{
	return mOldKeys[key] != '\0';
}

void InputHandler::Think(float time)
{
	mCurrentKeyboard->copyKeyStates(mOldKeys);
	mCurrentKeyboard->capture();
}


bool InputHandler::keyPressed( const OIS::KeyEvent &e ) {
    itKeyListener    = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if(!itKeyListener->second->keyPressed( e ))
			break;
    }

    return true;
}

bool InputHandler::keyReleased( const OIS::KeyEvent &e ) {
    itKeyListener    = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if(!itKeyListener->second->keyReleased( e ))
			break;
    }

    return true;
}

bool InputHandler::mouseMoved( const OIS::MouseEvent &e ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if(!itMouseListener->second->mouseMoved( e ))
			break;
    }

    return true;
}

bool InputHandler::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if(!itMouseListener->second->mousePressed( e, id ))
			break;
    }

    return true;
}

bool InputHandler::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if(!itMouseListener->second->mouseReleased( e, id ))
			break;
    }

    return true;
}


InputHandler::~InputHandler()
{
	mInputManager->destroyInputObject(mCurrentKeyboard);
}



