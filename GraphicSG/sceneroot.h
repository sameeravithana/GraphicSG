/* 
 * File:   sceneroot.h
 * Author: samtube405
 *
 * Created on September 25, 2013, 7:26 PM
 */


#ifndef SCENEROOT_H
#define	SCENEROOT_H

#include "node.h"


class SceneRoot : public Node{
public:
    SceneRoot();
    ~SceneRoot();
    
    void accept(class NodeVisitor* v);
    void initRendering();
    
    int getNodeType();
};


#endif	/* SCENEROOT_H */

