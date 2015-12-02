#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Sphere.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "OBJObject.h"

class Globals
{
    
public:
    
    static Camera camera;

    static Sphere sphere;
    static Light light;
    static DrawData drawData;
    static UpdateData updateData;
    //Feel free to add more member variables as needed
    
    static Drawable* drawable;
    static OBJObject volcano;
    
    
};

#endif
