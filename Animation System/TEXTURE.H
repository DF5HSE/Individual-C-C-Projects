/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME    : TEXTURE.H
 * PURPOSE      : Resource manager.
 *                Texture class declaration module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 14.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __TEXTURE_H_
#define __TEXTURE_H_

#include "resman.h"

/* Animation project namespace */
namespace figl
{
  /* Texture class declaration */
  class texture
  {
  public:
    INT W, H;   // Texture size
    UINT TexNo; // Texture number

    /* Copy texture class constructor.
     * AGRUMENTS:
     *   - link on texture for copying:
     *       const texture &Tex;
     * RETURNS: None.
     */
    VOID operator=( const texture &Tex );

    /* Get pointer on texture with TexNo == -1 function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (texture *) pointer on texture with TexNo == -1.
     */
    static texture * GetDefTex( VOID );
  }; /* End of 'texture' class */

  /* Texture manager class declaration */
  class texture_manager : public resource_manager<texture>
  {
  public:
    /* Add texture from image function.
     * ARGUMENTS:
     *   - reference on texture name:
     *       const std::string &Name;
     *   - reference on image size:
     *       const INT &W, &H;
     *   - reference on image pixel components:
     *       const INT &C;
     *   - pointer on pixels bits:
     *       BYTE *Bits;
     * RETURNS:
     *   (texture *) pointer on created texture.
     */
    texture * Create( const std::string Name, const INT &W, const INT &H, const INT &C, BYTE *Bits );
  }; /* End of 'texture_manager' class */
} /* end of 'figl' namespace */

#endif /* __TEXTURE_H_ */

/* END OF 'TEXTURE.H' FILE */