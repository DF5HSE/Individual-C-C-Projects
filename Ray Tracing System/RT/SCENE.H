/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SCENE.H
 * PURPOSE     : Ray tracing project
 *               Scene class declaration module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 01.09.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __SCENE_H_
#define __SCENE_H_

#include "../def.h"
#include "IMAGE/image.h"
#include "SHAPES/shapes.h"
#include "LIGHT/light.h"
#include "rt.h"

/* Project namespace */
namespace firt
{
  /* Shading data class declaration */
  class shade_data : public intr
  {
  public:
    material Mtl;     // Material
    environment Envi; // Environment

    /* Shade_data class constructor.
     * ARGUMENTS:
     *   - pointer on intersection:
     *       intr *Intr;
     */
    shade_data( intr *Intr );
  }; /* End of 'shade_data' class */

  /* Scene class declaration */
  class scene
  {
  private:
    INT CurrentLevel = 0, MaxLevel = 12; // Levels of recurtion

  public:
    shape_list SList;                                         // List of shapes
    std::vector<light *> LList;                               // List of lights
    vec Background = vec(0.3, 0.5, 0.7), Ambient = vec(0.99); // Backgroun and ambient colors
    // Thresolds
    DBL Thresold = 0.000001;
    vec ColorThresold = vec(1.0 / 256);
    environment AirEnvi = environment(0, 1.001); // Air environment

    /* Default scene class constructor.
     * ARGUMENTS: None.
     */
    scene( VOID );

    /* Render scene function.
     * ARGUMENTS:
     *   - link on camera:
     *       camera &Cam;
     *   - pointer on image for render:
     *       image *Img;
     *   - part of rendring image:
     *       INT PartOfImg;
     *   - number of parts of image:
     *       INT NumOfParts;
     * RETURNS: None.
     */
    VOID Render( camera &Cam, image *Img, INT PartOfImg, INT NumOfParts );

    /* Tracing ray function.
     * ARGUMENTS:
     *   - ray for tracing:
     *       const ray &R;
     *   - environment:
     *       const environment &Envi;
     *   - weight:
     *     const vec &Weight;
     * RETURNS:
     *   (vec) color.
     */
    vec Trace( const ray &R, const environment &Envi, const vec &Weight );

    /* Shade point function.
     * ARGUMENTS:
     *   - link on direction of ray vector:
     *       const vec &V;
     *   - pointer on intersection:
     *       intr *Intr;
     *   - around environment:
     *       const environment &Envi;
     *   - weight:
     *       const vec &Weight;
     * RETURNS:
     *   (vec) color.
     */
    vec Shade( const vec &V, intr *Intr, const environment &Envi, const vec &Weight );

    /* Changing operator << for adding shape to scene.
     * ARGUMENTS:
     *   - pointer on shape:
     *       shape *Shp;
     * RETURNS:
     *   (scene &) link on scene class;
     */
    scene & operator<<( shape *Shp );

    /* Changing operator << for adding light to scene.
     * ARGUMENTS:
     *   - pointer on light:
     *       light *Light;
     * RETURNS:
     *   (scene &) link on scene class;
     */
    scene & operator<<( light *Light );
  } /* End of 'scene' class */;
} /* end of 'firt' namespace */
#endif /* __SCENE_H_ */

/* END OF 'SCENE.H' FILE */
