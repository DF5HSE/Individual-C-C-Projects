/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : LIGHT.H
 * PURPOSE     : Ray tracing project
 *               Light class declaration module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 26.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __LIGHT_H_
#define __LIGHT_H_

#include "../../def.h"

/* Project namespace */
namespace firt
{
  /* Forward shader_data class declaration */
  class shade_data;

  /* Light attenuation class declaration */
  class light_attenuation
  {
  public:
    vec L;                     // Direction on light
    vec Color;                 // Light color
    DBL Cc, Cq, Cl;            // Coefficients
    DBL Distance, Distance2;   // Distance and square distance to point of shading
  }; /* End of 'light_attenuation' class */

  /* Light class declaration */
  class light
  {
  public:
    vec LightPos;   // Light position
    DBL Cc, Cq, Cl; // Coefficients
    vec Color;      // Light color

    /* Light class constructor.
     * ARGUMENTS:
     *   - light position:
     *       const vec &LightPos;
     *   - coefficients:
     *       const DBL &Cc, &Cq, &Cl;
     *   - light color:
     *       const vec &Color;
     */
    light( const vec &LightPos, const DBL &Cc, const DBL &Cq, const DBL &Cl, const vec &Color );

    /* Getting data from light function.
     * ARGUMENTS:
     *   - shading data:
     *       const shade_data &Shd;
     *   - pointer on light attenuation:
     *       light_attenuation *Att;
     * RETURNS:
     *   (BOOL) light has attenuation coefficients - TRUE, else - FALSE.
     */
    BOOL GetData( shade_data Shd, light_attenuation *Att );
  }; /* End of 'light' class*/
} /* end of 'firt' namespace*/

#endif /* __LIGHT_H_ */

/* END OF 'LIGHT.H' FILE */