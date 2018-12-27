/*
 * mainConfig.h
 *
 *  Created on: Dec 7, 2018
 *      Author: zied
 */

#ifndef SRC_MAIN_SIMULATOR_H_
#define SRC_MAIN_SIMULATOR_H_

#include <exception>
#include <iostream>

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreCameraMan.h"

#include "World.h"
#include "MainListener.h"

#include "OgreTrays.h"

using namespace Ogre;
using namespace OgreBites;

class MainSimulator: public ApplicationContext, public InputListener, public TrayListener {

public:
	MainSimulator();
	virtual ~MainSimulator();

    // Do all the application setup
	void setup();

    // Start run
    void go(void);
	void createSpecialDebugMenu();

	bool keyPressed(const KeyboardEvent& evt);

protected:

    // Create all of the required classes and do setup for all non-rendering tasks
    void createScene(void);

    // Free up all memory & resources created in createScene
    void destroyScene(void);

    void createCamera(void);

    void createViewports(void);

    void createGround(void);

    void createLight(void);

	//bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	void loadResources();

 	void createFrameListener(void);


	MainListener *mPongFrameListener;

	bool mShutdown;
	World *mWorld;
    TranslateCamera *mTranslateCamera;

	Root* root;
	SceneManager* scnMgr;
    SceneNode* camNode;
    Camera* cam;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;

	// Animation

    Ogre::AnimationState* mAnimationState;
    double mElapsedTime;

    TrayManager* mTrayMgr;
    OgreBites::Label* mInfoLabel;

};

#endif /* SRC_MAIN_SIMULATOR_H_ */
