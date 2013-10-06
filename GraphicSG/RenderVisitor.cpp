#include "transform.h"
#include "geometry.h"
#include "sceneroot.h"
#include <GL/gl.h>

#include "rendervisitor.h"

using namespace std;

RenderVisitor::RenderVisitor()
{
    
}

RenderVisitor::~RenderVisitor()
{
    
}

void RenderVisitor::visit(SceneRoot* root){
                cout << "Visit Root " << "\n";
                root->initRendering();
        }

void RenderVisitor::visit(Group* group){
                cout << "Visit Group " << group->GetNodeName() << "\n";
                group->setGroupBackground();
        }

void RenderVisitor::visit(Transform* transform){
                cout << "Visit Transform " << "\n";
                transform->applyTransform();
        }

void RenderVisitor::visit(Geometry* geometry){
                cout << "Visit Geometry" << "\n";
                geometry->draw();
        }