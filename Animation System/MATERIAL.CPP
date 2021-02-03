/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME    : MATERIAL.CPP
 * PURPOSE      : Resource manager.
 *                Material class implementation module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 23.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "material.h"
#include "render.h"

figl::texture * figl::material_manager::TexDefault = figl::texture::GetDefTex();               // Pointer on default texture
std::vector<figl::texture *> figl::material_manager::TexDefArray = {TexDefault, TexDefault, TexDefault, TexDefault,    // Array of
                                                                    TexDefault, TexDefault, TexDefault, TexDefault, }; // default textures

/* Create material function.
 * ARGUMENTS:
 *   - reference on material name:
 *       const std::string &Name;
 *   - references on ambient, diffuse and specular lighting coefficients:
 *       const vec &Ka0, &Kd0, &Ks0;
 *   - references on phong and transparency coefficients:
 *       const FLT &Ph0, &Trans0;
 *   - reference on textures ids array:
 *       const std::vector<INT> &Tex0;
 *   - reference on shader name:
 *       const std::string &ShdName0;
 * RETURNS:
 *   (material *) pointer on material.
 */
figl::material * figl::material_manager::Create( const std::string &Name, const vec &Ka0, const vec &Kd0, const vec &Ks0, const FLT &Ph0,
                                                 const FLT &Trans0, const std::vector<texture *> &Tex0,
                                                 const std::string &ShdName0 )
{
  material *mtl;

  if ((mtl = Find(Name)) == nullptr)
  {
    mtl = new material;
    mtl->Ka = Ka0;
    mtl->Kd = Kd0;
    mtl->Ks = Ks0;
    mtl->Ph = Ph0;
    mtl->Trans = Trans0;
    for (INT i = 0, TexSize = Tex0.size(); i < 8 && i < TexSize; i++)
      mtl->Tex[i] = Tex0[i];
    mtl->ShdName = ShdName0;
    Add(Name, mtl);
  }

  return mtl;
} /* End of 'figl::material_manager::Create' function */


/* Material manager initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID figl::material_manager::Init( VOID )
{
  Create("DEFAULT", vec(0.24, 0.19, 0.07), vec(0.75, 0.60, 0.23), vec(0.63, 0.56, 0.37), 51.2, 1); // may be gold
} /* End of 'figl::material_manager::Init' function */

/* Apply material function.
 * ARGUMENTS:
 *   - pointer on material for applying:
 *       material *Mtl;
 *   - reference on programm id of shader:
 *       const UINT &ProgId;
 * RETURNS: None.
 */
VOID figl::material_manager::Apply( figl::material *Mtl, const UINT &ProgId )
{
  INT loc;

  // set material pointer
  if (Mtl == nullptr)
    Mtl = Stock["DEFAULT"];

  glUseProgram(ProgId);

  if ((loc = glGetUniformLocation(ProgId, "Ka")) != -1)
    glUniform3fv(loc, 1, &Mtl->Ka.GetX());
  if ((loc = glGetUniformLocation(ProgId, "Kd")) != -1)
    glUniform3fv(loc, 1, &Mtl->Kd.GetX());
  if ((loc = glGetUniformLocation(ProgId, "Ks")) != -1)
    glUniform3fv(loc, 1, &Mtl->Ks.GetX());
  if ((loc = glGetUniformLocation(ProgId, "Ph")) != -1)
    glUniform1fv(loc, 1, &Mtl->Ph);
  if ((loc = glGetUniformLocation(ProgId, "Trans")) != -1)
    glUniform1fv(loc, 1, &Mtl->Trans);

  for (INT i = 0; i < 8; i++)
  {
    CHAR num = '0' + i;
    INT n;
    if (Mtl->Tex[i]->TexNo != -1)
    {
      n = 1;
      if ((loc = glGetUniformLocation(ProgId, "IsTexture" + num)) != -1)
        glUniform1iv(loc, 1, &n);
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, Mtl->Tex[i]->TexNo);
    }
    else
    {
      n = 0;
      if ((loc = glGetUniformLocation(ProgId, "IsTexture" + num)) != -1)
        glUniform1iv(loc, 1, &n);
    }
  }
} /* End of 'figl::material_manager::Apply' function */

/* END OF 'MATERIAL.CPP' FILE */