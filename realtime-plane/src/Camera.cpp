#include "OgreCamera.h"
#include "Camera.h"
#include "World.h"
#include "OgreVector3.h"
#include "MovingObject.h"


#include "OgreNode.h"

#include "OgreSceneNode.h"


TranslateCamera::TranslateCamera(Ogre::Camera *renderCamera, World *world, bool followPlane) :
mRenderCamera(renderCamera), mWorld(world)
{
	if (followPlane) {
		mRenderCamera->setPosition(Ogre::Vector3(7050,0,-500));
		mRenderCamera->setDirection(Ogre::Vector3(0,-3.5 ,5));
	} else {
		mRenderCamera->setPosition(Ogre::Vector3(11000,0,0)); // viem on Europe/Africa
		//mRenderCamera->setPosition(Ogre::Vector3(0,0,-3200)); // view on the Americas
		mRenderCamera->lookAt(Ogre::Vector3(0,0,0));
	}
	mRenderCamera->setNearClipDistance(2);

}

void
TranslateCamera::Think(float time)
{
	//mRenderCamera->getParentSceneNode()->rotate(Ogre::Quaternion(Ogre::Degree(2), Ogre::Vector3(0,0,0.1)));

	//mRenderCamera->lookAt(Ogre::Vector3(0,0,0));
	//mRenderCamera->lookAt(mWorld->mPlane->getCurrentPosition()) ;

	//mRenderCamera->move(Ogre::Vector3(-1,0.3,0.9));
	// Any code needed here to move the camera about per frame
	//  (use mRenderCamera to get the actual render camera, of course!)
}
