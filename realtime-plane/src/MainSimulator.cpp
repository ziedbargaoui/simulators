/*
 * main_simulator.cpp
 *
 *  Created on: Dec 8, 2018
 *      Author: zied
 */
#include "MainSimulator.h"
#include "World.h"
#include "InputHandler.h"
#include "Camera.h"
#include "MovingObject.h"

using namespace std;

MainSimulator::MainSimulator() : ApplicationContext("Real Time Plane - Simulation") {
	root = 0;
	scnMgr = 0;
	mTranslateCamera = 0;
}

MainSimulator::~MainSimulator() {
	if (root)
		delete root;

	if (scnMgr)
		delete scnMgr;
}

void MainSimulator::loadResources() {
	// Add our models to our resources and index it
	// TODO make loading the resources dynamic
	//ResourceGroupManager::getSingleton().addResourceLocation("../Media/materials/textures/nvidia", "FileSystem");
	//ResourceGroupManager::getSingleton().addResourceLocation("../Media/models/","FileSystem");
	//ResourceGroupManager::getSingleton().addResourceLocation("../content/models/","FileSystem");

	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	
	// DEBUG
	ResourceGroupManager::LocationList ll = ResourceGroupManager::getSingleton().getResourceLocationList("General");

	for (ResourceGroupManager::ResourceLocation loc : ll)
	{
		cout << "+++++" << loc.archive->getName() << " - " << loc.archive->getType() << endl;
	}
}



void MainSimulator::go(void) {

    initApp();
    root->startRendering();
    closeApp();

    // clean up
    destroyScene();
}

void MainSimulator::setup() {
	// do not forget to call the base first
	ApplicationContext::setup();
	addInputListener(this);

	// get a pointer to the already created root
	root = getRoot();
	scnMgr = root->createSceneManager();

	createSpecialDebugMenu();

	loadResources();

	createLight();

	createScene();

	createCamera();

	createViewports();

	createFrameListener();

	addInputListener(mTrayMgr);

}



// We will create a single frame listener, to handle our main event loop.  While we could
// add as many frame listeners as we want (and let the main rendering loop call them),
// we would not have as much control over the order that the listeners are called --
//  so we will just have one listener and handle everything ourselves.
void MainSimulator::createFrameListener(void) {
	mPongFrameListener = new MainListener(getRenderWindow(), mInputHandler, mWorld,mTranslateCamera);
	mRoot->addFrameListener(mPongFrameListener);
}

void MainSimulator::createLight() {

	Light* light = scnMgr->createLight("MainLight");
	light->setType(Ogre::Light::LT_POINT);

	// Set Light Color
	light->setDiffuseColour(54.0f, 1.0f, 1.0f);

	// Set Light Reflective Color
	light->setSpecularColour(100.0f, 6.0f, 0.0f);

	// Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
	//light->setAttenuation(0, 0.5, 0.045, 0.0);

	Real x = 20, y = 80, z = 50;

	SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);
	lightNode->setPosition(x, y, z);
	Real s = 0.05f;
	lightNode->setScale(s, s, s);

	scnMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));

	Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
	lightdir.normalise();

	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(lightdir);
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
}


void MainSimulator::createCamera() {

	bool followPlane =1;
	cam = scnMgr->createCamera("myCam");

	if (followPlane) {
		camNode = mWorld->getPlaneCentralEmpty()->mObjectSceneNode->createChildSceneNode();
	}
	else {
		camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
		camNode->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(1,1,1)));
	}

	camNode->attachObject(cam);

    mTranslateCamera = new TranslateCamera(cam, mWorld,mInputHandler,followPlane);
}

void MainSimulator::createViewports() {

	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(ColourValue(0.2,0.3,0.4));
	cam->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
}

// Here is where we set up all of the non-rendering stuff (our world, various managers, etc)
void MainSimulator::createScene() {
    mInputHandler = new InputHandler(getRenderWindow());

	mWorld = new World(scnMgr, mTrayMgr);
}


void MainSimulator::createSpecialDebugMenu() {
	// Process like ogre/Samples/Common/include/SdkSample.h
	scnMgr->addRenderQueueListener(mOverlaySystem);
	// create a tray interface
	mTrayMgr = new TrayManager("SampleControls", getRenderWindow(), this);
	// show stats and logo and hide the cursor
	// mTrayMgr->showFrameStats(TL_BOTTOMLEFT);
	mTrayMgr->showLogo(TL_BOTTOMRIGHT);
	mTrayMgr->hideCursor();
}
bool MainSimulator::keyPressed(const KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_ESCAPE) {
		getRoot()->queueEndRendering();
	}
	return true;
}

void MainSimulator::destroyScene() {
	delete mPongFrameListener;
	delete mWorld;
	delete mTranslateCamera;
	delete root;
	delete scnMgr;
	delete camNode;
	delete cam;
}

