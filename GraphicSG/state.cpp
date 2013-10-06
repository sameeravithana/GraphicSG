#include "texture.h"
#include "material.h"
#include "light.h"

#include "state.h"


#include <map>
#include <stdio.h>
#include <iostream>
#include <GL/glext.h>


#define FORI(x,j) \
    for(int x=0;x<j;x++)

using namespace std;




State::State()
{
    
}

State::~State()
{
    
}

void State::setEnable(GLenum face,bool flag){
    if(flag) glEnable(face);
    else{
        glDisable(face);
    }
}

void State::setEnableClient(GLenum face,bool flag){
    if(flag) glEnableClientState(face);
    else{
        glDisableClientState(face);
    }
}

void State::setEnableLight(light state,bool flag)
{
    //setEnable(state,flag);
    this->map_light[state]=flag;
}

void State::setEnablePolygonMode(polygonmode state,face face)
{    
    this->map_polygonmode[state]=face;
}

void State::setEnableSmooth(bool flag)
{
    
    if(flag) glShadeModel(GL_SMOOTH);
    else{
        glShadeModel(GL_FLAT);
    }
}

void State::setEnableCullFace(cullface state,bool flag)
{
    //setEnable(state,flag);
    
    this->map_cullface[state]=flag;
}

void State::setEnableClientState(clientstate state,bool flag)
{
    this->map_clientstate[state]=flag;
}

void State::setEnableColorMaterial(colormaterial state,bool flag)
{
    //setEnable(state,flag);
   
    this->map_colormaterial[state]=flag;
}

void State::setEnableMaterial(Material* m,bool flag)
{
    this->m=m;
    this->map_material[m]=flag;
    
}

void State::setEnableTexture(Texture* t,bool flag)
{
    this->t=t;
    this->map_texture[t]=flag;
}

void State::setEnableLighting(Light* l,bool flag)
{
    this->l=l;
    this->map_lighting[l]=flag;
}

void State::apply()
{
      
    for(map<light,bool>::iterator iter = this->map_light.begin(); iter != this->map_light.end(); ++iter){
                light k= iter->first;
                bool flag=iter->second;
                if(flag) setEnable(k,flag);
    }
    for(map<polygonmode,face,bool>::iterator iter = this->map_polygonmode.begin(); iter != this->map_polygonmode.end(); ++iter){
                polygonmode k= iter->first;
                face l=iter->second;
                
                glPolygonMode(l,k);
                
               
    }
    for(map<cullface,bool>::iterator iter = this->map_cullface.begin(); iter != this->map_cullface.end(); ++iter){
                cullface k= iter->first;
                bool flag=iter->second;
                if(flag) setEnable(k,flag);
    }
    for(map<clientstate,bool>::iterator iter = this->map_clientstate.begin(); iter != this->map_clientstate.end(); ++iter){
                clientstate k= iter->first;
                bool flag=iter->second;
                if(flag) setEnableClient(k,flag);
    }
    for(map<colormaterial,bool>::iterator iter = this->map_colormaterial.begin(); iter != this->map_colormaterial.end(); ++iter){
                colormaterial k= iter->first;
                bool flag=iter->second;
                if(flag) setEnable(k,flag);
    }
    
    
    
}

void State::applyWireFrame(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}

void State::appyMaterial(){
    for(map<Material*,bool>::iterator iter = this->map_material.begin(); iter != this->map_material.end(); ++iter){
                Material* k= iter->first;
                bool flag=iter->second;
                if(flag) k->applyMaterial();
    }
}

void State::appyTexture(){
 
    
    glEnable(GL_TEXTURE_2D);
 
    for(map<Texture*,bool>::iterator iter = this->map_texture.begin(); iter != this->map_texture.end(); ++iter){
                Texture* k= iter->first;
                bool flag=iter->second;
                if(flag){
                    if(k->hasTexture()){
                        GLuint textureID;
                        const unsigned char* data=k->getTImageData();
                        int width=k->getTImageWidth();
                        int height=k->getTImageHeight();
                        k->createTexture(1,&textureID);
                        k->BindTexture(GL_TEXTURE_2D,&textureID);
                        k->applyGLTexture2D(GL_TEXTURE_2D , 0 , GL_RGB , 
                            width , height , 0, GL_BGR , GL_UNSIGNED_BYTE , 
                            data);
                        
                        glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT);
                        glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_CLAMP);

                        
  
                    }
                }
                    
    }
}

void State::appyLighting(){
    for(map<Light*,bool>::iterator iter = this->map_lighting.begin(); iter != this->map_lighting.end(); ++iter){
                Light* k= iter->first;
                bool flag=iter->second;
                if(flag){
                    k->applyLightColor(GL_LIGHT0, GL_AMBIENT);
                    k->applyLightColor(GL_LIGHT0, GL_SPECULAR);    
                    k->applyLightPosition(GL_LIGHT0,1);
                }
    }
}