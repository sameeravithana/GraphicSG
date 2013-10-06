/* 
 * File:   scene.h
 * Author: samtube405
 *
 * Created on September 24, 2013, 4:11 PM
 */
#include "reader.h"
#include "sceneroot.h"
#include "group.h"


#ifndef SCENE_H
#define	SCENE_H

#include <map>

class Scene{
public:
    Scene();
    ~Scene();
    
    void setReader(Reader* r);
    
    SceneRoot* getRoot();
    
    void initGlut(int argc, char** argv);
    
    void DFS(Node* u);
    
    void renderScene();
    
    Group* createSceneGraph();
    //void InitializeGlutCallbacks();
    
private:
    
    Reader* cur_r;
    SceneRoot* root;
    
    
};


#endif	/* SCENE_H */

