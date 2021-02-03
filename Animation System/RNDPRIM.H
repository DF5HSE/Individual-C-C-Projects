/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME    : RNDPRIM.H
 * PURPOSE      : Render system.
 *                Primitive class declaration module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 23.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __RNDPRIM_H_
#define __RNDPRIM_H_

#include <vector>
#include "def.h"
#include "material.h"

/* Animation project namespace */
namespace figl
{
  /* Primitive class declaration */
  class prim
  {
  public:
    /* Vertex type declaration */
    struct VERTEX
    {
      mth::vec<FLT> P;   // Position
      mth::vec2<FLT> T;  // Texture coordinates
      mth::vec<FLT> N;   // Normal
      mth::vec4<FLT> C;  // Color

      /* Vertex structure default constructor.
       * ARGUMENTS: None.
       */
      VERTEX( VOID )
      {
      } /* End of 'VERTEX' function */

      /* Vertex structure constructor
       * ARGUMENTS:
       *   - new position:
       *       const mth::vec<FLT> &NewP;
       *   - new texture coordinates:
       *       const mth::vec2<FLT> &NewT;
       *   - new normal:
       *       const mth::vec<FLT> &NewN;
       *   - new color:
       *       const mth::vec4<FLT> &NewC;
       */
      VERTEX(const mth::vec<FLT> &NewP, const mth::vec2<FLT> &NewT, const mth::vec<FLT> &NewN, const mth::vec4<FLT> &NewC) :
        P(NewP), T(NewT), N(NewN), C(NewC)
      {
      } /* End of 'VERTEX' function*/
    }; /* End of 'VERTEX' structure */

    /* Primitiv type enum */
    enum prim_type
    {
      POINT, MESH, STRIP, LINESTRIP, LINE
    } Type;

    UINT VA, VBuf, IBuf;             // Vertex array and buffer, index buffer
    INT VertexCounter, IndexCounter; // Vertexes and indexes counter
    std::vector<vec> Vertexes;       // Vertex vector
    mth::matr<FLT> Transform;        // Transformation matrix
    vec MinBB, MaxBB;                // Bound box points
    material *Mtl;                   // Primitive material

    /* Default primitve class constructor.
     * ARGUMENTS: None.
     */
    prim( VOID );

   /* Primitive class constructor.
    * ARGUMENTS:
    *   - type of primitive:
    *       const prim_type NewType;
    *   - link on vertex vector:
    *       std::vector<VERTEX> &V;
    *   - link on indexes vector:
    *       std::vector<INT> &I;
    */
   prim( const prim_type NewType, const std::vector<VERTEX> &V, const std::vector<INT> &I );

    /* Primitive class destructor.
     * ARGUMENTS: None.
     */
    ~prim( VOID );
  }; /* End of 'prim' class */
} /* end of 'figl' namespace */

#endif /* __RNDPRIM_H_ */

/* END OF 'RNDPRIM.H' FILE */
