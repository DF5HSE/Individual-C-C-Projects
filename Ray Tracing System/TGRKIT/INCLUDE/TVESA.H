/***************************************************************
 * Copyright (C) 1997
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : TVESA.H
 * PURPOSE     : Tough VESA BIOS Extension (VBE) handle.
 *               VESA declaration module.
 * PROGRAMMER  : Vitaly A. Galinsky.
 * LAST UPDATE : 14.07.1997
 * NOTE        : Module prefix 'VBE'.
 *
 * Supported compiles:
 *   Turbo-C, Borland-C++ - memory model Large
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium
 */

#ifndef _TVESA_H_
#define _TVESA_H_

#include <commondf.h>

/***
 * VBE basic mode list
 ***/

/* VGA modes */
#define VBE_MODE640x350x16          0x10
#define VBE_MODE640x480x16          0x12

/* VESA modes */
/*
#define VBE_MODE640x350x16          0x150
*/
#define VBE_MODE640x400x16          0x151
/*
#define VBE_MODE640x480x16          0x152
*/
#define VBE_MODE800x600x16          0x102
#define VBE_MODE1024x768x16         0x104
#define VBE_MODE1280x1024x16        0x106
#define VBE_MODE1600x1200x16        0x123

#define VBE_MODE320x200x256         0x153
#define VBE_MODE320x240x256         0x154
#define VBE_MODE320x400x256         0x155
#define VBE_MODE360x200x256         0x156
#define VBE_MODE360x240x256         0x157
#define VBE_MODE360x400x256         0x158
#define VBE_MODE640x350x256         0x11C
#define VBE_MODE640x400x256         0x100
#define VBE_MODE640x480x256         0x101
#define VBE_MODE800x600x256         0x103
#define VBE_MODE1024x768x256        0x105
#define VBE_MODE1280x1024x256       0x107
#define VBE_MODE1600x1200x256       0x124

#define VBE_MODE320x200x32768       0x10D
#define VBE_MODE320x240x32768       0x12D
#define VBE_MODE320x400x32768       0x12E
#define VBE_MODE360x200x32768       0x12F
#define VBE_MODE360x240x32768       0x130
#define VBE_MODE360x400x32768       0x131
#define VBE_MODE640x350x32768       0x11D
#define VBE_MODE640x400x32768       0x11E
#define VBE_MODE640x480x32768       0x110
#define VBE_MODE800x600x32768       0x113
#define VBE_MODE1024x768x32768      0x116
#define VBE_MODE1280x1024x32768     0x119
#define VBE_MODE1600x1200x32768     0x125

#define VBE_MODE320x200x65536       0x10E
#define VBE_MODE320x240x65536       0x132
#define VBE_MODE320x400x65536       0x133
#define VBE_MODE360x200x65536       0x134
#define VBE_MODE360x240x65536       0x135
#define VBE_MODE360x400x65536       0x136
#define VBE_MODE640x350x65536       0x11F
#define VBE_MODE640x400x65536       0x120
#define VBE_MODE640x480x65536       0x111
#define VBE_MODE800x600x65536       0x114
#define VBE_MODE1024x768x65536      0x117
#define VBE_MODE1280x1024x65536     0x11A
#define VBE_MODE1600x1200x65536     0x126

#define VBE_MODE320x200x16M         0x10F
#define VBE_MODE320x240x16M         0x137
#define VBE_MODE320x400x16M         0x138
#define VBE_MODE640x350x16M         0x121
#define VBE_MODE640x400x16M         0x122
#define VBE_MODE640x480x16M         0x112
#define VBE_MODE800x600x16M         0x115
#define VBE_MODE1024x768x16M        0x118
#define VBE_MODE1280x1024x16M       0x11B
#define VBE_MODE1600x1200x16M       0x127

#define VBE_MODE640x350x16M_A       0x142
#define VBE_MODE640x400x16M_A       0x143
#define VBE_MODE640x480x16M_A       0x128
#define VBE_MODE800x600x16M_A       0x129
#define VBE_MODE1024x768x16M_A      0x12A
#define VBE_MODE1280x1024x16M_A     0x12B
#define VBE_MODE1600x1200x16M_A     0x12B

/***
 * Description structures
 ***/

/* General video information
 * need for AX = 0x4F00 function
 * ES:DI - pointer to info block */
typedef struct tagvbeVBEINFOBLOCK
{
  /* VBE signature, for VBE 2.0 before call should be set
   * to 'VBE2' (512B block), after call - filled by 'VESA'
   * (< VBE 2.0) or 'VBE2' (for VBE 2.0) */
  CHAR  Signature[4];

  /* Version: LoByte.HiByte in BCD format (0x0102 - v.1.2) */
  WORD  Version;

  /* Real mode pointer to EOM string */
  DWORD OemStringPtr;

  /* 32 bit capabilities array:
   * D0 = 0  DAC is fixed width, with 6 bits per primary color
   *    = 1  DAC width is switchable, to 8 bits per primary color
   * D1 = 0  Controller is VGA compatible
   *    = 1  Controller is not VGA compatible
   * D2 = 0  Normal RAMDAC operation
   *    = 1  When progarmming lage blocks of information to the
   *         RAMDAC use blank bit in function 09h, i.e. RAMDAC
   *         recommends programming during blank period only
   * D3 - D31  - Reserved
   */
  BYTE  Capabilities[4];

  /* Real mode pointer to array of 16 bit modes,
   * 0xFFFF - end element */
  DWORD VideoModePtr;

  /***
   * Added for VBE v.1.1
   ***/

  /* Memory size in 64K blocks */
  WORD  TotalMemory;

  /***
   * Added for VBE 2.0
   ***/

  /* VBE implementation software revision level */
  WORD OemSoftwareRev;

  /* Pointer to Vedor String */
  DWORD OemVendorNamePtr;

  /* Pointer to Product Name String */
  DWORD OemProductNamePtr;
  /* Pointer to Product Revision String */
  DWORD OemProductRevPtr;

  /* Reserved for VBE implementation scratch areas */
  BYTE  Reserved[222];

  /* Data Area for OEM Strings */
  BYTE OemData[256];
} vbeVBEINFOBLOCK;

/* Specified in function 0x4F01 mode information */
typedef struct tagvbeMODEINFOBLOCK
{
  /* Madatory information for all VBE revisions */
  WORD  ModeAttributes;    /* Mode attributes:
                            * D0 = Mode supported by hardware
                            *      configuration
			    *    = 0 Mode not supported in hardware
			    *    = 1 Mode supported in hardware
			    * D1 = 1 Extended information after
                            *        BytesPerScanLine is present
			    * D2 = 1 TTY Output functions supported by
                            *        BIOS INT 0x10 (function like 0x0A,
                            *        0x0E)
                            * D3 = 0 Monochrome mode
			    *    = 1 Color mode
			    * D4 = 0 Text mode
			    *	 = 1 Graphics mode
                            * VBE 2.0*********************
			    * D5 = 1 VGA compatible mode
			    * D6 = 1 VGA compatible mode momory is
                            *        available
			    * D7 = 1 Linear frame buffer mode is
                            *        available
			    * D8 - D15 = Reserved */
  BYTE  BankAAttribute;    /* Bank A attributes
			    * D0 = 1 Window A is supported
			    * D1 = 1 Window A is readable
			    * D2 = 1 Window A is writeable
			    * D3 - D7	     Reserved */
  BYTE  BankBAttribute;    /* Bank B attributes (the same as A) */
  WORD  Granularity;       /* Bank granularity (bank bounding
                            * size) in KB */
  WORD  BankSize;          /* Bank size in KB */
  WORD  BankASegment;      /* Bank A start segment */
  WORD  BankBSegment;      /* Bank B start segment */
  DWORD SelectBankFuncPtr; /* Pointer to bank switch function:
                            *  FAR CALL,
                            *  IN:
                            *    BH = 00 - select bank
                            *    BH = 01 - query current bank
                            *    BL = 0, 1 - bank ID (A or B)
                            *    DX (if BH = 0) - bank number
                            *  OUT:
                            *    AH = 00 - successful, otherwise error
                            *    AL = 0x4F - function supported
                            *    DX = current or new bank number */
  WORD  BytesPerLine;      /* Bytes per scan line (logical) */
  /* Madatory information all VBE 1.2 and above
   * (if bit D1 in ModeAttributes is 1) */
  WORD  ScreenWidth;       /* Horizontal resolution in pixels
                            * (graphics mode) or chars (text modes) */
  WORD  ScreenHeight;      /* Vertical resolution in pixels or chars */
  BYTE  CharWidth;         /* Character cell width in pixels */
  BYTE  CharHeight;        /* Character cell height in pixels */
  BYTE  PlanesAmount;      /* Number of memory planes */
  BYTE  BitsPerPixel;      /* Bits per pixel */
  BYTE  GroupsAmount;      /* Number of lines groups:
                            *  for obtaining video offset of
                            *  scan line Y:
                            *    StartBank = Y mod GroupsAmount
                            *    Offset = (Y div NumberGroup) *
                            *             BytesPerLine */
  BYTE  MemoryModel;       /* Memory model type:
			    *  00h =  Text mode
			    *  01h =  CGA graphics
			    *  02h =  Hercules graphis
			    *  03h =  Planar
			    *  04h =  Packet pixel
			    *  05h =  Non-chain 4, 256 color
			    *  06h =  Direct Color
			    *  07h =  YUV
			    *  08h - 0Fh = Reserved, to the
                            *              defined by VESA
			    *  10h - FFh = To be defined by OEM
			    */
  BYTE  GroupSize;         /* Lines group size in KB (see
                            * GroupsAmount) */
  BYTE  LastPageNumber;    /* (Total images amount - 1) - complete
                            * display images that will fit into frame
                            * buffer */
  BYTE  Reserved;          /* Reserved for page function */
  /* Direct Color fields (required) for direct/6 and YUV/7 memory models */
  BYTE  RedMaskSize;       /* Size of direct color red mask in bits */
  BYTE  RedFieldPos;       /* Bits position of LSB of red mask */
  BYTE  GreenMaskSize;     /* Size of direct color green mask in bits */
  BYTE  GreenFieldPos;     /* Bits position of LSB  of green mask */
  BYTE  BlueMaskSize;      /* Size of direct color blue mask in bits */
  BYTE  BlueFieldPos;      /* Bits position of LSB  of blue mask */
  BYTE  RsvdMaskSize;      /* Size of direct color reserved mask in bits */
  BYTE  RsvdFieldPosition; /* Bits position of LSB  of reserved mask */
  BYTE  DirectColorModeInfo;/* Direct color mode attributes
			    * D0 = 0 Color ramp is fixed
			    *    = 1 Color ramp is programmable
			    * D1 = 0 Bits in 'Rsvd***' field are reserved
			    *    = 1 Bits in 'Rsvd***' field are usable
                            *        by the application */
  /* Madatory information for VBE 2.0 and above */
  DWORD PhysBasePtr;       /* Phisical address for flat frame buffer */
  DWORD OffScreenMemOffset;/* Pointer to start of off screen memory */
  WORD  OffScreenMemSize;  /* Amount of off screen in 1K units */
  BYTE  Reserved1[206];    /* Remainded for ModeInfoBlock */
} vbeMODEINFOBLOCK;

#define VBE_IsModeGraphics(ModeInfo) \
    ((ModeInfo)->ModeAttributes & 0x10)

/***
 * Base VBE information obtain functions
 ***/

/* Obtain VBE controller information */
BOOL VBE_GetVBEInfo( vbeVBEINFOBLOCK *InfoBlock );

/* Obtain VBE screen mode information */
BOOL VBE_GetModeInfo( UINT Mode, vbeMODEINFOBLOCK *InfoBlock );

/***
 * Drawing trough VBE functions
 ***/

/*** Global information structures ***/

/* VBE controller information */
extern vbeVBEINFOBLOCK VBE_VBEInfoBlock;
/* VBE screen mode information */
extern vbeMODEINFOBLOCK VBE_ModeInfoBlock;
/* Current screen mode number */
extern UINT VBE_CurrentMode;

/*** Base drawing functions ***/

/* Enable VBE drawing mode function */
BOOL VBE_SetMode( UINT Mode );

/* Close VBE drawing mode function */
VOID VBE_Close( VOID );

/* Put pixel function */
VOID VBE_PutPixel( INT X, INT Y, DWORD Col );

/* Make color from triad RGB */
DWORD VBE_MakeColor( INT R, INT G, INT B );

/* Make dither color from triad RGB */
DWORD VBE_MakeDitherColor( INT X, INT Y, INT R, INT G, INT B );

/***
 * Output info functions
 ***/

/* Output common VBE info */
VOID VBE_OutVBEInfo( VOID );

#endif /* _TVESA_H_ */

/* END OF 'TVESA.H' FILE */
