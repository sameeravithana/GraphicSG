#include "material.h"

#include <GL/gl.h>
#include <vr/AC3DLoader.h>
#include <vr/Vec4.h>
#include <map>
#include <cstdio>

using namespace std;

map<mode,bool> map_modes;
map<mode,float*> map_params;

Material::Material()
{
    map_modes[AMBIENT]=false;
    map_modes[DIFFUSE]=false;
    map_modes[EMISSION]=false;
    map_modes[SPECULAR]=false;
    map_modes[SHININESS]=false;
}

Material::~Material()
{
    
}

float* Material::getColorParam(vr::Vec4 param)
{
    float* p;
    p[0]=param.x();
    p[1]=param.y();
    p[2]=param.z();
    p[3]=param.w();
    return p;
}

void Material::setAmbient(vr::Vec4 color)
{
    this->gcolor.cambient=color;
    map_modes[AMBIENT]=true;
    map_params[AMBIENT]=getColorParam(color);
}

vr::Vec4 Material::getAmbient()
{
    return this->gcolor.cambient;
}

void Material::setDiffuse(vr::Vec4 color)
{
    this->gcolor.cdiffuse=color;
    map_modes[DIFFUSE]=true;
    map_params[DIFFUSE]=getColorParam(color);
}

vr::Vec4 Material::getDiffuse()
{
    return this->gcolor.cdiffuse;
}

void Material::setEmission(vr::Vec4 color)
{
    this->gcolor.cemission=color;
    map_modes[EMISSION]=true;
    map_params[EMISSION]=getColorParam(color);
}

vr::Vec4 Material::getEmission()
{
    return this->gcolor.cemission;
}

void Material::setSpecular(vr::Vec4 color)
{
    this->gcolor.cspecular=color;
    map_modes[SPECULAR]=true;
    map_params[SPECULAR]=getColorParam(color);
}


vr::Vec4 Material::getSpecular()
{
    return this->gcolor.cspecular;
}

void Material::setShine(float shine)
{
    this->gcolor.shine=shine;
    map_modes[SHININESS]=true;
//    map_params[SHININESS]=getColorParam(color);
}

float Material::getShine()
{
    return this->gcolor.shine;
}


void Material::setTrans(float trans)
{
    this->gcolor.trans=trans;
}

float Material::getTrans()
{
    return this->gcolor.trans;
}

void Material::setFace(face f)
{
    this->f=f;
}

void Material::setMode(mode m)
{
    this->m=m;
}

bool Material::isSet(mode m)
{
    return map_modes[m];
}

void Material::applyMaterial()
{    
    for(map<mode,bool>::iterator iter = map_modes.begin(); iter != map_modes.end(); ++iter){
                mode k= iter->first;
                bool flag=iter->second;
                if(flag) glMaterialfv(this->f,this->m,map_params[k]);
    }
    
}