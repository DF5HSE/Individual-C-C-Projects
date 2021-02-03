/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME    : TIMER.H
 * PURPOSE      : Animation system.
 *                Timer module.
 * PROGRAMMER   : CGSG'2018.
 *                Filippov Denis.
 * LAST UPDATE  : 21.07.2018.
 * NOTE         : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __TIMER_H_
#define __TIMER_H_

#include <string>

#include "def.h"

/* Animation project namespace */
namespace figl
{
  /* Timer class declaration */
  class timer
  {
  private:
    UINT64
      StartTime,        // Start program time
      OldTime,          // Time from program start to previous frame
      OldTimeFPS,       // Old time FPS measurement
      PauseTime,        // Time during pausee period
      TimePerSec,       // Time resolution
      FrameCounter;     // Frames counter
  public:
    FLT
      GlobalTime,       // Global time
      GlobalDeltaTime,  // Global interframe interval
      Time,             // Time with pause and interframe interval
      DeltaTime,        // Interframe interval
      FPS;               // Frames per second
    BOOL IsPause;       // Pause flag

    /* Timer class constructor.
     * ARGUMENTS: None.
     */
    timer( VOID )
    {
      LARGE_INTEGER t;

      QueryPerformanceFrequency(&t);
      TimePerSec = t.QuadPart;
      QueryPerformanceCounter(&t);
      StartTime = OldTime = OldTimeFPS = t.QuadPart;
      PauseTime = FrameCounter = 0;
      IsPause = FALSE;
    } /* End of 'timer' function */

    /* Response timer function.
     * ARGUMENTS: None.
     * RETURNS:None.
     */
    VOID Response( VOID )
    {
      LARGE_INTEGER t;
      QueryPerformanceCounter(&t);

      /* Global time */
      FrameCounter++;
      GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
      GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
      /* Time with pause */
      if (IsPause)
      {
        DeltaTime = 0;
        PauseTime += t.QuadPart - OldTime;
      }
      else
      {
        DeltaTime = GlobalDeltaTime;
        Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
      }
      OldTime = t.QuadPart;
      /* FPS */
      if (t.QuadPart - OldTimeFPS > TimePerSec)
      {
        std::string str;

        FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
        OldTimeFPS = t.QuadPart;
        str += "FPS: ";
        str += FPS;
      }
    } /* End of 'Response' function */
  }; /* End of 'timer' class */
} /* end of 'figl' namespace */

#endif /* __TIMER_H_ */

/* END OF 'TIMER.H' FILE */
