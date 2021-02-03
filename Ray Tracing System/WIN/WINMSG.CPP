/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : WINMSG.CPP
 * PURPOSE     : WinAPI support.
 *               Window class message implementation module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 25.07.2018.
 * NOTE        : Namespace 'firt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#include "win.h"

/* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL firt::win::OnCreate( CREATESTRUCT *CS )
{
  SetTimer(hWnd, TimerInitId, 2, nullptr);
  return TRUE;
} /* End of 'win::OnCreate' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID firt::win::OnDestroy( VOID )
{
  PostQuitMessage(0);
  hWnd = nullptr;
} /* End of 'win::OnDestroy' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT W, H;
 * RETURNS: None.
 */
VOID firt::win::OnSize( UINT State, INT W, INT H )
{
  FrameW = W;
  FrameH = H;
  Resize(W, H);
} /* End of 'win::OnSize' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL firt::win::OnEraseBckgrnd( HDC hDC )
{
  Erase(hDC);
  return TRUE;
} /* End of 'win::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID firt::win::OnPaint( VOID )
{
  static BOOL WasPainted = FALSE;
  HDC hDC;
  PAINTSTRUCT ps;

  hDC = BeginPaint(hWnd, &ps);
  //if (IsInit)
    Paint(hDC);
  EndPaint(hWnd, &ps);
  if (!WasPainted)
  {
    InvalidateRect(hWnd, NULL, FALSE);
    WasPainted = !WasPainted;
  }
} /* End of 'win::OnPaint' function */ 

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier:
 *       INT Id;
 * RETURNS: None.
 */
VOID firt::win::OnTimer( INT Id ) 
{
  if (TimerInitId == Id && !IsInit)
  {
    KillTimer(hWnd, TimerInitId);
    IsInit = TRUE;
    Init();
    InvalidateRect(hWnd, NULL, FALSE);
    //Resize(FrameW, FrameH);
  }
} /* End of 'win::OnTimer' function */

/* WM_CLOSE window message handle funciton.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID firt::win::OnClose( VOID )
{
  DestroyWindow(hWnd);
} /* End of 'OnClose' function*/

/* END OF 'WINMSG.CPP' FILE */
