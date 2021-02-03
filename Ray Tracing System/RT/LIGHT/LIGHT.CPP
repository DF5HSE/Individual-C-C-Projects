/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : LIGHT.CPP
 * PURPOSE     : Ray tracing project
 *               Light class implementation module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 26.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "../scene.h"
#include "light.h"

/* Light class constructor.
 * ARGUMENTS:
 *   - light position:
 *       const vec &LightPos;
 *   - coefficients:
 *       const DBL &Cc, &Cq, &Cl;
 *   - light color:
 *       const vec &Color;
 */
firt::light::light( const vec &LightPos, const DBL &Cc, const DBL &Cq, const DBL &Cl, const vec &Color ) : LightPos(LightPos), Cc(Cc), Cq(Cq), Cl(Cl),
                    Color(Color)
{
} /* End of 'firt::light::light' function */

/* Getting data from light function.
 * ARGUMENTS:
 *   - shading data:
 *       const shade_data &Shd;
 *   - pointer on light attenuation:
 *       light_attenuation *Att;
 * RETURNS:
 *   (BOOL) light has attenuation coefficients - TRUE, else - FALSE.
 */
BOOL firt::light::GetData( shade_data Shd, light_attenuation *Att )
{
  Att->L = (LightPos - Shd.P).Normalizing();
  Att->Cc = Cc;
  Att->Cq = Cq;
  Att->Cl = Cl;
  Att->Distance2 = (LightPos - Shd.P).Length2();
  Att->Distance = sqrt(Att->Distance2);
  Att->Color = Color;
  return TRUE;
} /* End of 'firt::light::GetData' function */
/* END OF 'LIGHT.CPP' FILE */

