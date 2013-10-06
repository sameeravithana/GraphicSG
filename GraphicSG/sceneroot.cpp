
#include "sceneroot.h"
#include "nodevisitor.h"
#include "state.h"
#include <stdio.h>

using namespace std;

SceneRoot::SceneRoot()
{
    
}

SceneRoot::~SceneRoot()
{
    
}

void SceneRoot::accept(NodeVisitor* v){
    v->visit(this);
}

void SceneRoot::initRendering()
{
    State state;
    state.setEnableLight(LIGHT0,true);
    state.setEnableLight(LIGHTING,true);
    state.setEnableColorMaterial(COLOR_MATERIAL,true);
        //glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
        //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
        //glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
    ///glEnable(GL_DEPTH_TEST);
    //glEnable(GL_NORMALIZE);
    
        
    state.setEnableClientState(VERTEX_ARRAY,true);
    state.setEnableClientState(COLOR_ARRAY,true);
    state.setEnableClientState(NORMAL_ARRAY,true);
    state.setEnableClientState(TEXTURE_COORD_ARRAY,true);
    state.setEnableSmooth(true);
    
    state.apply();
    
        
}

int SceneRoot::getNodeType(){
    return 0;
}