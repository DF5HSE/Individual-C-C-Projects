/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SHAPES.H
 * PURPOSE     : Ray tracing project
 *               Shapes base classes declaration module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 26.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __SHAPES_H_
#define __SHAPES_H_

#include <vector>
#include "../../def.h"

/* Project namespace */
namespace firt
{
  /* Material class declaration */
  class material
  {
  public:
    vec Ka, Kd, Ks, KRefl, KTrans; // Coefficients ambience, diffuse, specular, reflaction and transparity
    DBL Kp;                        // Phong coefficient

    /* Default material class constructor.
     * ARGUMENTS: None.
     */
    material( VOID );

    /* Material class constructor.
     * ARGUMENTS:
     *   - coefficients ambience, diffuse, specular, reflaction and transparity:
     *       const vec &Ka, Kd, Ks, KRefl, KTrans;
     *   - Phong coefficient:
     *       const DBL &Kp;
     */
    material( const vec &Ka, const vec &Kd, const vec &Ks, const vec &KRefl, const vec &KTrans, const DBL &Kp );
  }; /* End of 'material' class */

  /* Environment class declaration */
  class environment
  {
  public:
    DBL Decay, NRefr; // Decay and refraction coefficients

    /* Default environment class constructor.
     * ARGUMENTS: None.
     */
    environment( VOID );

    /* Environment class constructor.
     * ARGUMENTS:
     *   - decay and refraction coefficients:
     *       const DBL &Decay, &NRefr;
     */
    environment( const DBL &Decay, const DBL &NRefr );
  }; /* End of 'environment' class */

  /* Forward intersection and shade data class declaration */
  class intr;
  class shade_data;
  /* Modifiers class declaration */
  class mod
  {
  public:
    /* Apply modifier function.
    * ARGUMENTS:
    *   - pointer on shading data:
    *       shade_data *Shd;
    * RETURNS: None.
    */
    virtual VOID Apply( shade_data *Shd )
    {
    } /* Enf of 'Apply' function */
  }; /* End of 'Mod' class*/
  typedef std::vector<intr> intr_list;
  /* Shape class declaration */
  class shape
  {
  public:
    mod Mods;
    material Mtl;     // Material
    environment Envi; // Environment
    BOOL IsTramsform; // Object transformation flag
    BOOL IsInverse;   // Object inverse flag
    matr Transform;   // Object transformation matrix

    /* Intesect ray and object function.
     * ARGUMENTS:
     *   - link on ray for intesect:
     *       const ray &R;
     *   - pointer on intersection:
     *       intr *Intr;
     * RETURNS:
     *   (BOOL) intesect exist - TRUE, else - FALSE.
     */
    virtual BOOL Intersect( const ray &R, intr *Intr )
    {
      return FALSE;
    } /* End of 'Intersect' function */

    /* Intesection of ray and objectes function.
     * ARGUMENTS:
     *   - ray for intesect:
     *       const ray &R;
     *   - link on vector of intesections:
     *       intr_list *Ilist;
     * RETURNS:
     *   (INT) number of intesections.
     */
    virtual INT AllIntersect( const ray &R, intr_list &Ilist )
    {
      return 0;
    } /* End of 'AllIntersect' function */

    /* Getting normal in intersection point function.
     * ARGUMENTS:
     *   - pointer on intersection:
     *       intr *Intr;
     * RETURNS: None.
     */
    virtual VOID GetNormal( intr *Intr )
    {
    } /* End of 'GetNormal' function */

    /* Existion of intesection of ray and object function.
     * ARGUMENTS:
     *   - ray for intesect:
     *       const ray &R;
     * RETURNS:
     *   (BOOL) intesection exist - TRUE, else - FALSE.
     */
    virtual BOOL IsIntersect( const ray &R )
    {
      return FALSE;
    } /* End of 'IsIntersect' function */

    /* Is something inside object function.
     * ARGUMENTS:
     *   - point of something:
     *       const vec &P;
     * RETURNS:
     *   (BOOL) TRUE - inside, FALSE - outside.
     */
    virtual BOOL IsInside( const vec &P )
    {
      return TRUE;
    } /* End of 'InsInside' function */

    /* Apply modifier function.
     * ARGUMENTS:
     *   - pointer on shading data:
     *       shade_data *Shd;
     * RETURNS: None.
     */
    virtual VOID Apply( shade_data *Shd )
    {
    } /* Enf of 'Apply' function */

  }; /* End of 'shape' class */

  /* Shape list class declaration */
  class shape_list : public shape
  {
  public:
    std::vector<shape *> Shapes; // List of shape

    /* Intesect ray and object function.
     * ARGUMENTS:
     *   - link on ray for intesect:
     *       const ray &R;
     *   - pointer on intersection:
     *       intr *Intr;
     * RETURNS:
     *   (BOOL) intesect exist - TRUE, else - FALSE.
     */
    BOOL Intersect( const ray &R, intr *Intr ) override;

    /* Intesection of ray and objectes function.
     * ARGUMENTS:
     *   - ray for intesect:
     *       const ray &R;
     *   - link on vector of intesections:
     *       intr_list *Ilist;
     * RETURNS:
     *   (INT) number of intesections.
     */
    INT AllIntersect( const ray &R, intr_list &Ilist ) override;

    /* Getting normal in intersection point function.
     * ARGUMENTS:
     *   - pointer on intersection:
     *       intr *Intr;
     * RETURNS: None.
     */
    VOID GetNormal( intr *Intr ) override;

    /* Existion of intesection of ray and object function.
     * ARGUMENTS:
     *   - ray for intesect:
     *       const ray &R;
     * RETURNS:
     *   (BOOL) intesection exist - TRUE, else - FALSE.
     */
    BOOL IsIntersect( const ray &R ) override;

    /* Is something inside object function.
    * ARGUMENTS:
    *   - point of something:
    *       const vec &P;
    * RETURNS:
    *   (BOOL) TRUE - inside, FALSE - outside.
    */
    BOOL IsInside( const vec &P ) override;
  } /* End of 'shape_list' class*/;
} /* end of 'firt' namespace */
#endif /* __SHAPES_H_ */

/* END OF 'SHAPES.H' FILE */
