/* 
 * File:   texture.h
 * Author: samtube405
 *
 * Created on September 23, 2013, 6:56 PM
 */
#include <vr/Image.h>
#include <GL/gl.h>

#ifndef TEXTURE_H
#define	TEXTURE_H



class Texture{
        public:
            Texture(const vr::Image* image,GLenum TextureTarget);
            ~Texture();
            
            bool hasTexture();
            
            const unsigned char *getTImageData();
            int getTImageWidth();
            int getTImageHeight();
            
            void createTexture(int n,GLuint* textures);
            void BindTexture(GLenum target,GLuint* texture);
            
            void applyGLTexture2D(GLenum target,GLint level,GLint internalformat, int width, int height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
            
        private:
            
            GLenum m_textureTarget;
            GLuint m_textureObj;
            const vr::Image* gTextureImage;
    
    
};


#endif	/* TEXTURE_H */

