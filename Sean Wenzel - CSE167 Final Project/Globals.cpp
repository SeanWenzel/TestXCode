#include "Globals.h"

#define VOLCANO "/Users/seanwenzel/Documents/BubbleVolcano.obj"

Camera Globals::camera;



Sphere Globals::sphere(3.0, 50.0, 50.0);



Light Globals::light;

DrawData Globals::drawData;
UpdateData Globals::updateData;

Drawable *Globals::drawable = &volcano;

//OBJObject Globals::volcano(VOLCANO);
OBJObject Globals::volcano("BubbleVolcano.obj");

