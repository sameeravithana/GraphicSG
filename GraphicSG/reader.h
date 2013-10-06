/* 
 * File:   reader.h
 * Author: samtube405
 *
 * Created on September 22, 2013, 9:04 PM
 */

#ifndef READER_H
#define	READER_H

#include <vr/AC3DLoader.h>
#include <vr/Vec3.h>
#include <cstdio>

class Reader{
        public:
            Reader(const char* fpath);
            ~Reader();
            
            //vr::AC3DLoader*  LoadFile(const char* fpath);
            bool getLoadFlag();
            vr::AC3DLoader* getFileNode();
            
            int getNumGeometries();
            const vr::AC3DLoader::GeometryArray* getGeometries();
            
            int getNumMaterials();
            const vr::AC3DLoader::MaterialArray* getMaterials();
            
            
            
        private:
            vr::AC3DLoader ac;
            bool loadflag;
    
};


#endif	/* READER_H */

