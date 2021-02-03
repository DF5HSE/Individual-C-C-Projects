/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SHAPES.CPP
 * PURPOSE     : Ray tracing project
 *               Shapes base classes implementatoin module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 25.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "../rt.h"
#include "shapes.h"

/* Default material class constructor.
 * ARGUMENTS: None.
 */
firt::material::material( VOID )
{
} /* End of 'firt::material::material' function */

/* Default environment class constructor.
 * ARGUMENTS: None.
 */
firt::environment::environment( VOID )
{
} /* End of 'firt::environment::environment' function */

/* Material class constructor.
 * ARGUMENTS:
 *   - coefficients ambience, diffuse, specular, reflaction and transparity:
 *       const vec &Ka, Kd, Ks, KRefl, KTrans;
 *   - Phong coefficient:
 *       const DBL &Kp;
 */
firt::material::material( const vec &Ka, const vec &Kd, const vec &Ks, const vec &KRefl, const vec &KTrans, const DBL &Kp ) :
                          Ka(Ka), Kd(Kd), Ks(Ks), KRefl(KRefl), KTrans(KTrans), Kp(Kp)
{
} /* End of 'firt::material::material' function */

/* Environment class constructor.
 * ARGUMENTS:
 *   - decay and refraction coefficients:
 *       const DBL &Decay, &NRefr;
 */
firt::environment::environment( const DBL &Decay, const DBL &NRefr ) : Decay(Decay), NRefr(NRefr)
{
} /* End of 'firt::environment::environment' function */

/* Intesect ray and object function.
 * ARGUMENTS:
 *   - link on ray for intesect:
 *       const ray &R;
 *   - pointer on intersection:
 *       intr *Intr;
 * RETURNS:
 *   (BOOL) intesect exist - TRUE, else - FALSE.
 */
BOOL firt::shape_list::Intersect( const ray &R, intr *Intr )
{
  DBL t = 65536;
  intr SaveIntr;

  for (auto s : Shapes)
    if (s->Intersect(R, Intr) && Intr->T < t)
    {
      t = Intr->T;
      SaveIntr = *Intr;
    }
  *Intr = SaveIntr;
  return t != 65536 ? TRUE : FALSE;
} /* End of 'firt::shape_list::Intersect' function */

/* Intesection of ray and objectes function.
 * ARGUMENTS:
 *   - ray for intesect:
 *       const ray &R;
 *   - link on vector of intesections:
 *       intr_list *Ilist;
 * RETURNS:
 *   (INT) number of intesections.
 */
INT firt::shape_list::AllIntersect( const ray &R, intr_list &Ilist )
{
  INT n = 0;

  for (auto s : Shapes)
    n += s->AllIntersect(R, Ilist);
  return n;
} /* End of 'firt::shape_list::AllIntersect' function */

/* Getting normal in intersection point function.
 * ARGUMENTS:
 *   - pointer on intersection:
 *       intr *Intr;
 * RETURNS: None.
 */
VOID firt::shape_list::GetNormal( intr *Intr )
{
  Intr->Shp->GetNormal(Intr);
} /* End of 'firt::shape_list::GetNormal' function */

/* Existion of intesection of ray and object function.
 * ARGUMENTS:
 *   - ray for intesect:
 *       const ray &R;
 * RETURNS:
 *   (BOOL) intesection exist - TRUE, else - FALSE.
 */
BOOL firt::shape_list::IsIntersect( const ray &R )
{
  for (auto s : Shapes)
    if (s->IsIntersect(R))
      return TRUE;
  return FALSE;
} /* End of 'firt::shape_list::IsIntersect' function */

/* Is something inside object function.
 * ARGUMENTS:
 *   - point of something:
 *       const vec &P;
 * RETURNS:
 *   (BOOL) TRUE - inside, FALSE - outside.
 */
BOOL firt::shape_list::IsInside( const vec &P )
{
  for (auto s : Shapes)
    if (s->IsInside(P))
      return TRUE;
  return FALSE;
} /* End of 'firt::shape_list::IsInside' function */

/* END OF 'SHAPES.CPP' FILE */
