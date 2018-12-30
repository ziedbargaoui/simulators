#ifndef __World_h_
#define __World_h_

#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreVector3.h"
#include "OgreSphere.h"
#include "OgreVector3.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"

#include "LiveTraffic.h"

#include <iostream>
#include <tgmath.h>


namespace Ogre {
    class SceneNode;
    class SceneManager;
}

class MovingObject;
class World 

{
public:
	
    World(Ogre::SceneManager *sceneManager, OgreBites::TrayManager* traymgr);
    virtual ~World();

    // You'll want various methods to access & change your world here
    
    void Think(float time);
    
	void Setup();

	MovingObject*& getPlaneEmpty()  {
		return mPlaneEmpty;
	}

	void setPlaneEmpty( MovingObject*& planeEmpty) {
		mPlaneEmpty = planeEmpty;
	}

	MovingObject*& getPlane()  {
		return mPlane;
	}

	void setPlane( MovingObject*& plane) {
		mPlane = plane;
	}

protected:

	int token = 0;

	float earth_radius = 6400;

	float longitude;
	float latitude;
	float baro_altitude;
	float velocity;
	float vertical_rate;
	float geo_altitude;

	float previous_lat=0;
	float previous_long=0;

	float lat_diff;
	float long_diff;

	float fake_lat_diff;
	float fake_long_diff;
	 
    Ogre::SceneManager *mSceneManager; 

    MovingObject *mPlane;
    MovingObject *mPlaneEmpty;

    MovingObject *mCube;
    MovingObject *mSibenik;
    MovingObject *mEarthObj;
    MovingObject *mColumn;
    MovingObject *mUVsphere;

    OgreBites::TrayManager* mTrayMgr;

    OgreBites::TextBox* mInfoTextBox;

    LiveTraffic *lt;


};


#endif
