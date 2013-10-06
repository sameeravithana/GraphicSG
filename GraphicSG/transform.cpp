#include <vr/Vec3.h>
#include <vr/Vec4.h>

#include "nodevisitor.h"
#include "transform.h"
#include "group.h"

using namespace std;

Transform::Transform()
{
    this->tflag=false;
    this->rflag=false;
    this->sflag=false;
}

Transform::~Transform()
{
    
}

void Transform::accept(class NodeVisitor* v){
    v->visit(this);
}

void Transform::setTranslate(vr::Vec3 translate)
{
    this->translate=translate;
    this->tflag=true;
}

vr::Vec3 Transform::getTranslate()
{
    return this->translate;
}

bool Transform::getTranslateFlag()
{
    return this->tflag;
}





void Transform::setRotate(vr::Vec4 rotate)
{
    this->rotate=rotate;
    this->rflag=true;
}

vr::Vec4 Transform::getRotate()
{
    return this->rotate;
}

bool Transform::getRotateFlag()
{
    return this->rflag;
}

void Transform::setScale(vr::Vec3 scale)
{
    this->scale=scale;
    this->sflag=true;
}

vr::Vec3 Transform::getScale()
{
    return this->scale;
}

bool Transform::getScaleFlag()
{
    return this->sflag;
}

void Transform::applyTransform()
{
            
    if(this->getTranslateFlag()) glTranslatef(this->translate.x(),this->translate.y(),this->translate.z());
    if(this->getRotateFlag()) glRotatef(this->rotate.x(),this->rotate.y(),this->rotate.z(),this->rotate.w());
    if(this->getScaleFlag()) glScalef(this->scale.x(),this->scale.y(),this->scale.z());
   
}

int Transform::getNodeType(){
    return 2;
}

