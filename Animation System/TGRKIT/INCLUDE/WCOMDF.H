/***************************************************************
 * Copyright (C) 2003
 *    Galinsky Software
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/*
 * FILE NAME   : WCOMDF.H
 * PURPOSE     : Basic type and macros definitions.
 * PROGRAMMER  : Vitaly A. Galinsky.
 * LAST UPDATE : 26.01.2003 (from 22.02.2000)
 * NOTE        : MS-Windows version of COMMONDF.H
 *
 *
 * No part of this file may be changed without agreement of
 * Vitaly A. Galinsky personally and Computer Graphics Support
 * Group of 30 Phys-Math Gymnasium
 */

#ifndef _WCOMDF_H_
#define _WCOMDF_H_

/* Include base MS-Windows files */
#ifndef __WINDOWS_H
#include <windows.h>
#include <commdlg.h>
#endif /* __WINDOWS_H */

/* NULL definition */
#ifndef NULL
#  if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
#    define NULL 0
#  else
#    define NULL 0L
#  endif
#endif

/* Empty data type */

#ifndef VOID
  typedef void VOID;
#endif

/* Unsigned simple data types */
#ifndef BYTE
  typedef unsigned char      BYTE;
#endif
#ifndef WORD
  typedef unsigned short int WORD;
#endif
#ifndef DWORD
  typedef unsigned long int  DWORD;
#endif

/* Signed simple data types */
#ifndef SBYTE
  typedef signed char      SBYTE;
#endif
#ifndef SWORD
  typedef signed short int SWORD;
#endif
#ifndef SDWORD
  typedef signed long int  SDWORD;
#endif

/* Simple integer data types */
#ifndef CHAR
  typedef char      CHAR;
#endif
#ifndef SHORT
  typedef short int SHORT;
#endif
#ifndef INT
  typedef int       INT;
#endif
#ifndef LONG
  typedef long int  LONG;
#endif

/* Signed/unsigned integer data types */
#ifndef UCHAR
  typedef unsigned char      UCHAR;
#endif
#ifndef SCHAR
  typedef signed char        SCHAR;
#endif
#ifndef ULONG
  typedef unsigned long int  ULONG;
#endif
#ifndef SLONG
  typedef signed long int    SLONG;
#endif

/* Boolean data type */
/*
#ifndef BOOL
  typedef short int BOOL;
#endif
*/

/* Graphics data type */
typedef struct tagPOINT2D
{
  INT X, Y;
} POINT2D;

typedef struct tagRECTANGLE
{
  SWORD X, Y;
  SWORD  cxWidth, cyHeight;
} RECTANGLE;

/* Real data types */
#ifndef FLOAT
  typedef float       FLOAT;
#endif
#ifndef DOUBLE
  typedef double      DOUBLE;
#endif
#ifndef REAL
  typedef long double LDOUBLE;
#endif

/* Some constant */
#define TRUE  1
#define FALSE 0

#define YES   1
#define NO    0

#define ON    1
#define OFF   0

#define SUCCESS  0
#define FAILURE -1

/* Usefull definitions */
#define COM_ABS(A)            (((A)>0)?(A):(-(A)))
#define COM_SIGN(A)           (((A)>0)?(1):(((A)<0)?(-1):(0)))
#define COM_SWAP(A,B,Tmp)     ((Tmp)=(A),(A)=(B),(B)=(Tmp))
#define COM_MAX(A,B)          (((A)>(B))?(A):(B))
#define COM_MIN(A,B)          (((A)<(B))?(A):(B))
#define COM_SQR(X)            ((X) * (X))
#define COM_CUB(X)            ((X) * (X) * (X))

/* Byte/word conversions */
#ifndef COM_LOBYTE
#  define COM_LOBYTE(W) ((BYTE)(((WORD)(W))))
#endif
#ifndef COM_HIBYTE
#  define COM_HIBYTE(W) ((BYTE)((((WORD)(W)>>8))))
#endif

#ifndef COM_LOWORD
#  define COM_LOWORD(D) ((WORD)(((DWORD)(D))))
#endif
#ifndef COM_HIWORD
#  define COM_HIWORD(D) ((WORD)((((DWORD)(D)>>16))))
#endif

#ifndef COM_LONGBYTE0
#  define COM_LONGBYTE0(D) ((BYTE)(((WORD)(D))))
#  define COM_LONGBYTE1(D) ((BYTE)((((WORD)(D)>>8))))
#  define COM_LONGBYTE2(D) ((BYTE)((((DWORD)(D)>>16))))
#  define COM_LONGBYTE3(D) ((BYTE)((((DWORD)(D)>>24))))
#endif

#ifndef COM_MAKEWORDLH
#  define COM_MAKEWORDLH(BL,BH) \
            ((WORD)((((WORD)((BYTE)(BH)))<<8)| \
            (WORD)((BYTE)BL)))
#endif

#ifndef COM_MAKELONGLH
#  define COM_MAKELONGLH(WL,WH) \
            ((DWORD)((((DWORD)((WORD)(WH)))<<16)| \
            (DWORD)((WORD)WL)))
#endif

#ifndef COM_MAKELONG0123
#  define COM_MAKELONG0123(B0,B1,B2,B3) \
            (DWORD)((((DWORD)((BYTE)(B3)))<<24)| \
            (((DWORD)((BYTE)(B2)))<<16)| \
            (((DWORD)((BYTE)(B1)))<<8)| \
            (DWORD)((BYTE)B0))

/* Bits operations */
#define COM_SETBIT(Val, BitNo)   ((Val) |=  (1 << (BitNo)))
#define COM_RESETBIT(Val, BitNo) ((Val) &= ~(1 << (BitNo)))
#define COM_GETBIT(Val, BitNo)   ((Val) &   (1 << (BitNo)))
#define COM_SETBITS(Val, Bits)   ((Val) |=  (Bits))
#define COM_RESETBITS(Val, Bits) ((Val) &= ~(Bits))
#define COM_ISBITS(Val, Bits)    (((Val) & (Bits)) == (Bits))

/* Structure field offset determination */
#define COM_GetFieldOffset(StructureType, FieldName) \
    ((INT)(&(((StructureType *)0L)->FieldName)))

#endif

#endif /* _WCOMDF_H_ */

/* END OF 'WCOMDF.H' FILE */
