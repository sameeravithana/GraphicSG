#include <iostream>

#ifdef WIN32
#include <windows.h>
#endif

#include <vr/Image.h>
#include <vr/PNGReader.h>
#include <vr/BMPReader.h>
#include <vr/AC3DLoader.h>
#include <iterator>    // for back_inserter
#include <locale>
#include <string>
#include <algorithm>
#include <cctype>      // old <ctype.h>
#include <cstring>


struct ToUpper
{
  ToUpper(std::locale const& l) : loc(l) {;}
  char operator() (char c) const  { return std::toupper(c,loc); }
private:
  std::locale const& loc;
};




using namespace vr;

AC3DLoader::AC3DLoader()
{
}

AC3DLoader::~AC3DLoader()
{
}

bool AC3DLoader::load(const char *fname)
{
   std::string buff;

   if(strlen(fname) > 0)
   {
      m_fin.open(fname, std::ios::in);

      if(!m_fin.is_open())
      {
         std::cerr << "[AC3DLoader::load] Can't open " << fname << " for loading\n";
         return false;
      }

      std::getline(m_fin, buff);

      std::string::size_type pos = buff.find("AC3D");
      if(pos == std::string::npos)
      {
         std::cerr << "[AC3DLoader::load] " << fname << " is not a valid AC3D file.\n";
         m_fin.close();
         return false;
      }

      std::getline(m_fin, buff);

      while(!m_fin.eof())
      {
         if(buff.find("MATERIAL") != std::string::npos)
            parseMaterial(buff);
         else if(buff.find("OBJECT") != std::string::npos)
            if (!parseObject())
              return false;

         std::getline(m_fin, buff);
      }

      m_fin.close();

      if (!processObjects())
        return false;
   }
  return true;
}

void AC3DLoader::parseMaterial(std::string &str)
{
   std::string dummy;
   std::stringstream ss(str);

   Material mat;

   ss >> dummy >> dummy
      >> dummy >> mat.diffuse[0]  >> mat.diffuse[1]  >> mat.diffuse[2] 
      >> dummy >> mat.ambient[0]  >> mat.ambient[1]  >> mat.ambient[2]
      >> dummy >> mat.emission[0] >> mat.emission[1] >> mat.emission[2]
      >> dummy >> mat.specular[0] >> mat.specular[1] >> mat.specular[2]
      >> dummy >> mat.shine
      >> dummy >> mat.trans;
      mat.diffuse[3]=1.0f;
      mat.ambient[3]=1.0f;
      mat.emission[3]=1.0f;
      mat.specular[3]=1.0f;

   m_materials.push_back(mat);
}

bool AC3DLoader::parseObject(void)
{
   ACObject ob;
   std::string buff;
   std::string command;
   std::stringstream ss("");

   clearObject(ob);

   do
   {
      std::getline(m_fin, buff);

      ss.str(buff);
      ss.clear();

      ss >> command;

      if(command == "name") {
        ss>> ob.name;
        if (ob.name.length() > 2) {
          ob.name = ob.name.substr(1,ob.name.length()-2);
        }
      }
      if ( command == "data" || command == "URL" )
      {
         /* Skip */
      }
      else if(command == "texture")
      {
        std::string texture_name;
        std::locale  loc_c("C");
        ToUpper      up(loc_c);
        ss >> texture_name;

        std::string upper = texture_name;
        std::transform(upper.begin(), upper.end(), upper.begin(), up);

        if (upper.find(".PNG") != upper.npos) {
        
          PNGReader r;
          Image *img = r.readImage(texture_name.substr(1, texture_name.length()-2));

          if(img)
            ob.texture = img;
          else 
            std::cerr << "[AC3DLoader::parseObject] Warning: Unable to load texture: " << texture_name << std::endl;          
        }
        else if(upper.find(".BMP") != upper.npos) {
          BMPReader r;
          Image *img = r.readImage(texture_name.substr(1, texture_name.length()-2));

          if(img)
            ob.texture = img;
          else 
            std::cerr << "[AC3DLoader::parseObject] Warning: Unable to load texture: " << texture_name << std::endl;          
        }
        else {
          std::cerr << "[AC3DLoader::parseObject] Invalid image type, can only handle .png and .bmp\n";
          return false;
        }
      }
      else if(command == "texrep")
      {
         ss >> ob.texture_repeat[0] >> ob.texture_repeat[1];
      }
      else if(command == "texoff")
      {
         ss >> ob.texture_offset[0] >> ob.texture_offset[1];
      }
      else if(command == "rot")
      {
         /* TODO? */
      }
      else if(command == "loc")
      {
         ss >> ob.loc[0] >> ob.loc[1] >> ob.loc[2];
      }
      else if(command == "numvert")
      {
         ss >> ob.num_vert;

         if(ob.num_vert > 0)
         {
            ob.vertices = new Vec3[ob.num_vert];

            for(int n=0; n<ob.num_vert; n++)
            {
               Vec3 v;
               std::getline(m_fin, buff);
               ss.str(buff);
               ss.clear();

               ss >> v[0] >> v[1] >> v[2];

               ob.vertices[n] = v;
            }
         }
      }
      else if(command == "numsurf")
      {
         ss >> ob.num_face;

         if(ob.num_face > 0)
         {
            ob.faces = new ACFace[ob.num_face];

            for(int n=0; n<ob.num_face; n++)
            {
               ACFace *newf = parseFace(ob, &ob.faces[n]);

               if(!newf)
               {
                  std::cerr << "[AC3DLoader::parseObject] error while reading face\n";
                  return false;
               }
            }
         }
      }
   } while(command != "kids");

   /* No need to save empty objects */
   if(ob.num_vert > 0 && ob.num_face > 0)
   {
      m_ac_objects.push_back(ob);
   }
   return true;
}

AC3DLoader::ACFace *AC3DLoader::parseFace(ACObject &ob, ACFace *s)
{
   std::string buff;
   std::string command;
   std::stringstream ss("");

   while(!m_fin.eof())
   {
      std::getline(m_fin, buff);

      ss.str(buff);
      ss.clear();

      ss >> command;

      if(command == "SURF")
      {
         ss >> std::hex >> s->flags >> std::dec;
      }
      else if(command == "mat")
      {
         ss >> s->material;
      }
      else if(command == "refs")
      {
         ss >> s->num_vertref;

         if(s->num_vertref > 0)
         {
            s->vertref = new int[s->num_vertref];
            s->uvs     = new Vec2[s->num_vertref];

            for(int n=0; n<s->num_vertref; n++)
            {
               float tmp1, tmp2;
               
               std::getline(m_fin, buff);

               ss.str(buff);
               ss.clear();

               ss >> s->vertref[n] >> tmp1 >> tmp2;
               s->uvs[n].set(tmp1, tmp2);
            }

            return s;
         }
      }
   }

   return NULL;
}

bool AC3DLoader::processObject(ACObject &obj)
{
   int nvert = obj.num_vert;
   int nface = obj.num_face;
   int ntris = 0;

   int cur_tri = 0;
   
   Geometry geom;
   geom.m_name = obj.name;
   geom.m_translation = obj.loc;

   // Calculate total number of triangles taking into account 
   // multiple triangles in polygons
   for(int i=0; i<obj.num_face; i++)
   {
      if(obj.faces[i].num_vertref >=3)
      {
         ntris += obj.faces[i].num_vertref - 2;
      }
   }

   int **triangles = new int *[ntris];
   for(int i=0; i<ntris; i++)
      triangles[i] = new int[3];

   std::vector<int> *vert_hash = new std::vector<int>[nvert];

   int *smooth = new int[ntris];
   int *mat    = new int[ntris];
   int is_smooth;

   // Loop over faces triangulating
   for(int i=0; i<nface; i++)
   {
      if(obj.faces[i].flags & SURFACE_SHADED)
         is_smooth = 1;   
      else
         is_smooth = 0;

      if(obj.faces[i].num_vertref == 3)
      {
         triangles[cur_tri][0] = obj.faces[i].vertref[0];
         triangles[cur_tri][1] = obj.faces[i].vertref[1];
         triangles[cur_tri][2] = obj.faces[i].vertref[2];

         vert_hash[triangles[cur_tri][0]].push_back(cur_tri);
         vert_hash[triangles[cur_tri][1]].push_back(cur_tri);
         vert_hash[triangles[cur_tri][2]].push_back(cur_tri);

         smooth[cur_tri] = is_smooth;
         mat[cur_tri]    = obj.faces[i].material;

         //TODO:
         //ob.texture_offset_x + TextureCoordinate._v[0] * ob.texture_repeat_x;
         geom.m_texcoords.push_back(obj.faces[i].uvs[0]);
         geom.m_texcoords.push_back(obj.faces[i].uvs[1]);
         geom.m_texcoords.push_back(obj.faces[i].uvs[2]);

         cur_tri++;
      }
      else if(obj.faces[i].num_vertref > 3)
      {
         for(int j=1; j<obj.faces[i].num_vertref-1; j++)
         {
            triangles[cur_tri][0] = obj.faces[i].vertref[0];
            triangles[cur_tri][1] = obj.faces[i].vertref[j];
            triangles[cur_tri][2] = obj.faces[i].vertref[j+1];

            vert_hash[triangles[cur_tri][0]].push_back(cur_tri);
            vert_hash[triangles[cur_tri][1]].push_back(cur_tri);
            vert_hash[triangles[cur_tri][2]].push_back(cur_tri);
         
            geom.m_texcoords.push_back(obj.faces[i].uvs[0]);
            geom.m_texcoords.push_back(obj.faces[i].uvs[j]);
            geom.m_texcoords.push_back(obj.faces[i].uvs[j+1]);

            smooth[cur_tri] = is_smooth;
            mat[cur_tri]    = obj.faces[i].material;
         
            cur_tri++;
         }
      }
   }

   Vec3 v0, v1, v2, normal;

   for(int i=0; i<ntris; i++)
   {
      v0 = obj.vertices[triangles[i][0]];
      geom.m_vertices.push_back( v0 );

      v1 = obj.vertices[triangles[i][1]];
      geom.m_vertices.push_back( v1 );

      v2 = obj.vertices[triangles[i][2]];
      geom.m_vertices.push_back( v2 );

      calcFaceNormal(v0, v1, v2, normal);

      geom.m_normals.push_back( normal );
      geom.m_normals.push_back( normal );
      geom.m_normals.push_back( normal );
   
      geom.m_materials.push_back( mat[i] );
      geom.m_materials.push_back( mat[i] );
      geom.m_materials.push_back( mat[i] );
   }

   int total, tri;
   Vec3 b, c;
   float thresh = 0.25;
   
   for(int i=0; i<ntris; i++)
   {
      if(smooth[i] == 0)
         continue;
      
      for(int j=0; j<3; j++)
      {
         total = 1;
         c = b = geom.m_normals[3*i+j];
         
         for(unsigned int k=0; k<vert_hash[triangles[i][j]].size(); k++)
         {
            tri = vert_hash[triangles[i][j]][k];

            if(tri != i)
            {
               v0 = obj.vertices[triangles[tri][0]];
               v1 = obj.vertices[triangles[tri][1]];
               v2 = obj.vertices[triangles[tri][2]];
               
               calcFaceNormal(v0, v1, v2, normal);

               if(normal*b >= thresh)
               {
                   c += normal;
                  total++;
               }
            }
         }

         if(total > 1)
         {
             normal = c / (float)total;
             normal.normalize();         

             geom.m_normals[3*i+j] = normal;
         }
      }
   }   
   
   geom.m_texture = obj.texture;
   
   m_geometries.push_back(geom);

   delete[] obj.vertices;
   
   for(int i=0; i<obj.num_face; i++)
   {
      delete[] obj.faces[i].uvs;
      delete[] obj.faces[i].vertref;
   }

   delete[] obj.faces;
   
   for(int i=0; i<ntris; i++)
      delete[] triangles[i];
   
   delete[] triangles;
   delete[] vert_hash;
   delete[] smooth;
   delete[] mat;

   return true;
}

bool AC3DLoader::processObjects()
{
   for(unsigned int i=0; i<m_ac_objects.size(); i++)
   {
      if (!processObject(m_ac_objects[i]))
        return false;
   }
   return true;
}

void AC3DLoader::calcFaceNormal(Vec3 &v1, Vec3 &v2, Vec3 &v3, Vec3 &n)
{
   Vec3 side1 = v2-v1;
   Vec3 side2 = v3-v2;

   n = side1 ^ side2;
   n.normalize();
}

void AC3DLoader::clearObject(ACObject &ob)
{
   ob.loc[0] = ob.loc[1] = ob.loc[2] = 0.0;
   ob.num_vert = 0;
   ob.num_face = 0;
   ob.texture = NULL;
   ob.texture_repeat[0] = ob.texture_repeat[1] = 1.0;
   ob.texture_offset[0] = ob.texture_offset[1] = 0.0;
}
