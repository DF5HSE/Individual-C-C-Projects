/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : PLANE.CPP
 * PURPOSE     : Ray tracing project
 *               Plane shape class implementation module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 02.09.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "plane.h"
#include "../scene.h"

/* Default plane class constructor.
 * ARGUMENTS: None
 */
firt::plane::plane( VOID )
{
} /* End of 'firt::plane::Intersect' function */

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
firt::plane::plane( const DBL &D, const vec &N, const material &M, const environment &Envir ) : D(D), N(N)
{
  Mtl = M;
  Envi = Envir;
  Mods = plane_mod();
} /* End of 'firt::plane::Intersect' function */

/* Plane class constructor.
 * ARGUMENTS:
 *   - points for plane;
 *       const vec &A, &B, &C;
 *   - material:
 *       const material &M;
 *   - environment:
 *       const environment &Envir;
 */
firt::plane::plane( const vec &A, const vec &B, const vec &C, const material &M, const environment &Envir )
{
  N = ((A - B) % (C - B)).Normalizing();
  D = A & N;
  Mtl = M;
  Envi = Envir;
  Mods = plane_mod();
} /* End of 'firt::plane::Intersect' function */

/* Intesect ray and object function.
 * ARGUMENTS:
 *   - link on ray for intesect:
 *       const ray &R;
 *   - pointer on intersection:
 *       intr *Intr;
 * RETURNS:
 *   (BOOL) intesect exist - TRUE, else - FALSE.
 */
BOOL firt::plane::Intersect( const ray &R, intr *Intr )
{
  DBL DirDotN = R.GetDir() & N, t;
  if (!DirDotN)
    return FALSE;
  if ((t = -((R.GetOrg() & N) - D) / DirDotN) < 0)
    return FALSE;

  vec p = R(t);
  if (p[0] > 20 || p[2] < -20)
    return FALSE;

  Intr->T = t;
  Intr->IsEnter = DirDotN > 0 ? FALSE : TRUE;
  Intr->Shp = this;
  return TRUE;
} /* End of 'firt::plane::Intersect' function */

/* Intesection of ray and objectes function.
 * ARGUMENTS:
 *   - ray for intesect:
 *       const ray &R;
 *   - link on vector of intesections:
 *       intr_list *Ilist;
 * RETURNS:
 *   (INT) number of intesections.
 */
INT firt::plane::AllIntersect( const ray &R, intr_list &Ilist )
{
  intr Intr;
  DBL DirDotN = R.GetDir() & N, t;

  if (!DirDotN)
    return 0;
  if ((t = -((R.GetOrg() & N) - D) / DirDotN) < 0)
    return 0;
  Intr.T = t;
  Intr.IsEnter = DirDotN > 0 ? FALSE : TRUE;
  Intr.Shp = this;
  Ilist.push_back(Intr);
  return 1;
} /* End of 'firt::plane::AllIntersect' function */

/* Getting normal in intersection point function.
 * ARGUMENTS:
 *   - pointer on intersection:
 *       intr *Intr;
 * RETURNS: None.
 */
VOID firt::plane::GetNormal( intr *Intr )
{
  Intr->N = N;
} /* End of 'firt::plane::GetNormal' function */

/* Existion of intesection of ray and object function.
 * ARGUMENTS:
 *   - ray for intesect:
 *       const ray &R;
 * RETURNS:
 *   (BOOL) intesection exist - TRUE, else - FALSE.
 */
BOOL firt::plane::IsIntersect( const ray &R )
{ 
  DBL DirDotN = R.GetDir() & N;
  if (!DirDotN)
    return FALSE;
  if (-(((R.GetOrg() & N) - D) / DirDotN) < 0)
    return FALSE;
  return TRUE;
} /* End of 'firt::plane::IsIntersect' function */

/* Is something inside object function.
 * ARGUMENTS:
 *   - point of something:
 *       const vec &P;
 * RETURNS:
 *   (BOOL) TRUE - inside, FALSE - outside.
 */
BOOL firt::plane::IsInside( const vec &P )
{
  return ((P & N) - D) > 0 ? FALSE : TRUE;
} /* End of 'firt::plane::IsInside' function */

/* Apply modifier function.
 * ARGUMENTS:
 *   - pointer on shading data:
 *       shade_data *Shd;
 * RETURNS: None.
 */
VOID firt::plane::Apply( shade_data *Shd )
{
  if ((((INT)abs(floor(Shd->P[0]))) % 2) == (((INT)abs(floor(Shd->P[2]))) % 2))
    Shd->Mtl.Ka = vec(0);
  else
    Shd->Mtl.Ka = vec(1);
} /* End of apply mode */

/* END OF 'PLANE.CPP' FILE */