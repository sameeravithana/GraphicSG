#ifndef __PNGREADER_H
#define __PNGREADER_H

#include <string>

#include <vr/Image.h>

namespace vr
{
   class PNGReader
   {
   public:
      PNGReader();

      /// \return a pointer to a loaded image, YOU are responsible for deleting it when done with it.
      Image *readImage(const std::string &);   
   };
}

#endif
