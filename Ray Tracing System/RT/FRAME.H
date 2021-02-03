/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : FRAME.H
 * PURPOSE     : Ray tracing project.
 *               Frame class declaration module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 25.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __FRAME_H_
#define __FRAME_H_

#include "../def.h"
#include "../WIN/win.h"
#include "IMAGE/image.h"
#include "SHAPES/sphere.h"
#include "SHAPES/plane.h"
#include "SHAPES/box.h"
#include "SHAPES/tor.h"
#include "SHAPES/quadric.h"
#include "scene.h"

/* Project namespace */
namespace firt
{
  /* Frame class declaration */
  class frame : public win
  {
  private:
    camera Cam;  // Camera
    image Img;   // Image
    scene Scene; // Scene
  public:
    /* Default frame class constructor.
     * ARGUMENTS: None.
     */
    frame( VOID );

    /* Frame class constructor.
     * ARGUMENTS:
     *   - hInstance:
     *       HINSTANCE hInst;
     */
    frame( HINSTANCE hInst );

    /* Frame class destructor.
     * ARGUMENTS: None.
     */
    ~frame( VOID );

    /* Frame initialization function.
     * ARGUMENTS: None.
     * RRTURNS: None.
     */
    VOID Init( VOID ) override;

    /* Paint window content function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Paint( HDC hDC ) override;

    /* Change window size handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( INT W, INT H ) override;
  }; /* End of 'frame' class */
} /* end of 'firt' namespace */

#endif /* __FRAME_H_ */

/* END OF 'FRAME.H' FILE */

