/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : RAY.H
 * PURPOSE     : Math support.
 *               Ray module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 25.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __RAY_H_
#define __RAY_H_

#include "mthdef.h"

/* Math support namespace */
namespace mth
{
  /* Ray class declaration */
  template<class type = DBL>
    class ray
    {
    private:
      vec<type> Org, Dir; // Origin of ray and ray direction
    public:
      /* Default ray class constructor.
       * ARGUMENTS: None.
       */
      ray( VOID )
      {
      } /* End of 'ray' function */

      /* Ray class constructor.
       * ARGUMENTS:
       *   - link on origin and direction:
       *       const vec<type> &O, &D;
       */
      ray( const vec<type> &O, const vec<type> &D ) : Org(O), Dir(D)
      {
        Dir.Normalize();
      } /* End of 'ray' function */

      /* Changing operator () for getting point on ray.
       * ARGUMENTS:
       *   - numbet t:
       *       type t;
       * RETURNS:
       *   (vec<type) point on ray.
       */
      vec<type> operator()( type t ) const
      {
        return Org + Dir * t;
      } /* End of 'operator()' function */

      /* Get ray origin function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec<type>) ray origin.
       */
      vec<type> GetOrg( VOID ) const
      {
        return Org;
      } /* End of 'GetOrg' function */

      /* Get ray direction function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec<type>) ray direction.
       */
      vec<type> GetDir( VOID ) const
      {
        return Dir;
      } /* End of 'GetDir' function */
    }; /* End of 'ray' class */
} /* end of 'mth' namespace */

#endif /* __RAY_H_ */
/* END OF 'RAY.H' FILE */



