/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SPHERE.CPP
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

#include "sphere.h"
#include "../rt.h"

/* Sphere class constructor.
 * ARGUMENTS:
 *   - link on sphere center position:
 *       const vec &C;
 *   - sphere radius:
 *       const DBL &R;
 *   - material:
 *       const material &M;
 *   - environment:
 *       const environment &Envir;
 */
firt::sphere::sphere( const vec &C, const DBL &R, const material &M, const environment &Envir ) : C(C), R(R), R2(R * R)
{
  Envi = Envir;
  Mtl = M;
} /* End of 'firt::firt::sphere' function */

/* Intesect ray and object function.
 * ARGUMENTS:
 *   - link on ray for intesect:
 *       const ray &R;
 *   - pointer on intersection:
 *       intr *Intr;
 * RETURNS:
 *   (BOOL) intesect exist - TRUE, else - FALSE.
 */
BOOL firt::sphere::Intersect( const ray &R, intr *Intr )
{
  vec OC = C - R.GetOrg();
  DBL
    OC2 = OC & OC,
    OK = OC & R.GetDir(),
    OK2 = OK * OK,
    h2 = R2 - (OC2 - OK2);

  // Check ray starts inside sphere
  if (OC2 < R2)
  {
    Intr->T = OK + sqrt(h2);
    Intr->IsEnter = FALSE;
    Intr->Shp = this;
    return TRUE;
  }
  // Ray starts behind of sphere
  if (OK < 0)
    return FALSE;
  // Ray goes near sphere
  if (h2 < 0)
    return FALSE;

  Intr->T = OK - sqrt(h2);
  Intr->IsEnter = TRUE;
  Intr->Shp = this;
  return TRUE;
} /* End of 'firt::sphere::Intersect' function */

/* Intesection of ray and objectes function.
 * ARGUMENTS:
 *   - ray for intesect:
 *       const ray &R;
 *   - link on vector of intesections:
 *       intr_list *Ilist;
 * RETURNS:
 *   (INT) number of intesections.
 */
INT firt::sphere::AllIntersect( const ray &R, intr_list &Ilist )
{
  intr Intr;
  vec OC = C - R.GetOrg();
  DBL
    OC2 = OC & OC,
    OK = OC & R.GetDir(),
    OK2 = OK * OK,
    h2 = R2 - (OC2 - OK2);

  // Check ray starts inside sphere
  if (OC2 < R2)
  {
    Intr.T = OK + sqrt(h2);
    Intr.IsEnter = FALSE;
    Intr.Shp = this;
    Ilist.push_back(Intr);
    return 1;
  }
  // Ray starts behind of sphere
  if (OK < 0)
    return 0;
  // Ray goes near sphere
  if (h2 < 0)
    return 0;

  Intr.T = OK + sqrt(h2);
  Intr.IsEnter = FALSE;
  Intr.Shp = this;
  Ilist.push_back(Intr);
  Intr.T = OK - sqrt(h2);
  Intr.IsEnter = TRUE;
  Intr.Shp = this;
  Ilist.push_back(Intr);
  return 2;
} /* End of 'firt::sphere::AllIntersect' function*/

/* Getting normal in intersection point function.
 * ARGUMENTS:
 *   - pointer on intersection:
 *       intr *Intr;
 * RETURNS: None.
 */
VOID firt::sphere::GetNormal( intr *Intr )
{
  Intr->N = (Intr->P - C).Normalizing();
} /* End of 'firt::sphere::GetNormal' function */

/* Existion of intesection of ray and object function.
 * ARGUMENTS:
 *   - ray for intesect:
 *       const ray &R;
 * RETURNS:
 *   (BOOL) intesection exist - TRUE, else - FALSE.
 */
BOOL firt::sphere::IsIntersect( const ray &R )
{
  vec OC = C - R.GetOrg();
  DBL
    OC2 = OC & OC;

  // Chech ray starts inside sphere
  if (OC2 < R2)
    return TRUE;
  DBL
    OK = OC & R.GetDir();
  // Ray starts behind of sphere
  if (OK < 0)
    return FALSE;
  if ((R2 - (OC2 - OK * OK)) < 0)
    return FALSE;
  return TRUE;
} /* End of 'firt::sphere::IsIntersect' function */

/* Is something inside object function.
  * ARGUMENTS:
  *   - point of something:
  *       const vec &P;
  * RETURNS:
  *   (BOOL) TRUE - inside, FALSE - outside.
  */
BOOL firt::sphere::IsInside( const vec &P )
{
  // Chech ray starts inside sphere
  if (((P - C) & (P - C)) < R2)
    return TRUE;
  return FALSE;
} /* End of 'firt::sphere::IsInside' function */

/* END OF 'SPHERE.CPP' FILE*/