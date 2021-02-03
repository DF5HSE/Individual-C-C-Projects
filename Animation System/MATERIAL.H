/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME    : MATERIAL.H
 * PURPOSE      : Resource manager.
 *                Material class declaration module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 23.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __MATERIAL_H_
#define __MATERIAL_H_

#include <vector>

#include "texture.h"
#include "shader.h"

/* Animation project namespace */
namespace figl
{
  /* Material class declaration */
  class material
  {
  public:
    vec Ka, Kd, Ks;          // Ambient, diffuse and specular lighting coefficients
    FLT Ph, Trans;           // Phong and transparency coefficients
    std::string ShdName;     // Shader name
    texture *Tex[8];         // Pointers on textures

    /* Copy material class constructor.
     * AGRUMENTS:
     *   - link on material for copying:
     *       const material &Mtl;
     * RETURNS: None.
     */
    VOID operator=( const material &Mtl );
  }; /* End of 'material' class */

  /* Material manager class declaration */
  class material_manager : public resource_manager<material>
  {
  public:
    static texture * TexDefault;               // Pointer on default texture
    static std::vector<texture *> TexDefArray; // Array of default textures

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
    material * Create( const std::string &Name, const vec &Ka0, const vec &Kd0, const vec &Ks0, const FLT &Ph0, const FLT &Trans0,
      const std::vector<texture *> &Tex0 = TexDefArray, const std::string &ShdName0 = "DEFAULT" );

    /* Material manager initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID );

    /* Apply material function.
     * ARGUMENTS:
     *   - pointer on material for applying:
     *       material *Mtl;
     *   - reference on programm id of shader:
     *       const UINT &ProgId;
     * RETURNS: None.
     */
    VOID Apply( figl::material *Mtl, const UINT &ProgId );
  }; /* End of 'material_manager' class */
} /* end of 'figl' namespace */

#endif /* __MATERIAL_H_ */

/* END OF 'MATERIAL.H' FILE */