#ifndef __Camera_h_
#define __Camera_h_


namespace Ogre
{
    class Camera;
}
class World;
class InputHandler;

class TranslateCamera
{

public:
    TranslateCamera(Ogre::Camera *renderCamera, World *world,bool followPlane = true);
    void Think(float time);
    // If you have a different cameras, you'll want some acessor methods here.
    //  If your camera always stays still, you could remove this class entirely


protected:

    Ogre::Camera *mRenderCamera; 
    World *mWorld;
};

#endif
