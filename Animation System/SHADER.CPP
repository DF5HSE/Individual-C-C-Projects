/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME    : SHADER.CPP
 * PURPOSE      : Resource manager.
 *                Shader class implementation module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 23.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include <fstream>
#include "shader.h"
#include "render.h"

/* Copy shader class constructor.
 * AGRUMENTS:
 *   - link on shader for copying:
 *       const shader &Shd;
 * RETURNS: None.
 */
VOID figl::shader::operator=( const shader &Shd )
{
  ProgId = Shd.ProgId;
} /* End of 'operator=' function */

/* Load text from file function.
 * ARGUMENTS:
 *  - reference on file name to be load from:
 *      const std::string &FileName;
 *  RETURNS:
 *    (std::string) loaded text.
 */
std::string figl::shader_manager::TextLoad( std::string FileName )
{
  std::ifstream f = std::ifstream(FileName);
  std::string ShdText;

  ShdText = std::string((std::istreambuf_iterator<CHAR>(f)), (std::istreambuf_iterator<CHAR>()));

  INT a = ShdText.size();
  INT b = ShdText.length();


  return ShdText;
} /* End of 'figl::shader_manager::TextLoad' function */

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
VOID figl::shader_manager::SaveLog( const std::string &Name, const std::string &Type, const std::string &Text )
{
  std::ofstream f("BIN/SHADERS/DF5{30}SHD.LOG", std::ios_base::app);

  f << Name.c_str() << "/" << Type.c_str() << ".GLSL: " << Text.c_str();
} /* End of 'figl::shader_manager::SaveLog' function */

/* Load shader function.
 * ARGUMENTS:
 *   - shader directory name:
 *       std::string ShaderDirectoryName;
 * RETURNS:
 *   (UINT) loaded shader program id.
 */
UINT figl::shader_manager::Load( std::string ShaderDirectoryName )
{
  struct
  {
  public:
    UINT Type;        // Shader type
    std::string Suff; // Shader suffix
    BOOL IsNecessery; // Is shader nessery flag
    UINT Id;          // Shader id
  } Shd[5] =
  {
    {GL_VERTEX_SHADER, "VERT", TRUE, 0},
    {GL_TESS_CONTROL_SHADER, "CTRL", FALSE, 0},
    {GL_TESS_EVALUATION_SHADER, "EVAL", FALSE, 0},
    {GL_GEOMETRY_SHADER, "GEOM", FALSE, 0},
    {GL_FRAGMENT_SHADER, "FRAG", TRUE, 0}
  };
  std::string TxtFromShd[5], Buf;
  INT NumOfShaders = 5, res;
  UINT Prg = 0;
  BOOL IsOK = TRUE;
  
  ShaderDirectoryName = "BIN/SHADERS/" + ShaderDirectoryName;
  
  // Loading shaders
  for (INT i = 0; i < NumOfShaders; i++)
  {
    Buf = ShaderDirectoryName + "/" + Shd[i].Suff + ".GLSL";
  
    // Load shader file
    TxtFromShd[i] = TextLoad(Buf);
    //TxtFromShd = "abc";
    if (TxtFromShd[i].length() == 0)
    {
      if (Shd[i].IsNecessery)
      {
        IsOK = FALSE;
        SaveLog(ShaderDirectoryName, Shd[i].Suff, "Error load file");
        break;
      }
      continue;
    }
  
    // Create shader in memory
    if ((Shd[i].Id = glCreateShader(Shd[i].Type)) == 0)
    {
      IsOK = FALSE;
      SaveLog(ShaderDirectoryName, Shd[i].Suff, "Error create shader");
      break;
    }

    // Attach text to shader
    const CHAR *txt = TxtFromShd[i].c_str();
    glShaderSource(Shd[i].Id, 1, &txt, nullptr);

    // Compile shader
    glCompileShader(Shd[i].Id);
    glGetShaderiv(Shd[i].Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      CHAR error[3078];
    
      // Compile error
      glGetShaderInfoLog(Shd[i].Id, sizeof(error), &res, error);
      SaveLog(ShaderDirectoryName, Shd[i].Suff, error);
      IsOK = FALSE;
      break;
    }
  }

  if (IsOK)
    // Initializing of program - shaders collection
    if ((Prg = glCreateProgram()) == 0)
    {
      IsOK = FALSE;
      SaveLog(ShaderDirectoryName, "PROG", "ErrorCreateProgram");
    }
    else
    {
      // Attach shaders to program
      for (INT i = 0; i < NumOfShaders; i++)
        if (Shd[i].Id != 0)
          glAttachShader(Prg, Shd[i].Id);
      // Compose program
      glLinkProgram(Prg);
      glGetProgramiv(Prg, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        CHAR error[3078];
  
        // Compiling error
        glGetProgramInfoLog(Prg, sizeof(Buf), &res, error);
        SaveLog(ShaderDirectoryName, "PROG", error);
        IsOK = FALSE;
      }
    }
  
  // Error handle
  if (!IsOK)
  {
    for (INT i = 0; i < NumOfShaders; i++)
      if (Shd[i].Id != 0)
      {
        if (Prg != 0)
          glDetachShader(Prg, Shd[i].Id);
        glDeleteShader(Shd[i].Id);
      }
    if (Prg != 0)
      glDeleteProgram(Prg);
  
    return 0;
  }

  return Prg;
} /* End of 'figl::shader_manager::Load' function */

/* Free shader from memory function.
 * ARGUMENTS:
 *   - shader program id:
 *       UINT ProgId;
 * RETURNS: None.
 */
VOID figl::shader_manager::Delete( UINT ProgId )
{
  INT n;
  UINT shdrs[5];

  if (ProgId == 0)
    return;

  // Get attached shaders
  glGetAttachedShaders(ProgId, 5, &n, shdrs);

  // Deleting
  for (INT i = 0; i < n; i++)
  {
    glDetachShader(ProgId, shdrs[i]);
    glDeleteShader(shdrs[i]);
  }
  glDeleteProgram(ProgId);
} /* End of 'figl::shader_manager::Delete' function */

/* Shader manager initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID figl::shader_manager::Init( VOID )
{
  Create("DEFAULT");
} /* End of 'figl::shader_manager::Init' function */

/* Shader manager deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID figl::shader_manager::Close( VOID )
{
  for (auto sh : Stock)
  {
    Delete(sh.second->ProgId);
    delete sh.second;
  }
} /* End of 'figl::shader_manager::Close' function */

/* Add shader to stock from file function.
 * ARGUMENTS: 
 *   - reference on shader file name:
 *       const std::string &ShaderDirectoryName;
 * RETURNS:
 *   (UINT) pointer on shader;
 */
figl::shader * figl::shader_manager::Create( const std::string ShaderDirectoryName )
{
  shader *shd;

  if ((shd = Find(ShaderDirectoryName)) == nullptr)
  {
    shd = new shader;

    shd->ProgId = Load(ShaderDirectoryName);

    Add(ShaderDirectoryName, shd);
  }
  return shd;
} /* End of 'figl::shader_manager::Add' function */

/* Update loaded shaders.
 * ARGUMENTS: None
 * RETURNS: None.
 */
VOID figl::shader_manager::Update( VOID )
{
  std::vector<std::string> ShdNames;
  INT i = 0;
  for (auto sh : Stock)
  {
    Delete(sh.second->ProgId);
    ShdNames.push_back(sh.first);
    delete sh.second;
  }

  for (auto name : ShdNames)
    Stock.erase(name);

  for (auto name : ShdNames)
    Create(name);
} /* End of 'figl::shader_manager::Update' function */

/* END OF 'SHADER.CPP' FILE */