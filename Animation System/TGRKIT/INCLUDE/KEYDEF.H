/***************************************************************
 * Copyright (C) 1992-1996
 *    Galinsky Software
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/*
 * FILE NAME   : KEYDEF.H
 * PURPOSE     : Some usefull key code & keyboard access
 *               definitions.
 * PROGRAMMER  : V.A.
 * LAST UPDATE : 05.08.1996
 * NOTE        : Updated from '17.04.1996' due to add conditions
 *               for Watcom C/C++.
 *               Updated from '21.07.1994' due to add
 *               prefix 'KEY'.
 *
 * Supported compiles:
 *   Turbo C/C++, Borland C/C++, Watcom C/C++
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium
 */

#ifndef _KEYDEF_H_
#define _KEYDEF_H_

#include <bios.h>

#ifdef __WATCOMC__
#define KEY_GetKey() (_bios_keybrd(0))
#define KEY_IsKeyAvail() (_bios_keybrd(1))
#else /* __WATCOMC__ */
#define KEY_GetKey() (bioskey(0))
#define KEY_IsKeyAvail() (bioskey(1))
#endif /* __WATCOMC__ */

#define KEY_F1       0x3B00
#define KEY_F2       0x3C00
#define KEY_F3       0x3D00
#define KEY_F4       0x3E00
#define KEY_F5       0x3F00
#define KEY_F6       0x4000
#define KEY_F7       0x4100
#define KEY_F8       0x4200
#define KEY_F9       0x4300
#define KEY_F0       0x4400

#define KEY_ALT_F1   0x6800
#define KEY_ALT_F2   0x6900
#define KEY_ALT_F3   0x6A00
#define KEY_ALT_F4   0x6B00
#define KEY_ALT_F5   0x6C00
#define KEY_ALT_F6   0x6D00
#define KEY_ALT_F7   0x6E00
#define KEY_ALT_F8   0x6F00
#define KEY_ALT_F9   0x7000
#define KEY_ALT_F0   0x7100

#define KEY_SHIFT_F1 0x5400
#define KEY_SHIFT_F2 0x5500
#define KEY_SHIFT_F3 0x5600
#define KEY_SHIFT_F4 0x5700
#define KEY_SHIFT_F5 0x5800
#define KEY_SHIFT_F6 0x5900
#define KEY_SHIFT_F7 0x5A00
#define KEY_SHIFT_F8 0x5B00
#define KEY_SHIFT_F9 0x5C00
#define KEY_SHIFT_F0 0x5D00

#define KEY_CTRL_F1  0x5E00
#define KEY_CTRL_F2  0x5F00
#define KEY_CTRL_F3  0x6000
#define KEY_CTRL_F4  0x6100
#define KEY_CTRL_F5  0x6200
#define KEY_CTRL_F6  0x6300
#define KEY_CTRL_F7  0x6400
#define KEY_CTRL_F8  0x6500
#define KEY_CTRL_F9  0x6600
#define KEY_CTRL_F0  0x6700

#define KEY_INS      0x5200
#define KEY_DEL      0x5300
#define KEY_HOME     0x4700
#define KEY_END      0x4F00
#define KEY_PGUP     0x4900
#define KEY_PGDN     0x5100

#define KEY_CTRL_HOME 0x7700
#define KEY_CTRL_PGUP 0x8400
#define KEY_CTRL_END  0x7500
#define KEY_CTRL_PGDN 0x7600

#define KEY_LEFT     0x4B00
#define KEY_UP       0x4800
#define KEY_DOWN     0x5000
#define KEY_RIGHT    0x4D00

#define KEY_ENTER    0x1C0D
#define KEY_BS       0x0E08
#define KEY_TAB      0x0F09
#define KEY_BTAB     0x0F00

#define KEY_ESC      0x011B

#define KEY_SHIFT_LEFT  0x4B34
#define KEY_SHIFT_UP    0x4838
#define KEY_SHIFT_DOWN  0x5032
#define KEY_SHIFT_RIGHT 0x4D36
#define KEY_SHIFT_HOME  0x4737
#define KEY_SHIFT_END   0x4F31
#define KEY_SHIFT_PGUP  0x4939
#define KEY_SHIFT_PGDN  0x5133
#define KEY_SHIFT_INS   0x5230
#define KEY_SHIFT_DEL   0x532E

#endif /* _KEYDEF_H_ */

/* END OF 'KEYDEF.H' FILE */
