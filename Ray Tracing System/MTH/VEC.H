/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : VEC.H
 * PURPOSE     : Math support.
 *               Vector module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 26.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __VEC_H_
#define __VEC_H_

#include "mthdef.h"

/* Math support namespace */
namespace mth
{
  /* 3D space vector class declaration */
  template<class type>
    class vec
    {
    private:
      template<class type>
        friend class matr;
      type X, Y, Z;  /* vector coordinates */

    public:
      /* Default class constructor.
       * ARGUMENTS: None.
       */
      vec( VOID )
      {
      } /* End of 'vec' function */

      /* Class constructor.
       * ARGUMENTS: 
       *   - x, y, z coordinates:
       *       type X, Y, Z.
       */
       vec( type X, type Y, type Z ) : X(X), Y(Y), Z(Z)
       {
       } /* End of 'vec' function */

       /* Class constructor.
        * ARGUMENTS: 
        *   - coordinate for all components:
        *       type A.
        */
       explicit vec( type A ) : X(A), Y(A), Z(A)
       {
       } /* End of 'vec' function */

       /* Changing operator & for dot product function.
        * ARGUMENTS:
        *   - link on vector for product:
        *       const vec<type> &V;
        * RETURNS:
        *   (type) result of product.
        */
       type operator&( const vec<type> &V ) const
       {
         return X * V.X + Y * V.Y + Z * V.Z;
       } /* End of 'operator&' function */

       /* Changing operator + for vector sum function.
        * ARGUMENTS:
        *   - link on vector for sum:
        *       const vec<type> &V;
        * RETURNS:
        *   (vec<type>) result of sum.
        */
       vec<type> operator+( const vec<type> &V ) const
       {
         return vec<type>(X + V.X, Y + V.Y, Z + V.Z);
       } /* End of 'operator+' function */

       /* Changing operator - for vector sub function.
        * ARGUMENTS:
        *   - link on vector for sub:
        *       const vec<type> &V;
        * RETURNS:
        *   (vec<type>) result of sub.
        */
       vec<type> operator-( const vec<type> &V ) const
       {
         return vec<type>(X - V.X, Y - V.Y, Z - V.Z);
       } /* End of 'operator-' function */

       /* Changing operator - (unary) for vector sub function.
        * ARGUMENTS: None.
        * RETURNS:
        *   (vec<type>) result of unary.
        */
       vec<type> operator-( VOID ) const
       {
         return vec<type>(-X, -Y, -Z);
       } /* End of 'operator-' function */

       /* Changing operator += for vector += vector function.
       * ARGUMENTS:
       *   - link on vector for +=:
       *       const vec<type> &V;
       * RETURNS:
       *   (vec<type> &) link on result of +=.
       */
       vec<type> & operator+=( const vec<type> &V )
       {
         X += V.X;
         Y += V.Y;
         Z += V.Z;

         return *this;
       } /* End of 'operator+=' function */

       /* Changing operator -= for vector -= vector function.
       * ARGUMENTS:
       *   - link on vector for -=:
       *       const vec<type> &V;
       * RETURNS:
       *   (vec<type> &) link on result of -=.
       */
       vec<type> & operator-=( const vec<type> &V )
       {
         X -= V.X;
         Y -= V.Y;
         Z -= V.Z;

         return *this;
       } /* End of 'operator-=' function */

       /* Changing operator * for vector product on number function.
       * ARGUMENTS:
       *   - link on number for product:
       *       const type &N;
       * RETURNS:
       *   (vec<type>) result of product.
       */
       vec<type> operator*( const type &N ) const
       {
         return vec(X * N, Y * N, Z * N);
       } /* End of 'operator*' function */

       /* Changing operator / for vector division on number function.
       * ARGUMENTS:
       *   - link on number for division:
       *       const type &N;
       * RETURNS:
       *   (vec<type>) result of division.
       */
       vec<type> operator/( const type &N ) const
       {
         return vec<type>(X / N, Y / N, Z / N);
       } /* End of 'operator/' function */

       /* Changing operator *= for vector *= number function.
        * ARGUMENTS:
        *   - link on number for *=:
        *       const type &N;
        * RETURNS:
        *   (vec<type> &) link on result of *=.
        */
       vec<type> & operator*=( const type &N )
       {
         X *= N;
         Y *= N;
         Z *= N;
       
         return *this;
       } /* End of 'operator*=' function */
       
       /* Changing operator * for vector * components of two vectors function.
        * ARGUMENTS:
        *   - link on vector for *:
        *       const vec<type> &V;
        * RETURNS:
        *   (vec<type>) link on result of *.
        */
       vec<type> operator*( const vec<type> &V ) const
       {
         return vec<type>(X * V.X, Y * V.Y, Z * V.Z);
       } /* End of 'operator*' function */

       /* Changing operator / for vector / components of two vectors function.
        * ARGUMENTS:
        *   - link on vector for /:
        *       const vec<type> &V;
        * RETURNS:
        *   (vec<type>) link on result of /.
        */
       vec<type> operator/( const vec<type> &V )
       {
         return vec<type>(X / V.X, Y / V.Y, Z / V.Z);
       } /* End of 'operator/' function */

       /* Changing operator *= for vector *= components of two vectors function.
        * ARGUMENTS:
        *   - link on vector for *=:
        *       const vec<type> &V;
        * RETURNS:
        *   (vec<type> &) link on result of *=.
        */
       vec<type> & operator*=( const vec<type> &V )
       {
         X *= V.X;
         Y *= V.Y;
         Z *= V.Z;
       
         return *this;
       } /* End of 'operator*=' function */

       /* Changing operator /= for vector /= components of two vectors function.
        * ARGUMENTS:
        *   - link on vector for /=:
        *       const vec<type> &V;
        * RETURNS:
        *   (vec<type> &) link on result of /=.
        */
       vec<type> & operator/=( const vec<type> &V )
       {
         X /= V.X;
         Y /= V.Y;
         Z /= V.Z;
       
         return *this;
       } /* End of 'operator/=' function */

       /* Changing operator /= for vector /= number function.
       * ARGUMENTS:
       *   - link on number for /=:
       *       const type &N;
       * RETURNS:
       *   (vec<type> &) link on result of /=.
       */
       vec<type> & operator/=( const type &N )
       {
         X /= N;
         Y /= N;
         Z /= N;

         return *this;
       } /* End of 'operator/=' function */

       /* Changing operator % for cross product function.
        * ARGUMENTS:
        *   - link on vector for product:
        *       const vec<type> &V;
        * RETURNS:
        *   (vec<type>) result of product.
        */
       vec<type> operator%( const vec<type> &V ) const
       {
         return vec<type>(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
       } /* End of 'operator&' function */

       /* Changing operator [] to get coordinate.
        * ARGUMENTS:
        *   - link on number of coordinate:
        *      const INT &NumOfCoord;
        * RETURNS:
        *  (type) coordinate.
        */
       type operator[]( const INT &NumOfCoord ) const
       {
         return NumOfCoord == 0 ? X :
                NumOfCoord == 1 ? Y : Z;
       } /* End of 'operator[]' function */

       /* Changing operator < for vectors.
        * ARGUMENTS:
        *  - vector for operation:
        *      const vec &V;
        * RETURNS:
        *   (BOOL) if every coordinate < every coordinate of vector - TRUE, else - FALSE.
        */
       BOOL operator<( const vec &V )
       {
         return ((X < V.X) && (Y < V.Y) && (Z < V.Z)) ? TRUE : FALSE;
       } /* End of 'operator<' function */

       /* Changing operator > for vectors.
        * ARGUMENTS:
        *  - vector for operation:
        *      const vec &V;
        * RETURNS:
        *   (BOOL) if every coordinate > every coordinate of vector - TRUE, else - FALSE.
        */
       BOOL operator>( const vec &V )
       {
         return ((X > V.X) && (Y > V.Y) && (Z > V.Z)) ? TRUE : FALSE;
       } /* End of 'operator>' function */

       /* Square length of vector function.
        * ARGUMENTS: None.
        * RETURNS:
        *   (type) square length of vector.
        */
      type Length2( VOID ) const
      {
        return X * X + Y * Y + Z * Z;
      } /* End of 'Length2' function */

       /* Normalize of vector function.
        * ARGUMENTS: None.
        * RETURNS:
        *   (vec<type> &) link on normalized vector.
        */
      vec<type> & Normalize( VOID )
      {
        type len;
        
        len = sqrt(Length2());
        X /= len;
        Y /= len;
        Z /= len;

        return *this;
      } /* End of 'Normalize' function */

       /* Normalizing of vector function.
        * ARGUMENTS: None.
        * RETURNS:
        *   (vec<type>) normalized vector.
        */
      vec<type> Normalizing( VOID ) const
      {
        type len;
        vec<type> r;

        len = sqrt(Length2());
        r.X = X / len;
        r.Y = Y / len;
        r.Z = Z / len;

        return r;
      } /* End of 'Normalizing' function */

      /* Square distanse to point space function.
       * ARGUMENTS: 
       *   - link on point in space:
       *       const vec<type> &P;
       * RETURNS:
       *   (type) square distance to point in space.
       */
      type Distance2( const vec<type> &P ) const
      {
        vec<type> dist = P - (*this);

        return dist.Length2();
      } /* End of 'Distance' function*/

      /* Filling coordinates by zero function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec<type>) the link to filled vector.
       */
      vec<type> Zero( VOID )
      {
        X = Y = Z = 0;

        return *this;
      } /* End of 'Zero' function*/

      /* Filling coordinates by random numbers function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec<type> &) the link to filled vector.
       */
      vec<type> & Rnd( VOID )
      {
        X = rand() * 10.0 / RAND_MAX;
        Y = rand() * 6.0 / RAND_MAX;
        Z = rand() * 8 / RAND_MAX;

        return *this;
      } /* End of 'Rnd' function*/
    }; /* End of 'vec' class */

  /* 2D space vector class declaration */
  template<class type>
    class vec2
    {
    private:
      type X, Y;  /* vector coordinates */

    public:
      /* Default class constructor.
       * ARGUMENTS: None.
       */
      vec2( VOID )
      {
      } /* End of 'vec2' function */

      /* Class constructor.
       * ARGUMENTS: 
       *   - x, y coordinates:
       *       type X, Y.
       */
      vec2( type X, type Y ) : X(X), Y(Y)
      {
      } /* End of 'vec2' function */

       /* Class constructor.
        * ARGUMENTS: 
        *   - coordinate for all components:
        *       type A.
        */
       vec2( type A ) : X(A), Y(A)
       {
       } /* End of 'vec' function */

      /* Changing operator & for dot product function.
       * ARGUMENTS:
       *   - link on vector for product:
       *       const vec2<type> &V;
       * RETURNS:
       *   (type) result of product.
       */
      type operator&( const vec2<type> &V ) const
      {
        return X * V.X + Y * V.Y;
      } /* End of 'operator&' function */

      /* Changing operator + for vector sum function.
       * ARGUMENTS:
       *   - link on vector for sum:
       *       const vec2<type> &V;
       * RETURNS:
       *   (vec2<type>) result of sum.
       */
      vec2<type> operator+( const vec2<type> &V ) const
      {
        return vec2<type>(X + V.X, Y + V.Y);
      } /* End of 'operator+' function */

      /* Changing operator - for vector sub function.
       * ARGUMENTS:
       *   - link on vector for sub:
       *       const vec2<type> &V;
       * RETURNS:
       *   (vec2<type>) result of sub.
       */
      vec2<type> operator-( const vec2<type> &V ) const
      {
        return vec2<type>(X - V.X, Y - V.Y);
      } /* End of 'operator-' function */

      /* Changing operator - (unary) for vector sub function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2<type>) result of unary.
       */
      vec2<type> operator-( VOID ) const
      {
        return vec2<type>(-X, -Y);
      } /* End of 'operator-' function */

      /* Changing operator += for vector += vector function.
       * ARGUMENTS:
       *   - link on vector for +=:
       *       const vec2<type> &V;
       * RETURNS:
       *   (vec2<type> &) link on result of +=.
       */
      vec2<type> & operator+=( const vec2<type> &V )
      {
        X += V.X;
        Y += V.Y;

        return *this;
      } /* End of 'operator+=' function */

      /* Changing operator -= for vector -= vector function.
       * ARGUMENTS:
       *   - link on vector for -=:
       *       const vec2<type> &V;
       * RETURNS:
       *   (vec2<type> &) link on result of -=.
       */
      vec2<type> & operator-=( const vec2<type> &V )
      {
        X -= V.X;
        Y -= V.Y;

        return *this;
      } /* End of 'operator-=' function */

      /* Changing operator * for vector product on number function.
       * ARGUMENTS:
       *   - link on number for product:
       *       const type &N;
       * RETURNS:
       *   (vec2<type>) result of product.
       */
      vec2<type> operator*( const type &N ) const
      {
        return vec2(X * N, Y * N);
      } /* End of 'operator*' function */

      /* Changing operator / for vector division on number function.
       * ARGUMENTS:
       *   - link on number for division:
       *       const type &N;
       * RETURNS:
       *   (vec2<type>) result of division.
       */
      vec2<type> operator/( const type &N ) const
      {
        return vec2(X / N, Y / N);
      } /* End of 'operator/' function */

      /* Changing operator *= for vector *= number function.
       * ARGUMENTS:
       *   - link on number for *=:
       *       const type &N;
       * RETURNS:
       *   (vec2<type> &) link on result of *=.
       */
      vec2<type> & operator*=( const type &N )
      {
        X *= N;
        Y *= N;

        return *this;
      } /* End of 'operator*=' function */

      /* Changing operator /= for vector /= number function.
       * ARGUMENTS:
       *   - link on number for /=:
       *       const type &N;
       * RETURNS:
       *   (vec2<type> &) link on result of /=.
       */
      vec2<type> & operator/=( const type &N )
      {
        X /= N;
        Y /= N;

        return *this;
      } /* End of 'operator/=' function */

      /* Changing operator * for vector * components of two vectors function.
       * ARGUMENTS:
       *   - link on vector for *:
       *       const vec2<type> &V;
       * RETURNS:
       *   (vec2<type>) link on result of *.
       */
      vec2<type> & operator*( const vec2<type> &V )
      {
        return vec2<type>(X * V.X, Y * V.Y);
      } /* End of 'operator*' function */
      
      /* Changing operator / for vector / components of two vectors function.
       * ARGUMENTS:
       *   - link on vector for /:
       *       const vec2<type> &V;
       * RETURNS:
       *   (vec2<type>) link on result of /.
       */
      vec2<type> operator/( const vec2<type> &V )
      {
        return vec2<type>(X / V.X, Y / V.Y);
      } /* End of 'operator/' function */

      /* Changing operator *= for vector *= components of two vectors function.
        * ARGUMENTS:
        *   - link on vector for *=:
        *       const vec2<type> &V;
        * RETURNS:
        *   (vec2<type> &) link on result of *=.
        */
       vec2<type> & operator*=( const vec2<type> &V )
       {
         X *= V.X;
         Y *= V.Y;

         return *this;
       } /* End of 'operator*=' function */

       /* Changing operator /= for vector /= components of two vectors function.
        * ARGUMENTS:
        *   - link on vector for /=:
        *       const vec2<type> &V;
        * RETURNS:
        *   (vec2<type> &) link on result of /=.
        */
       vec2<type> & operator/=( const vec2<type> &V )
       {
         X /= V.X;
         Y /= V.Y;

         return *this;
       } /* End of 'operator/=' function */

      /* Changing operator [] to get coordinate.
       * ARGUMENTS:
       *   - link on number of coordinate:
       *      const INT &NumOfCoord;
       * RETURNS:
       *  (type) coordinate.
       */
      type operator[]( const INT &NumOfCoord ) const
      {
        return NumOfCoord == 0 ? X : Y;
      } /* End of 'operator[]' function */
      /* Square length of vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) square length of vector.
       */
      type Length2( VOID ) const
      {
        return X * X + Y * Y;
      } /* End of 'Length2' function */

      /* Normalize of vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2<type> &) link on normalized vector.
       */
      vec2<type> & Normalize( VOID )
      {
        type len;
        
        len = sqrt(Length2());
        X /= len;
        Y /= len;

        return *this;
      } /* End of 'Normalize' function */

      /* Normalizing of vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2<type>) normalized vector.
       */
      vec2<type> Normalizing( VOID ) const
      {
        type len;
        vec2<type> r;

        len = sqrt(Length2());
        r.X = X / len;
        r.Y = Y / len;

        return r;
      } /* End of 'Normalizing' function */

      /* Square distanse to point space function.
       * ARGUMENTS: 
       *   - link on point in space:
       *       const vec2<type> &P;
       * RETURNS:
       *   (type) square distance to point in space.
       */
      type Distance2( const vec2<type> &P ) const
      {
        vec2<type> dist = P - (*this);

        return dist.Length2();
      } /* End of 'Distance' function*/

      /* Filling coordinates by zero function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2<type>) the link to filled vector.
       */
      vec2<type> Zero( VOID )
      {
        X = Y = 0;

        return *this;
      } /* End of 'Zero' function*/

      /* Filling coordinates by random numbers function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2<type> &) the link to filled vector.
       */
      vec2<type> & Rnd( VOID )
      {
        X = rand() * 10.0 / RAND_MAX;
        Y = rand() * 6.0 / RAND_MAX;

        return *this;
      } /* End of 'Rnd' function*/

    }; /* End of 'vec2' class */

  /* 4D space vector class declaration */
  template<class type>
    class vec4
    {
    private:
      type X, Y, Z, W;  /* vector coordinates */

    public:
      /* Default class constructor.
       * ARGUMENTS: None.
       */
      vec4( VOID )
      {
      } /* End of 'vec4' function */

      /* Class constructor.
       * ARGUMENTS: 
       *   - x, y, z, w coordinates:
       *       type X, Y, Z, W.
       */
      vec4( type X, type Y, type Z, type W ) : X(X), Y(Y), Z(Z), W(W)
      {
      } /* End of 'vec4' function */

       /* Class constructor.
        * ARGUMENTS: 
        *   - coordinate for all components:
        *       type A.
        */
       vec4( type A ) : X(A), Y(A), Z(A), W(A)
       {
       } /* End of 'vec' function */

      /* Changing operator & for dot product function.
       * ARGUMENTS:
       *   - link on vector for product:
       *       const vec4<type> &V;
       * RETURNS:
       *   (type) result of product.
       */
      type operator&( const vec4<type> &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z + W * V.W;
      } /* End of 'operator&' function */

      /* Changing operator + for vector sum function.
       * ARGUMENTS:
       *   - link on vector for sum:
       *       const vec4<type> &V;
       * RETURNS:
       *   (vec4<type>) result of sum.
       */
      vec4<type> operator+( const vec4<type> &V ) const
      {
        return vec4<type>(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
      } /* End of 'operator+' function */

      /* Changing operator - for vector sub function.
       * ARGUMENTS:
       *   - link on vector for sub:
       *       const vec4<type> &V;
       * RETURNS:
       *   (vec4<type>) result of sub.
       */
      vec4<type> operator-( const vec4<type> &V ) const
      {
        return vec4<type>(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
      } /* End of 'operator-' function */

      /* Changing operator - (unary) for vector sub function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2<type>) result of unary.
       */
      vec4<type> operator-( VOID ) const
      {
        return vec4<type>(-X, -Y, -Z, -W);
      } /* End of 'operator-' function */

      /* Changing operator += for vector += vector function.
       * ARGUMENTS:
       *   - link on vector for +=:
       *       const vec4<type> &V;
       * RETURNS:
       *   (vec4<type> &) link on result of +=.
       */
      vec4<type> & operator+=( const vec4<type> &V )
      {
        X += V.X;
        Y += V.Y;
        Z += V.Z;
        W += V.W;

        return *this;
      } /* End of 'operator+=' function */

      /* Changing operator -= for vector -= vector function.
       * ARGUMENTS:
       *   - link on vector for -=:
       *       const vec4<type> &V;
       * RETURNS:
       *   (vec4<type> &) link on result of -=.
       */
      vec4<type> & operator-=( const vec4<type> &V )
      {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;
        W -= V.W;

        return *this;
      } /* End of 'operator-=' function */

      /* Changing operator * for vector product on number function.
       * ARGUMENTS:
       *   - link on number for product:
       *       const type &N;
       * RETURNS:
       *   (vec4<type>) result of product.
       */
      vec4<type> operator*( const type &N ) const
      {
        return vec4<type>(X * N, Y * N, Z * N, W * N);
      } /* End of 'operator*' function */

      /* Changing operator / for vector division on number function.
       * ARGUMENTS:
       *   - link on number for division:
       *       const type &N;
       * RETURNS:
       *   (vec4<type>) result of division.
       */
      vec4<type> operator/( const type &N ) const
      {
        return vec4<type>(X / N, Y / N, Z / N, W / N);
      } /* End of 'operator/' function */

      /* Changing operator *= for vector *= number function.
       * ARGUMENTS:
       *   - link on number for *=:
       *       const type &N;
       * RETURNS:
       *   (vec4<type> &) link on result of *=.
       */
      vec4<type> & operator*=( const type &N )
      {
        X *= N;
        Y *= N;
        Z *= N;
        W *= N;

        return *this;
      } /* End of 'operator*=' function */

      /* Changing operator /= for vector /= number function.
       * ARGUMENTS:
       *   - link on number for /=:
       *       const type &N;
       * RETURNS:
       *   (vec4<type> &) link on result of /=.
       */
      vec4<type> & operator/=( const type &N )
      {
        X /= N;
        Y /= N;
        Z /= N;
        W /= N;

        return *this;
      } /* End of 'operator/=' function */

      /* Changing operator * for vector * components of two vectors function.
       * ARGUMENTS:
       *   - link on vector for *:
       *       const vec4<type> &V;
       * RETURNS:
       *   (vec4<type>) link on result of *.
       */
      vec4<type> & operator*( const vec4<type> &V )
      {
        return vec4<type>(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
      } /* End of 'operator*' function */
      
      /* Changing operator / for vector / components of two vectors function.
       * ARGUMENTS:
       *   - link on vector for /:
       *       const vec4<type> &V;
       * RETURNS:
       *   (vec4<type>) link on result of /.
       */
      vec4<type> operator/( const vec4<type> &V )
      {
        return vec4<type>(X / V.X, Y / V.Y, Z / V.Z, W / V.W);
      } /* End of 'operator/' function */


      /* Changing operator *= for vector *= components of two vectors function.
        * ARGUMENTS:
        *   - link on vector for *=:
        *       const vec4<type> &V;
        * RETURNS:
        *   (vec4<type> &) link on result of *=.
        */
       vec4<type> & operator*=( const vec4<type> &V )
       {
         X *= V.X;
         Y *= V.Y;
         Z *= V.Z;
         W *= V.Z;
       
         return *this;
       } /* End of 'operator*=' function */

       /* Changing operator /= for vector /= components of two vectors function.
        * ARGUMENTS:
        *   - link on vector for /=:
        *       const vec4<type> &V;
        * RETURNS:
        *   (vec4<type> &) link on result of /=.
        */
       vec4<type> & operator/=( const vec4<type> &V )
       {
         X /= V.X;
         Y /= V.Y;
         Z /= V.Z;
         W /= V.W;
       
         return *this;
       } /* End of 'operator/=' function */

      /* Changing operator [] to get coordinate.
       * ARGUMENTS:
       *   - link on number of coordinate:
       *      const INT &NumOfCoord;
       * RETURNS:
       *  (type) coordinate.
       */
      type operator[]( const INT &NumOfCoord ) const
      {
        return NumOfCoord == 0 ? X :
               NumOfCoord == 1 ? Y :
               NumOfCoord == 2 ? Z : W;
      } /* End of 'operator[]' function */

      /* Square length of vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) square length of vector.
       */
      type Length2( VOID ) const
      {
        return X * X + Y * Y + Z * Z + W * W;
      } /* End of 'Length2' function */

      /* Normalize of vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4<type> &) link on normalized vector.
       */
      vec4<type> & Normalize( VOID )
      {
        type len;
        
        len = sqrt(Length2());
        X /= len;
        Y /= len;
        Z /= len;
        W /= len;

        return *this;
      } /* End of 'Normalize' function */

      /* Normalizing of vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4<type>) normalized vector.
       */
      vec4<type> Normalizing( VOID ) const
      {
        type len;
        vec<type> r;

        len = sqrt(Length2());
        r.X = X / len;
        r.Y = Y / len;
        r.Z = Z / len;
        r.W = W / len;

        return r;
      } /* End of 'Normalizing' function */

      /* Square distanse to point space function.
       * ARGUMENTS: 
       *   - link on point in space:
       *       const vec4<type> &P;
       * RETURNS:
       *   (type) square distance to point in space.
       */
      type Distance2( const vec4<type> &P ) const
      {
        vec4<type> dist = P - (*this);

        return dist.Length2();
      } /* End of 'Distance' function*/

      /* Filling coordinates by zero function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4<type>) the link to filled vector.
       */
      vec4<type> Zero( VOID )
      {
        X = Y = Z = W = 0;

        return *this;
      } /* End of 'Zero' function*/

      /* Filling coordinates by random numbers function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4<type> &) the link to filled vector.
       */
      vec4<type> & Rnd( VOID )
      {
        X = rand() * 10.0 / RAND_MAX;
        Y = rand() * 6.0 / RAND_MAX;
        Z = rand() * 4.0 / RAND_MAX;
        W = rand() * 9.0 / RAND_MAX;

        return *this;
      } /* End of 'Rnd' function*/
    }; /* End of 'vec4' class */
} /* end of 'mth' namespace */
#endif /* __VEC_H_ */

/* END OF 'VEC.H' FILE */




