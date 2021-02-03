/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME    : ANIM.CPP
 * PURPOSE      : Animation system.
 *                Animation class implementation module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 23.07.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "anim.h"

/* Animation class constructor.
 * ARGUMENTS: None.
 */
figl::anim::anim( VOID ) : win(), timer(), input(figl::win::hWnd, figl::win::MouseWheel), render(figl::win::hWnd)
{
  INT a;

  a = 0;
} /* End of 'figl::anim::anim' function */

/* Animation class destructor.
 * ARGUMENTS: None.
 */
figl::anim::~anim( VOID )
{
  for (std::vector<unit *>::iterator unit = Units.begin(); unit != Units.end(); ++unit)
    delete *unit;
} /* End of 'figl::anim::~anim' function */

/* Singletone creation function
 * ARGUMENTS: None.
 * RETURNS:
 *   (anim &) mention to class instance.
 */
figl::anim & figl::anim::GetInstance( VOID )
{
  static anim Instance;
  return Instance;
} /* End of 'figl::anim::GetInstance' function */
/* Animation render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID figl::anim::Render( VOID )
{
  static FLT UpdateTime = 0;
  timer::Response();
  if (IsActive)
    input::UpdateInput();

  for (std::vector<unit *>::iterator unit = Units.begin(); unit != Units.end(); ++unit)
    (*unit)->Response(this);

  render::Start();
  for (std::vector<unit *>::iterator unit = Units.begin(); unit != Units.end(); ++unit)
    (*unit)->Render(this);

  if (GlobalTime - UpdateTime > 5)
  {
    Shaders.Update();
    UpdateTime = GlobalTime;
  }

  render::End();
} /* End of 'figl::anim::Render' function */

/* Do exit function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID figl::anim::DoExit( VOID )
{
  PostMessage(figl::win::hWnd, WM_CLOSE, 0, 0);
}

/* END OF 'ANIM.CPP' FILE */