#include "geometry.h"
#include "vertex.h"
#include "nodevisitor.h"
#include <vr/AC3DLoader.h>
#include <vr/Vec2.h>
#include <vr/Vec3.h>
#include <vr/Vec4.h>
#include <stdlib.h>
#include <GL/gl.h>


using namespace std;



// Initilaize vertex array
Geometry::Geometry(const int count){
    setVCount(count);      
    
    this->is_animation=false;
    
    this->state=new State();
}

void Geometry::setVCount(const int count)
{
    this->vcount=count;
    
    InitializeVerticesVector();
    
}

void Geometry::InitializeVerticesVector()
{
   //Vertex v[this->vcount];this->vertex=v;  
   this->vertex=(Vertex*)malloc(sizeof(Vertex)*(this->vcount));
}

// Destructor
Geometry::~Geometry(void)
{
    m_Parent = NULL;
    setVCount(0);
} 

void Geometry::accept(class NodeVisitor* v)
{
    v->visit(this);
}

// Get current vertex count
int Geometry::getVCount()
{
    return this->vcount;
}

void Geometry::addVertexCoordinate(int pos,vr::Vec3 v)
{
    this->vertex[pos].setVertex(v);    
}

vr::Vec3 Geometry::getVertexCoordinate(int pos)
{
    return this->vertex[pos].getVertex();
}

void Geometry::setMaterial(int pos,vr::AC3DLoader::Material m)
{
    this->vertex[pos].setMaterial(m);
}

vr::AC3DLoader::Material Geometry::getMaterial(int pos)
{
    return this->vertex[pos].getMaterial();
}

void Geometry::setNormal(int pos,const vr::Vec3 n)
{
    this->vertex[pos].setNormal(n);
}
vr::Vec3 Geometry::getNormal(int pos)
{
    return this->vertex[pos].getNormal();
}

void Geometry::setTextureCoordinate(int pos,const vr::Vec2 tc)
{
    this->vertex[pos].setTextureCoordinate(tc);
}

vr::Vec2 Geometry::getTextureCoordinate(int pos)
{
    return this->vertex[pos].getTextureCoordinate();
}

void Geometry::setState(State* state)
{
    this->state=state;
}
        
State Geometry::getState()
{
    return *(this->state);
}

int Geometry::getNodeType()
{
    return 3;
}

void Geometry::setAnimation(bool flag)
{
    this->is_animation=flag;
}

bool Geometry::getAnimation()
{
    return this->is_animation;
}
void Geometry::setVertexBuffer()
{
    
    this->vertices=(GLfloat*)malloc(sizeof(GLfloat)*(this->vcount)*3);
    this->colors=(GLfloat*)malloc(sizeof(GLfloat)*(this->vcount)*3);
    this->normals=(GLfloat*)malloc(sizeof(GLfloat)*(this->vcount)*3);
    this->texturecs=(GLfloat*)malloc(sizeof(GLfloat)*(this->vcount)*2);
    
    vr::Vec3 vertex;
    vr::Vec3 normal;
    vr::Vec2 texturec;
    vr::Vec4 col;
    int j=0;int k=0;
    for(int i=0;i<this->vcount;i++){
        vertex=this->vertex[i].getVertex();
        normal=this->getNormal(i);
        texturec=this->getTextureCoordinate(i);
        col=this->getMaterial(i).diffuse;
        this->vertices[j]=(GLfloat)vertex.x();this->colors[j]=(GLfloat)col.x();this->normals[j]=(GLfloat)normal.x();j++;
        this->vertices[j]=(GLfloat)vertex.y();this->colors[j]=(GLfloat)col.y();this->normals[j]=(GLfloat)normal.y();j++;
        this->vertices[j]=(GLfloat)vertex.z();this->colors[j]=(GLfloat)col.z();this->normals[j]=(GLfloat)normal.z();j++;
        
        this->texturecs[k]=(GLfloat)texturec.x();k++;
        this->texturecs[k]=(GLfloat)texturec.y();k++;
                             
                                
        
    } 
    cout << "**Rendering vertex count : " << this->vcount << "\n";
}



void Geometry::draw()
{
    
    this->getState().apply();
    
    this->getState().appyTexture();      
    
    this->getState().appyMaterial();
    
    if(this->getAnimation()){
        
    }
                
    setVertexBuffer();
    
    glVertexPointer(3,GL_FLOAT,0,this->vertices);
    glColorPointer(3,GL_FLOAT,0,this->colors);
    glNormalPointer(GL_FLOAT,0,this->normals);
    glTexCoordPointer(2,GL_FLOAT,0,this->texturecs);
    glDrawArrays(GL_TRIANGLES,0,this->vcount);
    
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    //glFlush();
    //glFinish();
    
}
