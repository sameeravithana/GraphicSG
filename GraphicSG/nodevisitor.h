/* 
 * File:   nodevisitor.h
 * Author: samtube405
 *
 * Created on September 25, 2013, 1:43 PM
 */
#include "transform.h"
#include "geometry.h"
#include "sceneroot.h"

#ifndef NODEVISITOR_H
#define	NODEVISITOR_H



class NodeVisitor{
    public:
        NodeVisitor();
        ~NodeVisitor();
        
        virtual void visit(SceneRoot *root) = 0;
        virtual void visit(Group *group) = 0;
        virtual void visit(Transform *transform) = 0;
        virtual void visit(Geometry *geometry) = 0;
};

#endif	/* NODEVISITOR_H */

