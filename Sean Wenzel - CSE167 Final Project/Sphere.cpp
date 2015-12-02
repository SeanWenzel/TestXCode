#include "Sphere.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Sphere::Sphere(double radius, int slices, int stacks) : Drawable()
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
}

void Sphere::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glutSolidSphere(radius, slices, stacks);
    
    glPopMatrix();
}


void Sphere::update(UpdateData& data)
{
    //
}

void Sphere::bounce() {
    
    Vector3 gravity = Vector3(0.0, -0.05, 0.0);
    
    Matrix4 translation;
    
    translation.makeTranslate(gravity);
    
    toWorld = translation * toWorld;
    
}


