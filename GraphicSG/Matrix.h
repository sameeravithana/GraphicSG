/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2004 Robert Osfield 
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/

#ifndef VRLIB_MATRIXF
#define VRLIB_MATRIXF 1

#include <vr/Vec3.h>
#include <vr/Vec4.h>
#include <vr/Quat.h>

#include <string.h>

#include <ostream>
#include <algorithm>

namespace vr {

   class Matrix
   {
      public:
    
         inline Matrix() { makeIdentity(); }
         inline Matrix( const Matrix& mat) { set(mat.ptr()); }
         inline explicit Matrix( float const * const ptr ) { set(ptr); }
         inline explicit Matrix( double const * const ptr ) { set(ptr); }
         inline explicit Matrix( const Quat& quat ) { set(quat); }

         Matrix( float a00, float a01, float a02, float a03,
                 float a10, float a11, float a12, float a13,
                 float a20, float a21, float a22, float a23,
                 float a30, float a31, float a32, float a33);

         ~Matrix() {}

         int compare(const Matrix& m) const { return memcmp(_mat,m._mat,sizeof(_mat)); }

         bool operator < (const Matrix& m) const { return compare(m)<0; }
         bool operator == (const Matrix& m) const { return compare(m)==0; }
         bool operator != (const Matrix& m) const { return compare(m)!=0; }

         inline float& operator()(int row, int col) { return _mat[row][col]; }
         inline float operator()(int row, int col) const { return _mat[row][col]; }

         inline bool valid() const { return !isNaN(); }
         inline bool isNaN() const { return vr::isNaN(_mat[0][0]) || vr::isNaN(_mat[0][1]) || vr::isNaN(_mat[0][2]) || vr::isNaN(_mat[0][3]) ||
                                        vr::isNaN(_mat[1][0]) || vr::isNaN(_mat[1][1]) || vr::isNaN(_mat[1][2]) || vr::isNaN(_mat[1][3]) ||
                                        vr::isNaN(_mat[2][0]) || vr::isNaN(_mat[2][1]) || vr::isNaN(_mat[2][2]) || vr::isNaN(_mat[2][3]) ||
                                        vr::isNaN(_mat[3][0]) || vr::isNaN(_mat[3][1]) || vr::isNaN(_mat[3][2]) || vr::isNaN(_mat[3][3]); }

         inline Matrix& operator = (const Matrix& rhs)
         {
            if( &rhs == this ) return *this;
            set(rhs.ptr());
            return *this;
         }
        
         inline void set(const Matrix& rhs) { set(rhs.ptr()); }

         inline void set(float const * const ptr)
         {
            float* local_ptr = (float*)_mat;
            for(int i=0;i<16;++i) local_ptr[i]=(float)ptr[i];
         }
        
         inline void set(double const * const ptr)
         {
            float* local_ptr = (float*)_mat;
            for(int i=0;i<16;++i) local_ptr[i]=(float)ptr[i];
         }

         void set(float a00, float a01, float a02,float a03,
                  float a10, float a11, float a12,float a13,
                  float a20, float a21, float a22,float a23,
                  float a30, float a31, float a32,float a33);
                  
         void set(const Quat& q);
        
         void get(Quat& q) const;

         float * ptr() { return (float*)_mat; }
         const float * ptr() const { return (const float *)_mat; }

         void makeIdentity();
        
         void makeScale( const Vec3& );
         void makeScale( float, float, float );
        
         void makeTranslate( const Vec3& );
         void makeTranslate( float, float, float );
        
         void makeRotate( const Vec3& from, const Vec3& to );
         void makeRotate( float angle, const Vec3& axis );
         void makeRotate( float angle, float x, float y, float z );
         void makeRotate( const Quat& );
         void makeRotate( float angle1, const Vec3& axis1, 
                          float angle2, const Vec3& axis2,
                          float angle3, const Vec3& axis3);

         void transpose()
         {
         for (int r = 0; r < 4; ++r)
               for (int c = 0; c < 4; ++c)
		            std::swap((*this)(c,r), (*this)(r,c));
         }

         Matrix transposed() const
         {
            Matrix t;
            for (int r = 0; r < 4; ++r)
               for (int c = 0; c < 4; ++c)
                  t(c,r) = (*this)(r,c);
            return t;
         }

         /** Set to an orthographic projection.
          * See glOrtho for further details.
          */
         void makeOrtho(double left,   double right,
                        double bottom, double top,
                        double zNear,  double zFar);

         /** Get the othogrraphic settings of the orthographic projection matrix.
          * Note, if matrix is not an orthographic matrix then invalid values 
          * will be returned.
          */
         bool getOrtho(double& left,   double& right,
                       double& bottom, double& top,
                       double& zNear,  double& zFar) const;

         /** Set to a 2D orthographic projection.
          * See glOrtho2D for further details.
          */
         inline void makeOrtho2D(double left,   double right,
                                 double bottom, double top)
         {
            makeOrtho(left,right,bottom,top,-1.0,1.0);
         }


         /** Set to a perspective projection.
          * See glFrustum for further details.
          */
         void makeFrustum(double left,   double right,
                          double bottom, double top,
                          double zNear,  double zFar);

         /** Get the frustum settings of a perspective projection matrix.
          * Note, if matrix is not a perspective matrix then invalid values
          * will be returned.
          */
         bool getFrustum(double& left,   double& right,
                         double& bottom, double& top,
                         double& zNear,  double& zFar) const;

         /** Set to a symmetrical perspective projection.
          * See gluPerspective for further details.
          * Aspect ratio is defined as width/height.
          */
         void makePerspective(double fovy,  double aspectRatio,
                              double zNear, double zFar);

         /** Get the frustum settings of a symmetric perspective projection
          * matrix.
          * Return false if matrix is not a perspective matrix,
          * where parameter values are undefined. 
          * Note, if matrix is not a symmetric perspective matrix then the
          * shear will be lost.
          * Asymmetric matrices occur when stereo, power walls, caves and
          * reality center display are used.
          * In these configuration one should use the AsFrustum method instead.
          */
         bool getPerspective(double& fovy,  double& aspectRatio,
                             double& zNear, double& zFar) const;

         /** Set the position and orientation to be a view matrix,
          * using the same convention as gluLookAt.
          */
         void makeLookAt(const Vec3& eye,const Vec3& center,const Vec3& up);

         /** Get to the position and orientation of a modelview matrix,
          * using the same convention as gluLookAt.
          */
         void getLookAt(Vec3& eye,Vec3& center,Vec3& up,
                        float lookDistance=1.0f) const;

         /** invert the matrix rhs. */
         bool invert( const Matrix& rhs);

         /** full 4x4 matrix invert. */
         bool invert_4x4_orig( const Matrix& );

         /** full 4x4 matrix invert. */
         bool invert_4x4_new( const Matrix& );

         //basic utility functions to create new matrices
         inline static Matrix identity( void );
         inline static Matrix scale( const Vec3& sv);
         inline static Matrix scale( float sx, float sy, float sz);
         inline static Matrix translate( const Vec3& dv);
         inline static Matrix translate( float x, float y, float z);
         inline static Matrix rotate( const Vec3& from, const Vec3& to);
         inline static Matrix rotate( float angle, float x, float y, float z);
         inline static Matrix rotate( float angle, const Vec3& axis);
         inline static Matrix rotate( float angle1, const Vec3& axis1, 
                                      float angle2, const Vec3& axis2,
                                      float angle3, const Vec3& axis3);
         inline static Matrix rotate( const Quat& quat);
         inline static Matrix inverse( const Matrix& matrix);
        
         /** Create an orthographic projection matrix.
          * See glOrtho for further details.
          */
         inline static Matrix ortho(double left,   double right,
                                    double bottom, double top,
                                    double zNear,  double zFar);

         /** Create a 2D orthographic projection.
          * See glOrtho for further details.
          */
         inline static Matrix ortho2D(double left,   double right,
                                      double bottom, double top);

         /** Create a perspective projection.
          * See glFrustum for further details.
          */
         inline static Matrix frustum(double left,   double right,
                                      double bottom, double top,
                                      double zNear,  double zFar);

         /** Create a symmetrical perspective projection.
          * See gluPerspective for further details.
          * Aspect ratio is defined as width/height.
          */
         inline static Matrix perspective(double fovy,  double aspectRatio,
                                          double zNear, double zFar);

         /** Create the position and orientation as per a camera,
          * using the same convention as gluLookAt.
          */
         inline static Matrix lookAt(const Vec3& eye,
                                     const Vec3& center,
                                     const Vec3& up);

         inline Vec3 preMult( const Vec3& v ) const;
         inline Vec3 postMult( const Vec3& v ) const;
         inline Vec3 operator* ( const Vec3& v ) const;
         inline Vec4 preMult( const Vec4& v ) const;
         inline Vec4 postMult( const Vec4& v ) const;
         inline Vec4 operator* ( const Vec4& v ) const;

         void setTrans( float tx, float ty, float tz );
         void setTrans( const Vec3& v );
        
         inline Vec3 getTrans() const { return Vec3(_mat[3][0],_mat[3][1],_mat[3][2]); } 
        
         inline Vec3 getScale() const { return Vec3(_mat[0][0],_mat[1][1],_mat[2][2]); }
        
         /** apply a 3x3 transform of v*M[0..2,0..2]. */
         inline static Vec3 transform3x3(const Vec3& v,const Matrix& m);

         /** apply a 3x3 transform of M[0..2,0..2]*v. */
         inline static Vec3 transform3x3(const Matrix& m,const Vec3& v);

         // basic Matrix multiplication, our workhorse methods.
         void mult( const Matrix&, const Matrix& );
         void preMult( const Matrix& );
         void postMult( const Matrix& );

         inline void operator *= ( const Matrix& other ) 
         {    if( this == &other ) {
            Matrix temp(other);
            postMult( temp );
         }
         else postMult( other ); 
         }

         inline Matrix operator * ( const Matrix &m ) const
         {
            Matrix r;
            r.mult(*this,m);
            return  r;
         }

      protected:
         float _mat[4][4];

   };

//static utility methods
   inline Matrix Matrix::identity(void)
   {
      Matrix m;
      m.makeIdentity();
      return m;
   }

   inline Matrix Matrix::scale(float sx, float sy, float sz)
   {
      Matrix m;
      m.makeScale(sx,sy,sz);
      return m;
   }

   inline Matrix Matrix::scale(const Vec3& v )
   {
      return scale(v.x(), v.y(), v.z() );
   }

   inline Matrix Matrix::translate(float tx, float ty, float tz)
   {
      Matrix m;
      m.makeTranslate(tx,ty,tz);
      return m;
   }

   inline Matrix Matrix::translate(const Vec3& v )
   {
      return translate(v.x(), v.y(), v.z() );
   }

   inline Matrix Matrix::rotate( const Quat& q )
   {
      return Matrix(q);
   }
   inline Matrix Matrix::rotate(float angle, float x, float y, float z )
   {
      Matrix m;
      m.makeRotate(angle,x,y,z);
      return m;
   }
   inline Matrix Matrix::rotate(float angle, const Vec3& axis )
   {
      Matrix m;
      m.makeRotate(angle,axis);
      return m;
   }
   inline Matrix Matrix::rotate( float angle1, const Vec3& axis1, 
                                 float angle2, const Vec3& axis2,
                                 float angle3, const Vec3& axis3)
   {
      Matrix m;
      m.makeRotate(angle1,axis1,angle2,axis2,angle3,axis3);
      return m;
   }
   inline Matrix Matrix::rotate(const Vec3& from, const Vec3& to )
   {
      Matrix m;
      m.makeRotate(from,to);
      return m;
   }
   inline Matrix Matrix::inverse( const Matrix& matrix)
   {
      Matrix m;
      m.invert(matrix);
      return m;
   }

   inline Matrix Matrix::ortho(double left, double right,
                               double bottom, double top,
                               double zNear, double zFar)
   {
      Matrix m;
      m.makeOrtho(left,right,bottom,top,zNear,zFar);
      return m;
   }

   inline Matrix Matrix::ortho2D(double left, double right,
                                 double bottom, double top)
   {
      Matrix m;
      m.makeOrtho2D(left,right,bottom,top);
      return m;
   }

   inline Matrix Matrix::frustum(double left, double right,
                                 double bottom, double top,
                                 double zNear, double zFar)
   {
      Matrix m;
      m.makeFrustum(left,right,bottom,top,zNear,zFar);
      return m;
   }

   inline Matrix Matrix::perspective(double fovy,double aspectRatio,
                                     double zNear, double zFar)
   {
      Matrix m;
      m.makePerspective(fovy,aspectRatio,zNear,zFar);
      return m;
   }

   inline Matrix Matrix::lookAt(const Vec3& eye,const Vec3& center,const Vec3& up)
   {
      Matrix m;
      m.makeLookAt(eye,center,up);
      return m;
   }
   inline Vec3 Matrix::postMult( const Vec3& v ) const
   {
      float d = 1.0f/(_mat[3][0]*v.x()+_mat[3][1]*v.y()+_mat[3][2]*v.z()+_mat[3][3]) ;
      return Vec3( (_mat[0][0]*v.x() + _mat[0][1]*v.y() + _mat[0][2]*v.z() + _mat[0][3])*d,
                   (_mat[1][0]*v.x() + _mat[1][1]*v.y() + _mat[1][2]*v.z() + _mat[1][3])*d,
                   (_mat[2][0]*v.x() + _mat[2][1]*v.y() + _mat[2][2]*v.z() + _mat[2][3])*d) ;
   }
   inline Vec3 Matrix::preMult( const Vec3& v ) const
   {
      float d = 1.0f/(_mat[0][3]*v.x()+_mat[1][3]*v.y()+_mat[2][3]*v.z()+_mat[3][3]) ;
      return Vec3( (_mat[0][0]*v.x() + _mat[1][0]*v.y() + _mat[2][0]*v.z() + _mat[3][0])*d,
                   (_mat[0][1]*v.x() + _mat[1][1]*v.y() + _mat[2][1]*v.z() + _mat[3][1])*d,
                   (_mat[0][2]*v.x() + _mat[1][2]*v.y() + _mat[2][2]*v.z() + _mat[3][2])*d);
   }
   inline Vec4 Matrix::postMult( const Vec4& v ) const
   {
      return Vec4( (_mat[0][0]*v.x() + _mat[0][1]*v.y() + _mat[0][2]*v.z() + _mat[0][3]*v.w()),
                   (_mat[1][0]*v.x() + _mat[1][1]*v.y() + _mat[1][2]*v.z() + _mat[1][3]*v.w()),
                   (_mat[2][0]*v.x() + _mat[2][1]*v.y() + _mat[2][2]*v.z() + _mat[2][3]*v.w()),
                   (_mat[3][0]*v.x() + _mat[3][1]*v.y() + _mat[3][2]*v.z() + _mat[3][3]*v.w())) ;
   }
   inline Vec4 Matrix::preMult( const Vec4& v ) const
   {
      return Vec4( (_mat[0][0]*v.x() + _mat[1][0]*v.y() + _mat[2][0]*v.z() + _mat[3][0]*v.w()),
                   (_mat[0][1]*v.x() + _mat[1][1]*v.y() + _mat[2][1]*v.z() + _mat[3][1]*v.w()),
                   (_mat[0][2]*v.x() + _mat[1][2]*v.y() + _mat[2][2]*v.z() + _mat[3][2]*v.w()),
                   (_mat[0][3]*v.x() + _mat[1][3]*v.y() + _mat[2][3]*v.z() + _mat[3][3]*v.w()));
   }
   inline Vec3 Matrix::transform3x3(const Vec3& v,const Matrix& m)
   {
      return Vec3( (m._mat[0][0]*v.x() + m._mat[1][0]*v.y() + m._mat[2][0]*v.z()),
                   (m._mat[0][1]*v.x() + m._mat[1][1]*v.y() + m._mat[2][1]*v.z()),
                   (m._mat[0][2]*v.x() + m._mat[1][2]*v.y() + m._mat[2][2]*v.z()));
   }
   inline Vec3 Matrix::transform3x3(const Matrix& m,const Vec3& v)
   {
      return Vec3( (m._mat[0][0]*v.x() + m._mat[0][1]*v.y() + m._mat[0][2]*v.z()),
                   (m._mat[1][0]*v.x() + m._mat[1][1]*v.y() + m._mat[1][2]*v.z()),
                   (m._mat[2][0]*v.x() + m._mat[2][1]*v.y() + m._mat[2][2]*v.z()) ) ;
   }

   inline Vec3 operator* (const Vec3& v, const Matrix& m )
   {
      return m.preMult(v);
   }
   inline Vec4 operator* (const Vec4& v, const Matrix& m )
   {
      return m.preMult(v);
   }
   inline Vec3 Matrix::operator* (const Vec3& v) const
   {
      return postMult(v);
   }
   inline Vec4 Matrix::operator* (const Vec4& v) const
   {
      return postMult(v);
   }

   inline std::ostream& operator<< (std::ostream& os, const Matrix& m )
   {
      os << "{"<<std::endl;
      for(int row=0; row<4; ++row) {
         os << "\t";
         for(int col=0; col<4; ++col)
            os << m(row,col) << " ";
         os << std::endl;
      }
      os << "}" << std::endl;
      return os;
   }


} //namespace osg


#endif
