#include "OgreCamera.h"
#include "OgreNode.h"
#include "OgreSceneNode.h"
#include "Camera.h"
#include "World.h"
#include "OgreVector3.h"
#include "InputHandler.h"
#include "MovingObject.h"

TranslateCamera::TranslateCamera(Ogre::Camera *renderCamera, World *world, InputHandler * ih, bool followPlane) :
mRenderCamera(renderCamera), mWorld(world)
{
	if (followPlane) {
		if (true) {
			mRenderCamera->setPosition(Ogre::Vector3(500,150,500));
			mRenderCamera->setDirection(Ogre::Vector3(-2,-0.6,2));
		} else {
			mRenderCamera->setPosition(Ogre::Vector3(50,7300,7600));
			mRenderCamera->setDirection(Ogre::Vector3(-2,-2,0));
		}
	} else {
		mRenderCamera->setPosition(Ogre::Vector3(18000,0,0)); // viem on Europe/Africa
		//mRenderCamera->setPosition(Ogre::Vector3(0,0,-3200)); // view on the Americas
		mRenderCamera->lookAt(Ogre::Vector3(0,0,0));
	}
	mRenderCamera->setNearClipDistance(2);

}

void TranslateCamera::Think(float time)
{
	//mRenderCamera->getParentSceneNode()->rotate(Ogre::Quaternion(Ogre::Degree(2), Ogre::Vector3(0,0,0.1)));

	//mRenderCamera->lookAt(Ogre::Vector3(0,0,0));
	//mRenderCamera->lookAt(mWorld->mPlane->getCurrentPosition()) ;

	//mRenderCamera->move(Ogre::Vector3(-1,0.3,0.9));
	// Any code needed here to move the camera about per frame
	//  (use mRenderCamera to get the actual render camera, of course!)
	mRenderCamera->getParentNode()->rotate(Ogre::Quaternion(Ogre::Degree(0.1),Ogre::Vector3(0, 1, 0)));
}

void TranslateCamera::zoom(float time, bool zoomIn=true)
{
	if (zoomIn) {
		mRenderCamera->move(Ogre::Vector3(210,50,210));  //rotate(Ogre::Quaternion(Ogre::Degree(0.1),Ogre::Vector3(0, 1, 0)));
	} else {
		mRenderCamera->move(Ogre::Vector3(-210,-50,-210));  //rotate(Ogre::Quaternion(Ogre::Degree(0.1),Ogre::Vector3(0, 1, 0)));
	}
}
