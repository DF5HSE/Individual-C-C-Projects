/*************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : IMAGE.H
 * PURPOSE     : Resource manager.
 *               Image handle class declaration module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis
 * LAST UPDATE : 14.08.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include <vector>
#include "def.h"

/* Project namespace */
namespace figl
{
  /* Image representation class */
  class image
  {
  private:
    // Image size in pixels
    INT Width = 0, Height = 0;
    // Image pixel data
    std::vector<BYTE> Pixels;
  public:
    // Rows access pointer by DWORD
    std::vector<DWORD *> RowsD;
    // Rows access pointer by BYTE quads
    std::vector<BYTE (*)[4]> RowsB;

    // Image size references
    const INT &W = Width, &H = Height;

    /* Class default construtor */
    image( VOID );

    /* Class construtor.
     * ARGUMENTS:
     *   - image file name:
     *       const std::string &FileName;
     */
    image( const std::string &FileName );
  }; /* End of image class */
} /* end of 'figl' namespace */

#endif /* __IMAGE_H_ */

/* END OF 'IMAGE.H' FILE */
