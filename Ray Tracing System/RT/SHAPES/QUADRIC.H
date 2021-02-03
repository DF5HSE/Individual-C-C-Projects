/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : QUADRIC.H
 * PURPOSE     : Ray tracing project
 *               Quadric class declaration module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 02.09.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __QUADRIC_H_
#define __QUADRIC_H_

#include <vector>
#include "../rt.h"
#include "shapes.h"

/* Project namespace */
namespace firt
{
  /* Forward intersection and shade data class declaration */
  class intr;

  /* Quadric class declaration */
  class quadric : public shape
  {
  public:
    DBL A, B, C, D, E, F, G, H, I, J; // Equation coefficients

    /* Default quadric class constructor.
     * ARGUMENTS: None.
     */
    quadric( VOID );

    /* Quadric class constructor.
     * ARGUMENTS:
     *   - equation coefficients:
     *       const DBL &A, &B, &C, &D, &E, &F, &G, &H, &I, &J;
     *   - material:
     *       const material &M;
     *   - environment:
     *       const environment &Envir;
     */
    quadric( const DBL &A, const DBL &B, const DBL &C, const DBL &D, const DBL &E,
             const DBL &F, const DBL &G, const DBL &H, const DBL &I, const DBL &J, 
             const material &M, const environment &Envir );

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
  } /* End of 'quadric' class*/;
} /* end of 'firt' namespace */

#endif /* __QUADRIC_H_ */

/* END OF 'QUADRIC.H' FILE */
