/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME    : RNDPRIM.CPP
 * PURPOSE      : Render system.
 *                Primitives class implementation module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 12.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "render.h"

/* Default primitve class constructor.
 * ARGUMENTS: None.
 */
figl::prim::prim( VOID )
{
} /* End of 'figl::prim::prim' function */

/* Primitive class constructor.
 * ARGUMENTS:
 *   - type of primitive:
 *       const prim_type NewType;
 *   - link on vertex vector:
 *       std::vector<VERTEX> &V;
 *   - link on indexes vector:
 *       std::vector<INT> &I;
 */
figl::prim::prim( const prim_type NewType, const std::vector<VERTEX> &V, const std::vector<INT> &I )
{
  Type = NewType;
  Transform = matr::Identity();
  VertexCounter = V.size();
  IndexCounter = I.size();

  FLT x = 65535, y = 65536, z = 65536;
  for (INT i = 0; i < V.size(); i++)
    Vertexes.push_back(V[i].P);

  for (std::vector<vec>::iterator vert = Vertexes.begin(); vert != Vertexes.end(); ++vert)
  {
    if ((*vert)[0] < x)
      x = (*vert)[0];
    if ((*vert)[1] < y)
      y = (*vert)[1];
    if ((*vert)[2] < z)
      z = (*vert)[2];
  }
  MinBB = vec(x, y, z);

  for (std::vector<vec>::iterator vert = Vertexes.begin(); vert != Vertexes.end(); ++vert)
  {
    if ((*vert)[0] > x)
      x = (*vert)[0];
    if ((*vert)[1] > y)
      y = (*vert)[1];
    if ((*vert)[2] > z)
      z = (*vert)[2];
  }
  MaxBB = vec(x, y, z);

  glGenBuffers(1, &VBuf);
  glGenVertexArrays(1, &VA);

  glBindVertexArray(VA);
  glBindBuffer(GL_ARRAY_BUFFER, VBuf);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX) * V.size(), &V[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)0); // Position
  glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)sizeof(vec)); // Texture coordinates
  glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)(sizeof(vec) + sizeof(vec2))); // Normal
  glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)(sizeof(vec) + sizeof(vec2) + sizeof(vec))); // Color

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);

  glBindVertexArray(0);
  if (IndexCounter != 0)
  {
    glGenBuffers(1, &IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * I.size(), &I[0], GL_STATIC_DRAW);
  }
  else
    IBuf = 0;
} /* End of 'figl::prim::prim' function */

/* Primitive class destructor.
 * ARGUMENTS: None.
 */
figl::prim::~prim( VOID )
{
  glBindVertexArray(VA);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &VBuf);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &VA);

  glDeleteBuffers(1, &VA);
} /* End of 'figl::prim::~prim' function */
/* END OF 'RNDPRIM.CPP' FILE */
