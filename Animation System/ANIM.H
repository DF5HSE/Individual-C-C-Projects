/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME    : ANIM.H
 * PURPOSE      : Animation system.
 *                Animation class declaration module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 23.08.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include <vector>

#include "win.h"
#include "timer.h"
#include "render.h"
#include "input.h"

/* Animation project namespace */
namespace figl
{
  /* Forward animation class declaration */
  class anim;

  /* Unit class declaration */
  class unit
  {
  public:
    /* Unit render function.
     * ARGUMENTS:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    virtual VOID Render( anim *Ani )
    {
    } /* End of 'Render' function */

    /* Unit response function.
     * ARGUMENTS:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    virtual VOID Response( anim *Ani )
    {
    } /* End of 'Response' function */

    /* Unit class destructor.
     * ARGUMENTS: None.
     */
    virtual ~unit( VOID )
    {
    } /* Enf of '~unit' function */
  }; /* End of 'unit' class */

  /* Animation class declaration */
  class anim : public win, public timer, public render, public input
  {
  private:
    std::vector<unit *> Units;
  public:
    /* Animation class constructor.
     * ARGUMENTS: None.
     */
    anim( VOID );

    /* Animation class destructor.
     * ARGUMENTS: None.
     */
    ~anim( VOID );

    /* Animation render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID );

    /* Do exit function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID DoExit( VOID );

    /* Singletone creation function
     * ARGUMENTS: None.
     * RETURNS:
     *   (anim &) mention to class instance.
     */
    static anim & GetInstance( VOID );

    /* Add unit by changing operator << function.
     * ARGUMENTS:
     *   -  pointer on unit for adding:
     *        unit * Unit;
     * RETURNS:
     *   (anim &) self reference.
     */
    anim & operator<<( unit * Unit )
    {
      Units.push_back(Unit);
      return *this;
    } /* End of 'operftor<<' function */

    /***
    * Virtual functions for window customization
    ***/

    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID )
    {
      Shaders.Init();
      Materials.Init();
    } /* End of 'Init' function */

    /* Deinitialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID )
    {
    } /* End of 'Close' function */

    /* Change window size handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID )
    {
      render::Resize(win::FrameW, win::FrameH);
      Render();
      CopyFrame();
    } /* End of 'Resize' function */

    /* Erase background handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Erase( HDC hDC )
    {
    } /* End of 'Erase' function */

    /* Paint window content function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Paint( HDC hDC )
    {
      Render();
      CopyFrame();
    } /* End of 'Paint' function */

    /* Timer handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Timer( VOID )
    {
      Render();
      render::CopyFrame();
    } /* End of 'Timer' function */

    /* Activate handle function.
     * ARGUMENTS:
     *   - activation window flag:
     *       BOOL IsActive;
     * RETURNS: None.
     */
    VOID Activate( BOOL IsActive )
    {
    } /* End of 'Activate' function */

    /* Free CPU time handling function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Idle( VOID )
    {
      Render();
      CopyFrame();
    } /* End of 'Idle' function */
  }; /* End of 'anim' class */
} /* end of 'figl' namespace */
#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */