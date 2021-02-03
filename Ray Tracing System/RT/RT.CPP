/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : RT.CPP
 * PURPOSE     : Ray tracing project.
 *               Intersection class implementation module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 26.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "rt.h"
#include "SHAPES/shapes.h"

/* Default intr class constructor.
 * ARGUMENTS: None
 */
firt::intr::intr( VOID ) : IsP(FALSE), IsN(FALSE), IsEnter(FALSE)
{
} /* End of 'firt::intr::intr function */

/* Intr class constructor
 * ARGUMENTS:
 *   - pointer on shape:
 *       shape *Sph;
 *   - t coefficient:
 *       DBL T;
 *   - ray enters into object shape flag:
 *       BOOL IsEnter;
 */
firt::intr::intr( shape *Shp, DBL T, BOOL IsEnter = TRUE ) : Shp(Shp), T(T), IsEnter(IsEnter), IsN(FALSE), IsP(FALSE)
{
} /* End of 'firt::intr::intr' function */

/* Intr class constructor
 * ARGUMENTS:
 *   - pointer on shape:
 *       shape *Sph;
 *   - t coefficient:
 *       DBL T;
 *   - ray enters into object shape flag:
 *       BOOL IsEnter;
 *   - link on normal vector:
 *       const vec &Norm;
 */
firt::intr::intr( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm ) : Shp(Shp), T(T), IsEnter(IsEnter), N(Norm), IsN(TRUE), IsP(FALSE)
{
} /* End of 'firt::intr::intr' function */

/* Intr class constructor
 * ARGUMENTS:
 *   - pointer on shape:
 *       shape *Sph;
 *   - t coefficient:
 *       DBL T;
 *   - ray enters into object shape flag:
 *       BOOL IsEnter;
 *   - link on normal vector:
 *       const vec &Norm;
 *   - link on point of intersection:
 *       const vec &Point;
 */
firt::intr::intr( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm, const vec &Point ) : Shp(Shp), T(T), IsEnter(IsEnter), N(Norm), P(Point),
                  IsN(TRUE), IsP(TRUE)
{
} /* End of 'firt::intr::intr' function */

/* Set intersection class constructor
 * ARGUMENTS:
 *   - pointer on shape:
 *       shape *Sph;
 *   - t coefficient:
 *       DBL T;
 *   - ray enters into object shape flag:
 *       BOOL IsEnter;
 * RETURNS: None.
 */
VOID firt::intr::Set( shape *Shp, DBL T, BOOL IsEnter = TRUE)
{
  this->Shp = Shp;
  this->T = T;
  this->IsEnter = IsEnter;
  this->IsN = FALSE;
  this->IsP = FALSE;
} /* End of 'firt::intr::Set' function */

/* Set intersection class constructor
 * ARGUMENTS:
 *   - pointer on shape:
 *       shape *Sph;
 *   - t coefficient:
 *       DBL T;
 *   - ray enters into object shape flag:
 *       BOOL IsEnter;
 *   - link on normal vector:
 *       const vec &Norm;
 * RETURNS: None.
 */
VOID firt::intr::Set( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm)
{
  this->Shp = Shp;
  this->T = T;
  this->IsEnter = IsEnter;
  this->N = Norm;
  this->IsN = TRUE;
  this->IsP = FALSE;
} /* End of 'firt::intr::Set' function */

/* Set intersection class constructor
 * ARGUMENTS:
 *   - pointer on shape:
 *       shape *Sph;
 *   - t coefficient:
 *       DBL T;
 *   - ray enters into object shape flag:
 *       BOOL IsEnter;
 *   - link on normal vector:
 *       const vec &Norm;
 *   - link on point of intersection:
 *       const vec &Point;
 * RETURNS: None.
 */
VOID firt::intr::Set( shape *Shp, DBL T, BOOL IsEnter, const vec &Norm, const vec &Point )
{
  this->Shp = Shp;
  this->T = T;
  this->IsEnter = IsEnter;
  this->N = Norm;
  this->IsN = TRUE;
  this->P = Point;
  this->IsP = TRUE;
} /* End of 'firt::intr::Set' function */

/* END OF 'RT.CPP' FILE */
