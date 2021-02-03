/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SCENE.CPP
 * PURPOSE     : Ray tracing project
 *               Scene class implementation module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 29.08.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "scene.h"

/* Default scene class constructor.
 * ARGUMENTS: None.
 */
firt::scene::scene( VOID )
{
} /* End of 'firt::scene::scene' function */

/* Render scene function.
 * ARGUMENTS:
 *   - link on camera:
 *       camera &Cam;
 *   - pointer on image for render:
 *       image *Img;
 *   - part of rendring image:
 *       INT PartOfImg;
 *   - number of parts of image:
 *       INT NumOfParts;
 * RETURNS: None.
 */
VOID firt::scene::Render( camera &Cam, image *Img, INT PartOfImg, INT NumOfParts )
{
  vec Weight = vec(1);

  Cam.Resize(Img->GetW(), Img->GetH());
  for (INT ys = 0; ys < Img->GetH(); ys++)
    for (INT xs = Img->GetW() * PartOfImg / NumOfParts; xs < Img->GetW() * (PartOfImg + 1) / NumOfParts; xs++)
    {
      INT a = 1;
      ray R = Cam.ToRay(xs, ys);
      if (xs > 712 && ys > 360)
        a = 0;
      vec Color = Trace(R, AirEnvi, Weight);
      Img->PutPixel(xs, ys, Img->vecRGBtoDWORD(Color));
    }
} /* End of 'firt::scene::Render' function */

/* Tracing ray function.
 * ARGUMENTS:
 *   - ray for tracing:
 *       const ray &R;
 *   - environment:
 *       const environment &Envi;
 *   - weight:
 *       const vec &Weight;
 * RETURNS:
 *   (vec) color.
 */
vec firt::scene::Trace( const ray &R, const environment &Envi, const vec &Weight )
{
  vec Color(Background);
  intr Intr;

  if (++CurrentLevel <= MaxLevel)
    if (SList.Intersect(R, &Intr))
    {
      if (!Intr.IsP)
        Intr.P = R(Intr.T);
      if (!Intr.IsN)
        SList.GetNormal(&Intr);
      // fog is here
      Color = Shade(R.GetDir(), &Intr, Envi, Weight) * exp(-Envi.Decay * Intr.T);
      if (Color[0] == Intr.Shp->Mtl.Ka[0] && Color[1] == Intr.Shp->Mtl.Ka[1] && Color[2] == Intr.Shp->Mtl.Ka[2])
        INT a = 0;
      if (Color[0] < 0.40 && Color[0] > 0.22)
        INT a = 0;
    }
  CurrentLevel--;
  return Color;
} /* End of 'firt::scene::Trace' function */

/* Shade_data class constructor.
 * ARGUMENTS:
 *   - pointer on intersection:
 *       intr *Intr;
 */
firt::shade_data::shade_data( intr *Intr )
{
  N = Intr->N;
  IsN = Intr->IsN;
  IsEnter = Intr->IsEnter;
  P = Intr->P;
  Shp = Intr->Shp;
  T = Intr->T;
  Shp = Intr->Shp;
} /* End of 'firt::shade_data::shade_data' function */

/* Shade point function.
 * ARGUMENTS:
 *   - link on direction of ray vector:
 *       const vec &V;
 *   - pointer on intersection:
 *       intr *Intr;
 *   - around environment:
 *       const environment &Envi;
 *   - weight:
 *       const vec &Weight;
 * RETURNS:
 *   (vec) color.
 */
vec firt::scene::Shade( const vec &V, intr *Intr, const environment &Envi, const vec &Weight )
{
  shade_data Shd(Intr);
  vec ResColor(0);

  // normal faceforward
  DBL vn = Shd.N & V;
  if (vn > 0)
    vn = - vn, Shd.N = - Shd.N, Shd.IsEnter = !Shd.IsEnter;

  // setup material
  Shd.Mtl = Intr->Shp->Mtl;
  Shd.Envi = Intr->Shp->Envi;

  Intr->Shp->Apply(&Shd);

  // ambient scene illumination
  ResColor += Ambient * Shd.Mtl.Ka;

  // light sources
  vec R = V - Shd.N * (2 * vn);
  for (auto Lig : LList)
  {
    // obtain attenuation data
    light_attenuation Att;
    if (Lig->GetData(Shd, &Att))
    {
      // determine shadow
      intr_list il;
      if (SList.AllIntersect(ray(Shd.P + Att.L * Thresold, Att.L), il) > 0)
        for (auto &i : il)
          if (i.T < Att.Distance)
              Att.Color *= i.Shp->Mtl.KTrans;
      // attenuate light distance
      Att.Color *= min(1.0 / (Att.Cc + Att.Cl * Att.Distance + Att.Cq * Att.Distance2), 1.0);

      if (Att.Color < ColorThresold)
        continue;

      // diffuse
      DBL nl = Shd.N & Att.L;

      if (nl > Thresold)
      {
        ResColor += Shd.Mtl.Kd * Att.Color * nl;

        // specular
        DBL rl = R & Att.L;
        if (rl > Thresold)
          ResColor += Shd.Mtl.Ks * Att.Color * pow(rl, Shd.Mtl.Kp);
      }
    }
  }

  // reflected ray
  vec wr = Weight * Shd.Mtl.KRefl;
  if (wr > ColorThresold)
    ResColor += Trace(ray(Shd.P + R * Thresold, R), Envi, wr) * Shd.Mtl.KRefl;

  // refracted ray
  vec wt = Weight * Shd.Mtl.KTrans;
  if (wt > ColorThresold)
  {
    DBL Eta = Shd.IsEnter ? Shd.Envi.NRefr / Envi.NRefr : AirEnvi.NRefr / Envi.NRefr;
    DBL coef = 1 - (1 - vn * vn) * Eta * Eta;

    if (coef > Thresold)
    {
      vec T = (V - Shd.N * vn) * Eta - Shd.N * sqrt(coef);
      ResColor += Trace(ray(Shd.P + T * Thresold, T), Shd.IsEnter ? Shd.Envi : AirEnvi, wt) * Shd.Mtl.KTrans;
    }
  }
  return vec(min(ResColor[0], 1), min(ResColor[1], 1), min(ResColor[2], 1));
} /* Enf of 'firt::scene::Shade' function */

/* Changing operator << for adding shape to scene.
* ARGUMENTS:
*   - pointer on shape:
*       shape *Shp;
* RETURNS:
*   (scene &) link on scene class;
*/
firt::scene & firt::scene::operator<<( shape *Shp )
{
  SList.Shapes.push_back(Shp);
  return *this;
} /* End of 'firt::scene::operator<<' function */

/* Changing operator << for adding light to scene.
 * ARGUMENTS:
 *   - pointer on light:
 *       light *Light;
 * RETURNS:
 *   (scene &) link on scene class;
 */
firt::scene & firt::scene::operator<<( light *Light )
{
  LList.push_back(Light);
  return *this;
}

/* END OF 'FILE' FILE */
