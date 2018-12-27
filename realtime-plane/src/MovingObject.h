#include "OgreMatrix3.h"
#include "OgreVector3.h"
#include <iostream>

class Ogre::SceneManager;
class Ogre::SceneNode;

class MovingObject
{

public:
    MovingObject(Ogre::SceneManager *sceneManager, const char *meshName, MovingObject *parent, Ogre::Vector3 scale);

    Ogre::Matrix3 getOrientation() {return mOrientation;}
    Ogre::Vector3 getPosition() {return mPosition;}
    Ogre::Vector3 getCurrentPosition();

    void setOrientation(Ogre::Matrix3 orientation); 
    void setPosition(Ogre::Vector3 position);

    void yaw(Ogre::Radian theta);
    void pitch(Ogre::Radian theta);
    void roll(Ogre::Radian theta);

    void translate(Ogre::Vector3 deltaPosition);
    void rotate(Ogre::Quaternion  q );
    Ogre::SceneNode *mObjectSceneNode;

		

protected:

    void GetWorldPositionAndOrientation(Ogre::Vector3 &position, Ogre::Matrix3 &orientation);
    void SetGraphicPosition();

    Ogre::Matrix3 mOrientation;
    Ogre::Vector3 mPosition;
    MovingObject *mParent;
};
