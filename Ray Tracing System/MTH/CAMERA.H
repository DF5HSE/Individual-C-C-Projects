/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME   : CAMERA.H
 * PURPOSE     : Math support.
 *               Camera module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 25.07.2018.
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
      vec<type> Loc, Dir, Up, Right, At; // View coordinate system vectors
      vec<type> A1, B1, B2, C1, C2, X1;   // Vectors for forward counting
      type ProjSize, ProjDist;           // Project plane fit square, near, far
      INT FrameW, FrameH;                // Frame size
      DBL Wp, Hp;                        // Wight and hight of projection

    public:
      /* Camera class constructor.
       * ARGUMENTS:
       *   - view coordinate system vectors(location, at, up):
       *       const vec<type> &Loc, &At, &Up1;
       *   - project plane fit square, near, far;
       *       const type ProjSize, ProjDist;
       *   - frame size:
       *       const INT FrameW, FrameH;
       */
      camera( const vec<type> &Loc = vec<type>(-10, 0, 0), const vec<type> &At = vec<type>(0, 0, 0), const vec<type> &Up1 = vec<type>(0, 1, 0),
              const type ProjSize = 0.1, const type ProjDist = 0.05, const INT FrameW = 78, const INT FrameH = 78 ) :
        Loc(Loc), At(At), FrameW(FrameW), FrameH(FrameH), ProjSize(ProjSize), ProjDist(ProjDist), Wp(1), Hp(1)
      {
        Dir = (At - Loc).Normalizing();
        Right = (Dir % Up1).Normalizing();
        Up = Right % Dir;

        A1 = Dir * ProjDist;
        B1 = Right * Wp / FrameW;
        B2 = B1 * (0.5 - FrameW / 2);
        C1 = Up * Hp / FrameH;
        C2 = C1 * (-0.5 + FrameH / 2);
        X1 = A1 + B2 + C2;
      } /* end of 'camera' function */

      /* Set projection function.
       * ARGUMENTS:
       *   - new frame size;
       *       INT W, H;
       * RETURNS: None.
       */
      VOID SetProj( INT W, INT H )
      {
        type ratio_x, ratio_y;

        ratio_x = ratio_y = 1;
        if (FrameW >= FrameH)
          ratio_x = type(FrameW) / FrameH;
        else
          ratio_y = type(FrameH) / FrameW;

        Wp = ratio_x * ProjSize;
        Hp = ratio_y * ProjSize;
      } /* End of 'SetProj' function */

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

        A1 = Dir * ProjDist;
        B1 = Right * Wp / FrameW;
        B2 = B1 * (0.5 - FrameW / 2);
        C1 = Up * Hp / FrameH;
        C2 = C1 * (-0.5 + FrameH / 2);
        X1 = A1 + B2 + C2;

        SetProj(W, H);
      } /* End of 'Resize' function */

      /* Set camera location and orientation function.
       * ARGUMENTS:
       *   - new camera location:
       *       const vec<type> &L;
       *   - new camera pivot point:
       *       const vec<type> &A;
       *   - new camera approx up direction:
       *       const vec<type> &U1;
       * RETURNS:
       *   (camera &) self reference.
       */
      camera & SetLocAtUp( const vec<type> &L, const vec<type> &A, const vec<type> &U1 = vec<type>(0, 1, 0) )
      {
        Loc = L;
        At = A;
        Dir = (At - Loc).Normalizing();
        Right = (Dir % U1).Normalizing();
        Up = Right % Dir;

        A1 = Dir * ProjDist;
        B1 = Right * Wp / FrameW;
        B2 = B1 * (0.5 - FrameW / 2);
        C1 = Up * Hp / FrameH;
        C2 = C1 * (-0.5 + FrameH / 2);
        X1 = A1 + B2 + C2;

        return *this;
      } /* End of 'SetLocAtUp' function */

      /* Make ray from camera to pixel of projection function.
       * ARGUMENTS:
       *   - screen coordinates:
       *       INT xs, ys;
       * RETURNS:
       *   (ray<type>) ray from camera to pixel of projection.
       */
      ray<type> ToRay( INT xs, INT ys )
      {
        vec<type> X = X1 + B1 * xs - C1 * ys;
        return ray<type>(X + Loc, X.Normalize());
      } /* End of 'ToRay' function */
    }; /* End of 'camera' class */
}; /* end of 'mth' namespace */

#endif /* __CAMERA_H_ */

/* END OF 'CAMERA.H' FILE */




