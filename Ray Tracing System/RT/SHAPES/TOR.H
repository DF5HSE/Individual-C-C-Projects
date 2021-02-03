/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TOR.H
 * PURPOSE     : Ray tracing project
 *               Tor class declaration module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 31.08.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __TOR_H_
#define __TOR_H_

#include <vector>
#include "../rt.h"
#include "shapes.h"

/* Project namespace */
namespace firt
{
  /* Forward intersection and shade data class declaration */
  class intr;

  /* Tor class declaration */
  class tor : public shape
  {
  public:
    DBL Rad, rad; // Radiuses of tor (R - radius around axis, r - radius of rotated circle)

    /* Default tor class constructor.
     * ARGUMENTS: None.
     */
    tor( VOID );
    
    /* Tor class constructor.
     * ARGUMENTS:
     *   - radius around axis:
     *       const DBL &Rad;
     *   - radius of rotated circle:
     *       const DBL &rad;
     *   - material:
     *       const material &M;
     *   - environment:
     *       const environment &Envir;
     */
    tor( const DBL &Rad, const DBL &rad, const material &M, const environment &Envir );

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
  } /* End of 'tor' class*/;
} /* end of 'firt' namespace */

#endif /* __TOR_H_ */

/* END OF 'TOR.H' FILE */
