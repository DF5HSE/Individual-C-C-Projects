/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME    : RNDPRIMS.H
 * PURPOSE      : Render system.
 *                Primitives class declaration module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 08.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __RNDPRIMS_H_
#define __RNDPRIMS_H_

#include <vector>
#include "def.h"
#include "rndprim.h"

/* Animation project namespace */
namespace figl
{
  /* Primitives class declaration */
  class prims
  {
  public:
    std::vector<prim *> Prims; // Primitives vector

    /* Default primitve class constructor.
     * ARGUMENTS: None.
     */
    prims( VOID );

    /* Primitive class destructor.
     * ARGUMENTS: None.
     */
    ~prims(VOID);

    /* Load primitives function.
     * ARGUMENTS:
     *   - file name:
     *       const std::string &FileName;
     *   - transformation matrix:
     *       const mth::matr<FLT> &Transform;
     * RETURNS:
     *   (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL Load( const std::string &FileName, const mth::matr<FLT> &Transform );
  }; /* End of 'prims' class */
} /* end of 'figl' namespace */

#endif /* __RNDPRIMS_H_ */

/* END OF 'RNDPRIMS.H' FILE */