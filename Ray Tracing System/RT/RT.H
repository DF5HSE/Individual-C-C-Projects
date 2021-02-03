/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : RT.H
 * PURPOSE     : Ray tracing project.
 *               Intersection class declaration module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 26.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __RT_H_
#define __RT_H_

#include "../def.h"

/* Project namespace */
namespace firt
{
  /* Forward shape class declaration */
  class shape;
  /* Declaration intersection class */
  class intr
  {
  public:
    shape *Shp;   // Object pointer
    DBL T;        // Ray parameter
    BOOL IsEnter; // Ray enters into object shape flag
    vec N;        // Normal
    BOOL IsN;     // Normal calculation flag
    vec P;        // Position
    BOOL IsP;     // Ray point calculation flag

    // Addon parametres
    INT I[5];
    DBL D[5];
    vec V[5];

    /* Default intr class constructor.
     * ARGUMENTS: None
     */
    intr( VOID );

    /* Intr class constructor.
     * ARGUMENTS:
     *   - pointer on shape:
     *       shape *Sph;
     *   - t coefficient:
     *       DBL T;
     *   - ray enters into object shape flag:
     *       BOOL IsEnter;
     */
    intr( shape *Shp, DBL T, BOOL IsEnter );

    /* Intr class constructor.
     * ARGUMENTS:
     *   - pointer on shape:
     *       shape *Sph;
     *   - t coefficient:
     *       DBL T;
     *   - ray enters into object shape flag:
     *       BOOL IsEnter;
     *   - link on normal vector:
     *       const vec &Norm;
     */
    intr( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm );

    /* Intr class constructor.
     * ARGUMENTS:
     *   - pointer on shape:
     *       shape *Sph;
     *   - t coefficient:
     *       DBL T;
     *   - ray enters into object shape flag:
     *       BOOL IsEnter;
     *   - link on normal vector:
     *       const vec &Norm;
     *   - link on point of intersection:
     *       const vec &Point;
     */
    intr( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm, const vec &Point );

    /* Set intersection class function.
     * ARGUMENTS:
     *   - pointer on shape:
     *       shape *Sph;
     *   - t coefficient:
     *       DBL T;
     *   - ray enters into object shape flag:
     *       BOOL IsEnter;
     * RETURNS: None.
     */
    VOID Set( shape *Shp, DBL T, BOOL IsEnter );

    /* Set intersection class function.
     * ARGUMENTS:
     *   - pointer on shape:
     *       shape *Sph;
     *   - t coefficient:
     *       DBL T;
     *   - ray enters into object shape flag:
     *       BOOL IsEnter;
     *   - link on normal vector:
     *       const vec &Norm;
     * RETURNS: None.
     */
    VOID Set( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm );

    /* Set intersection class function.
     * ARGUMENTS:
     *   - pointer on shape:
     *       shape *Sph;
     *   - t coefficient:
     *       DBL T;
     *   - ray enters into object shape flag:
     *       BOOL IsEnter;
     *   - link on normal vector:
     *       const vec &Norm;
     *   - link on point of intersection:
     *       const vec &Point;
     * RETURNS: None.
     */
    VOID Set( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm, const vec &Point );
  } /* End of 'intr' class*/;
} /* end of 'firt' namespace */


#endif /* __RT_H_ */

/* END OF 'RT.H' FILE */
