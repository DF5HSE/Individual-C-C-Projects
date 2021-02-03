/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME    : RENDER.CPP
 * PURPOSE      : Render system.
 *                Render class implementation module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 23.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "render.h"
#include "anim.h"

/* Render class constructor.
 * ARGUMENTS:
 *   - working window handle:
 *       HWND hWnd;
 */
figl::render::render( HWND hWnd ) : hWnd(hWnd), FrameW(78), FrameH(78), Camera()
{
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};

  /* OpenGl initialization */
  hDC = GetDC(hWnd);
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(hDC, &pfd);
  DescribePixelFormat(hDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  SetPixelFormat(hDC, i, &pfd);

  hGLRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hGLRC);

  if (glewInit() != GLEW_OK)
  {
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(hGLRC);
    ReleaseDC(hWnd, hDC);
    exit(0);
  }

  glEnable(GL_DEPTH_TEST);
  glClearColor(0.3, 0.5, 0.7, 1);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);

  Camera.SetCam();
  Camera.SetProj();
} /* End of 'figl::render::render' funciton */

/* Render class destructor
 * ARGUMENTS: None.
 */
figl::render::~render( VOID )
{
  wglMakeCurrent(nullptr, nullptr);
  wglDeleteContext(hGLRC);
  ReleaseDC(hWnd, hDC);
} /* End of 'figl::render::~render' funciton */

/* Render start function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID figl::render::Start( VOID )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} /* End of 'figl::render::Start' funciton */

/* Render end function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID figl::render::End( VOID )
{
  glFinish();
} /* End of 'figl::render::End' funciton */

/* Resize function.
 * ARGUMENTS:
 *   - new frame size:
 *       INT NewFrameW, NewFrameH:
 * RETURNS: None.
 */
VOID figl::render::Resize( INT NewFrameW, INT NewFrameH )
{
  glViewport(0, 0, NewFrameW, NewFrameH);
  FrameW = NewFrameW;
  FrameH = NewFrameH;
  Camera.Resize(FrameW, FrameH);
} /* End of 'figl::render::Resize' funciton */

/* Copy frame function.
 * ARGUMENTS: None.
 */
VOID figl::render::CopyFrame( VOID )
{
  SwapBuffers(hDC);
} /*   End of 'figl::render::CopyFrame' funciton */

/* Draw primitive function.
 * ARGUMENTS:
 *   - link on primitive for drawing:
 *       const figl::prim &Pr;
 *   - link on world matrix:
 *       matr World;
 * RETURNS: None.
 */
VOID figl::render::Draw( const figl::prim &Pr, matr World )
{
  INT gl_prim_type, loc;
  UINT ProgId = 0;
  matr
    WVP = Pr.Transform * World * Camera.GetVP(),
    MatrNormTrans = (Pr.Transform * World).Inverse().Transpose();

  /* Set transfor matrix (if shader not work) */
  //glLoadMatrixf(WVP.GetMatrNumbers());

  /* Working with shaders and materials */
  ProgId = Pr.Mtl == nullptr ? Shaders.Stock["DEFAULT"]->ProgId : Shaders.Stock[Pr.Mtl->ShdName]->ProgId;
  Materials.Apply(Pr.Mtl, ProgId);

  if ((loc = glGetUniformLocation(ProgId, "WVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE,  WVP.GetMatrNumbers());
  if ((loc = glGetUniformLocation(ProgId, "InvTrans")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, MatrNormTrans.GetMatrNumbers());
  if ((loc = glGetUniformLocation(ProgId, "World")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, World.GetMatrNumbers());
  if ((loc = glGetUniformLocation(ProgId, "CamLoc")) != -1)
    glUniform3fv(loc, 1, &Camera.GetLoc().GetX());
  if ((loc = glGetUniformLocation(ProgId, "Time")) != -1)
    glUniform1fv(loc, 1, &anim::GetInstance().Time);

  gl_prim_type = Pr.Type == prim::MESH ? GL_TRIANGLES : 
                 Pr.Type == prim::LINE ? GL_LINE : 
                 Pr.Type == prim::LINESTRIP ? GL_LINES :
                 Pr.Type == prim::POINT ? GL_POINTS : 
                 Pr.Type == prim::STRIP ? GL_TRIANGLE_STRIP :
                 0;
  glBindVertexArray(Pr.VA);
  if (Pr.IBuf == 0)
    glDrawArrays(gl_prim_type, 0, Pr.VertexCounter);
  else
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr.IBuf);
    glDrawElements(gl_prim_type, Pr.IndexCounter, GL_UNSIGNED_INT, nullptr);
  }
  glBindVertexArray(0);
  glUseProgram(0);
} /* End of 'figl::render::Draw' function */

/* Draw primitive function.
 * ARGUMENTS:
 *   - link on primitives for drawing:
 *       const figl::prims &Prs;
 *   - link on world matrix:
 *       const matr World;
 * RETURNS: None.
 */
VOID figl::render::Draw( const figl::prims &Prs, const matr World )
{
  for (auto it = Prs.Prims.begin(); it != Prs.Prims.end(); ++it)
    Draw((*(*it)), World);
} /* End of 'figl::render::Draw' function */

/* END OF 'RENDER.CPP' FILE */