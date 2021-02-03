/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME    : U_CONTRL.H
 * PURPOSE      : Animation system.
 *                Control unit class declaration module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 14.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __U_CONTRL_H_
#define __U_CONTRL_H_

#include "anim.h"

 /* Animation project namespace */
namespace figl
{
/* Control unit class declaration */
  class unit_control : public unit
  {
  public:
    BOOL IsWireFrame; // Fireframe flag
    /* Control unit class constructor.
     * ARGUMENTS: None.
     */
    unit_control( VOID )
    {
      IsWireFrame = FALSE;
    } /* End of 'unit_test' function */

    /* Control unit render function.
     * ARGUMENTS:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Render( anim *Ani )
    {
      glLoadMatrixf(Ani->Camera.GetVP().GetMatrNumbers());
      /* Axises */
      glBegin(GL_LINES);
        /* X */
        glColor3d(1, 0, 0);
        glVertex3d(0, 0, 0);
        glVertex3d(100, 0, 0);
        /* Y */
        glColor3d(0, 1, 0);
        glVertex3d(0, 0, 0);
        glVertex3d(0, 100, 0);
        /* Z */
        glColor3d(0, 0, 1);
        glVertex3d(0, 0, 0);
        glVertex3d(0, 0, 100);

        /* Cow color */
        glColor3d(0.1, 0.5, 0.3);
      glEnd();
    } /* End of 'Render' function */

    /* Control unit response function.
     * ARGUMENTS:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Response( anim *Ani )
    {
      if (Ani->KeysClick[VK_ESCAPE])
        Ani->DoExit();
      if (Ani->KeysClick['F'])
        Ani->FlipFullScreen();
      if (Ani->KeysClick['P'])
        Ani->IsPause = !Ani->IsPause;
      if (Ani->Keys[VK_LSHIFT] && Ani->KeysClick['W'])
      {
        if (!IsWireFrame)
          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        IsWireFrame = !IsWireFrame;
      }

      vec Move;
      FLT RotateAroundRight = 0, RotateAroundUp = 0;

      if (Ani->Keys[VK_RIGHT])
      {
        INT a;

        a = 0;
        a = 1;
      }

      Move = Ani->Camera.GetDir() * ((Ani->Keys[VK_LSHIFT] ? 0 : Ani->Keys['W']) - Ani->Keys['S']) * Ani->GlobalDeltaTime * 78 / 24 +
           Ani->Camera.GetRight() * (Ani->Keys['D'] - Ani->Keys['A']) * Ani->GlobalDeltaTime * 78 / 24 +
           Ani->Camera.GetUp() * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]) * Ani->GlobalDeltaTime * 78 / 24;
      //RotateAroundRight = -(Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]) * Ani->GlobalDeltaTime * 780 / 24,
      RotateAroundUp = (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT]) * Ani->GlobalDeltaTime * 780 / 24;

      Ani->Camera.Move(Move);
      //Ani->Camera.RotateAroundRight(RotateAroundRight);
      Ani->Camera.RotateAroundUp(RotateAroundUp);
    } /* End of 'Response' function */

    /* Unit class destructor.
     * ARGUMENTS: None.
     */
    ~unit_control( VOID )
    {
    } /* Enf of '~unit_test' function */
}; /* End of 'unit_test' class */
} /* end of 'figl' namespace */
#endif /* __U_CONTRL_H_*/

/* END OF ' U_CONTRL.H' FILE */
