/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TOR.CPP
 * PURPOSE     : Ray tracing project
 *               Tor class implementation module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 01.09.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "tor.h"

/* Default tor class constructor.
 * ARGUMENTS: None.
 */
firt::tor::tor( VOID )
{
} /* End of 'firt::tor::tor' function */

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
firt::tor::tor( const DBL &Rad, const DBL &rad, const material &M, const environment &Envir ) : Rad(Rad), rad(rad)
{
  Mtl = M;
  Envi = Envir;
} /* End of 'firt::tor::tor' function */

/* Intesect ray and object function.
 * ARGUMENTS:
 *   - link on ray for intesect:
 *       const ray &R;
 *   - pointer on intersection:
 *       intr *Intr;
 * RETURNS:
 *   (BOOL) intesect exist - TRUE, else - FALSE.
 */
BOOL firt::tor::Intersect( const ray &R, intr *Intr )
{
  std::vector<DBL> Sols1, Sols2;
  DBL 
    DirLength2 = R.GetDir().Length2(),
    OrgLength2 = R.GetOrg().Length2(),
    DirDotOrg = R.GetDir() & R.GetOrg(),
    RadSq_radSq = Rad * Rad - rad * rad;

  mth::Equation4<DBL>(DirLength2 * DirLength2,
                      4 * DirLength2 * DirDotOrg,
                      4 * DirDotOrg * DirDotOrg + 2 * OrgLength2 * DirLength2 + 2 * RadSq_radSq * DirLength2 - 4 * Rad * Rad *
                        (pow(R.GetDir()[0], 2) + pow(R.GetDir()[2], 2)),
                      4 * (DirDotOrg * (OrgLength2 + RadSq_radSq) - 2 * Rad * Rad *
                        (R.GetOrg()[0] * R.GetDir()[0] + R.GetOrg()[2] * R.GetDir()[2])),
                      pow(OrgLength2 + RadSq_radSq, 2) - 4 * Rad * Rad * (pow(R.GetOrg()[0], 2) + pow(R.GetOrg()[2], 2)),
                      &Sols1);

  for (auto s : Sols1)
    if (!isnan(s) && s > 0)
      Sols2.push_back(s);

  if (Sols2.size() == 0)
    return FALSE;

  DBL t = 780000;
  for (auto s : Sols2)
    if (s < t)
      t = s;

  Intr->T = t;
  Intr->Shp = this;
  Intr->IsP = TRUE;
  Intr->P = R(t);
  vec PY0(Intr->P[0], 0, Intr->P[2]);
  vec PY0Norm = PY0.Normalizing();
  if ((PY0Norm * (Rad + rad)).Length2() > PY0.Length2() &&
      (PY0Norm * (Rad - rad)).Length2() < PY0.Length2() &&
      (Intr->P - PY0Norm * Rad).Length2() < rad)
    Intr->IsEnter = FALSE;
  else
    Intr->IsEnter = TRUE;

  return TRUE;
} /* End of 'firt::tor::Intersect' function */

/* Intesection of ray and objectes function.
 * ARGUMENTS:
 *   - ray for intesect:
 *       const ray &R;
 *   - link on vector of intesections:
 *       intr_list *Ilist;
 * RETURNS:
 *   (INT) number of intesections.
 */
INT firt::tor::AllIntersect( const ray &R, intr_list &Ilist )
{
  std::vector<DBL> Sols1, Sols2;
  DBL 
    DirLength2 = R.GetDir().Length2(),
    OrgLength2 = R.GetOrg().Length2(),
    DirDotOrg = R.GetDir() & R.GetOrg(),
    RadSq_radSq = Rad * Rad - rad * rad;

  mth::Equation4<DBL>(DirLength2 * DirLength2,
                      4 * DirLength2 * DirDotOrg,
                      4 * DirDotOrg * DirDotOrg + 2 * OrgLength2 * DirLength2 + 2 * RadSq_radSq * DirLength2 - 4 * Rad * Rad *
                        (pow(R.GetDir()[0], 2) + pow(R.GetDir()[2], 2)),
                      4 * (DirDotOrg * (OrgLength2 + RadSq_radSq) - 2 * Rad * Rad *
                        (R.GetOrg()[0] * R.GetDir()[0] + R.GetOrg()[2] * R.GetDir()[2])),
                      pow(OrgLength2 + RadSq_radSq, 2) - 4 * Rad * Rad * (pow(R.GetOrg()[0], 2) + pow(R.GetOrg()[2], 2)),
                      &Sols1);

  for (auto s : Sols1)
    if (!isnan(s) && s > 0)
      Sols2.push_back(s);

  if (Sols2.size() == 0)
    return 0;

  for (auto t : Sols2)
  {
    intr Intr;
    Intr.T = t;
    Intr.Shp = this;
    Intr.IsP = TRUE;
    Intr.P = R(t);
    vec PY0(Intr.P[0], 0, Intr.P[2]);
    vec PY0Norm = PY0.Normalizing();
    DBL Treshold = 0.00000001;
    if ((PY0Norm * (Rad + rad + Treshold)).Length2() > PY0.Length2() &&
        (PY0Norm * (Rad - rad - Treshold)).Length2() < PY0.Length2() &&
        (Intr.P - PY0Norm * Rad).Length2() < rad + Treshold)
      Intr.IsEnter = FALSE;
    else
      Intr.IsEnter = TRUE;

    Ilist.push_back(Intr);
  }

  if (Ilist.size() > 0)
    return Ilist.size();
  else
    return Ilist.size();
} /* End of 'firt::tor::AllIntersect' function */

/* Getting normal in intersection point function.
 * ARGUMENTS:
 *   - pointer on intersection:
 *       intr *Intr;
 * RETURNS: None.
 */
VOID firt::tor::GetNormal( intr *Intr )
{
  vec PY0(Intr->P[0], 0, Intr->P[2]);
  vec PY0Norm = PY0.Normalizing();

  Intr->N = Intr->P - PY0Norm * Rad;
  Intr->N.Normalize();
} /* End of 'firt::tor::GetNormal' function */

/* Existion of intesection of ray and object function.
 * ARGUMENTS:
 *   - ray for intesect:
 *       const ray &R;
 * RETURNS:
 *   (BOOL) intesection exist - TRUE, else - FALSE.
 */
BOOL firt::tor::IsIntersect( const ray &R )
{
  std::vector<DBL> Sols1, Sols2;
  DBL 
    DirLength2 = R.GetDir().Length2(),
    OrgLength2 = R.GetOrg().Length2(),
    DirDotOrg = R.GetDir() & R.GetOrg(),
    RadSq_radSq = Rad * Rad - rad * rad;

  mth::Equation4<DBL>(DirLength2 * DirLength2,
                      4 * DirLength2 * DirDotOrg,
                      2 * DirLength2 * (3 * OrgLength2 + RadSq_radSq),
                      4 * DirDotOrg * (OrgLength2 + RadSq_radSq),
                      OrgLength2 * OrgLength2 + RadSq_radSq * RadSq_radSq + 2 * OrgLength2 * RadSq_radSq,
                      &Sols1);

  for (auto s : Sols1)
    if (!isnan(s) && s > 0)
      Sols2.push_back(s);

  if (!Sols2.size())
    return FALSE;
  else
    return TRUE;
} /* End of 'firt::tor::IsIntersect' function */

/* Is something inside object function.
 * ARGUMENTS:
 *   - point of something:
 *       const vec &P;
 * RETURNS:
 *   (BOOL) TRUE - inside, FALSE - outside.
 */
BOOL firt::tor::IsInside( const vec &P )
{
  vec PY0(P[0], 0, P[2]);
  vec PY0Norm = PY0.Normalizing();
  if ((PY0Norm * (Rad + rad)).Length2() > PY0.Length2() &&
      (PY0Norm * (Rad - rad)).Length2() < PY0.Length2() &&
      (P - PY0Norm * Rad).Length2() < rad)
    return FALSE;
  else
    return TRUE;
} /* End of 'firt::tor::IsInside' function */

/* END OF 'TOR.CPP' FILE */