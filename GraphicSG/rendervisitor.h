/* 
 * File:   rendervisitor.h
 * Author: samtube405
 *
 * Created on September 25, 2013, 1:49 PM
 */

#ifndef RENDERVISITOR_H
#define	RENDERVISITOR_H

#include "nodevisitor.h"

using namespace std;

class RenderVisitor : public NodeVisitor{
    public:
        RenderVisitor();
        ~RenderVisitor();
        void visit(SceneRoot* root);
        void visit(Group* group);
        void visit(Transform* transform);
        void visit(Geometry* geometry);
        
};


#endif	/* RENDERVISITOR_H */

