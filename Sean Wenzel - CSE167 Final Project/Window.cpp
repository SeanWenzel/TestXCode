#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"

#include "Matrix4.h"
#include "Globals.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here

void Window::initialize(void)
{
    //Setup the light
    Vector4 lightPos(0.0, 10.0, 15.0, 1.0);
    Globals::light.position = lightPos;
    Globals::light.quadraticAttenuation = 0.02;
    
    Globals::volcano.scalePrep();
    
    

    
    
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
    
    // TODO: Maybe update volcano erupting bubbles here?
    
    //Call the update function on cube
    Globals::drawable->update(Globals::updateData); // changed from cube
    
    
    
    //Call the display routine to draw the cube
    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
    
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    Globals::light.bind(0);
    
    
    
    //Draw
    // std::cout << "Draw is called in displayCallback" << std::endl;
    Globals::drawable->draw(Globals::drawData); // changed from cube
    Globals::sphere.draw(Globals::drawData);
    
   
    
    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}


//TODO: Keyboard callbacks!
void Window::keyboardCallback(unsigned char key, int x, int y) {
    
    // With every key press, display the new cube position with
    // your Vector3 print method in the text window.
    
    if (key == 'x') {
        // move cube left by a small amount.
        Globals::drawable->moveLeft();
    }
    else if (key == 'X') {
        // move cube right by a small amount.
        Globals::drawable->moveRight();
    }
    else if (key == 'y') {
        // move cube down by a small amount
        Globals::drawable->moveDown();
    }
    else if (key == 'Y') {
        // move cube up by a small amount
        Globals::drawable->moveUp();
    }
    else if (key == 'z') {
        // move cube into of the screen by a small amount.
        Globals::drawable->moveInto();
    }
    else if (key == 'Z') {
        // move cube out of the screen by a small amount.
        Globals::drawable->moveOut();
    }
    else if (key == 'r') {
        // reset cube position, orientation, and size
        Globals::drawable->reset();
    }
    else if (key == 'o') {
        // orbit cube about the OpenGL window's z axis by a small number of degrees (e.g., 10)
        // per key press, counterclockwise ('o') or clockwise ('O'). The z axis crosses the screen
        // in the center of the OpenGL window. This rotation should not affect the spin other than
        // that it will rotate the spin axis with the cube.
        
        Globals::drawable->orbitCounterClockwise();
    }
    else if (key == 'O') {
        Globals::drawable->orbitClockwise();
    }
    
    else if (key == 's') {
        // scale cube down
        Globals::drawable->scaleDown();
    }
    else if (key == 'S') {
        // scale cube up
        Globals::drawable->scaleUp();
    }
    else
        return;
    
}

//TODO: Function Key callbacks!


//TODO: Mouse callbacks!

//TODO: Mouse Motion callbacks!
