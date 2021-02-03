/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME    : U_TEST.H
 * PURPOSE      : Animation system.
 *                Test unit class declaration module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 14.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __U_TEST_H_
#define __U_TEST_H_

#include "anim.h"

 /* Animation project namespace */
namespace figl
{
/* Unit class declaration */
  class unit_test : public unit
  {
  public:
    prims Cow; // Cow primitives
    prims Car; // Car primitives
    prim Test;

    /* Test unit class constructor.
    * ARGUMENTS: None.
    */
    unit_test( VOID )
    {
      Cow.Load("Models/cow.g3dm", matr::Identity());
      //Cow.Load("Models/x6.g3dm", matr::Identity());
      Car.Load("Models/camaro69.g3dm", matr::Identity());
    } /* End of 'unit_test' function */

    /* Unit render function.
     * ARGUMENTS:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Render( anim *Ani )
    {
      Ani->Draw(Car, matr::Translate(vec(-10, -100, -10)) * matr::Scale(vec(0.1, 0.1, 0.1)));
      Ani->Draw(Cow, matr::Identity());

      /* At triangle */
      vec At = Ani->Camera.GetAt();
      FLT x = At.GetX(), y = At.GetY(), z = At.GetZ();
      glBegin(GL_TRIANGLES);
        glColor3d(1, 0, 0);
        glVertex3d(x + 0.1, y, z);
        glColor3d(0, 1, 0);
        glVertex3d(x, y + 0.1, z);
        glColor3d(0, 0, 1);
        glVertex3d(x, y, z + 0.1);
      glEnd();
    } /* End of 'Render' function */

    /* Unit response function.
     * ARGUMENTS:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Response( anim *Ani )
    {
    } /* End of 'Response' function */

    /* Unit class destructor.
     * ARGUMENTS: None.
     */
    ~unit_test( VOID )
    {
    } /* Enf of '~unit_test' function */
}; /* End of 'unit_test' class */
} /* end of 'figl' namespace */
#endif /* __U_TEST_H_*/

/* END OF 'U_TEST.H' FILE */
