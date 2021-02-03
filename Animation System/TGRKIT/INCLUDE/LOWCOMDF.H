/***************************************************************
 * Copyright (C) 1997
 *    Galinsky Software
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : LOWCOMDF.H
 * PURPOSE     : Low-level useful macros and definitions.
 *               Registers, ports, interrupts and memory handle
 * PROGRAMMER  : Vitaly A.Galinsky
 * LAST UPDATE : 05.12.1997
 * NOTE        : Module prefix 'LOW'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium
 */

#ifndef _LOWCOMDF_H_
#define _LOWCOMDF_H_

#include <dos.h>

#include <commondf.h>

/***
 * Registers handle
 ***/

/* Obtain registers values */

#ifdef __BORLAND_LARGE__

#define LOW_GetAX()    (_AX)
#define LOW_GetBX()    (_BX)
#define LOW_GetCX()    (_CX)
#define LOW_GetDX()    (_DX)
#define LOW_GetAL()    (_AL)
#define LOW_GetAH()    (_AH)
#define LOW_GetBL()    (_BL)
#define LOW_GetBH()    (_BH)
#define LOW_GetCL()    (_CL)
#define LOW_GetCH()    (_CH)
#define LOW_GetDL()    (_DL)
#define LOW_GetDH()    (_DH)
#define LOW_GetSI()    (_SI)
#define LOW_GetDI()    (_DI)
#define LOW_GetSP()    (_SP)
#define LOW_GetBP()    (_BP)
#define LOW_GetFlags() (_FLAGS)
#define LOW_GetES()    (_ES)
#define LOW_GetDS()    (_DS)
#define LOW_GetSS()    (_SS)
#define LOW_GetCS()    (_CS)

#else /* __BORLAND_LARGE__ */

#ifdef __WATCOM_FLAT__

WORD LOW_GetAX( VOID );
#pragma aux LOW_GetAX = \
    value [AX]
WORD LOW_GetBX( VOID );
#pragma aux LOW_GetBX = \
    value [BX]
WORD LOW_GetCX( VOID );
#pragma aux LOW_GetCX = \
    value [CX]
WORD LOW_GetDX( VOID );
#pragma aux LOW_GetDX = \
    value [DX]
BYTE LOW_GetAL( VOID );
#pragma aux LOW_GetAL = \
    value [AL]
BYTE LOW_GetAH( VOID );
#pragma aux LOW_GetAH = \
    value [AH]
BYTE LOW_GetBL( VOID );
#pragma aux LOW_GetBL = \
    value [BL]
BYTE LOW_GetBH( VOID );
#pragma aux LOW_GetBH = \
    value [BH]
BYTE LOW_GetCL( VOID );
#pragma aux LOW_GetCL = \
    value [CL]
BYTE LOW_GetCH( VOID );
#pragma aux LOW_GetCH = \
    value [CH]
BYTE LOW_GetDL( VOID );
#pragma aux LOW_GetDL = \
    value [DL]
BYTE LOW_GetDH( VOID );
#pragma aux LOW_GetDH = \
    value [DH]
WORD LOW_GetSI( VOID );
#pragma aux LOW_GetSI = \
    value [SI]
WORD LOW_GetDI( VOID );
#pragma aux LOW_GetDI = \
    value [DI]
WORD LOW_GetSP( VOID );
#pragma aux LOW_GetSP = \
    value [SP]
WORD LOW_GetBP( VOID );
#pragma aux LOW_GetBP = \
    value [BP]
WORD LOW_GetES( VOID );
#pragma aux LOW_GetES = \
    "mov   AX, ES" \
    value [AX]
WORD LOW_GetDS( VOID );
#pragma aux LOW_GetDS = \
    "mov   AX, DS" \
    value [AX]
WORD LOW_GetSS( VOID );
#pragma aux LOW_GetSS = \
    "mov   AX, SS" \
    value [AX]
WORD LOW_GetCS( VOID );
#pragma aux LOW_GetCS = \
    "mov   AX, CS" \
    value [AX]
WORD LOW_GetFS( VOID );
#pragma aux LOW_GetFS = \
    "mov   AX, FS" \
    value [AX]
WORD LOW_GetGS( VOID );
#pragma aux LOW_GetGS = \
    "mov   AX, GS" \
    value [AX]

DWORD LOW_GetEAX( VOID );
#pragma aux LOW_GetEAX = \
    value [EAX]
DWORD LOW_GetEBX( VOID );
#pragma aux LOW_GetEBX = \
    value [EBX]
DWORD LOW_GetECX( VOID );
#pragma aux LOW_GetECX = \
    value [ECX]
DWORD LOW_GetEDX( VOID );
#pragma aux LOW_GetEDX = \
    value [EDX]
DWORD LOW_GetESI( VOID );
#pragma aux LOW_GetESI = \
    value [ESI]
DWORD LOW_GetEDI( VOID );
#pragma aux LOW_GetEDI = \
    value [EDI]
DWORD LOW_GetESP( VOID );
#pragma aux LOW_GetESP = \
    value [ESP]
DWORD LOW_GetEBP( VOID );
#pragma aux LOW_GetEBP = \
    value [EBP]

#else /* __WATCOM_FLAT__ */

#endif /* __WATCOM_FLAT__ */

#endif /* __BORLAND_LARGE__ */

/* Set registers values */

#ifdef __BORLAND_LARGE__

#define LOW_SetAX(Val)    (_AX = (Val))
#define LOW_SetBX(Val)    (_BX = (Val))
#define LOW_SetCX(Val)    (_CX = (Val))
#define LOW_SetDX(Val)    (_DX = (Val))
#define LOW_SetAL(Val)    (_AL = (Val))
#define LOW_SetAH(Val)    (_AH = (Val))
#define LOW_SetBL(Val)    (_BL = (Val))
#define LOW_SetBH(Val)    (_BH = (Val))
#define LOW_SetCL(Val)    (_CL = (Val))
#define LOW_SetCH(Val)    (_CH = (Val))
#define LOW_SetDL(Val)    (_DL = (Val))
#define LOW_SetDH(Val)    (_DH = (Val))
#define LOW_SetSI(Val)    (_SI = (Val))
#define LOW_SetDI(Val)    (_DI = (Val))
#define LOW_SetSP(Val)    (_SP = (Val))
#define LOW_SetBP(Val)    (_BP = (Val))
#define LOW_SetES(Val)    (_AX = (Val), _ES = _AX)
#define LOW_SetDS(Val)    (_AX = (Val), _DS = _AX)

#else /* __BORLAND_LARGE__ */

#ifdef __WATCOM_FLAT__

VOID LOW_SetAX( WORD Val );
#pragma aux LOW_SetAX = \
    parm [AX]
VOID LOW_SetBX( WORD Val );
#pragma aux LOW_SetBX = \
    parm [BX]
VOID LOW_SetCX( WORD Val );
#pragma aux LOW_SetCX = \
    parm [CX]
VOID LOW_SetDX( WORD Val );
#pragma aux LOW_SetDX = \
    parm [DX]
VOID LOW_SetAL( BYTE Val );
#pragma aux LOW_SetAL = \
    parm [AL]
VOID LOW_SetAH( BYTE Val );
#pragma aux LOW_SetAH = \
    parm [AH]
VOID LOW_SetBL( BYTE Val );
#pragma aux LOW_SetBL = \
    parm [BL]
VOID LOW_SetBH( BYTE Val );
#pragma aux LOW_SetBH = \
    parm [BH]
VOID LOW_SetCL( BYTE Val );
#pragma aux LOW_SetCL = \
    parm [CL]
VOID LOW_SetCH( BYTE Val );
#pragma aux LOW_SetCH = \
    parm [CH]
VOID LOW_SetDL( BYTE Val );
#pragma aux LOW_SetDL = \
    parm [DL]
VOID LOW_SetDH( BYTE Val );
#pragma aux LOW_SetDH = \
    parm [DH]
WORD LOW_SetSI( WORD Val );
#pragma aux LOW_SetSI = \
    parm [SI]
WORD LOW_SetDI( WORD Val );
#pragma aux LOW_SetDI = \
    parm [DI]
WORD LOW_SetSP( WORD Val );
#pragma aux LOW_SetSP = \
    parm [SP]
WORD LOW_SetBP( WORD Val );
#pragma aux LOW_SetBP = \
    parm [BP]
VOID LOW_SetES( WORD Val );
#pragma aux LOW_SetES = \
    "mov   ES, AX" \
    parm [AX]
VOID LOW_SetDS( WORD Val );
#pragma aux LOW_SetDS = \
    "mov   DS, AX" \
    parm [AX]

VOID LOW_SetEAX( DWORD Val );
#pragma aux LOW_SetEAX = \
    parm [EAX]
VOID LOW_SetEBX( DWORD Val );
#pragma aux LOW_SetEBX = \
    parm [EBX]
VOID LOW_SetECX( DWORD Val );
#pragma aux LOW_SetECX = \
    parm [ECX]
VOID LOW_SetEDX( DWORD Val );
#pragma aux LOW_SetEDX = \
    parm [EDX]
VOID LOW_SetESI( DWORD Val );
#pragma aux LOW_SetESI = \
    parm [ESI]
VOID LOW_SetEDI( DWORD Val );
#pragma aux LOW_SetEDI = \
    parm [EDI]
VOID LOW_SetESP( DWORD Val );
#pragma aux LOW_SetESP = \
    parm [ESP]
VOID LOW_SetEBP( DWORD Val );
#pragma aux LOW_SetEBP = \
    parm [EBP]

#else /* __WATCOM_FLAT__ */

#endif /* __WATCOM_FLAT__ */

#endif /* __BORLAND_LARGE__ */

/***
 * Potrs handle
 ***/

#ifdef __BORLAND_LARGE__

#define LOW_OutPortByte(PortNo, Value)  outportb(PortNo, Value)
#define LOW_OutPortWord(PortNo, Value)  outport(PortNo, Value)
#define LOW_InPortByte(PortNo)          inportb(PortNo)
#define LOW_InPortWord(PortNo)          inport(PortNo)

#else /* __BORLAND_LARGE__ */

#ifdef __WATCOM_FLAT__

VOID LOW_OutPortByte( WORD PortNo, BYTE Value );
#pragma aux LOW_OutPortByte = \
    "out   DX, AL" \
    parm [DX] [AL]
VOID LOW_OutPortWord( WORD PortNo, WORD Value );
#pragma aux LOW_OutPortWord = \
    "out   DX, AX" \
    parm [DX] [AX]
BYTE LOW_InPortByte( WORD PortNo );
#pragma aux LOW_InPortByte = \
    "in    AL, DX" \
    parm [DX] value [AL]
WORD LOW_InPortWord( WORD PortNo );
#pragma aux LOW_InPortWord = \
    "in    AX, DX" \
    parm [DX] value [AX]

#endif /* __WATCOM_FLAT__ */

#endif /* __BORLAND_LARGE__ */

/***
 * Interrupt handle
 ***/

#ifdef __BORLAND_LARGE__

#define LOW_GenIntr21h() (geninterrupt(0x21))
#define LOW_GenIntr10h() (geninterrupt(0x10))
#define LOW_GenIntr33h() (geninterrupt(0x33))

#else /* __BORLAND_LARGE__ */

#ifdef __WATCOM_FLAT__

VOID LOW_GenIntr21h( VOID );
#pragma aux LOW_GenIntr21h = \
    "int   21h" \
    modify [EAX EBX ECX EDX ESI EDI]
VOID LOW_GenIntr10h( VOID );
#pragma aux LOW_GenIntr10h = \
    "int   10h" \
    modify [EAX EBX ECX EDX ESI EDI]
VOID LOW_GenIntr33h( VOID );
#pragma aux LOW_GenIntr33h = \
    "int   33h" \
    modify [EAX EBX ECX EDX ESI EDI]

#endif /* __WATCOM_FLAT__ */

#endif /* __BORLAND_LARGE__ */

/***
 * Memory handle
 ***/

#ifdef __BORLAND_LARGE__

/* Obtain value from address */
#define LOW_PeekByte(Seg, Off) \
  (*((BYTE *)((((DWORD)(Seg)) << 16) | ((WORD)(Off)))))
#define LOW_PeekWord(Seg, Off) \
  (*((WORD *)((((DWORD)(Seg)) << 16) | ((WORD)(Off)))))
#define LOW_PeekDword(Seg, Off) \
  (*((DWORD *)((((DWORD)(Seg)) << 16) | ((WORD)(Off)))))

/* Set value to address */
#define LOW_PokeByte(Seg, Off, Val) \
  ((*((BYTE *)((((DWORD)(Seg)) << 16) | ((WORD)(Off))))) = (Val))
#define LOW_PokeWord(Seg, Off, Val) \
  ((*((WORD *)((((DWORD)(Seg)) << 16) | ((WORD)(Off))))) = (Val))
#define LOW_PokeDword(Seg, Off, Val) \
  ((*((DWORD *)((((DWORD)(Seg)) << 16) | ((WORD)(Off))))) = (Val))

/* Segment, offset and make address */
#define LOW_GetPhysSeg(Address)  (FP_SEG((VOID *)(Address)))
#define LOW_GetPhysOff(Address)  (FP_OFF((VOID *)(Address)))
#define LOW_MakePhysFP(Seg, Off) ((VOID *)MK_FP((WORD)(Seg), (WORD)(Off)))
#define LOW_GetSeg(Address)      (FP_SEG((VOID *)(Address)))
#define LOW_GetOff(Address)      (FP_OFF((VOID *)(Address)))
#define LOW_MakeFP(Seg, Off)     ((VOID *)MK_FP((WORD)(Seg), (WORD)(Off)))

#else /* __BORLAND_LARGE__ */

#ifdef __WATCOM_FLAT__

#if 0

/* Workable variant */
/* Obtain value from address */
#define LOW_PeekByte(Seg, Off) \
  (*((BYTE *)((((DWORD)(Seg)) << 4) | ((WORD)(Off)))))
#define LOW_PeekWord(Seg, Off) \
  (*((WORD *)((((DWORD)(Seg)) << 4) | ((WORD)(Off)))))
#define LOW_PeekDword(Seg, Off) \
  (*((DWORD *)((((DWORD)(Seg)) << 4) | ((WORD)(Off)))))

/* Set value to address */
#define LOW_PokeByte(Seg, Off, Val) \
  ((*((BYTE *)((((DWORD)(Seg)) << 4) | ((WORD)(Off))))) = (Val))
#define LOW_PokeWord(Seg, Off, Val) \
  ((*((WORD *)((((DWORD)(Seg)) << 4) | ((WORD)(Off))))) = (Val))
#define LOW_PokeDword(Seg, Off, Val) \
  ((*((DWORD *)((((DWORD)(Seg)) << 4) | ((WORD)(Off))))) = (Val))

#else /* 0 */

/* Obtain value from address */
BYTE LOW_PeekByte( WORD Seg, WORD Off );
#pragma aux LOW_PeekByte = \
    "shl   EBX, 4"      \
    "add   EBX, EAX"    \
    "mov   AL, [EBX]"   \
    parm [EBX] [EAX] value [AL]
WORD LOW_PeekWord( WORD Seg, WORD Off );
#pragma aux LOW_PeekWord = \
    "shl   EBX, 4"      \
    "add   EBX, EAX"    \
    "mov   AX, [EBX]"   \
    parm [EBX] [EAX] value [AX]
DWORD LOW_PeekDword( WORD Seg, WORD Off );
#pragma aux LOW_PeekDword = \
    "shl   EBX, 4"      \
    "add   EBX, EAX"    \
    "mov   EAX, [EBX]"  \
    parm [EBX] [EAX] value [EAX]

/* Set value to address */
VOID LOW_PokeByte( WORD Seg, WORD Off, BYTE Val );
#pragma aux LOW_PokeByte = \
    "shl   EBX, 4"      \
    "add   EBX, EAX"    \
    "mov   [EBX], CL"   \
    parm [EBX] [EAX] [CL]
VOID LOW_PokeWord( WORD Seg, WORD Off, WORD Val );
#pragma aux LOW_PokeWord = \
    "shl   EBX, 4"      \
    "add   EBX, EAX"    \
    "mov   [EBX], CX"   \
    parm [EBX] [EAX] [CX]
VOID LOW_PokeDword( WORD Seg, WORD Off, DWORD Val );
#pragma aux LOW_PokeDword = \
    "shl   EBX, 4"      \
    "add   EBX, EAX"    \
    "mov   [EBX], ECX"  \
    parm [EBX] [EAX] [ECX]

#endif /* 0 */

/* Segment, offset and make address */
WORD LOW_GetPhysSeg( VOID *Address );
#pragma aux LOW_GetPhysSeg = \
    "shr   EAX, 4"      \
    "and   EAX, 0F000h" \
    parm [EAX] value [AX]
WORD LOW_GetPhysOff( VOID *Address );
#pragma aux LOW_GetPhysOff = \
    parm [EAX] value [AX]
VOID * LOW_MakePhysFP( WORD Seg, WORD Off );
#pragma aux LOW_MakePhysFP = \
    "shl   EBX, 4"      \
    "add   EAX, EBX"    \
    parm [EBX] [EAX] value [EAX]
#define LOW_GetSeg(Address)      (FP_SEG(Address))
#define LOW_GetOff(Address)      (FP_OFF(Address))
#define LOW_MakeFP(Seg, Off)     ((VOID __far *)MK_FP((WORD)(Seg), (DWORD)(Off)))

#endif /* __WATCOM_FLAT__ */

#endif /* __BORLAND_LARGE__ */

/***
 * Set video mode by BOIS function (INT 10h, AH = 0, AL = Mode)
 ***/

#ifdef __BORLAND_LARGE__

#define LOW_SetVideoMode(AXValue) \
  ((_AX) = (AXValue), geninterrupt(0x10))

#else /* __BORLAND_LARGE__ */

#ifdef __WATCOM_FLAT__

VOID LOW_SetVideoMode( WORD AXValue );
#pragma aux LOW_SetVideoMode = \
    "int   10h"  \
    parm [EAX]

#endif /* __WATCOM_FLAT__ */

#endif /* __BORLAND_LARGE__ */

#endif /* _LOWCOMDF_H_ */

/* END OF 'LOWCOMDF.C' FILE  */
