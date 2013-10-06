#include <GL/gl.h>
#include <GL/gl.h>

#include "light.h"


Light::Light()
{
    GLfloat lightC[4],lightP[4];
    
    this->lightColor=lightC;
    this->lightPos=lightP;
    
    //Default values    
    this->lightColor[0]=1.0f;
    this->lightColor[1]=1.0f;
    this->lightColor[2]=1.0f;
    this->lightColor[3]=1.0f;
    
    this->lightPos[0]=0.0f;
    this->lightPos[1]=0.0f;
    this->lightPos[2]=8.0f;
    this->lightPos[3]=0;
}

Light::~Light()
{
    
}

void Light::setLightColor(float r,float g,float b,float a)
{
    this->lightColor[0]=r;
    this->lightColor[1]=g;
    this->lightColor[2]=b;
    this->lightColor[3]=a;
}

void Light::setLightDirection(float x,float y,float z)
{
    this->lightPos[0]=x;
    this->lightPos[1]=y;
    this->lightPos[2]=z;
   
    
    
}

void Light::setLightPosition(int type)
{
    this->lightPos[3]=type;
}

void Light::applyLightColor(GLenum property,GLenum col)
{
    glLightfv(property, col, this->lightColor);
}

void Light::applyLightPosition(GLenum property,int type)
{
    setLightPosition(type);//0 For Directional, 1 For Positional 
    glLightfv(property, GL_POSITION, this->lightPos);
    
}

GLfloat* Light::getLightColor()
{
    return this->lightColor;
}

GLfloat* Light::getLightPosition()
{
    return this->lightPos;
}