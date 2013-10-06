#include <vr/AC3DLoader.h>
#include <cstdio>
#include "reader.h"

Reader::Reader(const char* fpath)
{
    if(this->ac.load(fpath)){
        this->loadflag=true;        
    }
}

Reader::~Reader()
{
   
}



bool Reader::getLoadFlag()
{
    return this->loadflag;
}
vr::AC3DLoader* Reader::getFileNode()
{
    if(getLoadFlag())
        return &(this->ac);
    
    return NULL;
}
            
int Reader::getNumGeometries()
{
    if(getLoadFlag())
        return (int)this->ac.getNumGeometries();
    return 0;
}
            
const vr::AC3DLoader::GeometryArray* Reader::getGeometries()
{
    if(getLoadFlag())
        return &(this->ac.getGeometries());
    return NULL;
}
            
int Reader::getNumMaterials()
{
    if(getLoadFlag())
        return this->ac.getNumMaterials();
    return 0;
}

const vr::AC3DLoader::MaterialArray* Reader::getMaterials()
{
    if(getLoadFlag())
        return &(this->ac.getMaterials());
    return NULL;
}
