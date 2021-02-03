/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME    : SHADER.H
 * PURPOSE      : Resource manager.
 *                Shader class declaration module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 15.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __SHADER_H_
#define __SHADER_H_

#include "resman.h"

/* Animation project namespace */
namespace figl
{
  /* Shader class declaration */
  class shader
  {
  public:
    UINT ProgId; // Shader program id

    /* Copy shader class constructor.
     * AGRUMENTS:
     *   - link on shader for copying:
     *       const shader &Shd;
     * RETURNS: None.
     */
    VOID operator=( const shader &Shd );
  }; /* End of 'shader' class */

  /* Shader manager class declaration */
  class shader_manager : public resource_manager<shader>
  {
  private:
    /* Load text from file function.
     * ARGUMENTS:
     *  - reference on file name to be load from:
     *      const std::string &FileName;
     *  RETURNS:
     *    (std::string) loaded text.
     */
    std::string TextLoad( std::string FileName );

    /* Saving log in file function.
     * ARGUMENTS:
     *   - reference on shader name:
     *       const std::string &Name;
     *   - reference on shader type:
     *       const std::string &Type;
     *   - reference on text of log:
     *       const std::string &Text;
     * RETURNS: None.
     */
    VOID SaveLog( const std::string &Name, const std::string &Type, const std::string &Text );

    /* Load shader function.
     * ARGUMENTS:
     *   - shader directory name:
     *       std::string ShaderDirectoryName;
     * RETURNS:
     *   (UINT) loaded shader program id.
     */
    UINT Load( std::string ShaderDirectoryName );

    /* Free shader from memory function.
     * ARGUMENTS:
     *   - shader program id:
     *       UINT ProgId;
     * RETURNS: None.
     */
    VOID Delete( UINT ProgId );

  public:
    /* Shader manager initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID );

    /* Shader manager deinitialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID );

    /* Add shader to stock from file function.
     * ARGUMENTS: 
     *   - reference on shader file name:
     *       const std::string &ShaderDirectoryName;
     * RETURNS:
     *   (UINT) pointer on shader;
     */
    shader * Create( const std::string ShaderDirectoryName );

    /* Update loaded shaders.
     * ARGUMENTS: None
     * RETURNS: None.
     */
    VOID Update( VOID );
  }; /* End of 'shader_manager' class */
} /* end of 'figl' namespace */

#endif /* __SHADER_H_ */

/* END OF 'SHADER.H' FILE */