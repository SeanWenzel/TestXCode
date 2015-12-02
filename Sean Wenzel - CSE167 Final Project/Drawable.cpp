#include "Drawable.h"
#include "Window.h"

Drawable::Drawable()
{
    this->toWorld.identity();
}

Drawable::~Drawable()
{
    //
}

void Drawable::draw(DrawData& data)
{
    std::cout << "Warning: draw() is not implemented" << std::endl;
}

void Drawable::update(UpdateData& data)
{
    std::cout << "Warning: update() is not implemented" << std::endl;
}

void Drawable::moveLeft(void) {
    Matrix4 xLeft;
    xLeft.makeTranslate(-0.5, 0, 0);
    toWorld = xLeft * toWorld;
    toWorld.positionPrint("Move Left");
}

void Drawable::moveRight(void) {
    Matrix4 xRight;
    xRight.makeTranslate(0.5, 0, 0);
    toWorld = xRight * toWorld;
    toWorld.positionPrint("Move Right");
}

void Drawable::moveUp(void) {
    Matrix4 yUp;
    yUp.makeTranslate(0, 0.5, 0);
    toWorld = yUp * toWorld;
    toWorld.positionPrint("Move Up");
}

void Drawable::moveDown(void) {
    Matrix4 yDown;
    yDown.makeTranslate(0, -0.5, 0);
    toWorld = yDown * toWorld;
    //toWorld.positionPrint("Move Down");
    toWorld.print("toWorld");
}

void Drawable::moveInto(void) {
    Matrix4 zInto;
    zInto.makeTranslate(0, 0, -0.5);
    toWorld = zInto * toWorld;
    toWorld.positionPrint("Move Into");
}

void Drawable::moveOut(void) {
    Matrix4 zOut;
    zOut.makeTranslate(0, 0, 0.5);
    toWorld = zOut * toWorld;
    toWorld.positionPrint("Move Out");
}

void Drawable::orbitClockwise(void) {
    Matrix4 zClockwise;
    zClockwise.makeRotateZ(-0.174533); // 10 degrees in radians is 0.174533
    toWorld = zClockwise * toWorld;
}

void Drawable::orbitCounterClockwise(void) {
    Matrix4 zCounterClockwise;
    zCounterClockwise.makeRotateZ(0.174533); // 10 degrees in radians is 0.174533
    toWorld = zCounterClockwise * toWorld;
}

void Drawable::scaleUp(void) {
    Matrix4 scaleUp;
    scaleUp.makeScale(1.1);
    toWorld = toWorld * scaleUp;
}

void Drawable::scaleDown(void) {
    Matrix4 scaleDown;
    scaleDown.makeScale(0.9);
    toWorld = toWorld * scaleDown;
    toWorld.print("toWorld");
}

void Drawable::reset(void) {
    toWorld.identity();
}
