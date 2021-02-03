/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME    : RENDER.H
 * PURPOSE      : Render system.
 *                Render class declaration module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 23.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#define GLEW_STATIC
#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

#pragma comment(lib, "glew32s")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

#include <map>
#include "def.h"
#include "rndprims.h"
#include "material.h"

/* Animation project namespace */
namespace figl
{
  /* Render class declaration */
  class render
  {
  private:
    HWND hWnd;                   // Link on work window handle
    HDC hDC;                     // Work windows device context
    HGLRC hGLRC;                 // OpenGL rendering context
    INT FrameW, FrameH;          // Frame size

  public:
    mth::camera<FLT> Camera;     // Camera
    material_manager Materials;  // Material manager
    texture_manager Textures;    // Texture manager
    shader_manager Shaders;      // Shader manager

    /* Render class constructor.
     * ARGUMENTS:
     *   - working window handle:
     *       HWND hWnd;
     */
    render( HWND hWnd );

    /* Render class destructor
     * ARGUMENTS: None.
     */
    ~render( VOID );

    /* Render start function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Start( VOID );

    /* Render end function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID End( VOID );

    /* Resize function.
     * ARGUMENTS:
     *   - new frame size:
     *       INT NewFrameW, NewFrameH:
     * RETURNS: None.
     */
    VOID Resize( INT NewFrameW, INT NewFrameH );

    /* Copy frame function.
     * ARGUMENTS: None.
     */
    VOID CopyFrame( VOID );

    /* Draw primitive function.
     * ARGUMENTS:
     *   - link on primitive for drawing:
     *       const figl::prim &Pr;
     *   - link on world matrix:
     *       matr World;
     * RETURNS: None.
     */
    VOID Draw( const figl::prim &Pr, matr World );

    /* Draw primitive function.
     * ARGUMENTS:
     *   - link on primitives for drawing:
     *       const figl::prims &Prs;
     *   - link on world matrix:
     *       const matr World;
     * RETURNS: None.
     */
    VOID Draw( const figl::prims &Prs, const matr World );
  }; /* End of 'render' class */
} /* end of 'figl' namespace */

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
