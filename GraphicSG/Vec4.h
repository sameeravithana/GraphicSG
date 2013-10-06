/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2003 Robert Osfield 
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

#ifndef VRLIB_VEC4F
#define VRLIB_VEC4F 1

#include <vr/Vec3.h>

namespace vr {

/** General purpose float quad. Uses include representation
  * of color coordinates.
  * No support yet added for float * Vec4 - is it necessary?
  * Need to define a non-member non-friend operator*  etc.
  *    Vec4 * float is okay
*/
class Vec4
{
    public:

        float _v[4];

        // Methods are defined here so that they are implicitly inlined

        Vec4() { _v[0]=0.0; _v[1]=0.0; _v[2]=0.0; _v[3]=0.0;}
        
        Vec4(float x, float y, float z, float w)
        {
            _v[0]=x;
            _v[1]=y;
            _v[2]=z;
            _v[3]=w;
        }

        Vec4(const Vec3& v3,float w)
        {
            _v[0]=v3[0];
            _v[1]=v3[1];
            _v[2]=v3[2];
            _v[3]=w;
        }
            
        inline bool operator == (const Vec4& v) const { return _v[0]==v._v[0] && _v[1]==v._v[1] && _v[2]==v._v[2] && _v[3]==v._v[3]; }

        inline bool operator != (const Vec4& v) const { return _v[0]!=v._v[0] || _v[1]!=v._v[1] || _v[2]!=v._v[2] || _v[3]!=v._v[3]; }

        inline bool operator <  (const Vec4& v) const
        {
            if (_v[0]<v._v[0]) return true;
            else if (_v[0]>v._v[0]) return false;
            else if (_v[1]<v._v[1]) return true;
            else if (_v[1]>v._v[1]) return false;
            else if (_v[2]<v._v[2]) return true;
            else if (_v[2]>v._v[2]) return false;
            else return (_v[3]<v._v[3]);
        }

        inline float* ptr() { return _v; }
        inline const float* ptr() const { return _v; }

        inline void set( float x, float y, float z, float w)
        {
            _v[0]=x; _v[1]=y; _v[2]=z; _v[3]=w;
        }

        inline float& operator [] (unsigned int i) { return _v[i]; }
        inline float  operator [] (unsigned int i) const { return _v[i]; }

        inline float& x() { return _v[0]; }
        inline float& y() { return _v[1]; }
        inline float& z() { return _v[2]; }
        inline float& w() { return _v[3]; }

        inline float x() const { return _v[0]; }
        inline float y() const { return _v[1]; }
        inline float z() const { return _v[2]; }
        inline float w() const { return _v[3]; }

        inline unsigned long asABGR() const
        {
            return (unsigned long)clampTo((_v[0]*255.0f),0.0f,255.0f)<<24 |
                   (unsigned long)clampTo((_v[1]*255.0f),0.0f,255.0f)<<16 |
                   (unsigned long)clampTo((_v[2]*255.0f),0.0f,255.0f)<<8  |
                   (unsigned long)clampTo((_v[3]*255.0f),0.0f,255.0f);
        }

        inline unsigned long asRGBA() const
        {
            return (unsigned long)clampTo((_v[3]*255.0f),0.0f,255.0f)<<24 |
                   (unsigned long)clampTo((_v[2]*255.0f),0.0f,255.0f)<<16 |
                   (unsigned long)clampTo((_v[1]*255.0f),0.0f,255.0f)<<8  |
                   (unsigned long)clampTo((_v[0]*255.0f),0.0f,255.0f);
        }

        inline bool valid() const { return !isNaN(); }
        inline bool isNaN() const { return vr::isNaN(_v[0]) || vr::isNaN(_v[1]) || vr::isNaN(_v[2]) || vr::isNaN(_v[3]); }

        /** Dot product. */
        inline float operator * (const Vec4& rhs) const
        {
            return _v[0]*rhs._v[0]+
                   _v[1]*rhs._v[1]+
                   _v[2]*rhs._v[2]+
                   _v[3]*rhs._v[3] ;
        }

        /** Multiply by scalar. */
        inline Vec4 operator * (float rhs) const
        {
            return Vec4(_v[0]*rhs, _v[1]*rhs, _v[2]*rhs, _v[3]*rhs);
        }

        /** Unary multiply by scalar. */
        inline Vec4& operator *= (float rhs)
        {
            _v[0]*=rhs;
            _v[1]*=rhs;
            _v[2]*=rhs;
            _v[3]*=rhs;
            return *this;
        }

        /** Divide by scalar. */
        inline Vec4 operator / (float rhs) const
        {
            return Vec4(_v[0]/rhs, _v[1]/rhs, _v[2]/rhs, _v[3]/rhs);
        }

        /** Unary divide by scalar. */
        inline Vec4& operator /= (float rhs)
        {
            _v[0]/=rhs;
            _v[1]/=rhs;
            _v[2]/=rhs;
            _v[3]/=rhs;
            return *this;
        }

        /** Binary vector add. */
        inline Vec4 operator + (const Vec4& rhs) const
        {
            return Vec4(_v[0]+rhs._v[0], _v[1]+rhs._v[1],
                         _v[2]+rhs._v[2], _v[3]+rhs._v[3]);
        }

        /** Unary vector add. Slightly more efficient because no temporary
          * intermediate object.
        */
        inline Vec4& operator += (const Vec4& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            _v[2] += rhs._v[2];
            _v[3] += rhs._v[3];
            return *this;
        }

        /** Binary vector subtract. */
        inline Vec4 operator - (const Vec4& rhs) const
        {
            return Vec4(_v[0]-rhs._v[0], _v[1]-rhs._v[1],
                         _v[2]-rhs._v[2], _v[3]-rhs._v[3] );
        }

        /** Unary vector subtract. */
        inline Vec4& operator -= (const Vec4& rhs)
        {
            _v[0]-=rhs._v[0];
            _v[1]-=rhs._v[1];
            _v[2]-=rhs._v[2];
            _v[3]-=rhs._v[3];
            return *this;
        }

        /** Negation operator. Returns the negative of the Vec4. */
        inline const Vec4 operator - () const
        {
            return Vec4 (-_v[0], -_v[1], -_v[2], -_v[3]);
        }

        /** Length of the vector = sqrt( vec . vec ) */
        inline float length() const
        {
            return sqrtf( _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] + _v[3]*_v[3]);
        }

        /** Length squared of the vector = vec . vec */
        inline float length2() const
        {
            return _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] + _v[3]*_v[3];
        }

        /** Normalize the vector so that it has length unity.
          * Returns the previous length of the vector.
        */
        inline float normalize()
        {
            float norm = Vec4::length();
            if (norm>0.0f)
            {
                float inv = 1.0f/norm;
                _v[0] *= inv;
                _v[1] *= inv;
                _v[2] *= inv;
                _v[3] *= inv;
            }
            return( norm );
        }

        friend inline std::ostream& operator << (std::ostream& output, const Vec4& vec)
        {
        output << vec._v[0] << " "
                   << vec._v[1] << " "
                   << vec._v[2] << " "
                   << vec._v[3];
        return output;     // to enable cascading
    }

};    // end of class Vec4


/** Compute the dot product of a (Vec3,1.0) and a Vec4. */
inline float operator * (const Vec3& lhs,const Vec4& rhs)
{
    return lhs[0]*rhs[0]+lhs[1]*rhs[1]+lhs[2]*rhs[2]+rhs[3];
}

/** Compute the dot product of a Vec4 and a (Vec3,1.0). */
inline float operator * (const Vec4& lhs,const Vec3& rhs)
{
    return lhs[0]*rhs[0]+lhs[1]*rhs[1]+lhs[2]*rhs[2]+lhs[3];
}

}    // end of namespace osg

#endif
