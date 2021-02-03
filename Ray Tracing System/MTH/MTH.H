/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MTH.H
 * PURPOSE     : Math support.
 *               Finale module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 31.08.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __MTH_H_
#define __MTH_H_

#include <vector>

#include "vec.h"
#include "matr.h"
#include "camera.h"
#include "ray.h"

/* Type defenition */
typedef mth::vec<DBL> vec;
typedef mth::vec2<DBL> vec2;
typedef mth::vec4<DBL> vec4;
typedef mth::matr<DBL> matr;
typedef mth::camera<DBL> camera;
typedef mth::ray<DBL> ray;

/* Math support namespace */
namespace mth
{
  template<typename type = DBL>
    /* Solving of equation of 4 degree function.
     * ARGUMENTS:
     *   - equation's coefficients:
     *       const type &A, &B, &C, &D, &E;
     *   - pointer on array of solutions:
     *       std::vector<type> *Sols;
     */
    VOID Equation4( const type &A, const type &B, const type &C, const type &D, const type &E, std::vector<type> *Sols )
    {
      type a1, b1, c1, P, Q, R, U, y, W, x;
      BOOL IsEval = FALSE;

      a1 = -3 * B * B / 8 / A / A + C / A;
      b1 = B * B * B / 8 / A / A / A - B * C / 2 / A / A + D / A;
      c1 = -3 * pow(B, 4) / 256 / pow(A, 4) + B * B * C / 16 / pow(A, 3) - B * D / 4 / A / A + E / A;

      P = -a1 * a1 / 12 - c1;
      Q = -pow(a1, 3) / 108 + a1 * c1 / 3 - b1 * b1 / 8;
      R = -Q / 2 + sqrt(Q * Q / 4 + pow(P, 3) / 27);
      U = pow(R, 1.0 / 3);
      if (U == 0)
        y = -5.0 / 6 * a1 + U - pow(Q, 1 / 3);
      else
        y = -5.0 / 6 * a1 + U - P / 3 / U;
      W = sqrt(a1 + 2 * y);

      /* First solution */
      x = -B / 4 / A + (W + sqrt(-(3 * a1 + 2 * y + 2 * b1 / W))) / 2;

      for (auto s : *Sols)
        if (s == x)
          IsEval = TRUE;
      if (!IsEval)
        Sols->push_back(x);

      /* Second solution */
      x = -B / 4 / A + (W - sqrt(-(3 * a1 + 2 * y + 2 * b1 / W))) / 2;

      for (auto s : *Sols)
        if (s == x)
          IsEval = TRUE;
      if (!IsEval)
        Sols->push_back(x);
      IsEval = FALSE;

      /* Third solution */
      x = -B / 4 / A + (-W + sqrt(-(3 * a1 + 2 * y - 2 * b1 / W))) / 2;

      for (auto s : *Sols)
        if (s == x)
          IsEval = TRUE;
      if (!IsEval)
        Sols->push_back(x);
      IsEval = FALSE;

      /* Forth solution */
      x = -B / 4 / A + (-W - sqrt(-(3 * a1 + 2 * y - 2 * b1 / W))) / 2;

      for (auto s : *Sols)
        if (s == x)
          IsEval = TRUE;
      if (!IsEval)
        Sols->push_back(x);
      IsEval = FALSE; 
    } /* End of 'Equation4' function */
} /* end of 'mth' namespace */

#endif /* __MTH_H_ */

/* END OF 'MTH.H' FILE */



