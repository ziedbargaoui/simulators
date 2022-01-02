#include "World.h"
#include "MovingObject.h"
#include <pthread.h>

using namespace std;
using namespace Ogre;

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

void World::Setup()
{
    mInfoTextBox = mTrayMgr->createTextBox(OgreBites::TL_TOPLEFT, "GeoLocationInfo", "Flight Details:", 250,140);

    // Set up Earth
    mEarthObj = new MovingObject(mSceneManager, "GlobeX.mesh", NULL, Ogre::Vector3(80.0f,80.0f,80.0f));
    mEarthObj->setPosition(Ogre::Vector3(0, 0, 0));
    mEarthObj->rotate(Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3(0,1.0f,0)));


    mPlaneEmpty = new MovingObject(mSceneManager, "robot.mesh", NULL, Ogre::Vector3::UNIT_SCALE);
    mPlaneEmpty->setPosition(Ogre::Vector3(0, 0, 0));


    Ogre::Radian theta = Ogre::Radian(Ogre::Math::PI * -90/180);
    Ogre::Matrix3 rotateAroundY(1,	0, 				0,
                         	0,	Ogre::Math::Cos(theta),	Ogre::Math::Sin(theta),
				0,	-Ogre::Math::Sin(theta),	Ogre::Math::Cos(theta));

    // empty object to rotate the plane
    mPlaneCentralEmpty = new MovingObject(mSceneManager, "fish.mesh", mPlaneEmpty, Ogre::Vector3::UNIT_SCALE);
    mPlaneCentralEmpty->setPosition(Ogre::Vector3(earth_radius, 0.0f, 0.0f));
    //mPlaneCentralEmpty->setOrientation(Ogre::Matrix3(rotateAroundY));
    //mPlaneCentralEmpty->rotate(Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3(0,0,1)));

	// start in Frankfurt airport
	float lat=50.033337f;
	float longi=8.570556f; 
	mPlaneEmpty->rotate(Ogre::Quaternion(Ogre::Degree(lat),Ogre::Vector3(0, -1.0f, 0)));
	mPlaneEmpty->rotate(Ogre::Quaternion(Ogre::Degree(longi),Ogre::Vector3(1.0f, 0.0f, 0)));

    // Real Plane plane747
    mRealPlane = new MovingObject(mSceneManager, "plane747.mesh", mPlaneCentralEmpty, Ogre::Vector3(400.0f,400.0f,400.0f));  

    //north pole
    mCube = new MovingObject(mSceneManager, "cube.mesh", NULL, Ogre::Vector3(10.0f,10.0f,10.0f));
    mCube->setPosition(Ogre::Vector3(0, 0, earth_radius));

    //south pole
    mColumn = new MovingObject(mSceneManager, "ogrehead.mesh", NULL,  Ogre::Vector3(10.0f,10.0f,10.0f));
    mColumn->setPosition(Ogre::Vector3(0, 0, -earth_radius));

    // 0,0
    mSibenik = new MovingObject(mSceneManager, "robot.mesh", NULL,  Ogre::Vector3(10.0f,10.0f,10.0f));
    mSibenik->setPosition(Ogre::Vector3(earth_radius, 0, 0));
	
    
    mUVsphere = new MovingObject(mSceneManager, "jaiqua.mesh", NULL,  Ogre::Vector3(10.0f,10.0f,10.0f));
    mUVsphere->setPosition(Ogre::Vector3(earth_radius, 0, 0));


}
//This function will be called from a thread

void *call_from_thread(void *args) {
	ThreadData* my_data = (ThreadData*) args;
	my_data->live_traffic->fetchLiveData();
	my_data->setLongitude(my_data->live_traffic->getLongitude());
	my_data->setLatitude(my_data->live_traffic->getLatitude());
	my_data->setFlight(my_data->live_traffic->getFlight());
	my_data->setCountry(my_data->live_traffic->getCountry());

	cout << "Launched by thread " << my_data->thread_id << endl;
	return NULL;
}

void World::Think(float time)
{

	if (token==1) 
	{

		if (fetch_via_thread) 
		{
			tdata.thread_id = 0;
			int ret = pthread_create(&tt, NULL, call_from_thread, (void *) &tdata);
			//pthread_join(tt, NULL);
			longitude	= tdata.getLongitude();
			latitude	= tdata.getLatitude();
			flight		= tdata.getFlight();
			country		= tdata.getCountry();

		} 
		else 
		{
			 lt->fetchLiveData();
			 longitude	= lt->getLongitude();
			 latitude	= lt->getLatitude();
			 flight		= lt->getFlight();
			 country	= lt->getCountry();
			 //vertical_rate 	= td->live_traffic->getVerticalRate();
			 //geo_altitude 	= td->live_traffic->getGeoAltitude();
		 }


		cout << "### lat,long: " << latitude << "," << longitude <<   "\n";

		long_diff=lat_diff=0;

		if (longitude!= previous_long)
			long_diff = fake_long_diff = longitude - previous_long;

		if (latitude!= previous_lat)
			lat_diff = fake_lat_diff = latitude-previous_lat;

		previous_lat = latitude;
		previous_long = longitude;

		// debugging the flight details to the screen #output #text
		mInfoTextBox->show();
		mInfoTextBox->setText(
			"Flight: "+flight+
			"\nCountry: "+ country +
			"\nLatitude: "+to_string(latitude)+
			"\nLongitude: "+to_string(longitude));

		// set the inclination of the plane
		//mPlane->rotate(Ogre::Quaternion(Ogre::Degree(20), Ogre::Vector3(1,0,0))); // ascending or descending

		// set the direction/orientation of the plane
		if (long_diff!=0 && lat_diff!=0) {

			cout << "### lat_diff: " << lat_diff << ",long_diff: " << long_diff << "\n";

			Ogre::Radian zAngle = Ogre::Radian(Ogre::Math::PI * -90 /180);
			Ogre::Matrix3 rotateAroundZ2(Ogre::Math::Cos(zAngle), -Ogre::Math::Sin(zAngle), 0,
										Ogre::Math::Sin(zAngle), Ogre::Math::Cos(zAngle),  0,
										0,                      0,                       1);
			Ogre::Radian thetan = Ogre::Math::Sign(lat_diff) * Ogre::Math::ATan2(Ogre::Math::Abs(lat_diff)/Ogre::Math::Abs(long_diff),Ogre::Math::Abs(long_diff)/Ogre::Math::Abs(lat_diff) );

			//mPlane->setOrientation(Ogre::Matrix3(rotateAroundZ2));
			//mPlane->rotate(Ogre::Quaternion(Ogre::Degree(Ogre::Math::Sign(long_diff) * (Ogre::Radian(Ogre::Math::PI * 90 / 180)+ Ogre::Degree(thetan))),
			//		Ogre::Vector3(0,1,0)));

			// test plane
			mPlaneCentralEmpty->setOrientation(Ogre::Matrix3(rotateAroundZ2));
			mPlaneCentralEmpty->rotate(Ogre::Quaternion(Ogre::Degree(Ogre::Math::Sign(long_diff) * (Ogre::Radian(Ogre::Math::PI * 90 / 180)+ Ogre::Degree(thetan))),
					Ogre::Vector3(0,1,0)));

		}
	}
	else if (token==380) 
	{
		token	= 0;
	}
	else 
	{
		if (fake_lat_diff!=latitude)
			latitude	+= fake_lat_diff * 0.001;

		if (fake_long_diff!=longitude)
			longitude	+= fake_long_diff * 0.001;
	}

	// reset planeEmpty to lat,long 0,0
	if (latitude!=0 && longitude!=0) {

		Ogre::Radian theta = Ogre::Radian(Ogre::Math::PI * (90-longitude) /180);
		Ogre::Matrix3 rotateAroundZ(Ogre::Math::Cos(theta), -Ogre::Math::Sin(theta), 0,
									Ogre::Math::Sin(theta), Ogre::Math::Cos(theta),  0,
									0,                      0,                       1);

		mPlaneEmpty->setOrientation(Ogre::Matrix3(rotateAroundZ));

		mPlaneEmpty->rotate(Ogre::Quaternion(Ogre::Degree(latitude),Ogre::Vector3(0, -1.0f, 0)));
		mPlaneEmpty->rotate(Ogre::Quaternion(Ogre::Degree(longitude),Ogre::Vector3(1.0f, 0.0f, 0)));

	}

	token++;

}
