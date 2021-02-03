/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME    : RESMAN.H
 * PURPOSE      : Resource manager.
 *                Resource manager class declaration module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 14.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __RESMAN_H_
#define __RESMAN_H_

#include <map>
#include "def.h"

/* Animation project namespace */
namespace figl
{
  template<class type>
    /* Resource manager class declaration */
    class resource_manager
    {
    public:
      std::map<std::string, type *> Stock;

      /* Resource manager class constructor.
       * ARGUMENTS: None.
       */
      resource_manager( VOID )
      {
      } /* End of 'resource_manager' function */
    
      /* Resource manager class destructor.
       * ARGUMENTS: None.
       */
      ~resource_manager( VOID )
      {
        for (auto r : Stock)
          delete r.second;
      } /* End of '~resource_manager' function */

      /* Adding new resource function.
       * ARGUMENTS:
       *   - name of recouse:
       *       const std::string &Name;
       *   - pointer on resourse;
       *       type *Res;
       * RETURNS: None.
       */
      resource_manager & Add( const std::string &Name, type *Res )
      {
        Stock[Name] = Res;
        return *this;
      } /* End of 'Add' function */

      /* Find resouce function.
       * ARGUMENTS:
       *   - name of recouse:
       *       const std::string &Name;
       * RETURNS:
       *   (type *) pointer on resource.
       */
      type * Find( const std::string &Name )
      {
        if (Stock.find(Name) == Stock.end())
          return nullptr;
        return Stock[Name];
      } /* End of 'Find' function */
    }; /* End of 'resource_manager' class */
} /* end of 'figl' namespace */

#endif /* __RESMAN_H_ */

/* END OF 'RESMAN.H' FILE */