#include "OBJObject.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include "Globals.h"

#include <sstream>
#include <fstream>
#include <stdio.h>


#define deleteVector(__type__, __vect__) do {\
std::vector<__type__>::iterator iter; \
std::vector<__type__>::iterator end; \
iter = __vect__->begin();\
end = __vect__->end();\
while(iter != end) delete (*(iter++));\
delete __vect__;\
} while(false)

bool initialTranslate = 0;
bool initialScale = 0;

OBJObject::OBJObject(std::string filename) : Drawable()
{
    std::cout << "Creating OBJObject for " << filename << std::endl;
    this->vertices = new std::vector<Vector3>();
    // this->colors = new std::vector<Vector3*>(); // custom
    this->normals = new std::vector<Vector3>();
    this->faces = new std::vector<Face>();
    
    parse(filename);
}

OBJObject::~OBJObject()
{
    //Delete any dynamically allocated memory/objects here
    /*
     deleteVector(Vector3*, vertices);
     deleteVector(Vector3*, normals);
     deleteVector(Face*, faces); */
}

void OBJObject::draw(DrawData& data)
{
    //apply();
    float xMid = (extreme.xMax+extreme.xMin)/2.0;
    float yMid = (extreme.yMax+extreme.yMin)/2.0;
    float zMid = (extreme.zMax+extreme.zMin)/2.0;
    
    Matrix4 translation;
    translation.makeTranslate(-xMid, -yMid, -zMid);
    
    Matrix4 scale;
    float scaleNum = 14.72 * tan(30*(M_PI/180.0));
    scale.makeScale(scaleNum);
    
    material.apply();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    glBegin(GL_TRIANGLES);
    
    
    //Loop through the faces
    //For each face:
    //  Look up the vertices, normals (if they exist), and texcoords (if they exist)
    //  Draw them as triplets:
    
    //      glNorm(normals->at(face.normalIndices[0]))
    //      glVert(vertices->at(face.vertexIndices[0]))
    //      Etc.
    //
    
    
    for (int j = 0; j < faces->size(); j++) {
        for (int i = 0; i < 3; i++) {
            float nx = normals->at(faces->at(j).normalIndices[i]-1).getElement(0);
            float ny = normals->at(faces->at(j).normalIndices[i]-1).getElement(1);
            float nz = normals->at(faces->at(j).normalIndices[i]-1).getElement(2);
            
            float vx = vertices->at(faces->at(j).vertexIndices[i]-1).getElement(0);
            float vy = vertices->at(faces->at(j).vertexIndices[i]-1).getElement(1);
            float vz = vertices->at(faces->at(j).vertexIndices[i]-1).getElement(2);
            
            glNormal3f(nx, ny, nz);
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(vx, vy, vz);
        }
    }
    glEnd();
    glPopMatrix();
    
}

/*
void OBJObject::apply(void) {
    
    if (this == &Globals::bunny) {
        material.ambientColor = Color(0.8f,0.0f,0.0f,0.6f);
        material.diffuseColor = Color(1.0f,165.0/255.0,0.0f,1.0f);
        material.specularColor = Color(1.0f,0.0f,0.0f,0.0f);
        material.emissionColor = Color(0.0f,0.0f,0.0f,0.0f);
        material.shininess = 75.0;
        glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS, &material.shininess);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, material.specularColor.ptr());
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, material.diffuseColor.ptr());
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, material.ambientColor.ptr());
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, material.emissionColor.ptr());
    }
    else if (this == &Globals::dragon) {
        
        material.ambientColor = Color(0.0,0.0f,0.0f,0.0f);
        material.diffuseColor = Color(0.0,1.0f,0.0f,0.8f);
        material.specularColor = Color(0.0,.9f,.1f,0.5f);
        material.emissionColor = Color(0.0f,0.0f,0.0f,0.0f);
        material.shininess = 200.0;
        glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS, &material.shininess);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, material.specularColor.ptr());
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, material.diffuseColor.ptr());
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, material.ambientColor.ptr());
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, material.emissionColor.ptr());
    }
    else if (this == &Globals::bear) {
        material.ambientColor = Color(0.0f,0.0f,1.0f,1.0f);
        material.diffuseColor = Color(0.0,1.0f,1.0f,0.3f);
        material.specularColor = Color(0.0,.5f,.2f,1.0f);
        material.emissionColor = Color(0.0f,0.0f,0.0f,0.0f);
        material.shininess = 255.0;
        glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS, &material.shininess);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, material.specularColor.ptr());
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, material.diffuseColor.ptr());
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, material.ambientColor.ptr());
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, material.emissionColor.ptr());
    }
} */

void OBJObject::update(UpdateData& data)
{
    //
}

void OBJObject::parse(std::string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> tokens;
    std::vector<std::string> tokensFace;
    std::string token;
    
    int lineNum = 0;
    
    std::cout << "Starting parse..." << std::endl;
    //While all your lines are belong to us
    while (std::getline(infile, line))
    {
        //Progress
        if(++lineNum % 10000 == 0)
            std::cout << "At line " << lineNum << std::endl;
        
        //Split a line into tokens by delimiting it on spaces
        //"Er Mah Gerd" becomes ["Er", "Mah", "Gerd"]
        tokens.clear();
        tokens = split(line, ' ', tokens);
        
        if(tokens.at(0).compare("#") == 0 || tokens.at(0).compare(" ") == 0) {
            continue;
        }
        
        //If first token is a v then it gots to be a vertex
        if(tokens.at(0).compare("v") == 0)
        {
            //Parse the vertex line
            float x = std::stof(tokens.at(1));
            float y = std::stof(tokens.at(2));
            float z = std::stof(tokens.at(3));
            
            checkExtremes(extreme, x, y, z);
            
            vertices->push_back(Vector3(x, y, z));
            
            
            //float r = std::stof(tokens.at(4));
            //float g = std::stof(tokens.at(5));
            //float b = std::stof(tokens.at(6));
            
            // colors->push_back(new Vector3(r, g, b));
        }
        else if(tokens.at(0).compare("vn") == 0)
        {
            //Parse the normal line
            float nx = std::stof(tokens.at(1));
            float ny = std::stof(tokens.at(2));
            float nz = std::stof(tokens.at(3));
            
            normals->push_back(Vector3(nx, ny, nz));
        }
        else if(tokens.at(0).compare("f") == 0)
        {
            Face face;
            
            tokensFace.clear(); // necessary? prob not
            for (int i = 1; i < tokens.size(); i++) {
                tokensFace = split(tokens[i], '/', tokensFace);
            }
            
            face.vertexIndices[0] = std::stof(tokensFace.at(0));
            face.vertexIndices[1] = std::stof(tokensFace.at(3));
            face.vertexIndices[2] = std::stof(tokensFace.at(6));
            
            face.normalIndices[0] = std::stof(tokensFace.at(2));
            face.normalIndices[1] = std::stof(tokensFace.at(5));
            face.normalIndices[2] = std::stof(tokensFace.at(8));
            
            //Parse the face line
            faces->push_back(face);
        }
        else if(tokens.at(0).compare("How does I are C++?!?!!") == 0)
        {
            //Parse as appropriate
            //There are more line types than just the above listed
            //See the Wavefront Object format specification for details
        }
    }
    
    std::cout << "Done parsing." << std::endl;
    
    
    
    float xMid = (extreme.xMax+extreme.xMin)/2.0;
    float yMid = (extreme.yMax+extreme.yMin)/2.0;
    float zMid = (extreme.zMax+extreme.zMin)/2.0;
    
    // Center Vertices
    for (int i = 0; i < vertices->size(); i++) {
        Vector3 temp = vertices->at(i);
        //temp.print("before");
        temp.set(0, (temp.getElement(0)-xMid));
        temp.set(1, (temp.getElement(1)-yMid));
        temp.set(2, (temp.getElement(2)-zMid));
        vertices->at(i) = temp;
        // vertices->at(i).print("after");
    }
}

//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::vector<Vector3>* OBJObject::getVerticesCopy() {
    return vertices;
}

std::vector<Vector3>* OBJObject::getNormalsCopy() {
    return normals;
}

std::vector<Face>* OBJObject::getFacesCopy() {
    return faces;
}

void OBJObject::checkExtremes(Extremes &extreme, float x, float y, float z) {
    if (x < extreme.xMin)
        extreme.xMin = x;
    if (x > extreme.xMax)
        extreme.xMax = x;
    if (y < extreme.yMin)
        extreme.yMin = y;
    if (y > extreme.yMax)
        extreme.yMax = y;
    if (z < extreme.zMin)
        extreme.zMin = z;
    if (z > extreme.zMax)
        extreme.zMax = z;
}

/*
 void OBJObject::centerModel() {
 
 toWorld.identity();
 float xMid = (extreme.xMax+extreme.xMin)/2.0;
 float yMid = (extreme.yMax+extreme.yMin)/2.0;
 float zMid = (extreme.zMax+extreme.zMin)/2.0;
 
 // Apply Translation
 Matrix4 translation;
 translation.makeTranslate(-xMid, -yMid, -zMid);
 toWorld = translation * toWorld;
 
 } */

void OBJObject::scaleModel(float scaleNum) {
    // Compute Halfsizes
    float halfsize_x = (extreme.xMax - extreme.xMin)/2.0;
    float halfsize_y = (extreme.yMax - extreme.yMin)/2.0;
    float halfsize_z = (extreme.zMax - extreme.zMin)/2.0;
    
    std::cout << "Halfsizes are: " << std::endl;
    std::cout << "HS_x " << halfsize_x << std::endl;
    std::cout << "HS_y " << halfsize_y << std::endl;
    std::cout << "HS_z " << halfsize_z << std::endl;
    
    float largest_hs = halfsize_x;
    if (halfsize_y > largest_hs)
        largest_hs = halfsize_y;
    if (halfsize_z > largest_hs)
        largest_hs = halfsize_z;
    
    std::cout << "Largest HS is: " << largest_hs << std::endl;
    
    
    Matrix4 scaleMatrix;
    float scaleNum1 = (scaleNum * tan(30.0*(M_PI/180.0)))/largest_hs;
    scaleMatrix.makeScale(scaleNum1);
    toWorld.identity();
    toWorld = toWorld * scaleMatrix;
}


void OBJObject::scalePrep() {
    float scaleNum = 14.00;
    
    toWorld.identity();
    scaleModel(scaleNum);
}
