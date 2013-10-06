#include <cstring>
#ifdef WIN32
#include <windows.h>
#endif
#include <vr/Image.h>

using namespace vr;

Image::Image()
   : m_width(0),
     m_height(0),
     m_depth(0),
     m_format(0),
     m_components(0),
     m_data(0)
{
}

Image::Image(const Image &i)
   : m_width(i.m_width),
     m_height(i.m_height),
     m_depth(i.m_depth),
     m_format(i.m_format),
     m_components(i.m_components),
     m_data(0)
{
   if(i.m_data)
   {
//       int components = 
//          m_format == GL_RGB  ? 3 :
// #ifndef WIN32
//       m_format == GL_BGR  ? 3 :
//          m_format == GL_BGRA ? 4 :
// #endif
//          m_format == GL_RGBA ? 4 : 4;

//      int components;
//       switch (m_format)
//       {
//          default: // Default arbitrarily chosen to be 1 component, this shouldn't happen...
//          case GL_LUMINANCE:
//             components = 1;
//             break;

//          case GL_LUMINANCE_ALPHA:
//             components = 2;
//             break;

//          case GL_RGB:
//             components = 3;
//             break;

//          case GL_RGBA:
//             components = 4;
//             break;
//       }
      
      //int size = m_width * m_height * m_depth * components;
      int size = m_width * m_height * m_depth * m_components;

      if(m_data)
         delete[] m_data;

      m_data = new unsigned char[size];

      memcpy(m_data, i.m_data, size);
   }
}

Image::~Image()
{
//   if(m_data)
      delete[] m_data;
}

void Image::setImage(int width, int height, int depth, int components, unsigned char *data)
{
   m_depth  = depth;
   m_width  = width;
   m_height = height;

   m_components = components;

   switch (components)
   {
      default: // Default arbitrarily chosen to be LUMINANCE, this shouldn't happen...
      case 1:
         m_format = GL_LUMINANCE;
         break;

      case 2:
         m_format = GL_LUMINANCE_ALPHA;
         break;

      case 3:
         m_format = GL_RGB;
         break;

      case 4:
         m_format = GL_RGBA;
         break;
   }

//   if(m_data)
      delete[] m_data;   
   
   m_data = data;
}
