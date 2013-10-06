/* 
 * File:   material.h
 * Author: samtube405
 *
 * Created on September 23, 2013, 4:35 PM
 */
#include <GL/gl.h>
#include <vr/AC3DLoader.h>
#include <vr/Vec4.h>


#ifndef MATERIAL_H
#define	MATERIAL_H



typedef struct color{
            vr::Vec4 cambient;
            vr::Vec4 cdiffuse;
            vr::Vec4 cemission;
            vr::Vec4 cspecular;
            float shine;
            float trans;
        }gcolors;
        
enum face{
    FRONT=GL_FRONT,
    BACK=GL_BACK,
    FRONT_BACK=GL_FRONT_AND_BACK
};
enum mode{
    AMBIENT=GL_AMBIENT,
    DIFFUSE=GL_DIFFUSE,
    EMISSION=GL_EMISSION,
    SPECULAR=GL_SPECULAR,
    SHININESS=GL_SHININESS,
    AMBIENT_AND_DIFFUSE=GL_AMBIENT_AND_DIFFUSE
};

class Material{
        public:
            Material();
            ~Material();
            
                       
            void setAmbient(vr::Vec4 color);
            vr::Vec4 getAmbient();
            

            void setDiffuse(vr::Vec4 color);
            vr::Vec4 getDiffuse();

            void setEmission(vr::Vec4 color);
            vr::Vec4 getEmission();
            
            void setSpecular(vr::Vec4 color);
            vr::Vec4 getSpecular();

            void setShine(float shine);
            float getShine();
            
            void setTrans(float trans);
            float getTrans();
            
            bool isSet(mode m);
            
            float* getColorParam(vr::Vec4 param);
            
            void setFace(face f);
            void setMode(mode m);
            
            void applyMaterial();
    
        private:
            //vr::AC3DLoader::Material* m;
            gcolors gcolor;
            
            face f;
            mode m;
            
            
            bool flaga;
            bool flagd;
            bool flage;
            bool flags;
            bool flagsh;
            bool flagt;
    
};


#endif	/* MATERIAL_H */

