/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MTHDEF.H
 * PURPOSE     : Math support.
 *               Definition module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 24.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __MTHDEF_H_
#define __MTHDEF_H_

#include <cmath>
#include <commondf.h>

/* Types defenition */
typedef double DBL;
typedef float FLT;

/* Math support namespace */
namespace mth
{
  /* Forward declaration of 3D space vector, matrix, ray and camera classes */
  template<class type>
    class matr;
  template<class type>
    class vec;
  template<class type>
    class vec2;
  template<class type>
    class vec4;
  template<class type>
    class ray;
  template<class type>
    class camera;

  /* Number PI */
  const DBL PI = 3.14159265358979323846;

  /* Translate from degrees to radian function.
   * ARGUMENTS:
   *   - number in degrees:
   *       const type1 A;
   * RETURNS:
   *   (type2) number in radian.
   */
  template<typename type1, typename type2>
    type2 Degree2Radian( const type1 A )
    {
      return A * PI / 180.0;
    } /* End of 'Degree2Radian' function */

  /* Translate from radian to degrees function.
   * ARGUMENTS:
   *   - number in radian:
   *       const type1 A;
   * RETURNS:
   *   (type2) number in degrees.
   */
  template<typename type1, typename type2>
    type2 Radian2Degree( const type1 A )
    {
      return A / PI * 180.0;
    } /* End of 'Radian2Degree' function */
} /* end of 'mth' namespace */

#endif /* __MTHDEF_H_ */

/* END OF 'MTHDEF.H' FILE */


