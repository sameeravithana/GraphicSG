/* 
 * File:   light.h
 * Author: samtube405
 *
 * Created on September 23, 2013, 9:54 PM
 */

#ifndef LIGHT_H
#define	LIGHT_H

#include <GL/gl.h>

class Light{
    public:
        Light();
        ~Light();
        void setLightColor(float r,float g,float b,float a);
        void setLightDirection(float x,float y,float z);
        
        void setLightPosition(int type);
        
        void applyLightColor(GLenum property,GLenum col);
        void applyLightPosition(GLenum property,int type);
        
        GLfloat* getLightColor();
        GLfloat* getLightPosition();
        
    private:
        GLfloat* lightColor;
        GLfloat* lightPos;
        
       
        
          
    
    
    
};


#endif	/* LIGHT_H */

