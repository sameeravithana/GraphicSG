/* 
 * File:   vertex.h
 * Author: samtube405
 *
 * Created on September 24, 2013, 5:31 PM
 */
#include "material.h"

#ifndef VERTEX_H
#define	VERTEX_H

#include <vr/AC3DLoader.h>
#include <vr/Vec3.h>
#include <vr/Vec2.h>


class Vertex{
public:
    Vertex();
    ~Vertex();
    
    void setVertex(vr::Vec3 v);
    vr::Vec3 getVertex();
    
    void setMaterial(vr::AC3DLoader::Material m);
    //Material* getMaterial();
    vr::AC3DLoader::Material getMaterial();
    
    void setNormal(vr::Vec3 n);
    vr::Vec3 getNormal();
    
    void setTextureCoordinate(vr::Vec2 tc);
    vr::Vec2 getTextureCoordinate();
    
private:
    vr::Vec3 vertex;
    Material* material;
    vr::Vec3 normal;
    vr::Vec2 textureCoordinate;
    
    vr::AC3DLoader::Material ac_mat;
    
    
};


#endif	/* VERTEX_H */

