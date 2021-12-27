#include "OgreCamera.h"
#include "OgreNode.h"
#include "OgreSceneNode.h"
#include "Camera.h"
#include "World.h"
#include "Ogre.h"
#include "InputHandler.h"
#include "MovingObject.h"

TranslateCamera::TranslateCamera(Ogre::Camera *renderCamera, World *world, InputHandler * ih, bool followPlane) :
mRenderCamera(renderCamera), 
mWorld(world)
{
	if (followPlane) {
		mRenderCamera->getParentSceneNode()->setPosition(mWorld->mRealPlane->getCurrentPosition()+Ogre::Vector3(0.0f,100.0f,2200.0f));
		mRenderCamera->getParentSceneNode()->rotate(Ogre::Quaternion(Ogre::Degree(0.001f), Ogre::Vector3(0.0f,0.0f,0.0f)));
		
		//FIXME for some reason the line below looks at the origin (probably parent node)
		//mRenderCamera->getParentSceneNode()->lookAt(mWorld->mRealPlane->getCurrentPosition(),Node::TransformSpace::TS_WORLD) ;

	} else {
		mRenderCamera->getParentSceneNode()->setPosition(Ogre::Vector3(-0.0f,166.0f,0.0f));
		mRenderCamera->getParentSceneNode()->lookAt(Ogre::Vector3(0.0f,0.0f,0.0f),Node::TransformSpace::TS_WORLD);

	}
	//mRenderCamera->setNearClipDistance(2);

}

void TranslateCamera::Think(float time)
{
	// mRenderCamera->getParentSceneNode()->rotate(Ogre::Vector3(-30.0f,0.0f,0.0f));

	// Any code needed here to move the camera about per frame
	//  (use mRenderCamera to get the actual render camera, of course!)
	//mRenderCamera->getParentNode()->rotate(Ogre::Quaternion(Ogre::Degree(0.1),Ogre::Vector3(0, 1, 0)));
}

void TranslateCamera::zoom(float time, bool zoomIn=true)
{
	if (zoomIn) {
		mRenderCamera->getParentSceneNode()->translate(Ogre::Vector3(0,0,10),Node::TransformSpace::TS_LOCAL);
	} else {
		mRenderCamera->getParentSceneNode()->translate(Ogre::Vector3(0,0,-10),Node::TransformSpace::TS_LOCAL);
	}
}
