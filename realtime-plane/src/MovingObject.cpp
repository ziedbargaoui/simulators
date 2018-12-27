#include "MovingObject.h"
#include "OgreSceneManager.h"
#include "OgreStringConverter.h"
#include "OgreSceneNode.h"
#include "OgreEntity.h"
#include "OgreQuaternion.h"
#include "OgreMath.h"


Ogre::Vector3 MovingObject::getCurrentPosition() {
	return mObjectSceneNode->getPosition();
}

MovingObject::MovingObject(Ogre::SceneManager *sceneManager, const char *meshName, MovingObject *parent, Ogre::Vector3 scale) :mParent(parent)
{
    Ogre::Entity *ent1 = sceneManager->createEntity(meshName);
    ent1->setCastShadows(true);

    if (parent) {
    	mObjectSceneNode  = parent->mObjectSceneNode->createChildSceneNode();
    	mObjectSceneNode->setInheritOrientation(true);
    }
    else {
        mObjectSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    }

    if (&scale)
    	mObjectSceneNode->setScale(scale);

    mObjectSceneNode->attachObject(ent1);
    mPosition = Ogre::Vector3::ZERO;
    mOrientation = Ogre::Matrix3::IDENTITY;
}

void 
MovingObject::yaw(Ogre::Radian theta)
{
	// TODO: Write me!
    // Modify the mOrientation matrix so that it rotates theta radians
    // around the y axis
	// You probably want to create a new orientation matrix, and then multiply ...
	//
	//  Remember Ogre uses Column vectors (not row vectors!)


	// Once we change our internal data structures, we will modify the OGRE 
	// internals to actually move the models around
	SetGraphicPosition();
}

void 
MovingObject::pitch(Ogre::Radian theta)
{
	// TODO: Write me!
    // Modify the mOrientation matrix so that it rotates theta radians
    // around the x axis
	// You probably want to create a new orientation matrix, and then multiply ...
	//
	// Remember Ogre uses Column vectors (not row vectors!)


	// Once we change our internal data structures, we will modify the OGRE 
	// internals to actually move the models around
	SetGraphicPosition();
}
void
MovingObject::roll(Ogre::Radian theta)
{
	// TODO: Write me!
    // Modify the mOrientation matrix so that it rotates theta radians
    // around the z axis
	// You probably want to create a new orientation matrix, and then multiply ...
	//
	//  Remember Ogre uses Column vectors (not row vectors!)



	// Once we change our internal data structures, we will modify the OGRE 
	// internals to actually move the models around
	SetGraphicPosition();
}

void MovingObject::translate(Ogre::Vector3 deltaPosition)
{
	mPosition = mPosition + deltaPosition;
	SetGraphicPosition();
}


void MovingObject::rotate(Ogre::Quaternion q )
{
    mObjectSceneNode->rotate(q);

	//SetGraphicPosition();
}

void 
MovingObject::setOrientation(Ogre::Matrix3 orientation)
{
	mOrientation = orientation; 
	SetGraphicPosition();
}
void 
MovingObject::setPosition(Ogre::Vector3 position)
{
	mPosition = position;
	SetGraphicPosition();
}

void MovingObject::SetGraphicPosition()
{
    Ogre::Vector3 pos;
    Ogre::Matrix3 orientation;

    GetWorldPositionAndOrientation(pos, orientation);
    mObjectSceneNode->setOrientation(Ogre::Quaternion(orientation));
    mObjectSceneNode->setPosition(pos);
}

void MovingObject::GetWorldPositionAndOrientation(Ogre::Vector3 &position, Ogre::Matrix3 &orientation)
{
	// TODO:
    // Modify this function so that it returns the position and orientation of the object in world space,
    //  not in local space.  
	//
	//  To go from a position in local space to a position in the parent space:
	//    * First rotate the position by the parent rotation
	//    * Then translate by the parent translation.
	//
	//  To go from local space to world space:
	//    Translate from local space to parent space
	//    Translate from parent space to parent's parent space
	//     ... and so on, until there are no more parents  
	//
	//  To go from an orientation in local space to an orientation in parent space:
	//    Combine the orientations
	//
	//  Remember Ogre uses Column vectors (not row vectors!), so rotating vector v by matrix M would be M * v, not v * M.

    position = mPosition;
	orientation = mOrientation;
}
