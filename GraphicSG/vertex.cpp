#include "vertex.h"

#include "material.h"


#include <vr/AC3DLoader.h>
#include <vr/Vec3.h>
#include <vr/Vec2.h>
#include <cstdio>
#include <iostream>
#include <stdlib.h>

using namespace std;

Vertex::Vertex()
{
    
}

Vertex::~Vertex()
{
    
}

void Vertex::setVertex(vr::Vec3 v)
{
    this->vertex=v;
   
}

vr::Vec3 Vertex::getVertex()
{
    
    return this->vertex;
    
}
    
void Vertex::setMaterial(vr::AC3DLoader::Material m)
{
    
    this->ac_mat=m;
}
    


vr::AC3DLoader::Material Vertex::getMaterial()
{
    return this->ac_mat;
}
    
void Vertex::setNormal(vr::Vec3 n)
{
    this->normal=n;
}
    
vr::Vec3 Vertex::getNormal(){
    return this->normal;
}
    
void Vertex::setTextureCoordinate(vr::Vec2 tc)
{
    this->textureCoordinate=tc;
}

vr::Vec2 Vertex::getTextureCoordinate()
{
    return this->textureCoordinate;
}
