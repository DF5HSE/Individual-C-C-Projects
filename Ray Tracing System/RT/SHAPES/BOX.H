/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : BOX.H
 * PURPOSE     : Ray tracing project
 *               Box class declaration module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 29.08.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __BOX_H_
#define __BOX_H_

#include <vector>
#include "../rt.h"
#include "shapes.h"

/* Project namespace */
namespace firt
{
  /* Forward intersection and shade data class declaration */
  class intr;

  /* Box class declaration */
  class box : public shape
  {
  public:
    vec B1, B2; // Diagonal points of box (axial aligned bound box)

    /* Default box class constructor.
     * ARGUMENTS: None.
     */
    box( VOID );

    /* Box class constructor.
     * ARGUMENTS:
     *   - references on diagonale points of box:
     *       const vec &B01, &B02;
     *   - material:
     *       const material &M;
     *   - environment:
     *       const environment &Envir;
     */
    box( const vec &B01, const vec &B02, const material &M, const environment &Envir );

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
  } /* End of 'box' class*/;
} /* end of 'firt' namespace */

#endif /* __BOX_H_ */

/* END OF 'BOX.H' FILE */
