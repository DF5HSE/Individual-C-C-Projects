/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MATR.H
 * PURPOSE     : 3D math support.
 *               Matrix module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 20.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __MATR_H_
#define __MATR_H_

#include "mthdef.h"

 /* Math support namespace */
namespace mth
{
  /* Matr4x4 class declaration */
  template<class type>
    class matr
    {
    private:
      template<class type>
        friend class vec;
      template<class type>
        friend class camera;

      type A[4][4];                     // Matrix
      mutable type InvA[4][4];          // Inverse matrix
      mutable BOOL IsInverseEvaluated;  // Flag of evaluation inverse matrix

      /* Evaluating inverse matrix function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID EvaluateInverseMatrix( VOID ) const
      {
        if (IsInverseEvaluated)
          return;
        IsInverseEvaluated = TRUE;
        type det = MatrDeterm(*this);
        if (det == 0)
        {
          InvA{
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
              };
          return;
        }
        InvA[0][0] = 
          MatrDeterm3x3(A[1][1], A[1][2], A[1][3],
                        A[2][1], A[2][2], A[2][3],
                        A[3][1], A[3][2], A[3][3]);
        InvA[1][0] = 
          MatrDeterm3x3(A[1][0], A[1][2], A[1][3],
                        A[2][0], A[2][2], A[2][3],
                        A[3][0], A[3][2], A[3][3]);
        InvA[2][0] = 
          MatrDeterm3x3(A[1][0], A[1][1], A[1][3],
                        A[2][0], A[2][1], A[2][3],
                        A[3][0], A[3][1], A[3][3]);
        InvA[3][0] = 
          MatrDeterm3x3(A[1][0], A[1][1], A[1][2],
                        A[2][0], A[2][1], A[2][2],
                        A[3][0], A[3][1], A[3][2]);
        InvA[0][1] = 
          MatrDeterm3x3(A[0][1], A[0][2], A[0][3],
                        A[2][1], A[2][2], A[2][3],
                        A[3][1], A[3][2], A[3][3]);
        InvA[1][1] = 
          MatrDeterm3x3(A[0][0], A[0][2], A[0][3],
                        A[2][0], A[2][2], A[2][3],
                        A[3][0], A[3][2], A[3][3]);
        InvA[2][1] = 
          MatrDeterm3x3(A[0][0], A[0][1], A[0][3],
                        A[2][0], A[2][1], A[2][3],
                        A[3][0], A[3][1], A[3][3]);
        InvA[3][1] =
          MatrDeterm3x3(A[0][0], A[0][1], A[0][2],
                        A[2][0], A[2][1], A[2][2],
                        A[3][0], A[3][1], A[3][2]);
        InvA[0][2] = 
          MatrDeterm3x3(A[0][1], A[0][2], A[0][3],
                        A[1][1], A[1][2], A[1][3],
                        A[3][1], A[3][2], A[3][3]);
        InvA[1][2] = 
          MatrDeterm3x3(A[0][0], A[0][2], A[0][3],
                        A[1][0], A[1][2], A[1][3],
                        A[3][0], A[3][2], A[3][3]);
        InvA[2][2] = 
          MatrDeterm3x3(A[0][0], A[0][1], A[0][3],
                        A[1][0], A[1][1], A[1][3],
                        A[3][0], A[3][1], A[3][3]);
        InvA[3][2] = 
          MatrDeterm3x3(A[0][0], A[0][1], A[0][2],
                        A[1][0], A[1][1], A[1][2],
                        A[3][0], A[3][1], A[3][2]);
        InvA[0][3] = 
          MatrDeterm3x3(A[0][1], A[0][2], A[0][3],
                        A[1][1], A[1][2], A[1][3],
                        A[2][1], A[2][2], A[2][3]);
        InvA[1][3] = 
          MatrDeterm3x3(A[0][0], A[0][2], A[0][3],
                        A[1][0], A[1][2], A[1][3],
                        A[2][0], A[2][2], A[2][3]);
        InvA[2][3] = 
          MatrDeterm3x3(A[0][0], A[0][1], A[0][3],
                        A[1][0], A[1][1], A[1][3],
                        A[2][0], A[2][1], A[2][3]);
        InvA[3][3] = 
          MatrDeterm3x3(A[0][0], A[0][1], A[0][2],
                        A[1][0], A[1][1], A[1][2],
                        A[2][0], A[2][1], A[2][2]);

        InvA[0][0] /= det;
        InvA[1][0] /= det;
        InvA[2][0] /= det;
        InvA[3][0] /= det;
        InvA[0][1] /= det;
        InvA[1][1] /= det;
        InvA[2][1] /= det;
        InvA[3][1] /= det;
        InvA[0][2] /= det;
        InvA[1][2] /= det;
        InvA[2][2] /= det;
        InvA[3][2] /= det;
        InvA[0][3] /= det;
        InvA[1][3] /= det;
        InvA[2][3] /= det;
        InvA[3][3] /= det;
      } /* End of 'EvaluateInverseMatrix' function*/

    public:
      /* Default class constructor.
       * ARGUMENTS: None.
       */
      matr( VOID ) : IsInverseEvaluated(FALSE)
      {
      } /* End of 'matr' function */

      /* Class constructor.
       * ARGUMENTS: 
       *   - numbers for matrix:
       *       const type 
       *               A11, A12, A13, A14,
       *               A21, A22, A23, A24,
       *               A31, A32, A33, A34,
       *               A41, A42, A43, A44.
       */
      explicit matr( const type A11, const type A12 = 0, const type A13 = 0, const type A14 = 0,
                     const type A21 = 0, const type A22 = 1, const type A23 = 0, const type A24 = 0,
                     const type A31 = 0, const type A32 = 0, const type A33 = 1, const type A34 = 0,
                     const type A41 = 0, const type A42 = 0, const type A43 = 0, const type A44 = 1 ) : A{
                                                                                                           {A11, A12, A13, A14},
                                                                                                           {A21, A22, A23, A24},
                                                                                                           {A31, A32, A33, A34},
                                                                                                           {A41, A42, A43, A44}
                                                                                                         }, IsInverseEvaluated(FALSE)
      {
      } /* End of 'matr' function */

      /* Countion determinant of matrix3x3 function.
       * ARGUMENTS:
       *   - numbers from matrix:
       *       const type 
       *               A11, A12, A13,
       *               A21, A22, A23,
       *               A31, A32, A33;
       * RETURNS:
       *   (type) matr 3x3 determinant.
       */
      static type MatrDeterm3x3( const type A11, const type A12, const type A13,
                                 const type A21, const type A22, const type A23,
                                 const type A31, const type A32, const type A33 )
      {
        return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 +
               A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
      } /* End of 'MatrDeterm3x3' function*/


      /* Change operator ! for counting determinant of matrix4x4 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) matrix 4x4 determinant.
       */
      type operator!( VOID ) const
      {
        return
          A[0][0] * MatrDeterm3x3(A[1][1], A[1][2], A[1][3],
                                  A[2][1], A[2][2], A[2][3],
                                  A[3][1], A[3][2], A[3][3]) -
          A[0][1] * MatrDeterm3x3(A[1][0], A[1][2], A[1][3],
                                  A[2][0], A[2][2], A[2][3],
                                  A[3][0], A[3][2], A[3][3]) +
          A[0][2] * MatrDeterm3x3(A[1][0], A[1][1], A[1][3],
                                  A[2][0], A[2][1], A[2][3],
                                  A[3][0], A[3][1], A[3][3]) -
          A[0][3] * MatrDeterm3x3(A[1][0], A[1][1], A[1][2],
                                  A[2][0], A[2][1], A[2][2],
                                  A[3][0], A[3][1], A[3][2]);
      } /* End of 'operator!' function*/

      /* Change operator * for product of matrix function.
       * ARGUMENTS:
       *   - link on matrix for product:
       *       const matr<type> &M;
       * RETURNS:
       *   (matr<type>) on result of product.
       */
      matr<type> operator*( const matr<type> &M ) const
      {
        matr<type> r(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
              r.A[i][j] += A[i][k] * M.A[k][j];

        return r;
      } /* End of 'operator*' function*/

      /* Change operator 
      
      
      for *= of matrix function.
       * ARGUMENTS:
       *   - link on matrix for product:
       *       const matr<type> &M;
       * RETURNS:
       *   (matr<type> &) link on result of product.
       */
      matr<type> & operator*=( const matr<type> &M )
      {
        *this = (*this) * M;
        IsInverseEvaluated = FALSE;

        return *this;
      } /* End of 'operator*=' function*/

      /* Identity matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr<type>) identity matrix.
       */
      static matr<type> Identity( VOID )
      {
        return matr<type>(1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1);
      } /* End of 'Identity' function */

      /* Matrix of rotation around vector function.
       * ARGUMENTS:
       *   - link on vector for rotation around it:
       *       vec<type> &R;
       *   - angle in degrees for rotation:
       *       FLT Angle;
       * RETURNS:
       *   (matr<type>) matrix rotation.
       */
      static matr<type> Rotate( vec<type> &R, const FLT Angle )
      {
        FLT A = Degree2Radian<FLT, FLT>(Angle), si = sin(A), co = cos(A);
        vec<type> V = R.Normalize();

        return matr<type>(co + V.X * V.X * (1 - co),        V.X * V.Y * (1 - co) - V.Z * si,  V.X * V.Z * (1 - co) + V.Y * si,  0,
                          V.Y * V.X * (1 - co) + V.Z * si,  co + V.Y * V.Y * (1 - co),        V.Y * V.Z * (1 - co) - V.X * si,  0,
                          V.Z * V.X * (1 - co) - V.Y * si,  V.Z * V.Y * (1 - co) + V.X * si,  co + V.Z * V.Z * (1 - co),        0,
                          0,                                0,                                0,                                1);
      } /* End of 'Rotate' function*/

      /* Transposposition of matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr<type>) transpose matrix.
       */
       matr<type> Transpose( VOID ) const
       {
         return matr<type>(A[0][0], A[1][0], A[2][0], A[3][0],
                           A[0][1], A[1][1], A[2][1], A[3][1],
                           A[0][2], A[1][2], A[2][2], A[3][2],
                           A[0][3], A[1][3], A[2][3], A[3][3]);
       } /* End of 'Transpose' funciton */

       /* Matrix of rotation around X axis function.
        * ARGUMENTS:
        *   - angle in degrees for rotation:
        *       FLT Angle;
        * RETURNS:
        *   (matr<type>) matrix rotation.
        */
       static matr<type> RotateX( const FLT Angle )
       {
         FLT A = Degree2Radian<FLT, FLT>(Angle), si = sin(A), co = cos(A);

         return matr<type>(1,  0,    0,   0,
                           0,  co,   si,  0,
                           0,  -si,  co,  0,
                           0,  0,    0,   1);
       } /* End of 'RotateX' function*/

       /* Matrix of rotation around Y axis function.
        * ARGUMENTS:
        *   - angle in degrees for rotation:
        *       FLT Angle;
        * RETURNS:
        *   (matr<type>) matrix rotation.
        */
       static matr<type> RotateY( const FLT Angle )
       {
         FLT A = Degree2Radian<FLT, FLT>(Angle), si = sin(A), co = cos(A);

         return matr<type>(co,  0,  -si,  0,
                           0,   1,  0,    0,
                           si,  0,  co,   0,
                           0,   0,  0,    1);
       } /* End of 'RotateY' function*/

       /* Matrix of rotation around Z axis function.
        * ARGUMENTS:
        *   - angle in degrees for rotation:
        *       FLT Angle;
        * RETURNS:
        *   (matr<type>) matrix rotation.
        */
       static matr<type> RotateZ( const FLT Angle )
       {
         FLT A = Degree2Radian<FLT, FLT>(Angle), si = sin(A), co = cos(A);

         return matr<type>(co,   si,  0,  0,
                           -si,  co,  0,  0,
                           0,    0,   1,  0,
                           0,    0,   0,  1);
       } /* End of 'RotateZ' function*/

       /* Translate matrix function.
        * ARGUMENTS:
        *   - vector for translating:
        *       vec<type> Tr;
        * RETURNS:
        *   (matr<type>) translate matrix.
        */
        static matr<type> Translate( const vec<type> Tr )
        {
          return matr<type>(1,     0,     0,     0,
                            0,     1,     0,     0,
                            0,     0,     1,     0,
                            Tr.X,  Tr.Y,  Tr.Z,  1);
        } /* End of 'Translate' function */

        /* Scale matrix function.
         * ARGUMENTS:
         *   - vector for scaling:
         *       vec<type> Sc;
         * RETURNS:
         *   (matr<type>) translate matrix.
         */
        static matr<type> Scale( const vec<type> Sc )
        {
          return matr<type>(Sc.X,  0,     0,     0,
                            0,     Sc.Y,  0,     0,
                            0,     0,     Sc.Z,  0,
                            0,     0,     0,     1);
        } /* End of 'Scale' function */

        /* Vector transformation function.
         * ARGUMENTS:
         *   - link on vector for transform:
         *       const vec<type> &V;
         * RETURNS:
         *   (vec<type>) on transformed vector.
         */
        vec<type> VectorTransform( const vec<type> &V ) const
        {
          type w = V.X * A[0][3] + V.Y * A[1][3] + V.Z * A[2][3];

          return vec<type>((V.X * A[0][0] + V.Y * A[1][0] + V.Z * A[2][0]) / w,
                           (V.X * A[0][1] + V.Y * A[1][1] + V.Z * A[2][1]) / w,
                           (V.X * A[0][2] + V.Y * A[1][2] + V.Z * A[2][2]) / w);
        }/* End of 'VectorTransform' function */

        /* Point transformation function.
         * ARGUMENTS:
         *   - link on point for transform:
         *       const vec<type> &P;
         * RETURNS:
         *   (vec<type>) on transformed point.
         */
        vec<type> PointTransform( const vec<type> &P ) const
        {
          type w = P.X * A[0][3] + P.Y * A[1][3] + P.Z * A[2][3] + A[3][3];

          return vec<type>((P.X * A[0][0] + P.Y * A[1][0] + P.Z * A[2][0] + A[3][0]) / w,
                           (P.X * A[0][1] + P.Y * A[1][1] + P.Z * A[2][1] + A[3][1]) / w,
                           (P.X * A[0][2] + P.Y * A[1][2] + P.Z * A[2][2] + A[3][2]) / w);
        }/* End of 'PointTransform' function */

        /* Normal transformation function.
         * ARGUMENTS:
         *   - link on normal for transform:
         *       const vec<type> &N;
         * RETURNS:
         *   (vec<type>) on transformed normal.
         */
        vec<type> NormalTransform( const vec<type> &N ) const
        {
          EvaluateInverseMatrix();
          return vec<type>(N.X * InvA[0][0] + N.Y * InvA[0][1] + N.Z * InvA[0][2],
                           N.X * InvA[1][0] + N.Y * InvA[1][1] + N.Z * InvA[1][2],
                           N.X * InvA[2][0] + N.Y * InvA[1][1] + N.Z * InvA[2][2]);
        }/* End of 'NormalTransform' function */

        /* View coordinate system matrix function.
         * ARGUMENTS:
         *   - vectors location, direction, up, right:
         *      const vec<type> Loc, Dir, Up, Right;
         * RETURNS:
         *   (matr<type>) VCS matrix.
         */
        static matr<type> View( const vec<type> Loc, const vec<type> Dir, const vec<type> Up, const vec<type> Right )
        {
          return matr<type>(Right.X, Up.X, -Dir.X, 0,
                            Right.Y, Up.Y, -Dir.Y, 0,
                            Right.Z, Up.X, -Dir.Z, 0,
                            -(Loc & Right), -(Loc & Up), Loc & Dir, 1);
        } /* end of 'View' function*/

        /* View frustum matrix function.
         * ARGUMENTS:
         *   - distanses to left, right, bottom, top, near and far:
         *      const type l, r, b, t, n, f;
         * RETURNS:
         *   (matr<type>) frustum matrix.
         */
         static matr<type> Frustum( const type l, const type r, const type b, const type t, const type n, const type f )
         {
           return matr<type>(2 * n / (r - l),    0,                  0,                     0,
                             0,                  2 * n / (t - b),    0,                     0,
                             (r + l) / (r - l),  (t + b) / (t - b),  -(f + n) / (f - n),    -1,
                             0,                  0,                  -2 * n * f / (f - n),  0);
         } /* End of 'Frustum' function */
    }; /* End of 'matr' class */
} /* end of 'mth' namespace */


#endif /* __MATR_H_ */

/* END OF 'MATR.H' FILE */





