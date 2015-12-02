#ifndef CSE167_OBJObject_h
#define CSE167_OBJObject_h

#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"
#include "Drawable.h"

struct Face
{
    int vertexIndices[3];
    int normalIndices[3];
    //Add more members as necessary
};

struct Extremes
{
    float xMin = FLT_MAX;
    float xMax = FLT_MIN;
    float yMin = FLT_MAX;
    float yMax = FLT_MIN;
    float zMin = FLT_MAX;
    float zMax = FLT_MIN;
};

class OBJObject : public Drawable
{
    
protected:
    
    //Storage vectors
    std::vector<Vector3>* vertices;
    // std::vector<Vector3*>* colors; // Custom
    std::vector<Vector3>* normals;
    std::vector<Face>* faces;
    Extremes extreme;
    
    //Helper functions
    std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
    std::vector<std::string> split(const std::string&, char);
    
    //Parse
    void parse(std::string&);
    
public:
    
    OBJObject(std::string);
    OBJObject(){};
    virtual ~OBJObject(void);
    
    virtual void draw(DrawData&);
    void apply(void);
    virtual void update(UpdateData&);
    
    std::vector<Vector3>* getVerticesCopy(void);
    std::vector<Vector3>* getNormalsCopy(void);
    std::vector<Face>* getFacesCopy(void);
    
    void checkExtremes(Extremes&, float, float, float);
    /*
     float get_xMin(void);
     float get_xMax(void);
     float get_yMin(void);
     float get_yMax(void);
     float get_zMin(void);
     float get_zMax(void); */
    
    void scalePrep(void);
    void centerModel(void);
    float maxOf3(float, float, float);
    void scaleModel(float);
};

#endif
