/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME   : CAMERA.H
 * PURPOSE     : 3D math support.
 *               Camera module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 23.08.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "mthdef.h"

 /* Math support namespace */
namespace mth
{
  /* 3D space  class declaration */
  template<class type>
    class camera
    {
    private:
      vec<type> Loc, Dir, Up, Right, At;         // View coordinate system vectors
      matr<type> View, Proj, VP;             // View coordinate system, projection coordinate system and them production matrix
      type ProjSize, ProjDist, ProjFarClip;  // Project plane fit square, near, far
      INT FrameW, FrameH;                    // Frame size

    public:
      /* Camera class constructor.
       * ARGUMENTS:
       *   - view coordinate system vectors(location, at, up):
       *       const vec<type> &Loc, &At, &Up1;
       *   - project plane fit square, near, far;
       *       const type ProjSize, ProjDist, ProjFarClip;
       *   - frame size:
       *       const INT FrameW, FrameH;
       */
      camera( const vec<type> &Loc = vec<type>(3, 0, 4), const vec<type> &At = vec<type>(0, 0, 0), const vec<type> &Up1 = vec<type>(0, 1, 0),
              const type ProjSize = 0.1, const type ProjDist = 0.1, const type ProjFarClip = 1000, const INT FrameW = 1009, const INT FrameH = 488 ) :
        Loc(Loc), At(At), FrameW(FrameW), FrameH(FrameH), ProjSize(ProjSize), ProjDist(ProjDist), ProjFarClip(ProjFarClip)
      {
        Dir = (At - Loc).Normalizing();
        Right = (Dir % Up1).Normalizing();
        Up = Right % Dir;
      } /* end of 'camera' function */

      /* Set projection function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID SetProj( VOID )
      {
        type ratio_x, ratio_y;

        ratio_x = ratio_y = ProjSize / 2;
        if (FrameW > FrameH)
          ratio_x *= type(FrameW) / FrameH;
        else
          ratio_y *= type(FrameH) / FrameW;
        Proj = matr<type>::Frustum(-ratio_x, ratio_x, -ratio_y, ratio_y, ProjDist, ProjFarClip);
        VP = View * Proj;
      } /* End of 'SetProj' function */

      /* Set camera function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID SetCam( VOID )
      {
        View = matr<type>::View(Loc, Dir, Up, Right);
      } /* End of 'SetCam' function*/

      /* Set view matrix.
       * ARGUMENTS:
       *   - view coordinate system vectors(location, at, up):
       *       const vec<type> &Loc1, &At1, &Up1;
       * RETURNS: None.
       */
      VOID SetView( const vec<type> &Loc1, const vec<type> &At1, const vec<type> &Up1 )
      {
        Loc = Loc1;
        At = At1;
        Dir = (At - Loc).Normalizing();
        Right = (Dir % Up1).Normalizing();
        Up = Right % Dir;

        SetCam();
        VP = View * Proj;
      } /* End of 'SetView' function */

      /* Set view matrix.
       * ARGUMENTS:
       *   - new view matrix:
       *       const matr<type> &M;
       * RETURNS: None.
       */
      VOID SetView( const matr<type> &M )
      {
        View = M;
        VP = View * Proj;
      } /* End of 'SetView' function */

      /* Resize projection function.
       * ARGUMENTS:
       *   - new frame size:
       *       const INT W, H;
       * RETURNS: None.
       */
      VOID Resize( const INT W, const INT H )
      {
        FrameW = W;
        FrameH = H;
        SetProj();
      } /* End of 'Resize' function */

      /* Get view matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr<type>) view matrix.
       */
      matr<type> GetView( VOID )
      {
        return View;
      } /* End of 'GetView' function */
      
      /* Get projection matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr<type>) projection matrix.
       */
      matr<type> GetProj( VOID )
      {
        return Proj;
      } /* End of 'GetProj' function */

      /* Get VP matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr<type>) VP matrix.
       */
      matr<type> GetVP( VOID )
      {
        return VP;
      } /* End of 'GetVP' function */

      /* Get direction vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   vec<type> direction vector.
       */
      vec<type> GetDir( VOID )
      {
        return Dir;
      } /* End of 'GetDir' function */

      /* Get right vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   vec<type> right vector.
       */
      vec<type> GetRight( VOID )
      {
        return Right;
      } /* End of 'GetRight' function */

      /* Get up vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   vec<type> up vector.
       */
      vec<type> GetUp( VOID )
      {
        return Up;
      } /* End of 'GetUp' function */

      /* Get at point function.
       * ARGUMENTS: None.
       * RETURNS:
       *   vec<type> at point.
       */
      vec<type> GetAt( VOID )
      {
        return At;
      } /* End of 'GetAt' function */

      /* Get location point function.
       * ARGUMENTS: None.
       * RETURNS:
       *   vec<type> location point.
       */
      vec<type> GetLoc( VOID )
      {
        return Loc;
      } /* End of 'GetLoc' function */


      /* Camera move function.
       * ARGUMENTS:
       *   - link on move vector:
       *       const vec<type> &dV;
       * RETURNS: None.
       */
      VOID Move( const vec<type> &dV )
      {
        if (dV.Length2() == 0)
          return;
        Loc += dV;
        At += dV;
        Dir = At - Loc;
        Dir.Normalize();
        SetCam();
        VP = View * Proj;
      } /* End of 'Move' function */

      /* Camera rotate around right vector function.
       * ARGUMENTS:
       *   - link on rotate angle in degrees:
       *       const type &AngleInDegrees;
       * RETURNS:None.
       */
      VOID RotateAroundRight( const type &AngleInDegrees )
      {
        if (AngleInDegrees == 0)
          return;
        At -= Loc;
        matr<type> transform = matr<type>::Rotate(Right, AngleInDegrees);
        At = transform.PointTransform(At);
        At += Loc;
        Dir = (At - Loc);
        //Dir = transform.VectorTransform(Dir);
        Dir.Normalize();
        Up = Right % Dir;
        SetCam();
        VP = View * Proj;
      } /* End of 'RotateAroundRight' function */

      /* Camera rotate around Y function.
       * ARGUMENTS:
       *   - link on rotate angle in degrees:
       *       const type &AngleInDegrees;
       * RETURNS:None.
       */
      VOID RotateAroundY( const type &AngleInDegrees )
      {
        if (AngleInDegrees == 0)
          return;
        At -= Loc;
        vec<type> Y(0, 1, 0);
        matr<type> transform = matr<type>::Rotate(Y, AngleInDegrees);
        At = transform.PointTransform(At);
        At += Loc;
        Dir = (At - Loc);
        //Dir = transform.VectorTransform(Dir);
        Dir.Normalize();
        Up = Right % Dir;
        SetCam();
        VP = View * Proj;
      } /* End of 'RotateAroundY' function */

      /* Camera rotate around right vector function.
       * ARGUMENTS:
       *   - link on rotate angle in degrees:
       *       const type &AngleInDegrees;
       * RETURNS: None.
       */
      VOID RotateAroundUp( const type &AngleInDegrees )
      {
        if (AngleInDegrees == 0)
          return;
        At -= Loc;
        matr<type> transform = matr<type>::Rotate(Up, AngleInDegrees);
        At = transform.PointTransform(At);
        At += Loc;
        Dir = (At - Loc);
        //Dir = transform.VectorTransform(Dir);
        Dir.Normalize();
        Right = Dir % Up;
        Right.Normalize();
        SetCam();
        VP = View * Proj;
      } /* End of 'RotateAroundUp' function */
    }; /* End of 'camera' class */
}; /* end of 'mth' namespace */

#endif /* __CAMERA_H_ */

/* END OF 'CAMERA.H' FILE */




