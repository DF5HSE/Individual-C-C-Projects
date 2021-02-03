/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SPHERE.H
 * PURPOSE     : Ray tracing project
 *               Sphere shape class declaration module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 26.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __SPHERE_H_
#define __SPHERE_H_

#include "../../def.h"
#include "shapes.h"

namespace firt
{
  /* Forward intersection class declaration */
  class intr;
  /* Sphere class declaration */
  class sphere : public shape
  {
  private:
    vec C;     // Sphere center
    DBL R, R2; // Sphere radius and radius in square

  public:
    /* Sphere class constructor.
     * ARGUMENTS:
     *   - link on sphere center position:
     *       const vec &C;
     *   - sphere radius:
     *       const DBL &R;
     *   - material:
     *       const material &Mtl;
     *   - environment:
     *       const environment &Envi;
     */
    sphere( const vec &C, const DBL &R, const material &Mtl, const environment &Envi );

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
  }; /* End of 'sphere' class */
} /* end of 'firt' namespace */
#endif /* __SPHERE_H_ */

/* END OF 'SPHERE.H' FILE */
