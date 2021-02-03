/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME    : TEXTURE.CPP
 * PURPOSE      : Resource manager.
 *                Texture class implementation module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 23.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "texture.h"
#include "render.h"

/* Get pointer on texture with TexNo == -1 function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (texture *) pointer on texture with TexNo == -1.
 */
figl::texture * figl::texture::GetDefTex( VOID )
{
  static texture TexDef;

  TexDef.H = 0;
  TexDef.W = 0;
  TexDef.TexNo = -1;

  return &TexDef;
} /* End of 'figl::texture::GetDefTex' function */

/* Copy texture class constructor.
 * AGRUMENTS:
 *   - link on texture for copying:
 *       const texture &Tex;
 * RETURNS: None.
 */
VOID figl::texture::operator=( const texture &Tex )
{
  W = Tex.W;
  H = Tex.H;
  TexNo = Tex.TexNo;
} /* End of 'figl::texture::operator=' function */

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
figl::texture * figl::texture_manager::Create( const std::string Name, const INT &W, const INT &H, const INT &C, BYTE *Bits )
{
  texture *Tex = new texture;
  if ((Tex = Find(Name)) == nullptr)
  {
    glGenTextures(1, &Tex->TexNo);
    glBindTexture(GL_TEXTURE_2D, Tex->TexNo);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, W, H, C == 1 ? GL_LUMINANCE : C == 3 ? GL_BGR_EXT : GL_BGRA_EXT, GL_UNSIGNED_BYTE, Bits);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    Tex->W = W;
    Tex->H = H;

    glBindTexture(GL_TEXTURE_2D, 0);

    Add(Name, Tex);
  }
  return Tex;
} /* End of 'figl::texture_manager::AddTexture' function */

/* END OF 'TEXTURE.CPP' FILE */