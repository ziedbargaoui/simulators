#include "World.h"
#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreVector3.h"
#include "OgreSphere.h"
#include "MovingObject.h"
#include <iostream>
#include <tgmath.h>

#include "boost/thread.hpp"

using namespace Ogre;

using namespace boost ;
using namespace boost::this_thread;

World::World(Ogre::SceneManager *sceneManager, OgreBites::TrayManager* traymgr) : mSceneManager(sceneManager),
		mTrayMgr(traymgr),mInfoTextBox(0)
{

	lt = new LiveTraffic();

	// register our scene with the RTSS
	RTShader::ShaderGenerator* shadergen =
			RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(mSceneManager);


    mSceneManager->setAmbientLight(ColourValue(1,1,1));
    Setup();
}

World::~World() {
	if (mSceneManager)
		delete mSceneManager;

	delete mPlane;
	delete mPlaneEmpty;
	delete mCube;
	delete mSibenik;
	delete mEarthObj;
	delete mColumn;
	delete mUVsphere;
	delete mTrayMgr;
	delete mInfoTextBox;
	delete lt;
}

// Global function called by thread
void World::GlobalFunction()
{
	for (int i=0; i<10; ++i)
	{
		std::cout<< i << "Do something in parallel with main method." << std::endl;
		//boost::this_thread::yield(); // 'yield' discussed in section 18.6
	}
}

void World::Setup()
{
	mInfoTextBox = mTrayMgr->createTextBox(OgreBites::TL_TOPLEFT, "GeoLocationInfo", "Flight Details:", 250,140);

	// Set up Earth
    //mEarthObj = new MovingObject(mSceneManager, "geosphere8000.mesh", NULL, Ogre::Vector3(31,31,31));
    mEarthObj = new MovingObject(mSceneManager, "Earth.mesh", NULL, Ogre::Vector3(1600,1600,1600));

    mEarthObj->setPosition(Ogre::Vector3(0, 0, 0));
    mEarthObj->rotate(Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3(1,1.06,0.05)));

    mPlaneEmpty = new MovingObject(mSceneManager, "sphere.mesh", NULL, Ogre::Vector3::UNIT_SCALE);
    mPlaneEmpty->setPosition(Ogre::Vector3(0, 0, 0));
	mPlaneEmpty->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(0,0,1)));
	setPlaneEmpty(mPlaneEmpty);

    // Plane
    mPlane = new MovingObject(mSceneManager, "razor.mesh", mPlaneEmpty, Ogre::Vector3::UNIT_SCALE);
    mPlane->setPosition(Ogre::Vector3(6400,30,0));

	Ogre::Radian theta = Ogre::Radian(Ogre::Math::PI * -90/180);
    Ogre::Matrix3 rotateAroundY(1	, 0, 0,
                         	 	0	, Ogre::Math::Cos(theta),  Ogre::Math::Sin(theta),
								0,	-Ogre::Math::Sin(theta), Ogre::Math::Cos(theta));
    mPlane->setOrientation(Ogre::Matrix3(rotateAroundY));
    mPlane->rotate(Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3(0,0,1)));


    mCube = new MovingObject(mSceneManager, "cube.mesh", NULL, Ogre::Vector3(0.1,0.1,0.1));
    mSibenik = new MovingObject(mSceneManager, "cube.mesh", NULL, Ogre::Vector3(0.1,0.1,0.1));
    mColumn = new MovingObject(mSceneManager, "column.mesh", NULL, Ogre::Vector3(0.1,0.1,0.1));
    mUVsphere = new MovingObject(mSceneManager, "cube.mesh", NULL, Ogre::Vector3(0.1,1,0.1));

    //north pole
    mCube->setPosition(Ogre::Vector3(0, 0, 6400));
    //south pole
    mColumn->setPosition(Ogre::Vector3(0, 0, -6400));
    // 0,0
    mSibenik->setPosition(Ogre::Vector3(0, 6400, 0));
    mUVsphere->setPosition(Ogre::Vector3(6400, 0, 0));
}

void World::Think(float time)
{
	 if (token==1) {

		lt->fetchLiveData();

		longitude 		= lt->getLongitude();
		latitude 		= lt->getLatitude();
		vertical_rate 	= lt->getVerticalRate();
		geo_altitude 	= lt->getGeoAltitude();

		std::cout << "*** lat,long *** " << latitude << "," << longitude <<   "\n";

		long_diff=lat_diff=0;

		if (previous_long!=0 &&  previous_lat!=0) {

			if (longitude!= previous_long)
				long_diff = fake_long_diff = longitude - previous_long;


			if (latitude!= previous_lat)
				lat_diff = fake_lat_diff = latitude-previous_lat;

			std::cout << "++++++++ Differences +++++++ lat_diff  : " << lat_diff << "longitude diff: " << long_diff << "\n";
		}
		previous_lat = latitude;
		previous_long = longitude;

		// debugging the flight details to the screen #output #text
		mInfoTextBox->show();
		mInfoTextBox->setText("Flight: "+lt->getFlight()+"\nCountry: "+ lt->getCountry()+"\nLatitude: "+std::to_string(latitude)+"\nLongitude: "+std::to_string(longitude));

		// set the inclination of the plane
		//mPlane->rotate(Ogre::Quaternion(Ogre::Degree(20), Ogre::Vector3(1,0,0))); // ascending or descending

		// set the direction of the plane
		if (long_diff!=0 && lat_diff!=0) {

			Ogre::Radian zAngle = Ogre::Radian(Ogre::Math::PI * -90 /180);
			Ogre::Matrix3 rotateAroundZ2(Ogre::Math::Cos(zAngle), -Ogre::Math::Sin(zAngle), 0,
										Ogre::Math::Sin(zAngle), Ogre::Math::Cos(zAngle),  0,
										0,                      0,                       1);

			mPlane->setOrientation(Ogre::Matrix3(rotateAroundZ2));
			Ogre::Radian thetan = Ogre::Math::Sign(lat_diff) * Ogre::Math::ATan2(Ogre::Math::Abs(lat_diff)/Ogre::Math::Abs(long_diff),Ogre::Math::Abs(long_diff)/Ogre::Math::Abs(lat_diff) );// Ogre::Radian(Ogre::Math::ASin(latitude/longitude) * 180.0 / Ogre::Math::PI);

			std::cout << Ogre::Degree(thetan);

			mPlane->rotate(Ogre::Quaternion(Ogre::Degree(Ogre::Math::Sign(long_diff) * (Ogre::Radian(Ogre::Math::PI * 90 / 180)+ Ogre::Degree(thetan))), Ogre::Vector3(0,1,0)));

		}
	}
	else if (token==40) {
		token = 0;
		std::cout << "++++++++ Predicting +++++++ lat_diff  : " << lat_diff << "longitude diff: " << long_diff << "\n";
	}
	else {
		latitude += fake_lat_diff*0.001;
		longitude += fake_long_diff*0.001;
		//mPlaneEmpty->rotate(Ogre::Quaternion(Ogre::Degree(Ogre::Math::Sign(lat_diff)*0.0001),Ogre::Vector3(0, 1, 0)));
		//mPlaneEmpty->rotate(Ogre::Quaternion(Ogre::Degree(Ogre::Math::Sign(long_diff)*0.0001),Ogre::Vector3(0, 0, 1)));
		//std::cout << "++++++++ Predicting +++++++ lat_diff  : " << lat_diff << "longitude diff: " << long_diff << "\n";
	}

	// reset planeEmpty to lat,long 0,0
	Ogre::Radian theta = Ogre::Radian(Ogre::Math::PI * (90-longitude) /180);
	Ogre::Matrix3 rotateAroundZ(Ogre::Math::Cos(theta), -Ogre::Math::Sin(theta), 0,
								Ogre::Math::Sin(theta), Ogre::Math::Cos(theta),  0,
								0,                      0,                       1);

	mPlaneEmpty->setOrientation(Ogre::Matrix3(rotateAroundZ));
	mPlaneEmpty->rotate(Ogre::Quaternion(Ogre::Degree(latitude),Ogre::Vector3(0, 1, 0)));

	token++;
}
