//#include <GL/gl.h>
#include <vr/Image.h>


#include "texture.h"



Texture::Texture(const vr::Image* image,GLenum TextureTarget)
{
    this->gTextureImage=image;
}

Texture::~Texture()
{
    
}

bool Texture::hasTexture()
{
    return this->gTextureImage!=NULL;
}

const unsigned char* Texture::getTImageData()
{
    if(hasTexture())
        return this->gTextureImage->data();
    return NULL;
}

int Texture::getTImageWidth()
{
    if(hasTexture()) return this->gTextureImage->width();
    return 0;
}

int Texture::getTImageHeight()
{
    if(hasTexture()) return this->gTextureImage->height();
    return 0;
}

void Texture::createTexture(int n,GLuint* textures)
{
    glGenTextures(n,textures);
    
}

void Texture::BindTexture(GLenum target,GLuint* texture)
{
    glBindTexture(target, *texture);
}

void Texture::applyGLTexture2D(GLenum target,GLint level,GLint internalformat, int width, int height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{
    glTexImage2D(target, level,internalformat, width, height, border, format, type, pixels);
}
