#include "Camera.h"

Camera::Camera()
{
    c.identity();
    e.set(0.0, 0.0, 20.0);
    d.set(0.0, 0.0, 0.0);
    up.set(0.0, 1.0, 0.0);
    
    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera position for Project 1
    c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
    ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
}

Camera::~Camera()
{
    //Delete and dynamically allocated memory/objects here
}

Matrix4& Camera::getMatrix()
{
    return c;
}

Matrix4& Camera::getInverseMatrix()
{
    return ci;
}

void Camera::update()
{
    //Update the Camera Matrix using d, e, and up
    //Solve for the z, x, and y axes of the camera matrix
    //Use these axes and the e vector to create a camera matrix c
    //Use c to solve for an inverse camera matrix ci
    
    // Solve for the z, x, and y axes of the camera matrix
    Vector3 z = (e - d).normalize();
    Vector3 x = (up.cross(z)).normalize();
    Vector3 y = z.cross(x);
    
    // Use these axes and the e vector to create a camera matrix c
    c.set(x.getElement(0), x.getElement(1), x.getElement(2), 0,
          y.getElement(0), y.getElement(1), y.getElement(2), 0,
          z.getElement(0), z.getElement(1), z.getElement(2), 0,
          e.getElement(0), e.getElement(1), e.getElement(2), 1);
    
    // Use c to solve for an inverse camera matrix ci
    // Ci = Ri * Ti
    
    Matrix4 Ri = Matrix4(x.getElement(0), y.getElement(0), z.getElement(0), 0,
                         x.getElement(1), y.getElement(1), z.getElement(1), 0,
                         x.getElement(2), y.getElement(2), z.getElement(2), 0,
                         0, 0, 0, 1);
    
    Matrix4 Ti = Matrix4(1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, 0,
                         -e.getElement(0), -e.getElement(1), -e.getElement(2), 1);
    ci = Ri * Ti;
    
}

void Camera::set(Vector3& e, Vector3& d, Vector3& up)
{
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}
