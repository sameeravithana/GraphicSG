#ifdef WIN32
#  define _CRT_SECURE_NO_WARNINGS
#  include <windows.h>
#endif
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>


extern "C"
{
#include <png.h>
}
   
#include <vr/PNGReader.h>

using namespace vr;

static jmp_buf setjmp_buffer;

void warn_callback(png_structp, png_const_charp pc)
{
   std::cerr << "[PNGReader::warning]: ";
  
   if(pc) 
      std::cerr << pc << std::endl;
}

void err_callback(png_structp, png_const_charp pc)
{
  std::cerr << "[PNGReader::error]: ";
  
  if(pc) 
     std::cerr << pc << std::endl;

  longjmp(setjmp_buffer, 1);
}

unsigned char *read_png_file(const char *filename, int *w, int *h, int *c)
{
   png_structp png_ptr;
   png_infop   info_ptr;
   png_uint_32 width, height;

   FILE *fp;
   unsigned char *buffer = NULL;
   int bpp, color_type, interlace_type;
   int bytes_per_row, number_passes, channels, format;

   if((fp = fopen(filename, "rb")) == NULL)
   {
      std::cerr << "[read_png_file]: Could not read file " << filename << std::endl;
      return NULL;
   }

   png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, err_callback, warn_callback);

   if(!png_ptr)
   {
      std::cerr << "[read_png_file]: Internal error png_ptr == NULL\n";
      fclose(fp);
      return NULL;
   }

   info_ptr = png_create_info_struct(png_ptr);
   
   if(!info_ptr)
   {
      std::cerr << "[read_png_file]: Internal error info_ptr == NULL\n";
      fclose(fp);
      png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
      return NULL;
   }
   
   if(setjmp(setjmp_buffer))
   {
      png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
      fclose(fp);

      std::cerr << "[read_png_file]: Internal error (Unknown)\n";
      
      if(buffer)
         free(buffer);

      return NULL;
   }

   png_init_io(png_ptr, fp);
   png_read_info(png_ptr, info_ptr);
   png_get_IHDR(png_ptr, info_ptr, &width, &height, &bpp, 
                &color_type, &interlace_type, NULL, NULL);
   png_set_strip_16(png_ptr);

   if(color_type == PNG_COLOR_TYPE_PALETTE)
      png_set_expand(png_ptr);
   
   if(color_type == PNG_COLOR_TYPE_GRAY && bpp < 8)
      png_set_expand(png_ptr);

   if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
      png_set_expand(png_ptr);

   png_read_update_info(png_ptr, info_ptr);

   number_passes = png_set_interlace_handling(png_ptr);
   channels = png_get_channels(png_ptr, info_ptr);

   bytes_per_row = png_get_rowbytes(png_ptr, info_ptr);
   //buffer = (unsigned char *)malloc(bytes_per_row * height);
   buffer = new unsigned char[bytes_per_row * height];
   
   format = channels;

   if(buffer)
   {
      unsigned char *dummy[1];

      for(int pass=0; pass < number_passes; pass++)
      {
         for(int y=0; (unsigned int)y<height; y++)
         {
            dummy[0] = &buffer[bytes_per_row * (height-1-y)];
            png_read_rows(png_ptr, dummy, NULL, 1);
         }
      }

      png_read_end(png_ptr, info_ptr);
   }

   png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);

   fclose(fp);

   if(buffer)
   {
      *w = width;
      *h = height;
      
      //*c = (format == 3) ? GL_RGB : GL_RGBA;
//       switch (format)
//       {
//         default: // Default arbitrarily chosen to be LUMINANCE, this shouldn't happen...
//          case 1:
//             *c = GL_LUMINANCE;
//             break;

//          case 2:
//             *c = GL_LUMINANCE_ALPHA;
//             break;

//          case 3:
//             *c = GL_RGB;
//             break;

//          case 4:
//             *c = GL_RGBA;
//             break;
//       }
      *c = format;
   }

   return buffer;
}



PNGReader::PNGReader()
{
}

Image *PNGReader::readImage(const std::string &filename)
{
   int width;
   int height;
   int components;
   unsigned char *data;

   data = read_png_file(filename.c_str(), &width, &height, &components);

   if (data == 0)
      return 0;

   Image *newImage = new Image;
   newImage->setImage(width, height, 1, components, data);
   
   return newImage;
}

