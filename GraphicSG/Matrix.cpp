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

#include <vr/vrMath.h>
#include <vr/Quat.h>
#include <vr/Matrix.h>

#include <stdlib.h>

using namespace vr;

#define SET_ROW(row, v1, v2, v3, v4 )    \
    _mat[(row)][0] = (v1); \
    _mat[(row)][1] = (v2); \
    _mat[(row)][2] = (v3); \
    _mat[(row)][3] = (v4);

#define INNER_PRODUCT(a,b,r,c) \
     ((a)._mat[r][0] * (b)._mat[0][c]) \
    +((a)._mat[r][1] * (b)._mat[1][c]) \
    +((a)._mat[r][2] * (b)._mat[2][c]) \
    +((a)._mat[r][3] * (b)._mat[3][c])


Matrix::Matrix( float a00, float a01, float a02, float a03,
                  float a10, float a11, float a12, float a13,
                  float a20, float a21, float a22, float a23,
                  float a30, float a31, float a32, float a33)
{
    SET_ROW(0, a00, a01, a02, a03 )
    SET_ROW(1, a10, a11, a12, a13 )
    SET_ROW(2, a20, a21, a22, a23 )
    SET_ROW(3, a30, a31, a32, a33 )
}

void Matrix::set( float a00, float a01, float a02, float a03,
                   float a10, float a11, float a12, float a13,
                   float a20, float a21, float a22, float a23,
                   float a30, float a31, float a32, float a33)
{
    SET_ROW(0, a00, a01, a02, a03 )
    SET_ROW(1, a10, a11, a12, a13 )
    SET_ROW(2, a20, a21, a22, a23 )
    SET_ROW(3, a30, a31, a32, a33 )
}

#define QX  q._v[0]
#define QY  q._v[1]
#define QZ  q._v[2]
#define QW  q._v[3]

void Matrix::set(const Quat& q_in)
{
    Quat q(q_in);
    double length2 = q.length2();
	if (length2!=1.0 && length2!=0)
    {
        // normalize quat if required.
        q /= (float)sqrt(length2);
    }

    // Source: Gamasutra, Rotating Objects Using Quaternions
    //
    //http://www.gamasutra.com/features/programming/19980703/quaternions_01.htm

    double wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

    // calculate coefficients
    x2 = QX + QX;
    y2 = QY + QY;
    z2 = QZ + QZ;

    xx = QX * x2;
    xy = QX * y2;
    xz = QX * z2;

    yy = QY * y2;
    yz = QY * z2;
    zz = QZ * z2;

    wx = QW * x2;
    wy = QW * y2;
    wz = QW * z2;

    // Note.  Gamasutra gets the matrix assignments inverted, resulting
    // in left-handed rotations, which is contrary to OpenGL and OSG's 
    // methodology.  The matrix assignment has been altered in the next
    // few lines of code to do the right thing.
    // Don Burns - Oct 13, 2001
    _mat[0][0] = (float)(1.0f - (yy + zz));
    _mat[1][0] = (float)(xy - wz);
    _mat[2][0] = (float)(xz + wy);
    _mat[3][0] = 0.0f;

    _mat[0][1] = (float)(xy + wz);
    _mat[1][1] = (float)(1.0 - (xx + zz));
    _mat[2][1] = (float)(yz - wx);
    _mat[3][1] = 0.0f;

    _mat[0][2] = (float)(xz - wy);
    _mat[1][2] = (float)(yz + wx);
    _mat[2][2] = (float)(1.0 - (xx + yy));
    _mat[3][2] = 0.0f;

    _mat[0][3] = 0.0f;
    _mat[1][3] = 0.0f;
    _mat[2][3] = 0.0f;
    _mat[3][3] = 1.0f;
}

void Matrix::get( Quat& q ) const
{
    // Source: Gamasutra, Rotating Objects Using Quaternions
    //
    //http://www.gamasutra.com/features/programming/19980703/quaternions_01.htm

    float  tr, s;
    float tq[4];
    int    i, j, k;

    int nxt[3] = {1, 2, 0};

    tr =(float)( _mat[0][0] + _mat[1][1] + _mat[2][2]+1.0);

    // check the diagonal
    if (tr > 0.0)
    {
        s = (float)sqrt (tr);
        QW = (float)(s / 2.0);
        s = (float)(0.5 / s);
        QX = (float)((_mat[1][2] - _mat[2][1]) * s);
        QY = (float)((_mat[2][0] - _mat[0][2]) * s);
        QZ = (float)((_mat[0][1] - _mat[1][0]) * s);
    }
    else
    {
        // diagonal is negative
        i = 0;
        if (_mat[1][1] > _mat[0][0])
            i = 1;
        if (_mat[2][2] > _mat[i][i])
            i = 2;
        j = nxt[i];
        k = nxt[j];

        s = (float)sqrt ((_mat[i][i] - (_mat[j][j] + _mat[k][k])) + 1.0);

        tq[i] = (float)(s * 0.5);

        if (s != 0.0)
            s = 0.5f / s;

        tq[3] = (float)((_mat[j][k] - _mat[k][j]) * s);
        tq[j] = (float)((_mat[i][j] + _mat[j][i]) * s);
        tq[k] = (float)((_mat[i][k] + _mat[k][i]) * s);

        QX = tq[0];
        QY = tq[1];
        QZ = tq[2];
        QW = tq[3];
    }
}


void Matrix::setTrans( float tx, float ty, float tz )
{
    _mat[3][0] = tx;
    _mat[3][1] = ty;
    _mat[3][2] = tz;
}


void Matrix::setTrans( const Vec3& v )
{
    _mat[3][0] = v[0];
    _mat[3][1] = v[1];
    _mat[3][2] = v[2];
}

void Matrix::makeIdentity()
{
    SET_ROW(0,    1, 0, 0, 0 )
    SET_ROW(1,    0, 1, 0, 0 )
    SET_ROW(2,    0, 0, 1, 0 )
    SET_ROW(3,    0, 0, 0, 1 )
}

void Matrix::makeScale( const Vec3& v )
{
    makeScale(v[0], v[1], v[2] );
}

void Matrix::makeScale( float x, float y, float z )
{
    SET_ROW(0,    x, 0, 0, 0 )
    SET_ROW(1,    0, y, 0, 0 )
    SET_ROW(2,    0, 0, z, 0 )
    SET_ROW(3,    0, 0, 0, 1 )
}

void Matrix::makeTranslate( const Vec3& v )
{
    makeTranslate( v[0], v[1], v[2] );
}

void Matrix::makeTranslate( float x, float y, float z )
{
    SET_ROW(0,    1, 0, 0, 0 )
    SET_ROW(1,    0, 1, 0, 0 )
    SET_ROW(2,    0, 0, 1, 0 )
    SET_ROW(3,    x, y, z, 1 )
}

void Matrix::makeRotate( const Vec3& from, const Vec3& to )
{
    Quat quat;
    quat.makeRotate(from,to);
    set(quat);
}

void Matrix::makeRotate( float angle, const Vec3& axis )
{
    Quat quat;
    quat.makeRotate( angle, axis);
    set(quat);
}

void Matrix::makeRotate( float angle, float x, float y, float z ) 
{
    Quat quat;
    quat.makeRotate( angle, x, y, z);
    set(quat);
}

void Matrix::makeRotate( const Quat& quat )
{
    set(quat);
}

void Matrix::makeRotate( float angle1, const Vec3& axis1, 
                         float angle2, const Vec3& axis2,
                         float angle3, const Vec3& axis3)
{
    Quat quat;
    quat.makeRotate(angle1, axis1, 
                    angle2, axis2,
                    angle3, axis3);
    set(quat);
}

void Matrix::mult( const Matrix& lhs, const Matrix& rhs )
{   
    if (&lhs==this)
    {
        postMult(rhs);
        return;
    }
    if (&rhs==this)
    {
        preMult(lhs);
        return;
    }

// PRECONDITION: We assume neither &lhs nor &rhs == this
// if it did, use preMult or postMult instead
    _mat[0][0] = INNER_PRODUCT(lhs, rhs, 0, 0);
    _mat[0][1] = INNER_PRODUCT(lhs, rhs, 0, 1);
    _mat[0][2] = INNER_PRODUCT(lhs, rhs, 0, 2);
    _mat[0][3] = INNER_PRODUCT(lhs, rhs, 0, 3);
    _mat[1][0] = INNER_PRODUCT(lhs, rhs, 1, 0);
    _mat[1][1] = INNER_PRODUCT(lhs, rhs, 1, 1);
    _mat[1][2] = INNER_PRODUCT(lhs, rhs, 1, 2);
    _mat[1][3] = INNER_PRODUCT(lhs, rhs, 1, 3);
    _mat[2][0] = INNER_PRODUCT(lhs, rhs, 2, 0);
    _mat[2][1] = INNER_PRODUCT(lhs, rhs, 2, 1);
    _mat[2][2] = INNER_PRODUCT(lhs, rhs, 2, 2);
    _mat[2][3] = INNER_PRODUCT(lhs, rhs, 2, 3);
    _mat[3][0] = INNER_PRODUCT(lhs, rhs, 3, 0);
    _mat[3][1] = INNER_PRODUCT(lhs, rhs, 3, 1);
    _mat[3][2] = INNER_PRODUCT(lhs, rhs, 3, 2);
    _mat[3][3] = INNER_PRODUCT(lhs, rhs, 3, 3);
}

void Matrix::preMult( const Matrix& other )
{
    // brute force method requiring a copy
    //Matrix tmp(other* *this);
    // *this = tmp;

    // more efficient method just use a float[4] for temporary storage.
    float t[4];
    for(int col=0; col<4; ++col) {
        t[0] = INNER_PRODUCT( other, *this, 0, col );
        t[1] = INNER_PRODUCT( other, *this, 1, col );
        t[2] = INNER_PRODUCT( other, *this, 2, col );
        t[3] = INNER_PRODUCT( other, *this, 3, col );
        _mat[0][col] = t[0];
        _mat[1][col] = t[1];
        _mat[2][col] = t[2];
        _mat[3][col] = t[3];
    }

}

void Matrix::postMult( const Matrix& other )
{
    // brute force method requiring a copy
    //Matrix tmp(*this * other);
    // *this = tmp;

    // more efficient method just use a float[4] for temporary storage.
    float t[4];
    for(int row=0; row<4; ++row)
    {
        t[0] = INNER_PRODUCT( *this, other, row, 0 );
        t[1] = INNER_PRODUCT( *this, other, row, 1 );
        t[2] = INNER_PRODUCT( *this, other, row, 2 );
        t[3] = INNER_PRODUCT( *this, other, row, 3 );
        SET_ROW(row, t[0], t[1], t[2], t[3] )
    }
}

#undef INNER_PRODUCT


bool Matrix::invert( const Matrix& rhs)
{
    return invert_4x4_new(rhs);
}

/******************************************
  Matrix inversion technique:
Given a matrix mat, we want to invert it.
mat = [ r00 r01 r02 a
        r10 r11 r12 b
        r20 r21 r22 c
        tx  ty  tz  d ]
We note that this matrix can be split into three matrices.
mat = rot * trans * corr, where rot is rotation part, trans is translation part, and corr is the correction due to perspective (if any).
rot = [ r00 r01 r02 0
        r10 r11 r12 0
        r20 r21 r22 0
        0   0   0   1 ]
trans = [ 1  0  0  0
          0  1  0  0
          0  0  1  0
          tx ty tz 1 ]
corr = [ 1 0 0 px
         0 1 0 py
         0 0 1 pz
         0 0 0 s ]
where the elements of corr are obtained from linear combinations of the elements of rot, trans, and mat.
So the inverse is mat' = (trans * corr)' * rot', where rot' must be computed the traditional way, which is easy since it is only a 3x3 matrix.
This problem is simplified if [px py pz s] = [0 0 0 1], which will happen if mat was composed only of rotations, scales, and translations (which is common).  In this case, we can ignore corr entirely which saves on a lot of computations.
******************************************/

bool Matrix::invert_4x4_new( const Matrix& mat )
{
    if (&mat==this)
    {
       Matrix tm(mat);
       return invert_4x4_new(tm);
    }

    register float r00, r01, r02,
                        r10, r11, r12,
                        r20, r21, r22;
      // Copy rotation components directly into registers for speed
    r00 = mat._mat[0][0]; r01 = mat._mat[0][1]; r02 = mat._mat[0][2];
    r10 = mat._mat[1][0]; r11 = mat._mat[1][1]; r12 = mat._mat[1][2];
    r20 = mat._mat[2][0]; r21 = mat._mat[2][1]; r22 = mat._mat[2][2];

        // Partially compute inverse of rot
    _mat[0][0] = r11*r22 - r12*r21;
    _mat[0][1] = r02*r21 - r01*r22;
    _mat[0][2] = r01*r12 - r02*r11;

      // Compute determinant of rot from 3 elements just computed
    register float one_over_det = (float)(1.0/(r00*_mat[0][0] + r10*_mat[0][1] + r20*_mat[0][2]));
    r00 *= one_over_det; r10 *= one_over_det; r20 *= one_over_det;  // Saves on later computations

      // Finish computing inverse of rot
    _mat[0][0] *= one_over_det;
    _mat[0][1] *= one_over_det;
    _mat[0][2] *= one_over_det;
    _mat[0][3] = 0.0;
    _mat[1][0] = r12*r20 - r10*r22; // Have already been divided by det
    _mat[1][1] = r00*r22 - r02*r20; // same
    _mat[1][2] = r02*r10 - r00*r12; // same
    _mat[1][3] = 0.0;
    _mat[2][0] = r10*r21 - r11*r20; // Have already been divided by det
    _mat[2][1] = r01*r20 - r00*r21; // same
    _mat[2][2] = r00*r11 - r01*r10; // same
    _mat[2][3] = 0.0;
    _mat[3][3] = 1.0;

// We no longer need the rxx or det variables anymore, so we can reuse them for whatever we want.  But we will still rename them for the sake of clarity.

#define d r22
    d  = mat._mat[3][3];

    if( vr::square(d-1.0) > 1.0e-6 )  // Involves perspective, so we must
    {                       // compute the full inverse
    
        Matrix TPinv;
        _mat[3][0] = _mat[3][1] = _mat[3][2] = 0.0;

#define px r00
#define py r01
#define pz r02
#define one_over_s  one_over_det
#define a  r10
#define b  r11
#define c  r12

        a  = mat._mat[0][3]; b  = mat._mat[1][3]; c  = mat._mat[2][3];
        px = _mat[0][0]*a + _mat[0][1]*b + _mat[0][2]*c;
        py = _mat[1][0]*a + _mat[1][1]*b + _mat[1][2]*c;
        pz = _mat[2][0]*a + _mat[2][1]*b + _mat[2][2]*c;

#undef a
#undef b
#undef c
#define tx r10
#define ty r11
#define tz r12

        tx = mat._mat[3][0]; ty = mat._mat[3][1]; tz = mat._mat[3][2];
        one_over_s  = (float)(1.0/(d - (tx*px + ty*py + tz*pz)));

        tx *= one_over_s; ty *= one_over_s; tz *= one_over_s;  // Reduces number of calculations later on

        // Compute inverse of trans*corr
        TPinv._mat[0][0] = (float)(tx*px + 1.0);
        TPinv._mat[0][1] = (float)(ty*px);
        TPinv._mat[0][2] = (float)(tz*px);
        TPinv._mat[0][3] = (float)(-px * one_over_s);
        TPinv._mat[1][0] = (float)(tx*py);
        TPinv._mat[1][1] = (float)(ty*py + 1.0);
        TPinv._mat[1][2] = (float)(tz*py);
        TPinv._mat[1][3] = (float)(-py * one_over_s);
        TPinv._mat[2][0] = (float)(tx*pz);
        TPinv._mat[2][1] = (float)(ty*pz);
        TPinv._mat[2][2] = (float)(tz*pz + 1.0);
        TPinv._mat[2][3] = (float)(-pz * one_over_s);
        TPinv._mat[3][0] = (float)(-tx);
        TPinv._mat[3][1] = (float)(-ty);
        TPinv._mat[3][2] = (float)(-tz);
        TPinv._mat[3][3] = (float)(one_over_s);

        preMult(TPinv); // Finish computing full inverse of mat

#undef px
#undef py
#undef pz
#undef one_over_s
#undef d
    }
    else // Rightmost column is [0; 0; 0; 1] so it can be ignored
    {
        tx = mat._mat[3][0]; ty = mat._mat[3][1]; tz = mat._mat[3][2];

        // Compute translation components of mat'
        _mat[3][0] = -(tx*_mat[0][0] + ty*_mat[1][0] + tz*_mat[2][0]);
        _mat[3][1] = -(tx*_mat[0][1] + ty*_mat[1][1] + tz*_mat[2][1]);
        _mat[3][2] = -(tx*_mat[0][2] + ty*_mat[1][2] + tz*_mat[2][2]);

#undef tx
#undef ty
#undef tz
    }

    return true;
}


template <class T>
inline T SGL_ABS(T a)
{
   return (a >= 0 ? a : -a);
}

#ifndef SGL_SWAP
#define SGL_SWAP(a,b,temp) ((temp)=(a),(a)=(b),(b)=(temp))
#endif

bool Matrix::invert_4x4_orig( const Matrix& mat )
{
    if (&mat==this) {
       Matrix tm(mat);
       return invert_4x4_orig(tm);
    }

    unsigned int indxc[4], indxr[4], ipiv[4];
    unsigned int i,j,k,l,ll;
    unsigned int icol = 0;
    unsigned int irow = 0;
    float temp, pivinv, dum, big;

    // copy in place this may be unnecessary
    *this = mat;

    for (j=0; j<4; j++) ipiv[j]=0;

    for(i=0;i<4;i++)
    {
       big=0.0;
       for (j=0; j<4; j++)
          if (ipiv[j] != 1)
             for (k=0; k<4; k++)
             {
                if (ipiv[k] == 0)
                {
                   if (SGL_ABS(operator()(j,k)) >= big)
                   {
                      big = SGL_ABS(operator()(j,k));
                      irow=j;
                      icol=k;
                   }
                }
                else if (ipiv[k] > 1)
                   return false;
             }
       ++(ipiv[icol]);
       if (irow != icol)
          for (l=0; l<4; l++) SGL_SWAP(operator()(irow,l),
                                       operator()(icol,l),
                                       temp);

       indxr[i]=irow;
       indxc[i]=icol;
       if (operator()(icol,icol) == 0)
          return false;

       pivinv = 1.0f/operator()(icol,icol);
       operator()(icol,icol) = 1;
       for (l=0; l<4; l++) operator()(icol,l) *= pivinv;
       for (ll=0; ll<4; ll++)
          if (ll != icol)
          {
             dum=operator()(ll,icol);
             operator()(ll,icol) = 0;
             for (l=0; l<4; l++) operator()(ll,l) -= operator()(icol,l)*dum;
          }
    }
    for (int lx=4; lx>0; --lx)
    {
       if (indxr[lx-1] != indxc[lx-1])
          for (k=0; k<4; k++) SGL_SWAP(operator()(k,indxr[lx-1]),
                                       operator()(k,indxc[lx-1]),temp);
    }

    return true;
}

void Matrix::makeOrtho(double left, double right,
                       double bottom, double top,
                       double zNear, double zFar)
{
    // note transpose of Matrix wr.t OpenGL documentation, since the OSG use post multiplication rather than pre.
    double tx = -(right+left)/(right-left);
    double ty = -(top+bottom)/(top-bottom);
    double tz = -(zFar+zNear)/(zFar-zNear);
    SET_ROW(0, 2/float(right-left),               0,               0, 0 )
    SET_ROW(1,              0,  2/float(top-bottom),               0, 0 )
    SET_ROW(2,              0,               0,  -2.0f/float(zFar-zNear), 0 )
    SET_ROW(3,               (float)tx,                (float)ty,                 (float)tz, 1 )
}

bool Matrix::getOrtho(double& left, double& right,
                      double& bottom, double& top,
                      double& zNear, double& zFar) const
{
    if (_mat[0][3]!=0.0 || _mat[1][3]!=0.0 || _mat[2][3]!=0.0 || _mat[3][3]!=1.0) return false;

    zNear = (_mat[3][2]+1.0) / _mat[2][2];
    zFar = (_mat[3][2]-1.0) / _mat[2][2];
    
    left = -(1.0+_mat[3][0]) / _mat[0][0];
    right = (1.0-_mat[3][0]) / _mat[0][0];

    bottom = -(1.0+_mat[3][1]) / _mat[1][1];
    top = (1.0-_mat[3][1]) / _mat[1][1];
    
    return true;
}            


void Matrix::makeFrustum(double left, double right,
                         double bottom, double top,
                         double zNear, double zFar)
{
    // note transpose of Matrix wr.t OpenGL documentation, since the OSG use post multiplication rather than pre.
    double A = (right+left)/(right-left);
    double B = (top+bottom)/(top-bottom);
    double C = -(zFar+zNear)/(zFar-zNear);
    double D = -2.0*zFar*zNear/(zFar-zNear);
    SET_ROW(0, 2*(float)zNear/(float)(right-left),                    0.0f, 0.0f,  0.0f )
    SET_ROW(1,                    0.0f, (float)(2.0*zNear/(top-bottom)), 0.0f,  0.0f )
    SET_ROW(2,                      (float)A,                      (float)B,   (float)C, -1.0f )
    SET_ROW(3,                    0.0f,                    0.0f,   (float)D,  0.0f )
}

bool Matrix::getFrustum(double& left, double& right,
                                       double& bottom, double& top,
                                       double& zNear, double& zFar) const
{
    if (_mat[0][3]!=0.0f || _mat[1][3]!=0.0f || _mat[2][3]!=-1.0f || _mat[3][3]!=0.0f) return false;


    zNear = _mat[3][2] / (_mat[2][2]-1.0);
    zFar = _mat[3][2] / (1.0+_mat[2][2]);
    
    left = zNear * (_mat[2][0]-1.0) / _mat[0][0];
    right = zNear * (1.0+_mat[2][0]) / _mat[0][0];

    top = zNear * (1.0+_mat[2][1]) / _mat[1][1];
    bottom = zNear * (_mat[2][1]-1.0) / _mat[1][1];
    
    return true;
}                 


void Matrix::makePerspective(double fovy,double aspectRatio,
                                            double zNear, double zFar)
{
    // calculate the appropriate left, right etc.
    double tan_fovy = tan(DegreesToRadians(fovy*0.5));
    double right  =  tan_fovy * aspectRatio * zNear;
    double left   = -right;
    double top    =  tan_fovy * zNear;
    double bottom =  -top;
    makeFrustum(left,right,bottom,top,zNear,zFar);
}

bool Matrix::getPerspective(double& fovy,double& aspectRatio,
                                           double& zNear, double& zFar) const
{
    double right  =  0.0;
    double left   =  0.0;
    double top    =  0.0;
    double bottom =  0.0;
    if (getFrustum(left,right,bottom,top,zNear,zFar))
    {
        fovy = RadiansToDegrees(atan(top/zNear)-atan(bottom/zNear));
        aspectRatio = (right-left)/(top-bottom);
        return true;
    }
    return false;
}

void Matrix::makeLookAt(const Vec3& eye,const Vec3& center,const Vec3& up)
{
    Vec3 f(center-eye);
    f.normalize();
    Vec3 s(f^up);
    s.normalize();
    Vec3 u(s^f);
    u.normalize();

    set(
        s[0],     u[0],     -f[0],     0.0,
        s[1],     u[1],     -f[1],     0.0,
        s[2],     u[2],     -f[2],     0.0,
        0.0,     0.0,     0.0,      1.0);

    preMult(Matrix::translate(-eye));
}


void Matrix::getLookAt(Vec3& eye,Vec3& center,Vec3& up,float lookDistance) const
{
    Matrix inv;
    inv.invert(*this);
    eye = Vec3(0.0,0.0,0.0)*inv;
    up = transform3x3(*this,Vec3(0.0,1.0,0.0));
    center = transform3x3(*this,Vec3(0.0,0.0,-1));
    center.normalize();
    center = eye + center*lookDistance;
}

#undef SET_ROW
