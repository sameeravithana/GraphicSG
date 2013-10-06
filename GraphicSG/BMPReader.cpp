/* Takes a filename, returns an array of RGB pixel data

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
	glTexImage2D(GL_TEXTURE_2D,0,3,bmp.width(),bmp.height(),0,GL_RGB,GL_UNSIGNED_BYTE,bmp.data());
*/

#ifdef WIN32
#  define _CRT_SECURE_NO_WARNINGS
#  include <windows.h>
#endif

#include "vr/BMPReader.h"
#include <cstdio>
#define PIXEL(X,Y,C,WIDTH,DATA) DATA[(Y*WIDTH+X)*3+C]

/*
std::string TranslateBMPError(BMPError err)
{
	switch(err)
	{
	case(BMPNOTABITMAP):
		return "This file is not a bitmap, specifically it doesn't start 'BM'";
	case(BMPNOOPEN):
		return "Failed to open the file, suspect it doesn't exist";
	case(BMPFILEERROR):
		return "Some kind of error while physically reading the file";
	case(BMPNOERROR):
		return "No errors detected";
	case(BMPUNKNOWNFORMAT):
		return "Unknown bmp format, ie not 24bit, 256,16 or 2 colour";
	default:
		return "Not a valid error code";
	}
}
*/

using namespace vr;


vr::Image *BMPReader::readImage(const std::string& fname)
{
	FILE * f=fopen(fname.c_str(),"rb");		//open for reading in binary mode
  if(!f) {
    m_status = BMPNOOPEN;
    return 0;
  }

  char header[54];
	fread(header,54,1,f);			//read the 54bit main header

	if(header[0]!='B' || header[1]!='M') 
	{
		fclose(f);
		m_status =  BMPNOTABITMAP;		//all bitmaps should start "BM"
    return 0;
	}

  int w,h;
  if(sizeof(int)==4)	//Annoyingly I can't just assume this
	{
		w=*(int*)(header+18);
		h=*(int*)(header+22);
	}
	else
	{
		w=header[18]+256*header[19]+256*256*header[20]+256*256*256*header[21];
		h=header[22]+256*header[23]+256*256*header[24]+256*256*256*header[25];
	}

  unsigned char *data=0L;
 
  // Allocate memory
  data = new unsigned char[w*h*3];

	int bits=int(header[28]);		//colourdepth

	int x,y,c;
	unsigned char cols[256*4];
	switch(bits)
	{
	case(24):
		fread(data,w*h*3,1,f);	//24bit is easy
		for(x=0;x<w*h*3;x+=3)			//except the format is BGR, grr
		{
			unsigned char temp=data[x];
			data[x]=data[x+2];
			data[x+2]=temp;
		}
		break;

	case(8):
		fread(cols,256*4,1,f);							//read colortable
		for(y=0;y<h;++y)						//(Notice 4bytes/col for some reason)
			for(x=0;x<w;++x)
			{
				unsigned char byte;			
				fread(&byte,1,1,f);						//just read byte					
				for(int c=0;c<3;++c)
          PIXEL(x,y,c,w,data)=cols[byte*4+2-c];	//and look up in the table
			}
		break;

	case(4):
		fread(cols,16*4,1,f);
		for(y=0;y<256;++y)
			for(x=0;x<256;x+=2)
			{
				unsigned char byte;
				fread(&byte,1,1,f);						//as above, but need to extract two
				for(c=0;c<3;++c)						//pixels from each byte
					PIXEL(x,y,c,w,data)=cols[byte/16*4+2-c];
				for(c=0;c<3;++c)
					PIXEL(x+1,y,c,w,data)=cols[byte%16*4+2-c];
			}
		break;

	//NOT CURRENTLY WORKING PROPERLY
	case(1):
		fread(cols,8,1,f);		//colourtable
		for(y=0;y<256;++y)
			for(x=0;x<256;x+=8)
			{
				unsigned char byte;
				fread(&byte,1,1,f);
				//The idea here is that every byte is eight pixels
				//so I'm shifting the byte to the relevant position, then masking out
				//all but the lowest bit in order to get the index into the colourtable.
				for(int x2=0;x2<8;++x2)
				{
					for(int c=0;c<3;++c)
						PIXEL(x+x2,y,c,w,data)=cols[((byte>>(7-x2))&1)*4+2-c];
				}
			}
		break;
	default:
		fclose(f);
    m_status = BMPUNKNOWNFORMAT;
    delete [] data;
    return 0;
	}

	fclose(f);
  if(ferror(f)) {
    delete [] data;
    m_status = BMPFILEERROR;
    return 0;
  }

  vr::Image *image = new vr::Image();
  //image->setImage(w,h,1,GL_RGB, data);
  image->setImage(w,h,1,3, data);
  m_status = BMPNOERROR;
  return image;
}

//BMPError BMPLoad(std::string fname){BMPImage bmp;return BMPLoad(fname,bmp);}
/*

#ifdef __gl_h
BMPError BMPLoadGL(std::string fname)
{
	BMPImage bmp;
	BMPError e=BMPLoad(fname,bmp);
	if(e!=BMPNOERROR) return e;
		
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,3,bmp.width(),bmp.height(),0,GL_RGB,GL_UNSIGNED_BYTE,bmp.data());

	return BMPNOERROR;
}
#endif
*/
