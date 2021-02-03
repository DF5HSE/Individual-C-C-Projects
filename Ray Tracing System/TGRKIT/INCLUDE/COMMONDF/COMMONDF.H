/***************************************************************
 * Copyright (C) 1992-1997
 *    Galinsky Software
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : COMMONDF.H
 * PURPOSE     : Basic type and macros definitions.
 * PROGRAMMER  : Vitaly Galinsky.
 * LAST UPDATE : 24.07.1997
 * NOTE        : Size 8668b
 *               Updated version from 03.10.1996, size 8195b
 *               Updated version from 05.08.1996, size 7928b
 *               Updated version from 29.02.1996, size 7222b
 *               which is updated version from 15.01.1996
 *               which is updated version from 29.05.1994
 *               (real date 26.11.1994), size 4061b
 *               which is updated version from 08.12.1993, size 1628b
 *               Update of 23.12.1995 was needed for change REAL
 *               to LDOUBLE.
 *               Update 15.01.1996 was needed for add to all macro
 *               function 'COM_' and structured types 'com'
 *               Update of 29.02.1996 was needed for change High to
 *               Height and add comRECT type.
 *               Update of 05.08.1996 was needed for:
 *                 update compiler checks (__***_***__ add)
 *                 structure field offset determination.
 *               Update of 03.10.1996 was needed for add COM_SQR and
 *                 COM_CUB macros.
 *               Update of 24.07.1997 was needed for correct UINT type
 *                 from 'unsigned short int' to 'unsigned int'
 *                 COM_CUB macros, add comAREA type and add end
 *                 comments.
 *               File prefix - 'COM'.
 *
 * Supported compiles:
 *   Turbo C/C++, Borland C++ - memory model Large.
 *   Watcom C/C++ - memory model Flat (32-bit protected mode
 *       with DOS4GW DOS extender), v.9-50 and later.
 *
 * No part of this file may be changed without agreement of
 * Vitaly A. Galinsky personally and Computer Graphics Support
 * Group of 30 Phys-Math Gymnasium.
 */

#ifndef _COMMONDF_H_
#define _COMMONDF_H_

/*
 * Define the _COMMON_TYPES_USE_DEFINE_ definition for
 * use #define besides typedef for type definition
 *
 * For example:
 * #define _COMMON_TYPES_USE_DEFINE_
 */

/* Check compiler and memory model */
#if !defined(__TURBOC__) && !defined(__BORLANDC__) && \
    !defined(__WATCOMC__)
# error Unknown compiler. Correct "COMMONDF.H" and others files, please.
#endif /* Compilers defines check */

#ifdef __TURBOC__
# ifndef __LARGE__
#   error For Turbo-C and Borland-C you should set "LARGE" memory model
# endif /* __LARGE__ */
#endif /* __TURBOC__ */

#ifdef __WATCOMC__
# ifndef __FLAT__
#   error For Watcom-C you should use "FLAT" memory model (DOS4GW)
# endif /* __FLAT__ */
#endif /* __WATCOMC__ */

/* Define appropriate macro for compiler determination */
#ifdef __TURBOC__
#define __BORLAND_LARGE__
#endif /* __TURBOC__ */

#ifdef __WATCOMC__
#define __WATCOM_FLAT__
#endif /* __WATCOMC__ */

/* NULL definition */
#ifndef NULL
#  if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
#    define NULL 0
#  else /* defined ... */
#    define NULL 0L
#  endif /* defined ... */
#endif /* NULL */

/* Empty data type */

#ifdef _COMMON_TYPES_USE_DEFINE_
# define  VOID     void
#else
  typedef void VOID;
#endif

/* Low level simple data types */
#ifdef _COMMON_TYPES_USE_DEFINE_
# define BYTE      unsigned char
# define WORD      unsigned short int
# define DWORD     unsigned long  int
# define SBYTE     signed   char
# define SWORD     signed   short int
# define SDWORD    signed   long  int
#else
  typedef unsigned char      BYTE;
  typedef unsigned short int WORD;
  typedef unsigned long  int DWORD;
  typedef signed   char      SBYTE;
  typedef signed   short int SWORD;
  typedef signed   long  int SDWORD;
#endif

/* Simple integer data types */
#ifdef _COMMON_TYPES_USE_DEFINE_
# define CHAR      char
# define SHORT     short int
# define INT       int
# define LONG      long int
#else
  typedef char      CHAR;
  typedef short int SHORT;
  typedef int       INT;
  typedef long int  LONG;
#endif

/* Signed/unsigned integer data types */
#ifdef _COMMON_TYPES_USE_DEFINE_
# define UCHAR     unsigned char
# define SCHAR     signed char
# define UINT      unsigned int
# define USHORT    unsigned short int
# define ULONG     unsigned long int
#else
  typedef unsigned char      UCHAR;
  typedef signed   char      SCHAR;
  typedef unsigned int       UINT;
  typedef unsigned short int USHORT;
  typedef unsigned long int  ULONG;
#endif

/* Size depended integer types */
#ifdef _COMMON_TYPES_USE_DEFINE_
# define INT8      signed   char
# define UINT8     unsigned char
# define INT16     signed   short int
# define UINT16    unsigned short int
# define INT32     signed   long  int
# define UINT32    unsigned long  int
#else
  typedef signed   char      INT8;
  typedef unsigned char      UINT8;
  typedef signed   short int INT16;
  typedef unsigned short int UINT16;
  typedef signed   long  int INT32;
  typedef unsigned long  int UINT32;
#endif

/* Boolean data type */
#ifdef _COMMON_TYPES_USE_DEFINE_
# define BOOL      short int
#else
  typedef short int BOOL;
#endif

/* Useful plane graphics data type */
/* 2D point description */
typedef struct tagcomPOINT2D
{
  INT X, Y;
} comPOINT2D;

/* 2D rectangle description */
typedef struct tagcomRECTANGLE
{
  INT X, Y;          /* Left upper corner position */
  INT Width, Height; /* Horizontal and vertical size */
} comRECTANGLE;

#ifdef _COMMON_TYPES_USE_DEFINE_
# define comRECT2D comRECTANGLE
# define comRECT comRECTANGLE
#else
  typedef comRECTANGLE comRECT2D;
  typedef comRECTANGLE comRECT;
#endif

/* 2D rectangular area description */
typedef struct tagcomAREA2D
{
  /* Border corners coordinates */
  INT Left, Top, Right, Bottom;
} comAREA2D;

#ifdef _COMMON_TYPES_USE_DEFINE_
# define comAREA comAREA2D
#else
  typedef comAREA2D comAREA;
#endif

/* Real data types */
#ifdef _COMMON_TYPES_USE_DEFINE_
# define FLOAT     float
# define DOUBLE    double
# define REAL      long double
#else
  typedef float       FLOAT;
  typedef double      DOUBLE;
  typedef long double LDOUBLE;
#endif

/* Some useful constants */
#define TRUE  1
#define FALSE 0

#define YES   1
#define NO    0

#define ON    1
#define OFF   0

#define SUCCESS  0
#define FAILURE -1

/* Useful common definitions */
#define COM_ABS(A)            (((A) > 0) ? (A) : (-(A)))
#define COM_SIGN(A)           (((A) > 0) ? (1) : (((A) < 0) ? (-1) : (0)))
#define COM_SWAP(A, B, C)     ((C) = (A), (A) = (B), (B) = (C))
#define COM_MAX(A, B)         (((A) > (B)) ? (A) : (B))
#define COM_MIN(A, B)         (((A) < (B)) ? (A) : (B))
#define COM_SQR(X)            ((X) * (X))
#define COM_CUB(X)            ((X) * (X) * (X))

/* Byte/word/dword conversions */
#define COM_LOBYTE(W) ((BYTE)(((WORD)(W))))
#define COM_HIBYTE(W) ((BYTE)((((WORD)(W) >> 8))))

#define COM_LOWORD(D) ((WORD)(((DWORD)(D))))
#define COM_HIWORD(D) ((WORD)((((DWORD)(D) >> 16))))

#define COM_LONGBYTE0(D) ((BYTE)(((WORD)(D))))
#define COM_LONGBYTE1(D) ((BYTE)((((WORD)(D) >> 8))))
#define COM_LONGBYTE2(D) ((BYTE)((((DWORD)(D) >> 16))))
#define COM_LONGBYTE3(D) ((BYTE)((((DWORD)(D) >> 24))))

#define COM_MAKEWORDLH(BL, BH) \
     ((WORD)((((WORD)((BYTE)(BH))) << 8) | (WORD)((BYTE)(BL))))

#define COM_MAKELONGLH(WL, WH) \
     ((DWORD)((((DWORD)((WORD)(WH))) << 16) | (DWORD)((WORD)(WL))))

#define COM_MAKELONG0123(B0, B1, B2, B3) \
     (DWORD)((((DWORD)((BYTE)(B3))) << 24) | \
             (((DWORD)((BYTE)(B2))) << 16) | \
             (((DWORD)((BYTE)(B1))) << 8) | \
               (DWORD)((BYTE)(B0)))

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

/* Compiler depended pointer data types modifiers */
#ifdef __WATCOM_FLAT__
# undef huge
# define huge
#endif /* __WATCOM_FLAT__ */

#endif /* _COMMONDF_H_ */

/* END OF 'COMMONDF.H' FILE */
