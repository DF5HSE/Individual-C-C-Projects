/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : PLANE.H
 * PURPOSE     : Ray tracing project
 *               Plane shape class declaration module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 26.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __PLANE_H_
#define __PLANE_H_

#include "../../def.h"
#include "shapes.h"
#include "../rt.h"

namespace firt
{
  /* Forward intersection class declaration */
  class intr;
  /* Plane class declaration */
  class plane : public shape
  {
  private:
    vec N; // Normal to plane
    DBL D; // Distanse to start coordinate system

  public:
    //std::vector<plane_mod> Mods;
    /* Default plane class constructor.
     * ARGUMENTS: None
     */
    plane( VOID );

    /* Plane class constructor.
     * ARGUMENTS:
     *   - distance to start of coordinate system:
     *       const DBL &D;
     *   - normal to plane:
     *       const vec &N;
     *   - material:
     *       const material &M;
     *   - environment:
     *       const environment &Envir;
     */
    plane( const DBL &D, const vec &N, const material &M, const environment &Envir );

    /* Plane class constructor.
     * ARGUMENTS:
     *   - points for plane;
     *       const vec &A, &B, &C;
     *   - material:
     *       const material &M;
     *   - environment:
     *       const environment &Envir;
     */
    plane( const vec &A, const vec &B, const vec &C, const material &M, const environment &Envir );

    /* Intesect ray and object function.
     * ARGUMENTS:
     *   - link on ray for intesect:
     *       const ray &R;
     *   - pointer on intersection:
     *       intr *Intr;
     * RETURNS:
     *   (BOOL) intesect exist - TRUE, else - FALSE.
     */
    BOOL Intersect( const ray &R, intr *Intr ) override;

    /* Intesection of ray and objectes function.
     * ARGUMENTS:
     *   - ray for intesect:
     *       const ray &R;
     *   - link on vector of intesections:
     *       intr_list *Ilist;
     * RETURNS:
     *   (INT) number of intesections.
     */
    INT AllIntersect( const ray &R, intr_list &Ilist ) override;

    /* Getting normal in intersection point function.
     * ARGUMENTS:
     *   - pointer on intersection:
     *       intr *Intr;
     * RETURNS: None.
     */
    VOID GetNormal( intr *Intr ) override;

    /* Existion of intesection of ray and object function.
     * ARGUMENTS:
     *   - ray for intesect:
     *       const ray &R;
     * RETURNS:
     *   (BOOL) intesection exist - TRUE, else - FALSE.
     */
    BOOL IsIntersect( const ray &R ) override;

    /* Is something inside object function.
     * ARGUMENTS:
     *   - point of something:
     *       const vec &P;
     * RETURNS:
     *   (BOOL) TRUE - inside, FALSE - outside.
     */
    BOOL IsInside( const vec &P ) override;

    /* Apply modifier function.
    * ARGUMENTS:
    *   - pointer on shading data:
    *       shade_data *Shd;
    * RETURNS: None.
    */
    VOID Apply( shade_data *Shd ) override;
  }; /* End of 'plane' class */

  /* Plane mod time declaration */
  class plane_mod : public mod
  {
  public:
    plane_mod( VOID ) : mod()
    {
    }

  }; /* End of 'plane_mode' class */
} /* end of 'firt' namespace */
#endif /* __PLANE_H_ */

/* END OF 'PLANE.H' FILE */

