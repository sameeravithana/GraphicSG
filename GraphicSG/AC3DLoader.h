#ifndef __vr_AC3DLoader_h__
#define __vr_AC3DLoader_h__

#ifdef WIN32
#include <windows.h>
#endif

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include <vr/Image.h>

#include <vr/Vec2.h>
#include <vr/Vec3.h>
#include <vr/Vec4.h>

#define SURFACE_SHADED   (1<<4)
#define SURFACE_TWOSIDED (1<<5)

namespace vr
{
  /**
  Class for loading ac3d files (not all, only older ones) into memory, where data 
  (geometries containing vertices, normals, texture coordinates, materials and textures)
  can be accesed.
  This data should then be copied into your own datastructure.
  Pointers to images can be kept, this memory will not be deleted when the Loader is deleted.

  Usage:

  vr::AC3DLoader loader;

  loader.
  */
  class AC3DLoader
  {
  public:
    /// Structure containing materals  
    struct Material
    {
      Vec4 diffuse, ambient, specular, emission;
      float shine, trans;
    };

    /** 
    Class containing all information for a geometry, including
    normals, images (textures), vertices etc.
    When using this, the data should be COPIED, except for the Image,
    this can be stored and deleted by you.
    */
    class Geometry
    {
      friend class AC3DLoader;
    public:
      typedef std::vector<Vec3> Vec3Array;
      typedef std::vector<Vec2> Vec2Array;
      typedef std::vector<int> IntArray;
    protected:

      Vec3Array m_vertices;
      Vec3Array m_normals;
      Vec2Array m_texcoords;
      IntArray m_materials;
      std::string m_name;
      Vec3 m_translation;
      Image *m_texture;

    public:

      /// \return Number of vertices in this geometry
      size_t getNumVertices() const { return m_vertices.size(); };

      /// \return The translation for this geometry.
      const Vec3& getTranslation() const { return m_translation; } 
      
      /// \return the i:th [0..getNumVertices()] vertex
      Vec3 const& getVertex( int vertexN ) const { return m_vertices[vertexN]; };
      
      /// \return the i:th [0..getNumVertices()] normal
      Vec3 const& getNormal( int vertexN ) const { return m_normals[vertexN]; };
      /// \return the i:th [0..getNumVertices()] texture coordinate
      Vec2 const& getTexCoord( int vertexN ) const { return m_texcoords[vertexN]; };
      
      /**
      Each vertex can have its own material (color).
      This method returns an index into the Geometries material array.
      So every vertex CAN refer to the same material, OR each and every one can have different
      materials.

      \return the index into the material array (accessible with Geometry::getMaterial( i );
      */
      int  const& getMaterial( int i ) const { return m_materials[i]; };

      /// \return the name of this geometry as stored in the file
      const std::string& getName() const { return m_name; }

      /**
      This pointer is NOT deleted by the loader, you as a user of this API
      is responsible for calling delete on it.

      \return a pointer to a loaded image.
      */
      Image const* getTexture() const { return m_texture; }
    };

    typedef std::vector<Geometry> GeometryArray;
    typedef std::vector<Material> MaterialArray;
  public:

    /// Constructor
    AC3DLoader();

    /// Destructor
    ~AC3DLoader();

    /**
    Opens and parses a .ac file. If this method returns true data is available through the getNumGeometries(), getNumMaterials()
    At destruction, you are responsible for going through all images and delete them.
    \return true if loading is successful.
    */
    bool load(const char* filename);

    /// \return Number of geometries found in the file
    size_t getNumGeometries() const { return m_geometries.size(); };
    
    /** 
    A File can have N materials, these materials are then referred from the Geometry::getMaterial( verticeN );
    \return Number of Materials found in the file
    */
    size_t getNumMaterials() const { return m_materials.size(); };

    ///\return the i:th geometry [0..getNumGeometries()]
    Geometry const& getGeometry( unsigned int i ) { return m_geometries[i]; };
    
    ///\return the i:th material [0..getNumMaterials()]
    Material const& getMaterial( unsigned int i ) { return m_materials[i]; };

    ///\return a reference to the array with all geometries, an alternative way to access geometries than getGeometry( i ); 
    GeometryArray const& getGeometries() const { return m_geometries;  };

    ///\return a reference to the array with all materials, an alternative way to access materials than getMaterial( i );
    MaterialArray const& getMaterials() const { return m_materials; };

  private:
    struct ACFace
    {
      int num_vertref;
      int *vertref;
      Vec2 *uvs;
      int flags;
      int material;
      Vec3 normal;
    };

    struct ACObject
    {
      Vec3 loc;
      std::string name;
      std::string data;
      std::string url;

      int num_vert;
      int num_face;

      Vec2 texture_repeat;
      Vec2 texture_offset;

      Vec3 *vertices;
      ACFace *faces;

      Image *texture;
    };

    void parseMaterial(std::string &);
    bool parseObject(void);
    ACFace *parseFace(ACObject &, ACFace *);

    void clearObject(ACObject &);
    void calcFaceNormal(Vec3 &, Vec3 &, Vec3 &, Vec3 &);
    void calcVertexNormals(ACObject *);

    bool processObjects();
    bool processObject(ACObject &);

    std::fstream m_fin;
    std::vector<Material> m_materials;
    std::vector<Geometry> m_geometries;
    std::vector<ACObject> m_ac_objects;
  };
}

#endif // __vr_AC3DLoader_h__