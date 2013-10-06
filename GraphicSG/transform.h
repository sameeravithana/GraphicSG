/* 
 * File:   transform.h
 * Author: samtube405
 *
 * Created on September 21, 2013, 6:18 PM
 */

#ifndef TRANSFORM_H
#define	TRANSFORM_H

#include "group.h"
#include <vr/Vec3.h>
#include <vr/Vec4.h>

class Transform : public Group{
    public:
        Transform();
        ~Transform();
        
        void accept(class NodeVisitor* v);
                  
        void setTranslate(vr::Vec3 translate);
        vr::Vec3 getTranslate();
        bool getTranslateFlag();
        
        void setRotate(vr::Vec4 rotate);
        vr::Vec4 getRotate();
        bool getRotateFlag();
        
        void setScale(vr::Vec3 scale);
        vr::Vec3 getScale();
        bool getScaleFlag();
        
        void applyTransform();
        
        int getNodeType();
        
    private:
                
        vr::Vec3 translate;bool tflag;
        vr::Vec4 rotate;bool rflag;
        vr::Vec3 scale;bool sflag;
};


#endif	/* TRANSFORM_H */

