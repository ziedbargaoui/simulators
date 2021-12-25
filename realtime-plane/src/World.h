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
#include "ThreadData.h"

#include <iostream>
#include <tgmath.h>
#include <string>


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
    MovingObject *mPlane;
    MovingObject *mRealPlane;

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

	MovingObject*& getPlaneCentralEmpty() {
		return mPlaneCentralEmpty;
	}

	void setPlaneCentralEmpty(MovingObject*& planeCentralEmpty) {
		mPlaneCentralEmpty = planeCentralEmpty;
	}

protected:

	int token = 0;
	bool fetch_via_thread = true;
	float earth_radius = 6400;

	float longitude=0;
	float latitude=0;
	float baro_altitude=0;
	float velocity=0;
	float vertical_rate=0;
	float geo_altitude=0;
	std::string country;
	std::string flight;

	float previous_lat=0;
	float previous_long=0;

	float lat_diff=0;
	float long_diff=0;

	float fake_lat_diff=0;
	float fake_long_diff=0;
	 
    Ogre::SceneManager *mSceneManager;
    OgreBites::TrayManager* mTrayMgr;
    OgreBites::TextBox* mInfoTextBox;

    MovingObject *mPlaneEmpty;

    MovingObject *mPlaneCentralEmpty;

    MovingObject *mCube;
    MovingObject *mSibenik;
    MovingObject *mEarthObj;
    MovingObject *mColumn;
    MovingObject *mUVsphere;

    LiveTraffic *lt;
	pthread_t tt;
	ThreadData tdata;

};


#endif
