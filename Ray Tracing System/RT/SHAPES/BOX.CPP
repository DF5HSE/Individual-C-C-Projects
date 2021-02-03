/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : BOX.CPP
 * PURPOSE     : Ray tracing project
 *               Box classs implementation module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 31.08.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "box.h"

/* Default box class constructor.
 * ARGUMENTS: None.
 */
firt::box::box( VOID )
{
} /* End of 'firt::box::box' function */

/* Box class constructor.
 * ARGUMENTS:
 *   - references on diagonale points of box:
 *       const vec &B01, &B02;
 *   - material:
 *       const material &M;
 *   - environment:
 *       const environment &Envir;
 */
firt::box::box( const vec &B01, const vec &B02, const material &M, const environment &Envir )
{
  B1 = vec(min(B01[0], B02[0]), min(B01[1], B02[1]), min(B01[2], B02[2]));
  B2 = vec(max(B01[0], B02[0]), max(B01[1], B02[1]), max(B01[2], B02[2]));
  Mtl = M;
  Envi = Envir;
} /* End of 'firt::box::box' function */

/* Intesect ray and object function.
 * ARGUMENTS:
 *   - link on ray for intesect:
 *       const ray &R;
 *   - pointer on intersection:
 *       intr *Intr;
 * RETURNS:
 *   (BOOL) intesect exist - TRUE, else - FALSE.
 */
BOOL firt::box::Intersect( const ray &R, intr *Intr )
{
  DBL tnear = -780000, tfar = 780000, t0 = -780000, t1 = 780000;
  for (INT i = 0; i < 3; i++)
  {
    if (R.GetDir()[i] == 0)
    {
      if (R.GetOrg()[i] < B1[i] || R.GetOrg()[i] > B2[i])
        return FALSE;
    }
    else
    {
      t0 = (B1[i] - R.GetOrg()[i]) / R.GetDir()[i];
      t1 = (B2[i] - R.GetOrg()[i]) / R.GetDir()[i];
      if (t0 > t1)
      {
        DBL tmp = t0;

        t0 = t1;
        t1 = tmp;
      }

      if (t0 > tnear)
        tnear = t0;
      if (t1 < tfar)
        tfar = t1;
      if (tnear > tfar)
        return FALSE;
      if (tfar < 0)
        return FALSE;
    }
  }

  Intr->T = tnear > 0 ? tnear : tfar;
  Intr->Shp = this;
  Intr->IsEnter = tnear > 0 ? TRUE : FALSE;
  return TRUE;
} /* End of 'firt::box::Intersect' function */

/* Intesection of ray and objectes function.
 * ARGUMENTS:
 *   - ray for intesect:
 *       const ray &R;
 *   - link on vector of intesections:
 *       intr_list *Ilist;
 * RETURNS:
 *   (INT) number of intesections.
 */
INT firt::box::AllIntersect( const ray &R, intr_list &Ilist )
{
  DBL tnear = -780000, tfar = 780000, t0, t1;
  for (INT i = 0; i < 3; i++)
  {
    if (R.GetDir()[i] == 0)
    {
      if (R.GetOrg()[i] < B1[i] || R.GetOrg()[i] > B2[i])
        return 0;
    }
    else
    {
      t0 = (B1[i] - R.GetOrg()[i]) / R.GetDir()[i];
      t1 = (B2[i] - R.GetOrg()[i]) / R.GetDir()[i];
      if (t0 > t1)
      {
        DBL tmp = t0;

        t0 = t1;
        t1 = t0;
      }

      if (t0 > tnear)
        tnear = t0;
      if (t1 < tfar)
        tfar = t1;
      if (tnear > tfar)
        return 0;
      if (tfar < 0)
        return 0;
    }
  }

  intr Intr;

  if (tnear > 0)
  {
    Intr.T = tnear;
    Intr.Shp = this;
    Intr.IsEnter = TRUE;
    Ilist.push_back(Intr);

    Intr.T = tfar;
    Intr.Shp = this;
    Intr.IsEnter = FALSE;
    Ilist.push_back(Intr);

    return 2;
  }
  Intr.T = tfar;
  Intr.Shp = this;
  Intr.IsEnter = FALSE;
  Ilist.push_back(Intr);

  return 1;
} /* End of 'firt::box::AllIntersect' function */

/* Getting normal in intersection point function.
 * ARGUMENTS:
 *   - pointer on intersection:
 *       intr *Intr;
 * RETURNS: None.
 */
VOID firt::box::GetNormal( intr *Intr )
{
  DBL Trsh = 0.000001;
  if (Intr->P[0] > B1[0] - Trsh && Intr->P[0] < B1[0] + Trsh)
    Intr->N = vec(-1, 0, 0);
  else if (Intr->P[0] > B2[0] - Trsh && Intr->P[0] < B2[0] + Trsh)
    Intr->N = vec(1, 0, 0);
  else if (Intr->P[1] > B1[1] - Trsh && Intr->P[1] < B1[1] + Trsh)
    Intr->N = vec(0, -1, 0);
  else if (Intr->P[1] > B2[1] - Trsh && Intr->P[1] < B2[1] + Trsh)
    Intr->N = vec(0, 1, 0);
  else if (Intr->P[2] > B1[2] - Trsh && Intr->P[2] < B1[2] + Trsh)
    Intr->N = vec(0, 0, -1);
  else if (Intr->P[2] > B2[2] - Trsh && Intr->P[2] < B2[2] + Trsh)
    Intr->N = vec(0, 0, 1);
  else
    INT a = 0;
} /* End of 'firt::box::GetNormal' function */

/* Existion of intesection of ray and object function.
 * ARGUMENTS:
 *   - ray for intesect:
 *       const ray &R;
 * RETURNS:
 *   (BOOL) intesection exist - TRUE, else - FALSE.
 */
BOOL firt::box::IsIntersect( const ray &R )
{
  DBL tnear = -780000, tfar = 780000, t0, t1;
  for (INT i = 0; i < 3; i++)
  {
    if (R.GetDir()[i] == 0)
    {
      if (R.GetOrg()[i] < B1[i] || R.GetOrg()[i] > B2[i])
        return FALSE;
    }
    else
    {
      t0 = (B1[i] - R.GetOrg()[i]) / R.GetDir()[i];
      t1 = (B2[i] - R.GetOrg()[i]) / R.GetDir()[i];
      if (t0 > t1)
      {
        DBL tmp = t0;

        t0 = t1;
        t1 = t0;
      }

      if (t0 > tnear)
        tnear = t0;
      if (t1 < tfar)
        tfar = t1;
      if (tnear > tfar)
        return FALSE;
      if (tfar < 0)
        return FALSE;
    }
  }

  return TRUE;
} /* End of 'firt::box::IsIntersect' function */

/* Is something inside object function.
 * ARGUMENTS:
 *   - point of something:
 *       const vec &P;
 * RETURNS:
 *   (BOOL) TRUE - inside, FALSE - outside.
 */
BOOL firt::box::IsInside( const vec &P )
{
  if (P[0] > B1[0] && P[0] < B2[0] && P[1] > B1[1] && P[1] < B2[1] && P[2] > B1[2] && P[2] < B2[2])
    return TRUE;
  return FALSE;
} /* End of 'firt::box::IsInside(' function */

/* END OF 'BOX.CPP' FILE */