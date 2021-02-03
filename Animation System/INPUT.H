/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME    : INPUT.H
 * PURPOSE      : Animation system.
 *                Input class declaration module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 23.07.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __INPUT_H_
#define __INPUT_H_

#include "def.h"

/* Animation project namespace */
namespace figl
{
  /* Input class declaration */
  class input
  {
  public:
    HWND hWnd;              // window working handle
    INT
      Mx, My,               // Mouse cursor position
      Mz,                   // Mouse wheel absolute value
      Mdx, Mdy, Mdz;        // Delta values of mouse axes
    INT &MouseWheel;        // Global mouse wheel delta value
    BYTE
      Keys[256],            // Current key states
      OldKeys[256];         // Previous frame key states
    BOOL KeysClick[256];    // Click key flags

    /* Input class constructor.
     * ARGUMENTS:
     *   - window handle:
     *       HWND hWnd;
     *   - link on mouse wheel delta value:
     *       INT &MouseWheel;
     */
    input( HWND hWnd, INT &MouseWheel ) : hWnd(hWnd), MouseWheel(MouseWheel), Mx(0), My(0), Mz(0), Mdx(0), Mdy(0), Mdz(0)
    {
      memset(Keys, 0, 256);
      memset(OldKeys, 0, 256);
      memset(KeysClick, FALSE, 256);
    } /* End of 'input' funciton */

    /* Update input function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID UpdateInput( VOID )
    {
      POINT pt;

      /* Keyboard*/
      GetKeyboardState(Keys);
      for (int i = 0; i < 256; i++)
      {
        Keys[i] >>= 7;
        if (!OldKeys[i] && Keys[i])
          KeysClick[i] = TRUE;
        else
          KeysClick[i] = FALSE;
      }
      memcpy(OldKeys, Keys, 256);

      /* Mouse */
      GetCursorPos(&pt);
      ScreenToClient(hWnd, &pt);
      Mdx = pt.x - Mx;
      Mdy = pt.y - My;
      Mx = pt.x;
      My = pt.y;
      Mz += Mdz = MouseWheel;
      MouseWheel = 0;
    }
  }; /* End of 'input' class */
} /* end of 'figl' namespace */

#endif /* __INPUT_H_ */

/* END OF 'INPUT.H' FILE */