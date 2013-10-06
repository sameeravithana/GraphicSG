#ifndef __IMAGE_H
#define __IMAGE_H

#ifndef _MAC_OS_X
#include <GL/gl.h>
#else
#include <OpenGL/gl.h>
#endif

namespace vr
{
   class Image
   {
   public:
      Image();
      Image(const Image &);
      ~Image();

      int width()  const { return m_width;  }
      int height() const { return m_height; }
      int depth()  const { return m_depth;  }
      int format() const { return m_format; }
      int components() const { return m_components; }
      
      unsigned char *data() { return m_data; }
      const unsigned char *data() const { return m_data; }

      /*!
        THe Image is responsible for deleting data  
        so make sure you dont delete data after calling this method.
      */
      void setImage(int width, int height, int depth, int format, unsigned char *data);

   protected:
      int m_width;
      int m_height;
      int m_depth;
      GLenum m_format; // GL_RGB or GL_RGBA
      int m_components;

      unsigned char *m_data;
   };
}


#endif
