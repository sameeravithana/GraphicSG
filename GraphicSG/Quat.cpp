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
#include <vr/Quat.h>
#include <vr/Matrix.h>

#include <vr/vrMath.h>

/// Good introductions to Quaternions at:
/// http://www.gamasutra.com/features/programming/19980703/quaternions_01.htm
/// http://mathworld.wolfram.com/Quaternion.html

using namespace vr;


void Quat::set(const Matrix& matrix)
{
    matrix.get(*this);
}

void Quat::get(Matrix& matrix) const
{
    matrix.set(*this);
}


/// Set the elements of the Quat to represent a rotation of angle
/// (radians) around the axis (x,y,z)
void Quat::makeRotate( float angle, float x, float y, float z )
{
    const float epsilon = 0.0000001f;

    float length = sqrt( x*x + y*y + z*z );
    if (length < epsilon)
    {
        // ~zero length axis, so reset rotation to zero.
        *this = Quat();
        return;
    }

    float inversenorm  = 1/length;
    float coshalfangle = cos( 0.5f*angle );
    float sinhalfangle = sin( 0.5f*angle );

    _v[0] = x * sinhalfangle * inversenorm;
    _v[1] = y * sinhalfangle * inversenorm;
    _v[2] = z * sinhalfangle * inversenorm;
    _v[3] = coshalfangle;
}


void Quat::makeRotate( float angle, const Vec3& vec )
{
    makeRotate( angle, vec[0], vec[1], vec[2] );
}

void Quat::makeRotate ( float angle1, const Vec3& axis1, 
                        float angle2, const Vec3& axis2,
                        float angle3, const Vec3& axis3)
{
    Quat q1; q1.makeRotate(angle1,axis1);
    Quat q2; q2.makeRotate(angle2,axis2);
    Quat q3; q3.makeRotate(angle3,axis3);

    *this = q1*q2*q3;
}                        


// Make a rotation Quat which will rotate vec1 to vec2
// Generally take adot product to get the angle between these
// and then use a cross product to get the rotation axis
// Watch out for the two special cases of when the vectors
// are co-incident or opposite in direction.
void Quat::makeRotate( const Vec3& from, const Vec3& to )
{
    const float epsilon = 0.0000001f;

    float length1  = from.length();
    float length2  = to.length();
    
    // dot product vec1*vec2
    float cosangle = from*to/(length1*length2);

    if ( fabs(cosangle - 1) < epsilon )
    {
        // cosangle is close to 1, so the vectors are close to being coincident
        // Need to generate an angle of zero with any vector we like
        // We'll choose (1,0,0)
        makeRotate( 0.0, 0.0, 0.0, 1.0 );
    }
    else
    if ( fabs(cosangle + 1.0) < epsilon )
    {
        // vectors are close to being opposite, so will need to find a
        // vector orthongonal to from to rotate about.
        Vec3 tmp;
        if (fabs(from.x())<fabs(from.y()))
            if (fabs(from.x())<fabs(from.z())) tmp.set(1.0,0.0,0.0); // use x axis.
            else tmp.set(0.0,0.0,1.0);
        else if (fabs(from.y())<fabs(from.z())) tmp.set(0.0,1.0,0.0);
        else tmp.set(0.0,0.0,1.0);
        
        Vec3 fromd(from.x(),from.y(),from.z());
        
        // find orthogonal axis.
        Vec3 axis(fromd^tmp);
        axis.normalize();
        
        _v[0] = axis[0]; // sin of half angle of PI is 1.0.
        _v[1] = axis[1]; // sin of half angle of PI is 1.0.
        _v[2] = axis[2]; // sin of half angle of PI is 1.0.
        _v[3] = 0; // cos of half angle of PI is zero.

    }
    else
    {
        // This is the usual situation - take a cross-product of vec1 and vec2
        // and that is the axis around which to rotate.
        Vec3 axis(from^to);
        float angle = acos( cosangle );
        makeRotate( angle, axis );
    }
}


void Quat::getRotate( float& angle, Vec3& vec ) const
{
    float x,y,z;
    getRotate(angle,x,y,z);
    vec[0]=x;
    vec[1]=y;
    vec[2]=z;
}

// Get the angle of rotation and axis of this Quat object.
// Won't give very meaningful results if the Quat is not associated
// with a rotation!
void Quat::getRotate( float& angle, float& x, float& y, float& z ) const
{
    float sinhalfangle = sqrt( _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] );

    angle = 2 * atan2( sinhalfangle, _v[3] );
    if(sinhalfangle)
    {
        x = _v[0] / sinhalfangle;
        y = _v[1] / sinhalfangle;
        z = _v[2] / sinhalfangle;
    }
    else
    {
        x = 0.0;
        y = 0.0;
        z = 1.0;
    }

}


/// Spherical Linear Interpolation
/// As t goes from 0 to 1, the Quat object goes from "from" to "to"
/// Reference: Shoemake at SIGGRAPH 89
/// See also
/// http://www.gamasutra.com/features/programming/19980703/quaternions_01.htm
void Quat::slerp( float t, const Quat& from, const Quat& to )
{
    const double epsilon = 0.00001;
    double omega, cosomega, sinomega, scale_from, scale_to ;
    
    Quat quatTo(to);
    // this is a dot product
    
    cosomega = from.asVec4() * to.asVec4();
    
    if ( cosomega <0.0 )
    { 
        cosomega = -cosomega; 
        quatTo = -to;
    }

    if( (1.0 - cosomega) > epsilon )
    {
        omega= acos(cosomega) ;  // 0 <= omega <= Pi (see man acos)
        sinomega = sin(omega) ;  // this sinomega should always be +ve so
        // could try sinomega=sqrt(1-cosomega*cosomega) to avoid a sin()?
        scale_from = sin((1.0-t)*omega)/sinomega ;
        scale_to = sin(t*omega)/sinomega ;
    }
    else
    {
        /* --------------------------------------------------
           The ends of the vectors are very close
           we can use simple linear interpolation - no need
           to worry about the "spherical" interpolation
           -------------------------------------------------- */
        scale_from = 1.0 - t ;
        scale_to = t ;
    }

    *this = (from*(float)scale_from) + (quatTo*(float)scale_to);
    
    // so that we get a Vec4
}


#define QX  _v[0]
#define QY  _v[1]
#define QZ  _v[2]
#define QW  _v[3]

