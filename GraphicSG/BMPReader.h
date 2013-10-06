/*
  Takes a filename, returns an array of RGB pixel data

  Loads:
  24bit bitmaps
  256 colour bitmaps
  16 colour bitmaps
  2 colour bitmaps  (Currently not working correctly)

  This code is designed for use in openGL programs, so bitmaps not correctly padded will not
  load properly, I believe this only applies to: 
  256cols if width is not a multiple of 4
  16cols if width is not a multiple of 8
  2cols if width is not a multiple of 32

  Sample code:

	BMPImage bmp;
	BMPLoad(fname,bmp);
	glTexImage2D(GL_TEXTURE_2D,0,3,bmp.width,bmp.height,0,GL_RGB,GL_UNSIGNED_unsigned char,bmp.bytes);

  You may use this code in non-commercial programs, and may modify it (especially if you
  manage to fix the 2cols mode) but I would appreciate a note crediting me and (to feed my
  ego) being told if you use it in something cool: cjbackhouse@hotmail.com
*/

#ifndef BMPREADER_H
#define BMPREADER_H

#include <string>
#include <vr/Image.h>


namespace vr
{
  class BMPReader
  {
    class BMPImage;
  public:

    enum BMPerror {
      BMPNOTABITMAP ='b',	//Possible error flags
      BMPNOOPEN ='o',
      BMPFILEERROR ='f',
      BMPNOERROR ='\0',
      BMPUNKNOWNFORMAT ='u'
    };


    BMPReader() : m_status(BMPNOERROR)  {}

    vr::Image *readImage(const std::string &);   
    int status() const { return m_status; }

  private:
    int m_status;
  };
}

//Translates my error codes into English	
//std::string TranslateBMPError(BMPError err);	


#endif
