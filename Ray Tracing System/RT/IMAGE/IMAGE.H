/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : IMAGE.H
 * PURPOSE     : Ray tracing project.
 *               Image class declaration module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 25.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include <string>
#include "../../def.h"
//#include "../../WIN/win.h"

/* Project namespace */
namespace firt
{
  /* Image class declaration */
  class image
  {
  private:
    camera Cam;            // Camera
    HDC hMemDC;            // Window context
    HWND hWnd;             // Window handle
    HBITMAP hBm;           // Bit map hadle for creating picture
    BITMAPINFOHEADER bmih; // Bit map information header
    DWORD *Bits;           // Frame buffer with colors of pixels
    INT FrameW, FrameH;    // Frame size

  public:
    /* Default image class constructor.
     * ARGUMENTS: None.
     */
    image( VOID );

    /* Image class constructor.
    * ARGUMENTS:
    *   - window handle:
    *       HWND hWnd;
    *   - image size:
    *       INT W, H;
    */
    image( HWND hWnd, INT W, INT H );

    /* Image class destructor.
     * ARGUMENTS: None.
     */
    ~image( VOID );

    /* Image resize function.
     * ARGUMENTS:
     *   - new frame size:
     *       INT NewW, NewH;
     * RETURNS: None.
     */
    VOID Resize( INT NewW, INT NewH );

    /* Draw image function.
     * ARGUMENTS:
     *   - hDC for drawing:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Draw( HDC hDC );

    /* Get image width function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) image width.
     */
    INT GetW( VOID );

    /* Get image hight function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) image hight.
     */
    INT GetH( VOID );

    /* Put pixel function.
     * ARGUMENTS:
     *   - pixels image coordinates:
     *       INT X, Y;
     *   - color:
     *       DWORD Color;
     * RETURNS: None.
     */
    VOID PutPixel( INT X, INT Y, DWORD Color );

    /* Get pixel function.
     * ARGUMENTS:
     *   - pixels image coordinates:
     *       INT X, Y;
     * RETURNS:
     *   (DWORD) color of pixel.
     */
    DWORD GetPixel( INT X, INT Y );

    /* Make color from vector to DWORD function.
     * ARGUMENTS:
     *   - color vector:
     *       const vec &Color;
     * RETURNS:
     *   (DWORD) color.
     */
    static DWORD vecRGBtoDWORD( const vec &Color );

    /* Save image in BMP format function.
     * ARGUMENTS:
     *   - name of file for saving:
     *        const std::string &SaveFileName;
     * RETURNS:
     *   (BOOL) if succesfull - TRUE, else - FALSE;
     */
    BOOL SaveBMP( const std::string &SaveFileName );

  } /* End of 'image' class */;
} /* end of 'firt' namespace */

#endif /* __IMAGE_H_ */
/* END OF 'IMAGE.H' FILE */
