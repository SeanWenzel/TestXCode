#ifndef CSE167_Drawable_h
#define CSE167_Drawable_h

#include <iostream>
#include "Matrix4.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Material.h"
#include <float.h>
#include <math.h>
#include <vector>


class Drawable
{
    
public:
    
    Matrix4 toWorld;
    Material material;
    
    Drawable(void);
    ~Drawable(void);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
    void moveLeft(void);
    void moveRight(void);
    void moveUp(void);
    void moveDown(void);
    void moveInto(void);
    void moveOut(void);
    void orbitClockwise(void);
    void orbitCounterClockwise(void);
    void scaleUp(void);
    void scaleDown(void);
    void reset(void);
    
    
};

#endif
