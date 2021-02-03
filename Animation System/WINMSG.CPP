/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME    : WINMSG.CPP
 * PURPOSE      : WinAPI support.
 *                Window class message implementation module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 23.07.2018.
 * NOTE         : Namespace 'figl'.
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
BOOL figl::win::OnCreate( CREATESTRUCT *CS )
{
  SetTimer(hWnd, TimerInitId, 2, nullptr);
  return TRUE;
} /* End of 'win::OnCreate' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID figl::win::OnDestroy( VOID )
{
  if (IsInit)
  {
    IsInit = FALSE;
    Close();
    KillTimer(hWnd, TimerRefreshId);
  }
  else
    KillTimer(hWnd, TimerInitId);
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
VOID figl::win::OnSize( UINT State, INT W, INT H )
{
  FrameW = W;
  FrameH = H;
  if (IsInit)
    Resize();
} /* End of 'win::OnSize' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL figl::win::OnEraseBckgrnd( HDC hDC )
{
  if (IsInit)
    Erase(hDC);
  return TRUE;
} /* End of 'win::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID figl::win::OnPaint( VOID )
{
  HDC hDC;
  PAINTSTRUCT ps;

  hDC = BeginPaint(hWnd, &ps);
  if (IsInit)
    Paint(hDC);
  EndPaint(hWnd, &ps);
} /* End of 'win::OnPaint' function */ 

/* WM_ACTIVATE window message handle function.
 * ARGUMENTS:
 *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
 *       UINT Reason;
 *   - handle of active window:
 *       HWND hWndActDeact;
 *   - minimized flag:
 *       BOOL IsMinimized;
 * RETURNS: None.
 */
VOID figl::win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{
  IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;
  if (IsInit)
    Activate(IsActive);
} /* End of 'win::OnActivate' function */

/* WM_CLOSE window message handle funciton.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID figl::win::OnClose( VOID )
{
  DestroyWindow(hWnd);
} /* End of 'OnClose' function*/

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier:
 *       INT Id;
 * RETURNS: None.
 */
VOID figl::win::OnTimer( INT Id ) 
{
  if (TimerInitId == Id && !IsInit)
  {
    KillTimer(hWnd, TimerInitId);
    SetTimer(hWnd, TimerRefreshId, 1, nullptr);
    IsInit = TRUE;
    Init();
    Resize();
    Timer();
  }
  else
    Timer();
} /* End of 'win::OnTimer' function */

/* WM_MOUSEWHEEL window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse wheel relative delta value:
 *       INT Z;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID figl::win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
  MouseWheel += Z;
} /* End of 'win::OnMouseWheel' function */

/* END OF 'WINMSG.CPP' FILE */