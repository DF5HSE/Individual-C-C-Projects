/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : QUADRIC.CPP
 * PURPOSE     : Ray tracing project
 *               Quadric class iplementation module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 02.09.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "quadric.h"

/* Default quadric class constructor.
 * ARGUMENTS: None.
 */
firt::quadric::quadric( VOID )
{
} /* End of 'firt::quadric::quadric' function */

/* Quadric class constructor.
 * ARGUMENTS:
 *   - equation coefficients:
 *       const DBL &A, &B, &C, &D, &E, &F, &G, &H, &I, &J;
 *   - material:
 *       const material &M;
 *   - environment:
 *       const environment &Envir;
 */
firt::quadric::quadric( const DBL &A, const DBL &B, const DBL &C, const DBL &D, const DBL &E,
                        const DBL &F, const DBL &G, const DBL &H, const DBL &I, const DBL &J,
                        const material &M, const environment &Envir )
                        : A(A), B(B), C(C), D(D), E(E),
                          F(F), G(G), H(H), I(I), J(J)
{
  Mtl = M;
  Envi = Envir;
} /* End of 'firt::quadric::quadric' function */

/* Intesect ray and object function.
 * ARGUMENTS:
 *   - link on ray for intesect:
 *       const ray &R;
 *   - pointer on intersection:
 *       intr *Intr;
 * RETURNS:
 *   (BOOL) intesect exist - TRUE, else - FALSE.
 */
BOOL firt::quadric::Intersect( const ray &R, intr *Intr )
{
  vec Dir = R.GetDir(), O = R.GetOrg();
  DBL
    a = A * Dir[0] * Dir[0] + 2 * B * Dir[0] * Dir[1] + 2 * C * Dir[0] * Dir[2] + E * Dir[1] * Dir[1] + 2 * F * Dir[1] * Dir[2] + H * Dir[2] * Dir[2],
    b = 2 *(A * O[0] * Dir[0] + B * (O[0] * Dir[1] + Dir[0] * O[1]) + C * (O[0] * Dir[2] + Dir[0] * O[2]) +
        D * Dir[0] + E * O[1] * Dir[1] + F * (O[1] * Dir[2] + Dir[1] * O[2]) + G * Dir[1] + H * O[2] * Dir[2] + I * Dir[2]),
    c = A * O[0] * O[0] + 2 * B * O[0] * O[1] + 2 * C * O[0] * O[2] + 2 * D * O[0] +
        E * O[1] * O[1] + 2 * F * O[1] * O[2] + 2 * G * O[1] + H * O[2] * O[2] + 2 * I * O[2] + J;

  DBL t0 = (-b + sqrt(b * b - 4 * a * c)) / 2 / a, t1 = (-b - sqrt(b * b - 4 * a * c)) / 2 / a;

  if (isnan(t0) || t0 < 0)
    if (isnan(t1) || t1 < 0)
      return FALSE;
    else
    {
      Intr->T = t1;
      Intr->Shp = this;
      Intr->IsEnter = FALSE;
      return TRUE;
    }
  else if (isnan(t1) || t1 < 0)
  {
    Intr->T = t0;
    Intr->Shp = this;
    Intr->IsEnter = FALSE;
    return TRUE;
  }
  else if (t0 < t1)
  {
    Intr->T = t0;
    Intr->Shp = this;
    Intr->IsEnter = TRUE;
    return TRUE;
  }
  else
  {
    Intr->T = t1;
    Intr->Shp = this;
    Intr->IsEnter = TRUE;
    return TRUE;
  }
} /* End of 'firt::quadric::Intersect' function */

/* Intesection of ray and objectes function.
 * ARGUMENTS:
 *   - ray for intesect:
 *       const ray &R;
 *   - link on vector of intesections:
 *       intr_list *Ilist;
 * RETURNS:
 *   (INT) number of intesections.
 */
INT firt::quadric::AllIntersect( const ray &R, intr_list &Ilist )
{
    vec Dir = R.GetDir(), O = R.GetOrg();
  DBL
    a = A * Dir[0] * Dir[0] + 2 * B * Dir[0] * Dir[1] + 2 * C * Dir[0] * Dir[2] + E * Dir[1] * Dir[1] + 2 * F * Dir[1] * Dir[2] + H * Dir[2] * Dir[2],
    b = 2 *(A * O[0] * Dir[0] + B * (O[0] * Dir[1] + Dir[0] * O[1]) + C * (O[0] * Dir[2] + Dir[0] * O[2]) +
        D * Dir[0] + E * O[1] * Dir[1] + F * (O[2] * Dir[2] + Dir[1] * O[2]) + G * Dir[1] + H * O[2] * Dir[2] + I * Dir[2]),
    c = A * O[0] * O[0] + 2 * B * O[0] * O[2] + 2 * C * O[0] * O[2] + 2 * D * O[0] +
        E * O[1] * O[1] + 2 * F * O[1] * O[2] + 2 * G * O[1] + H * O[2] *O[2] + 2 * I * O[2] + J;

  DBL t0 = (-b + sqrt(b * b - 4 * a * c)) / 2 / a, t1 = (-b - sqrt(b * b - 4 * a * c)) / 2 / a;

  intr Intr;
  if (isnan(t0) || t0 < 0)
    if (isnan(t1) || t1 < 0)
      return 0;
    else
    {
      Intr.T = t1;
      Intr.Shp = this;
      Intr.IsEnter = FALSE;
      Ilist.push_back(Intr);

      return 1;
    }
  else if (isnan(t1) || t1 < 0)
  {
    Intr.T = t0;
    Intr.Shp = this;
    Intr.IsEnter = FALSE;
    Ilist.push_back(Intr);

    return 1;
  }
  else if (t0 < t1)
  {
    Intr.T = t0;
    Intr.Shp = this;
    Intr.IsEnter = TRUE;
    Ilist.push_back(Intr);

    Intr.T = t1;
    Intr.Shp = this;
    Intr.IsEnter = FALSE;
    Ilist.push_back(Intr);

    return 2;
  }
  else
  {
    Intr.T = t1;
    Intr.Shp = this;
    Intr.IsEnter = TRUE;
    Ilist.push_back(Intr);

    Intr.T = t0;
    Intr.Shp = this;
    Intr.IsEnter = FALSE;
    Ilist.push_back(Intr);

    return 2;
  }
} /* End of 'firt::quadric::AllIntersect' function */

/* Getting normal in intersection point function.
 * ARGUMENTS:
 *   - pointer on intersection:
 *       intr *Intr;
 * RETURNS: None.
 */
VOID firt::quadric::GetNormal( intr *Intr )
{
  // f = A * x * x + 2 * B * x * y + 2 * C * x * z + 2 * D * x + E * y * y + 2 * F * y * z + 2 * G * y + H * z * z  + 2 * I * z + J
  DBL
    x = Intr->P[0], y = Intr->P[1], z = Intr->P[2],
    fx = A * 2 * x + 2 * B * y + 2 * C * z + 2 * D,
    fy = 2 * B * x + E * 2 * y + 2 * F * z + 2 * G,
    fz = 2 * C * x + 2 * F * y + H * 2 * z  + 2 * I;

  Intr->N = vec(fx, fy, fz);
  Intr->N.Normalize();
} /* End of 'firt::quadric::GetNormal' function */

/* Existion of intesection of ray and object function.
 * ARGUMENTS:
 *   - ray for intesect:
 *       const ray &R;
 * RETURNS:
 *   (BOOL) intesection exist - TRUE, else - FALSE.
 */
BOOL firt::quadric::IsIntersect( const ray &R )
{
  vec Dir = R.GetDir(), O = R.GetOrg();
  DBL
    a = A * Dir[0] * Dir[0] + 2 * B * Dir[0] * Dir[1] + 2 * C * Dir[0] * Dir[2] + E * Dir[1] * Dir[1] + 2 * F * Dir[1] * Dir[2] + H * Dir[2] * Dir[2],
    b = 2 *(A * O[0] * Dir[0] + B * (O[0] * Dir[1] + Dir[0] * O[1]) + C * (O[0] * Dir[2] + Dir[0] * O[2]) +
        D * Dir[0] + E * O[1] * Dir[1] + F * (O[2] * Dir[2] + Dir[1] * O[2]) + G * Dir[1] + H * O[2] * Dir[2] + I * Dir[2]),
    c = A * O[0] * O[0] + 2 * B * O[0] * O[2] + 2 * C * O[0] * O[2] + 2 * D * O[0] +
        E * O[1] * O[1] + 2 * F * O[1] * O[2] + 2 * G * O[1] + H * O[2] *O[2] + 2 * I * O[2] + J;

  DBL t0 = (-b + sqrt(b * b - 4 * a * c)) / 2 / a, t1 = (-b - sqrt(b * b - 4 * a * c)) / 2 / a;

  if (isnan(t0) || t0 < 0)
    if (isnan(t1) || t1 < 0)
      return FALSE;
    else
      return TRUE;
  return TRUE;
} /* End of 'firt::quadric::IsIntersect' function */

/* Is something inside object function.
 * ARGUMENTS:
 *   - point of something:
 *       const vec &P;
 * RETURNS:
 *   (BOOL) TRUE - inside, FALSE - outside.
 */
BOOL firt::quadric::IsInside( const vec &P )
{
  DBL x = P[0], y = P[1], z = P[2];
  DBL f = A * x * x + 2 * B * x * y + 2 * C * x * z + 2 * D * x + E * y * y + 2 * F * y * z + 2 * G * y + H * z * z  + 2 * I * z + J;

  if (F < 0)
    return TRUE;
  return FALSE;
} /* End of 'firt::quadric::IsInside' function */

/* END OF 'QUADRIC.CPP' FILE */