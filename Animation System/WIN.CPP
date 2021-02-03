/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME    : WIN.CPP
 * PURPOSE      : WinAPI support.
 *                Window class implementation module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 21.07.2018.
 * NOTE         : Namespace 'figl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "win.h"

/* Win class constructor.
 * ARGUMENTS:
 *   - application handle:
 *       HINSTANCE hInst;
 */
figl::win::win( HINSTANCE hInst ) : hInstance(hInst), IsInit(FALSE), IsActive(FALSE), IsFullScreen(FALSE),
FrameW(0), FrameH(0), hWnd(nullptr), MouseWheel(0)
{
  /* Create window class */
  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = sizeof(VOID *);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = WinFunc;
  wc.lpszClassName = "My WindowClass";
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK | MB_ICONERROR);
    return;
  }
  /* Create window */
  hWnd = CreateWindow("My WindowClass", "3D animation",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    NULL, NULL, hInstance, (VOID *)this);

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);
} /* End of 'win::win' function*/

/* Win class destructor.
 * ARGUMENTS: None.
 */
figl::win::~win( VOID )
{
} /* End of 'win::~win' function */

/* Window message handle function (CALLBACK version).
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 *   - message identifier:
 *       UINT Msg;
 *   - message first parameter ('word' param):
 *       WPARAM wParam;
 *   - message second parameter ('long' param):
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message return code (depended to Msg type).
 */
LRESULT CALLBACK figl::win::WinFunc( HWND hWnd, UINT Msg,
  WPARAM wParam, LPARAM lParam )
{
  win *Win;
  MINMAXINFO *MinMax;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    MinMax = (MINMAXINFO *)lParam;
    MinMax->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) +
      GetSystemMetrics(SM_CYMENU) +
      GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;
  case WM_CREATE:
    /* Attach 'this' pointer to window class to window */
    SetWindowLong(hWnd, 0, (DWORD) ((CREATESTRUCT *)lParam)->lpCreateParams);
    ((win*)((CREATESTRUCT *)lParam)->lpCreateParams)->hWnd = hWnd;
    Win = ((win*)((CREATESTRUCT *)lParam)->lpCreateParams);
  default:
    Win = (win *)GetWindowLong(hWnd, 0);
    if (Win != NULL)
      switch (Msg)
      {
      case WM_CREATE:
        return Win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;
      case WM_SIZE:
        Win->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
        return 0;
      case WM_ERASEBKGND:
        return (LRESULT)Win->OnEraseBckgrnd((HDC)wParam);
      case WM_PAINT:
        Win->OnPaint();
        return 0;
      case WM_TIMER:
        Win->OnTimer((UINT)wParam);
        return 0;
      case WM_MOUSEWHEEL:
        Win->OnMouseWheel((INT)(SHORT)LOWORD(lParam),
          (INT)(SHORT)HIWORD(lParam),
          (INT)(SHORT)HIWORD(wParam),
          (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_CLOSE:
        Win->OnClose();
        return 0;
      case WM_ACTIVATE:
        Win->OnActivate((UINT)LOWORD(wParam), (HWND)(lParam), (BOOL)HIWORD(lParam));
        return 0;
      case WM_DESTROY:
        Win->OnDestroy();
        return 0;
      }
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'win::WinFunc' function */

/* Window run function.
 * ARGUMENTS: None.
 * RETURNS:None.
 */
VOID figl::win::Run( VOID )
{
  MSG msg;
  while (TRUE)
  {
    /* Check message at window message queue */
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      if (msg.message == WM_QUIT)
        break;
      else
      {
        /* Displatch message to window */
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    else
    {
       Idle();
    }
  }
} /* End of 'Run' function */

/* Flip full screen function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID figl::win::FlipFullScreen( VOID )
{
  static RECT SaveRC;

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    GetWindowRect(hWnd, &SaveRC);
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);
    
    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);
    SetWindowPos(hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top, SWP_NOOWNERZORDER);
  }
  else
    SetWindowPos(hWnd, HWND_TOP,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top, SWP_NOOWNERZORDER);
  IsFullScreen = !IsFullScreen;


}
/* END OF 'WIN.CPP' FILE */