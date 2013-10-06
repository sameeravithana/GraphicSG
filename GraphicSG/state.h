/* 
 * File:   state.h
 * Author: samtube405
 *
 * Created on September 24, 2013, 12:18 PM
 */


#include "material.h"
#include "texture.h"
#include "light.h"


#include <map>

using namespace std;

#ifndef STATE_H
#define	STATE_H

enum light{
    LIGHT0=GL_LIGHT0,
    LIGHT1=GL_LIGHT1,
    LIGHT2=GL_LIGHT2,
    LIGHT3=GL_LIGHT3,
    LIGHT4=GL_LIGHT4,
    LIGHT5=GL_LIGHT5,
    LIGHT6=GL_LIGHT6,
    LIGHT7=GL_LIGHT7,
    LIGHTING=GL_LIGHTING
};

enum polygonmode{
    FILL=GL_FILL,
    WIREFRAME=GL_LINE,
    POINTS=GL_POINT
};
/*enum polygonface{
    FRONT=GL_FRONT,
    BACK=GL_BACK,
    FRONT_BACK=GL_FRONT_AND_BACK
};*/
enum cullface{
    CULL_FACE=GL_CULL_FACE
};

enum colormaterial{
    COLOR_MATERIAL=GL_COLOR_MATERIAL
};

enum clientstate{
    COLOR_ARRAY=GL_COLOR_ARRAY, 
    EDGE_FLAG_ARRAY=GL_EDGE_FLAG_ARRAY, 
    FOG_COORD_ARRAY=GL_FOG_COORD_ARRAY, 
    INDEX_ARRAY=GL_INDEX_ARRAY, 
    NORMAL_ARRAY=GL_NORMAL_ARRAY, 
    SECONDARY_COLOR_ARRAY=GL_SECONDARY_COLOR_ARRAY, 
    TEXTURE_COORD_ARRAY=GL_TEXTURE_COORD_ARRAY, 
    VERTEX_ARRAY=GL_VERTEX_ARRAY
};


class State{//void enableState()
public:
    State();
    ~State();
    void setEnableLight(light state,bool flag);
    void setEnablePolygonMode(polygonmode state,face face);
    void setEnableSmooth(bool flag);
    void setEnableCullFace(cullface state,bool flag);
    void setEnableColorMaterial(colormaterial state,bool flag);
    void setEnableClientState(clientstate state,bool flag);
    
    void setEnableMaterial(Material* m,bool flag);
    void setEnableTexture(Texture* t,bool flag);
    void setEnableLighting(Light* l,bool flag);
    
    void appyMaterial();
    void appyTexture();
    void appyLighting();
    
    void applyWireFrame();
    
    void apply();
    
private:
    map<light,bool> map_light;
    map<polygonmode,face> map_polygonmode;
    map<cullface,bool> map_cullface;
    map<clientstate,bool> map_clientstate;
    map<colormaterial,bool> map_colormaterial;
    map<Material*,bool> map_material;
    map<Texture*,bool> map_texture;
    map<Light*,bool> map_lighting;

    void setEnable(GLenum face,bool flag);
    void setEnableClient(GLenum face,bool flag);
    Material* m;
    Texture* t;
    Light* l;
    
    
};


#endif	/* STATE_H */

