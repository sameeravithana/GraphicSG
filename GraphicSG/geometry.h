/* 
 * File:   geomtery.h
 * Author: samtube405
 *
 * Created on September 21, 2013, 3:05 PM
 */
#include <vr/AC3DLoader.h>
#include <vr/Vec2.h>
#include <vr/Vec3.h>
#include <vr/Vec4.h>

#include "node.h"
#include "material.h"
#include "vertex.h"
#include "state.h"



#ifndef GEOMTERY_H
#define	GEOMTERY_H




        
class Geometry : public Node{
    public:
        //Geometry();
        Geometry(const int count=0);
        ~Geometry();        
        
        int getVCount();        
               
        void accept(class NodeVisitor* v);   
        
        
        void addVertexCoordinate(int pos,const vr::Vec3 v);
        vr::Vec3 getVertexCoordinate(int pos); 
        
        void setMaterial(int pos,vr::AC3DLoader::Material m);
        vr::AC3DLoader::Material getMaterial(int pos);
        
        void setNormal(int pos,const vr::Vec3 n);
        vr::Vec3 getNormal(int pos);        
       
        void setTextureCoordinate(int pos,const vr::Vec2 tc);
        vr::Vec2 getTextureCoordinate(int pos);
        
        void setVertexBuffer();
        
        void setState(State* state);
        State getState();
        
        void draw();
        
        int getNodeType();
        
        void setAnimation(bool flag);
        bool getAnimation();
        
        
    private:
        void setVCount(const int count);
        void InitializeVerticesVector();
        
        Geometry* m_Parent;
        State* state;
        const char* m_Name;
        
        unsigned int vcount;
        unsigned int ccount;
        
        
        Vertex* vertex;
        
        GLfloat* vertices;
        GLfloat* colors;
        GLfloat* normals;
        GLfloat* texturecs;
        
        bool is_animation;
        
        
        
};


#endif	/* GEOMTERY_H */

