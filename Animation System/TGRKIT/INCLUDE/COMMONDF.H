/***************************************************************
 * Copyright (C) 1992-2003
 *    Galinsky Software
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : COMMONDF.H
 * PURPOSE     : Temporary OS depended implementation.
 * PROGRAMMER  : Vitaly Galinsky.
 * LAST UPDATE : 14.12.2003 (from 22.02.2000)
 * NOTE        : None (partial module prefix 'COM')
 *
 * Supported compiles:
 *   Turbo C/C++, Borland C++ - memory model Large.
 *   Watcom C/C++ - memory model Flat (32-bit protected mode
 *       with DOS4GW DOS extender), v.9-50 and later.
 *   and OpenGL
 *
 * No part of this file may be changed without agreement of
 * Vitaly A. Galinsky personally and Computer Graphics Support
 * Group of 30 Phys-Math Gymnasium.
 */

#ifndef _WWWCOMMONDF_H_
#define _WWWCOMMONDF_H_

#ifdef WIN32
#pragma warning(disable : 4200 4244 4013 4018 4115 4761 4127 4305)
#pragma warning(error : 4016 4027 4701)
#include <wcomdf.h>
#include <windows.h>
#else /* WIN32 */
#include <commondf\commondf.h>
#endif /* WIN32 */

#endif /* _WWWCOMMONDF_H_ */

/* END OF 'COMMONDF.H' FILE */
