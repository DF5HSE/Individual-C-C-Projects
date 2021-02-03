/***************************************************************
 * Copyright (C) 2001
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : TGRP.H
 * PURPOSE     : Tough Graphics library.
 *               The main description header file.
 * PROGRAMMER  : CGSG'2001.
 * LAST UPDATE : 10.06.2001.
 * NOTE        : Module prefix 'TGR'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium
 */

#ifndef _TGRP_H_
#define _TGRP_H_

#include <commondf.h>

/***
 * Basic geometry representation types
 ***/

/* Point representation type */
typedef struct tagtgrPOINT
{
  INT X, Y; /* Point coordinates */
} tgrPOINT;

/* Rectangle representation type */
typedef struct tagtgrRECT
{
  INT
    X, Y,          /* Left-top rectangle point coordinates */
    Width, Height; /* Rectangle size */
} tgrRECT;

/* Area representation type */
typedef struct tagtgrAREA
{
  INT
    Left, Top,     /* Left-top area point coordinates */
    Right, Bottom; /* Right-bottom area point coordinates */
} tgrAREA;

/***
 * Memory allocation function pointers
 ***/

/* Basic memory allocation function pointer */
extern VOID * (*TGR_AllocMem)( UINT Size );

/* Large block memory allocation function pointer */
extern VOID * (*TGR_AllocMemLarge)( ULONG Size );

/* Memory deallocation function pointer */
extern VOID (*TGR_FreeMem)( VOID *Ptr );

/* Get maximum available memory block size function */
DWORD TGR_GetMaxMemSize( VOID );

/* Set default handle allocation */
VOID TGR_SetMemAllocToStd( VOID );

/* Set core handle allocation */
VOID TGR_SetMemAllocToCore( VOID );

/* Obtain core size function */
LONG TGR_GetCoreSize( VOID );

/* Print core lost info function */
VOID TGR_PrintCoreLostInfo( VOID );

/* Store call place in local data function */
VOID TGR_MemAllocStorePlace( CHAR *ModuleName, INT LineNumber );

#define TGR_AllocMem(Size) \
  (TGR_MemAllocStorePlace(__FILE__, __LINE__), \
   TGR_AllocMem(Size))
#define TGR_AllocMemLarge(Size) \
  (TGR_MemAllocStorePlace(__FILE__, __LINE__), \
   TGR_AllocMemLarge(Size))
#define TGR_FreeMem(Ptr) \
  (TGR_MemAllocStorePlace(__FILE__, __LINE__), \
   TGR_FreeMem(Ptr))

/***
 * Timer functions
 ***/

/* Timer initializing (reset counters) function */
VOID TGR_TimerReset( VOID );

/* Timer obtaining relative time (in microseconds) */
ULONG TGR_TimerGetTime( VOID );

/***
 * Initialization/deinitialization library and modes.
 ***/

/*** Mode detection flags ***/
#define TGR_DETECT_CGA        0x00000001UL
#define TGR_DETECT_EGAVGA16   0x00000002UL
#define TGR_DETECT_VGA256     0x00000004UL
#define TGR_DETECT_VGAX       0x00000008UL
#define TGR_DETECT_SVGA16     0x00000010UL
#define TGR_DETECT_SVGA256    0x00000020UL
#define TGR_DETECT_SVGA32K    0x00000040UL
#define TGR_DETECT_SVGA64K    0x00000080UL
#define TGR_DETECT_SVGA16M    0x00000100UL
#define TGR_DETECT_SVGABANKED 0x00000200UL
#define TGR_DETECT_SVGALINEAR 0x00000400UL

#define TGR_DETECT_EGAVGA \
  (TGR_DETECT_EGAVGA16 | TGR_DETECT_VGA256 | TGR_DETECT_VGAX)

#define TGR_DETECT_SVGA \
  (TGR_DETECT_SVGA16 | TGR_DETECT_SVGA256 | TGR_DETECT_SVGA32K | \
   TGR_DETECT_SVGA64K | TGR_DETECT_SVGA16M |                     \
   TGR_DETECT_SVGABANKED | TGR_DETECT_SVGALINEAR)

#define TGR_DETECT_ALL \
  (TGR_DETECT_CGA | TGR_DETECT_EGAVGA | TGR_DETECT_EGAVGA16 |    \
   TGR_DETECT_VGA256 | TGR_DETECT_VGAX | TGR_DETECT_SVGA |       \
   TGR_DETECT_SVGA16 | TGR_DETECT_SVGA256 | TGR_DETECT_SVGA32K | \
   TGR_DETECT_SVGA64K | TGR_DETECT_SVGA16M |                     \
   TGR_DETECT_SVGABANKED | TGR_DETECT_SVGALINEAR)

/* Set detection flag function (flags - bitwise ored) */
VOID TGR_SetDetectModes( ULONG Flags );

/* Reset detection flag function (flags - bitwise ored) */
VOID TGR_ResetDetectModes( ULONG Flags );

/*** Library initialization functions ***/

/* Library common initialization function */
BOOL TGR_InitLib( VOID );

/* Library deinitialization function */
VOID TGR_CloseLib( VOID );

/* Library common static initialization function */
VOID TGR_InitLibStatic( VOID );

/*** Graphics mode initialization functions ***/

/* Mode initialization function by mode number */
BOOL TGR_InitModeByNum( UINT ModeNumber );

/* Mode initialization function */
BOOL TGR_InitMode( INT Width, INT Height, INT BitsPerPixel );

/* Current graphics mode deinitialization function */
VOID TGR_CloseMode( VOID );

/***
 * Color handle types, macros and functions
 ***/

/***
 * Color convertion (combine-extract) helpful macros
 * True-color DWORD value format (by bits) (type 1):
 *  MSB                         LSB
 *   |31..24|23..16|15..08|07..00|
 *   [type]   red   green   blue
 * Monochrome color is one-byte intence value from 0 (black) to
 * 255 (white) (type 2):
 *  MSB                         LSB
 *   |31..24|23..16|15..08|07..00|
 *   [type]                intence
 * Paletted color is one-byte index to logic palette table
 * (0 - 255)  (type 3):
 *  MSB                         LSB
 *   |31..24|23..16|15..08|07..00|
 *   [type]                index
 * Index color is mode-specific color value (low-level
 * representation) (type 0):
 *  MSB                         LSB
 *   |31..24|23..16|15..08|07..00|
 *   [type]  <---   color    --->
 * [type] - color type: see TGR_COLOR_*** macros.
 ***/

/* Color representation type */
typedef DWORD tgrCOLOR;

/* Pseudo-3D color values type */
typedef struct tagtgrCOLOR3D
{
  tgrCOLOR
    Light,  /* Light side color value */
    Back,   /* Background color value */
    Dark;   /* Dark side color value */
} tgrCOLOR3D;

/*** Color convertion macros and constants ***/

/* High (3d) byte color value (specified color model) constants */
#define TGR_COLOR_INDEX   0x0000000UL
#define TGR_COLOR_RGB     0x1000000UL
#define TGR_COLOR_MONO    0x2000000UL
#define TGR_COLOR_PALETTE 0x3000000UL

/* Component from RGB color obtaining macros */
#define TGR_GetRGBRed(Color)   ((BYTE)((Color) >> 16))
#define TGR_GetRGBGreen(Color) ((BYTE)((Color) >> 8))
#define TGR_GetRGBBlue(Color)  ((BYTE)(Color))

/* Obtain component from palette and monochrome value macros */
#define TGR_GetPaletteIndex(Color) ((BYTE)(Color))
#define TGR_GetMonoValue(Color)    ((BYTE)(Color))

/* Making color macros */
#define TGR_RGB(R, G, B) \
  (((DWORD)((BYTE)(R)) << 16) | \
   ((DWORD)((BYTE)(G)) << 8) | \
   ((DWORD)((BYTE)(B))) | TGR_COLOR_RGB)

#define TGR_PALETTE(PalIndex) \
   (((DWORD)((BYTE)(PalIndex))) | TGR_COLOR_PALETTE)

#define TGR_MONO(MonoIntence) \
   (((DWORD)((BYTE)(MonoIntence))) | TGR_COLOR_MONO)

/* Macro for convert RGB value to monochrome one
 * (by separate values) */
#define TGR_RGB2MonoByValues(Red, Green, Blue) \
  ((30 * (Red) + 59 * (Green) + 11 * (Blue)) / 100)

/* Macro for convert RGB value to monochrome one */
#define TGR_RGB2Mono(RGB) \
  TGR_RGB2MonoByValues(TGR_GetRGBRed(RGB),   \
                       TGR_GetRGBGreen(RGB), \
                       TGR_GetRGBBlue(RGB))

/* Macro for obtain component values from [A]RGB by number
 * 2 - red, 1 - green, 0 - blue, 3 - color type */
#define TGR_GetColorComponent(TRGB, Comp) \
    ((BYTE)((TRGB) >> ((Comp) << 3)))

/*** Color conversion functions ***/

/* Conversion from color to index function */
tgrCOLOR TGR_Color2Index( tgrCOLOR Color );

/* Conversion from color to RGB index function */
tgrCOLOR TGR_Color2RGB( tgrCOLOR Color );

/* Conversion from color to mono index function */
tgrCOLOR TGR_Color2Mono( tgrCOLOR Color );

/* Conversion from RGB to index function */
tgrCOLOR TGR_RGB2Index( INT Red, INT Green, INT Blue );

/* Conversion from mono to index function */
tgrCOLOR TGR_Mono2Index( INT MonoIntense );

/* Conversion from palette to index function */
tgrCOLOR TGR_Palette2Index( INT PaletteColorNumber );

/* Spread conversion from color to index function */
tgrCOLOR TGR_Color2IndexSpread( tgrCOLOR Color, INT X, INT Y );

/*** Palette handle functions ***/

/* Get Palette Entry Color function */
tgrCOLOR TGR_GetPaletteEntryColor( INT No );

/* Set palette entry function */
tgrCOLOR TGR_SetPaletteEntry( INT No, INT Red, INT Green, INT Blue );

/* Set palette entry color function */
tgrCOLOR TGR_SetPaletteEntryColor( INT No, tgrCOLOR Color );

/* Set palette table (pass by RGB byte triads) function */
VOID TGR_SetPaletteTable( INT No, INT TableSize, VOID * PalTable );

/***
 * Graphics context handle types, macros and functions
 ***/

/* Graphics context index type */
typedef INT tgrGC;

/* Graphics context description type */
typedef struct tagtgrGCDESCR
{
  INT Width, Height; /* Graphics context work area size */
  UINT BytesPerLine; /* Bytes per one work area line */
  INT BitsPerPixel;  /* Color depth in bits */
  VOID *BufferPtr;   /* Graphics context buffer pointer
                      * (NULL for screen graphics contexts) */
  tgrAREA ViewPort;  /* Graphics context viewport coordinates */
} tgrGCDESCR;

/*** Graphics context hi-level handle functions ***/

/* Get graphics context information function */
tgrGCDESCR TGR_GetGCDescr( tgrGC GC, tgrGCDESCR *Descr );

/* Get current graphics context information function */
tgrGCDESCR TGR_GetCurrentGCDescr( tgrGCDESCR *Descr );

/* Create compatible with screen graphics context  */
tgrGC TGR_CreateCompGC( tgrGC ContextNo, INT Width, INT Height );

/* Create typed graphics context */
tgrGC TGR_CreateTypedGC( INT BitsPerPixel, INT Width, INT Height );

/* Create graphics context with alloced buffer function */
tgrGC TGR_CreateBufGC( INT BitsPerPixel, INT Width, INT Height,
          UINT BytesPerBufLine, VOID *Buf );

/* Duplicate graphics context function */
tgrGC TGR_DuplicateGC( tgrGC GC );

/* Delete graphics context data function */
BOOL TGR_FreeGC( tgrGC GC );

/* Set graphics context function */
tgrGC TGR_SetGC( tgrGC GC );

/* Get current graphics context function */
tgrGC TGR_GetGC( VOID );

/* Context blitting function */
VOID TGR_BlitGC( INT X, INT Y, INT Width, INT Height,
         tgrGC GC, INT Dx, INT Dy );

/* Context blitting with transparency function */
VOID TGR_BlitGCTrans( INT X, INT Y, INT Width, INT Height,
         tgrGC SrcGC, INT Dx, INT Dy, tgrCOLOR TransColor );

/* Context blitting to another context function */
VOID TGR_BlitGC2GC( tgrGC DestGC, INT X, INT Y, INT Width, INT Height,
         tgrGC SrcGC, INT Dx, INT Dy );

/* Context blitting to another context with transparency function */
VOID TGR_BlitGC2GCTrans( tgrGC DestGC, INT X, INT Y, INT Width, INT Height,
         tgrGC SrcGC, INT Dx, INT Dy, tgrCOLOR TransColor );

/***
 * Drawing parameters handle types, macros and functions
 ***/

/* Video mode addressing types */
#define TGR_CGA       1
#define TGR_EGA16     2
#define TGR_VGA16     3
#define TGR_VGA256    4
#define TGR_VGAX      5
#define TGR_SVGA16    6
#define TGR_SVGA256   7
#define TGR_SVGA15b   8
#define TGR_SVGA16b   9
#define TGR_SVGA24b  10
#define TGR_SVGA32b  11

/* Screen mode description type */
typedef struct tagtgrMODEDESCR
{
  INT ModeType;                    /* Video mode access type
                                    * (TGR_CGA, ... */
  INT Width, Height;               /* Mode screen size */
  UINT BytesPerLine;               /* Bytes per one scan line */
  INT BytesPerPixel, BitsPerColor; /* Pixel format */
  BOOL IsLinear;                   /* Linearity flag */
  ULONG VideoMemorySize;           /* Memory size in bytes */
} tgrMODEDESCR;

/* Logic operation type */
typedef enum tagtgrLOGOP
{
  TGR_COPY = 0,
  TGR_XOR  = 1,
  TGR_OR   = 2,
  TGR_AND  = 3
} tgrLOGOP;

/* Background mode values */
typedef enum tagtgrBACKMODE
{
  TGR_OPAQUE      = 0,
  TGR_TRANSPARENT = 1
} tgrBACKMODE;

/* Getting current mode number funcion (returns '-1' if no mode) */
INT TGR_GetCurrentMode( VOID );

/* Get number of registered graphics modes function */
INT TGR_GetNumOfModes( VOID );

/* Get video mode info by num function */
BOOL TGR_GetModeDescr( INT No, tgrMODEDESCR *ModeDescr );

/* Get current mode info high-level function */
VOID TGR_GetCurrentModeDescr( tgrMODEDESCR *ModeDescr );

/* Obtain current mode width in pixels function */
INT TGR_GetWidth( VOID );

/* Obtain current mode height in pixels */
INT TGR_GetHeight( VOID );

/* Geting number of bits for pixel function */
INT TGR_GetColorDepth( VOID );

/* Obtain current logical operation function */
tgrLOGOP TGR_GetLogOp( VOID );

/* Set current logic operation high-level function*/
tgrLOGOP TGR_SetLogOp( tgrLOGOP NewLogOp );

/* Obtain coordinate shift position function*/
tgrPOINT TGR_GetCenter( INT *X, INT *Y );

/* Obtain coordinate shift position to structure function */
tgrPOINT TGR_GetCenterS( tgrPOINT *Center );

/* Set current context center function */
tgrPOINT TGR_SetCenter( INT CenterX, INT CenterY );

/*  Set centers for current context function */
tgrPOINT TGR_SetCenterS( tgrPOINT *CenterP );

/* Set view port function */
tgrAREA TGR_GetViewPort( INT *Left, INT *Top, INT *Right, INT *Bottom );

/* Set view port to structure function */
tgrAREA TGR_GetViewPortS( VOID );

/* Set view port function */
tgrAREA TGR_SetViewPort( INT Left, INT Top, INT Right, INT Bottom );

/* Set view port from structure function */
tgrAREA TGR_SetViewPortS( tgrAREA *ViewPort );

/* Set view port to full work area function */
tgrAREA TGR_SetViewPortFull( VOID );

/* Get color 3D function */
tgrCOLOR3D TGR_GetColor3D( tgrCOLOR *Light, tgrCOLOR *Back, tgrCOLOR *Dark );

/* Get color 3D from current context to sructure function */
tgrCOLOR3D TGR_GetColor3DS( VOID );

/* Setting current 3D color funcion */
tgrCOLOR3D TGR_SetColor3D( tgrCOLOR Light, tgrCOLOR Back, tgrCOLOR Dark );

/* Initialize 3D color from structure function */
tgrCOLOR3D TGR_SetColor3DS( tgrCOLOR3D NewColor3D );

/* Get text color function */
tgrCOLOR TGR_GetTextColor( VOID );

/* Getting current back color funcion */
tgrCOLOR TGR_GetBackColor( VOID );

/* Get back mode function */
tgrBACKMODE TGR_GetBackMode( VOID );

/* Set text color function */
tgrCOLOR TGR_SetTextColor( tgrCOLOR NewTextColor );

/* Set back color current context function */
tgrCOLOR TGR_SetBackColor( tgrCOLOR BackColor );

/* Set back mode function */
tgrBACKMODE TGR_SetBackMode( tgrBACKMODE NewBackMode );

/* Set text current drawing attributes function */
VOID TGR_SetTextAttr( tgrCOLOR TextColor, tgrCOLOR BackColor,
         INT BackMode );

/***
 * Clip area handle types, macros and functions
 ***/

/*** Clip area specified types ***/

/* Range store type */
typedef struct tagtgrRANGE
{
  INT A, B;          /* Range paramenetrs (min & max values) */
} tgrRANGE;

/* Vertical range (with reference to horizontal segments) store type */
typedef struct tagtgrVRANGE
{
  tgrRANGE Y;        /* Vertical range parameters (top & bottom) */
  UINT NumOfRanges;  /* Number of horizontal segments */
  tgrRANGE *X;       /* Horizontal segments array (left-right, ...) */
} tgrVRANGE;

/* Base clip area description store type */
typedef struct tagtgrCLIP
{
  UINT NumOfRanges;  /* Number of vertical segments */
  tgrVRANGE *Spans;  /* Vertical segments array */
} tgrCLIP;

/* Clip area operation type ('New' OP 'Old'), current clip
 * area become the result of operation */
typedef enum tagtgrCLIPOP
{
  /* Delete 'Old', set current clip area to 'New' */
  TGR_CLIP_REPLACE = 0,
  /* Push current clip area ('Old'), set current clip area
   * to 'New' */
  TGR_CLIP_PUSH    = 1,
  /* Add 'New' clip area to 'Old' */
  TGR_CLIP_ADD     = 2,
  /* Subtract 'New' clip area from 'Old' */
  TGR_CLIP_SUB     = 3,
  /* Multiply (intersect) 'New' clip area with 'Old' */
  TGR_CLIP_MUL     = 4,
  /* Subtract inverse 'Old' clip area from 'New' */
  TGR_CLIP_INVSUB  = 5,
} tgrCLIPOP;

/*** Clip area common purpose handle function ***/

/* Obtain cover area-rectangle (left-top, right-bottom) from
 * clip area (return 'FALSE' if clip area is empty) */
BOOL TGR_ClipGetCoverClipAreaRectArea( tgrCLIP *ClipArea,
         tgrAREA *RectArea );

/* Obtain cover area-rectangle (X, Y, Width and Height) from
 * clip area (return 'FALSE' if clip area is empty) */
BOOL TGR_ClipGetCoverClipAreaRect( tgrCLIP *ClipArea,
         tgrRECT *Rect );

/* Clear clip area */
VOID TGR_ClipClearClipArea( tgrCLIP *ClipArea );

/* Compare two clip areas (return TRUE if they area equal) */
BOOL TGR_ClipIsTwoClipAreasEqual( tgrCLIP *ClipArea1,
         tgrCLIP *ClipArea2 );

/* Check if point is belong to clip area */
BOOL TGR_ClipIsPointInClipArea( INT X, INT Y, tgrCLIP *ClipArea );

/*** Object specified clip area handle */

/* Set empty clip area */
VOID TGR_ClipSetEmptyClipArea( tgrCLIP *ClipArea );

/* Set rectangular (X, Y, Width and Height) clip area */
BOOL TGR_ClipSetRectClipArea( tgrCLIP *ClipArea,
         INT X, INT Y, INT Width, INT Height );

/* Set rectangular clip area by 2 points */
BOOL TGR_ClipSetRectClipAreaBy2Points( tgrCLIP *ClipArea,
         INT X1, INT Y1, INT X2, INT Y2 );

/* Set ellipse clip area */
BOOL TGR_ClipSetEllipseClipArea( tgrCLIP *ClipArea,
         INT Xc, INT Yc, INT Rx, INT Ry );

/* Set ellipse clip area by two points */
VOID TGR_ClipSetEllipseClipAreaBy2Points( tgrCLIP *ClipArea,
         INT X, INT Y, INT X2, INT Y2 );

/* Set rectangular ellipse clip area: (X, Y, Width, Height),
 * Rx, Ry - horizontal and vertical radiuses */
BOOL TGR_ClipSetRectEllipseClipArea( tgrCLIP *ClipArea,
         INT X, INT Y, INT Width, INT Height,
         INT Rx, INT Ry );

/* Set rectangular ellipse clip area by two points */
VOID TGR_ClipSetRectEllipseClipAreaBy2Points( tgrCLIP *ClipArea,
         INT X, INT Y, INT X2, INT Y2, INT Rx, INT Ry );

/* Set chessboard clip area:
 *   (X, Y, Width, Height) - full rectangle
 *   OffX, OffY - adjust values (offset to top-left visible
 *                point)
 *   CellWidth, CellHeight - 2x2 cell size
 *   GridWidth, GridHeight - top-left 1x1 cell size
 *   IsInvert   - invert flag for subcells
 */
BOOL TGR_ClipSetChessClipArea( tgrCLIP *ClipArea, INT X, INT Y,
         INT Width, INT Height, INT OffX, INT OffY,
         INT CellWidth, INT CellHeight,
         INT GridWidth, INT GridHeight, BOOL IsInvert );

/* Set chess clip area by two points:
 * (full rectangle - (X1, Y1, X2, Y2)) */
BOOL TGR_ClipSetChessClipAreaBy2Points( tgrCLIP *ClipArea,
         INT X, INT Y, INT X2, INT Y2, INT OffX, INT OffY,
         INT CellWidth, INT CellHeight,
         INT GridWidth, INT GridHeight, BOOL IsInvert );

/*** Basic logic operations for clip area ***/

/* Merge two clip areas */
BOOL TGR_ClipClipAreaAddClipArea( tgrCLIP *ResClip, tgrCLIP *Clip1,
         tgrCLIP *Clip2 );

/* Merge two clip areas with assigment */
BOOL TGR_ClipClipAreaAddClipAreaAss( tgrCLIP *ResClip,
         tgrCLIP *Clip );

/* Subtract two clip areas */
BOOL TGR_ClipClipAreaSubClipArea( tgrCLIP *ResClip, tgrCLIP *Clip1,
         tgrCLIP *Clip2 );

/* Subtract two clip areas with assigment */
BOOL TGR_ClipClipAreaSubClipAreaAss( tgrCLIP *ResClip,
         tgrCLIP *Clip );

/* Inverse subtract two clip areas with assigment */
BOOL TGR_ClipClipAreaInvSubClipAreaAss( tgrCLIP *ResClip,
         tgrCLIP *Clip );

/* Intersect two clip areas */
BOOL TGR_ClipClipAreaMulClipArea( tgrCLIP *ResClip, tgrCLIP *Clip1,
         tgrCLIP *Clip2 );

/* Intersect two clip areas with assigment */
BOOL TGR_ClipClipAreaMulClipAreaAss( tgrCLIP *ResClip,
         tgrCLIP *Clip );

/*** Clip area handle with clip area stack ***/

/* Push new clip area to clip area stack (if new clip pointer is
 * NULL - duplicate old current clip) */
BOOL TGR_ClpPush( tgrCLIP *Clip );

/* Duplicate current clip area to clip area stack */
BOOL TGR_ClpDup( VOID );

/* Swap to bottom values on clip stack, return FALSE if
 * no clip area on the stack */
BOOL TGR_ClpSwap( VOID );

/* Pop old clip area from clip area stack (if old clip pointer is
 * NULL - delete current clip, if rest the only clip - clear it one
 * and set clip to empty), return FALSE if no clip area is rest on
 * stack and set empty clip */
BOOL TGR_ClpPop( tgrCLIP *Clip );

/* Drop top clip area from clip area stack (if rest the only clip -
 * clear it one and set clip to empty), return FALSE if no clip area
 * is rest on stack and set empty clip */
BOOL TGR_ClpDrop( VOID );

/* Add top clip areas */
BOOL TGR_ClpAdd( VOID );

/* Subtract top clip areas */
BOOL TGR_ClpSub( VOID );

/* Mul top clip areas */
BOOL TGR_ClpMul( VOID );

/* Inverse subtract top clip areas */
BOOL TGR_ClpInvSub( VOID );

/* Replace current clip area */
VOID TGR_ClpReplace( tgrCLIP *Clip );

/*** Object specified clip area stack handle */

/* Set (push) or replace current clip area to empty one */
BOOL TGR_ClpEmpty( tgrCLIPOP ClipOp );

/* Set (push) or replace current clip area to rectangular one */
BOOL TGR_ClpRect( tgrCLIPOP ClipOp,
         INT X, INT Y, INT Width, INT Height );

/* Set (push) or replace current clip area to rectangular (by 2
 * points) one */
BOOL TGR_ClpRectBy2Points( tgrCLIPOP ClipOp,
         INT X1, INT Y1, INT X2, INT Y2 );

/* Set (push) or replace current clip area to empty one */
BOOL TGR_ClpEllipse( tgrCLIPOP ClipOp,
         INT Xc, INT Yc, INT Rx, INT Ry );

/* Set (push) or replace current clip area to ellipse one by
 * two points */
VOID TGR_ClpEllipseBy2Points( tgrCLIPOP ClipOp,
         INT X, INT Y, INT X2, INT Y2 );

/* Set (push) or replace current clip area to rectangular
 * ellipse one: (X, Y, Width, Height), Rx, Ry - horizontal
 * and vertical radiuses */
BOOL TGR_ClpRectEllipse( tgrCLIPOP ClipOp,
         INT X, INT Y, INT Width, INT Height, INT Rx, INT Ry );

/* Set (push) or replace current clip area to rectangular
 * ellipse one by two points */
VOID TGR_ClpRectEllipseBy2Points( tgrCLIPOP ClipOp,
         INT X, INT Y, INT X2, INT Y2, INT Rx, INT Ry );

/* Set (push) or replace current clip area to chess one:
 *   (X, Y, Width, Height) - full rectangle
 *   OffX, OffY - adjust values (offset to top-left visible
 *                point)
 *   CellWidth, CellHeight - 2x2 cell size
 *   GridWidth, GridHeight - top-left 1x1 cell size
 *   IsInvert   - invert flag for subcells
 */
BOOL TGR_ClpChess( tgrCLIPOP ClipOp, INT X, INT Y, INT Width,
         INT Height, INT OffX, INT OffY, INT CellWidth,
         INT CellHeight, INT GridWidth, INT GridHeight,
         BOOL IsInvert );

/* Set (push) or replace current clip area to chess one by two
 * points: (full rectangle - (X1, Y1, X2, Y2)) */
BOOL TGR_ClpChessBy2Points( tgrCLIPOP ClipOp, INT X, INT Y,
         INT X2, INT Y2, INT OffX, INT OffY,
         INT CellWidth, INT CellHeight,
         INT GridWidth, INT GridHeight, BOOL IsInvert );

/***
 * Buffers handle types, macros and functions
 ***/

/*** Address value correct increment macro ***/

/* Increment a pointer: (Buf + Value_in_bytes),
 * Prototype:
 *   VOID * TGR_BufIncrAddr( VOID *Buf, ULONG IncrValue );
 */

#ifdef __WATCOM_FLAT__

/* Physical addres correction */
#define TGR_BufIncrAddr(Buf, Value) \
  ((VOID *)((BYTE *)(Buf) + (DWORD)(Value)))

#else /* __WATCOM_FLAT__ */

/* Physical addres correction */
#define __TGR_LA2PA(LA) \
  ((VOID *)((((DWORD)(LA) & 0xFFFF0UL) << 12) | \
             ((DWORD)(LA) & 0xF)))
#define __TGR_PA2LA(PA) \
  ((((DWORD)(PA) >> 16) << 4) + ((DWORD)(PA) & 0xFFFFUL))
#define TGR_BufIncrAddr(Buf, Value) \
  __TGR_LA2PA(__TGR_PA2LA(Buf) + (DWORD)(Value))

#endif /* __WATCOM_FLAT__ */

/*** Creation/destroing buffer functions ***/

/* Get size of horizontal buffer function */
UINT TGR_GetHBufTypedSize( INT BitsPerPixel, INT Width );

/* Get horizontal buffer size function */
UINT TGR_GetHBufCompSize( INT Width );

/* Get size of rectangular buffer function */
ULONG TGR_GetRBufTypedSize( INT BitsPerPixel, INT Width,
          INT Height, UINT *BytesPerBufLine);

/* Get rectangular buffer size function */
ULONG TGR_GetRBufCompSize( INT Width, INT Height,
          UINT *BytesPerBufLine );

/* Create horizontal compatible buffer function */
VOID * TGR_CreateHBufComp( INT Width );

/* Create horizontal 1-bit buffer function */
VOID * TGR_CreateHBuf1Bit( INT Width );

/* Create horizontal RGB buffer function */
VOID * TGR_CreateHBufRGB( INT Width );

/* Create horizontal buffer of specified type function */
VOID * TGR_CreateHBufTyped( INT BitsPerPixel, INT Width );

/* Create rectangular compatible buffer function */
VOID * TGR_CreateRBufComp( INT Width, INT Height,
           UINT *BytesPerBufLine );

/* Create rectangular 1-bit buffer function */
VOID * TGR_CreateRBuf1Bit( INT Width, INT Height,
           UINT *BytesPerBufLine );

/* Create rectangular RGB buffer function */
VOID * TGR_CreateRBufRGB( INT Width, INT Height,
           UINT *BytesPerBufLine );

/* Create rectangular buffer of specified type function */
VOID * TGR_CreateRBufTyped( INT BitsPerPixel, INT Width,
           INT Height, UINT *BytesPerBufLine );

/* Free any type buffer function */
VOID TGR_FreeBuf( VOID *Buf );

/*** Buffer conversion functions ***/

/* Conversion from compatible buffer to RGB buffer function */
VOID TGR_HBufComp2RGB( INT Width,
         VOID *BufRGB, VOID *BufComp );

/* Conversion from RGB buffer to compatible buffer function */
VOID TGR_HBufRGB2Comp( INT Width,
         VOID *BufComp, VOID *BufRGB );

/* Conversion from mono buffer to compatible buffer function */
VOID TGR_HBufMono2Comp( INT Width,
         VOID *BufComp, VOID *BufMono );

/* Spread conversion from RGB buffer to compatible
 * buffer function */
VOID TGR_HBufRGB2CompSpread( INT Width,
         VOID *BufComp, VOID *BufRGB );

/* Spread conversion from mono buffer to compatible
 * buffer function */
VOID TGR_HBufMono2CompSpread( INT Width,
         VOID *BufComp, VOID *BufMono );

/* Conversion from compatible to RGB rectangle buffer function */
VOID TGR_RBufComp2RGB( INT Width, INT Height,
         UINT BytesPerRGBBufLine, VOID *BufRGB,
         UINT BytesPerCompBufLine, VOID *BufComp );

/* Conversion from RGB to compatible rectangle buffer function */
VOID TGR_RBufRGB2Comp( INT Width, INT Height,
         UINT BytesPerCompBufLine, VOID *BufComp,
         UINT BytesPerRGBBufLine, VOID *BufRGB );

/* Conversion from mono to compatible rectangle buffer function */
VOID TGR_RBufMono2Comp( INT Width, INT Height,
         UINT BytesPerCompBufLine, VOID *BufComp,
         UINT BytesPerMonoBufLine, VOID *BufMono );

/* Spread conversion from RGB to compatible rectangle
 * buffer function */
VOID TGR_RBufRGB2CompSpread( INT Width, INT Height,
         UINT BytesPerCompBufLine, VOID *BufComp,
         UINT BytesPerRGBBufLine, VOID *BufRGB );

/* Spread conversion from mono to compatible rectangle
 * buffer function */
VOID TGR_RBufMono2CompSpread( INT Width, INT Height,
         UINT BytesPerCompBufLine, VOID *BufComp,
         UINT BytesPerMonoBufLine, VOID *BufMono );

/*** Buffer drawing/obtaining functions ***/

/* Get horizontal buffer function */
VOID TGR_GetHBuf( INT X, INT Y, INT Width,
         VOID *Buffer, INT FirstPoint );

/* Get buffer function */
VOID TGR_GetRBuf( INT X, INT Y, INT Width, INT Height,
         VOID *Buffer, INT OffX, INT OffY,
         UINT BytesPerLine );

/* Put compatible buffer function */
VOID TGR_PutHBufComp( INT X, INT Y, INT Width, VOID *Buffer,
         INT FirstPoint );

/* Put compatible buffer transparent function */
VOID TGR_PutHBufCompTrans( INT X, INT Y, INT Width,
         VOID *Buffer, INT FirstPoint, tgrCOLOR TransColor );

/* Put rectangle compatible buffer function */
VOID TGR_PutRBufComp( INT X, INT Y, INT Width, INT Height,
         VOID *Buffer, INT OffX, INT OffY, UINT BytesPerLine );

/* Put rectangle compatible transparent buffer function */
VOID TGR_PutRBufCompTrans( INT X, INT Y, INT Width, INT Height,
         VOID *Buffer, INT OffX, INT OffY, UINT BytesPerLine,
         tgrCOLOR TransColor );

/* Put buffer 1-bit function */
VOID TGR_PutHBuf1Bit( INT X, INT Y, INT Width, VOID *Buffer,
         INT FirstPoint, tgrCOLOR Color0, tgrCOLOR Color1 );

/* Put buffer 1-bit transparent function */
VOID TGR_PutHBuf1BitTrans( INT X, INT Y, INT Width, VOID *Buffer,
         INT FirstPoint, tgrCOLOR Color1 );

/* Put rectangle buffer 1-bit function */
VOID TGR_PutRBuf1Bit( INT X, INT Y, INT Width, INT Height,
         VOID *Buffer, INT OffX, INT OffY,
         UINT BytesPerLine, tgrCOLOR Color0, tgrCOLOR Color1 );

/* Put rectangle buffer 1-bit transparent function */
VOID TGR_PutRBuf1BitTrans( INT X, INT Y, INT Width, INT Height,
         VOID *Buffer, INT OffX, INT OffY, UINT BytesPerLine,
         tgrCOLOR Color1 );

/***
 * Drawing functions
 ***/

/* Get pixel color function */
tgrCOLOR TGR_GetPixel( INT X, INT Y );

/* Put pixel function */
VOID TGR_PutPixel( INT X, INT Y, tgrCOLOR Color );

/* Put horizontal line function */
VOID TGR_PutHLine( INT X, INT Y, INT Width, tgrCOLOR Color );

/* Put horizontal line by two points function */
VOID TGR_PutHLineBy2Points( INT X, INT Y, INT X2,
         tgrCOLOR Color );

/* Put vertical line function */
VOID TGR_PutVLine( INT X, INT Y, INT Height, tgrCOLOR Color );

/* Put vertical line by two points function */
VOID TGR_PutVLineBy2Points( INT X, INT Y, INT Y2,
         tgrCOLOR Color );

/* Put arbitrary line function */
VOID TGR_PutLine( INT X1, INT Y1, INT X2, INT Y2,
         tgrCOLOR Color );

/* Put rectangle function */
VOID TGR_PutRect( INT X, INT Y, INT Width, INT Height,
         tgrCOLOR Color );

/* Put rectangle by two points function */
VOID TGR_PutRectBy2Points( INT X, INT Y, INT X2, INT Y2,
         tgrCOLOR Color );

/* Put bar function */
VOID TGR_PutBar( INT X, INT Y, INT Width, INT Height,
         tgrCOLOR Color );

/* Put bar by two points function */
VOID TGR_PutBarBy2Points( INT X, INT Y, INT X2, INT Y2,
         tgrCOLOR Color );

/* Fill entire clip area function */
VOID TGR_Fill( tgrCOLOR Color );

/* Fill entire view port function */
VOID TGR_ClearViewPort( tgrCOLOR Color );

/* Fill entire work area function */
VOID TGR_ClearDevice( tgrCOLOR Color );

/* Copying of horizontal area function */
VOID TGR_CopyHArea( INT DestX, INT DestY, INT Width,
          INT SrcX, INT SrcY);

/* Copying of rectangular area function */
VOID TGR_CopyRArea( INT DestX, INT DestY,
         INT Width, INT Height,
         INT SrcX, INT SrcY);

/*** Circle/ellipse drawing ***/

/* Draw circle function */
VOID TGR_PutCircle( INT Xc, INT Yc, INT Radius, tgrCOLOR Color );

/* Draw fill circle function */
VOID TGR_PutFillCircle( INT Xc, INT Yc, INT Radius, tgrCOLOR Color );

/* Ellipse drawing function */
VOID TGR_PutEllipse( INT Xc, INT Yc, INT Rx, INT Ry,
         tgrCOLOR Color );

/* Ellipse drawing by two points function */
VOID TGR_PutEllipseBy2Points( INT X, INT Y, INT X2, INT Y2,
         tgrCOLOR Color );

/* Fill ellipse drawing function */
VOID TGR_PutFillEllipse( INT Xc, INT Yc, INT Rx, INT Ry,
         tgrCOLOR Color );

/* Ellipse drawing by two points function */
VOID TGR_PutFillEllipseBy2Points( INT X, INT Y, INT X2, INT Y2,
         tgrCOLOR Color );

/* Rectangular ellipse drawing function */
VOID TGR_PutRectEllipse( INT X, INT Y, INT Width, INT Height,
         INT Rx, INT Ry, tgrCOLOR Color );

/* Rectangular ellipse drawing function */
VOID TGR_PutRectEllipseBy2Points( INT X, INT Y, INT X2, INT Y2,
         INT Rx, INT Ry, tgrCOLOR Color );

/* Rectangular ellipse drawing function */
VOID TGR_PutBarEllipse( INT X, INT Y, INT Width, INT Height,
         INT Rx, INT Ry, tgrCOLOR Color );

/* Rectangular ellipse drawing function */
VOID TGR_PutBarEllipseBy2Points( INT X, INT Y, INT X2, INT Y2,
         INT Rx, INT Ry, tgrCOLOR Color );

/*** Chessnoard drawing ***/

/* Draw chessboard function. Parameters:
 *   (X, Y, Width, Height) - full rectangle
 *   OffX, OffY - adjust values (offset to top-left visible
 *                point)
 *   CellWidth, CellHeight - 2x2 cell size
 *   GridWidth, GridHeight - top-left 1x1 cell size
 *   IsBothDraw - flag for drawing both subcells
 *   IsInvert   - invert flag for subcells
 *   Color0 - left-top subcell color
 *   Color1 - another one */
VOID TGR_PutChess( INT X, INT Y, INT Width, INT Height,
         INT OffX, INT OffY,
         INT CellWidth, INT CellHeight,
         INT GridWidth, INT GridHeight,
         tgrCOLOR Color0, tgrCOLOR Color1,
         BOOL IsBothDraw, BOOL IsInvert );

/* Put chess by two points function
 * (rectangle - (X1, Y1, X2, Y2)) */
VOID TGR_PutChessBy2Points( INT X1, INT Y1, INT X2, INT Y2,
         INT OffX, INT OffY,
         INT CellWidth, INT CellHeight,
         INT GridWidth, INT GridHeight,
         tgrCOLOR Color0, tgrCOLOR Color1,
         BOOL IsBothDraw, BOOL IsInvert );

/*** Triangle drawing ***/

/* Put fill triangle function */
VOID TGR_PutTriangle( INT X0, INT Y0, INT X1, INT Y1,
         INT X2, INT Y2, tgrCOLOR Color );

/* Gouraud shading triangle drawing function */
VOID TGR_PutGouraudTriangle( INT X0, INT Y0, tgrCOLOR Color0,
         INT X1, INT Y1, tgrCOLOR Color1,
         INT X2, INT Y2, tgrCOLOR Color2 );

/*** Polygon drawing ***/

/* Draw hollow polygon function ('PolyPoints' is array of 'INT'
 * values: X1, Y1, X2, Y2, X3, Y3, ...) */
VOID TGR_PutPoly( INT PointsAmount, INT *PolyPoints,
         tgrCOLOR Color );

/* Draw hollow multi-parts polygon function, polygon consist from
 * several conturs (sub polygons), all sub-polygons stored in
 * 'PolyParts' parameter (all values are 'INT'):
 *   'Poly0_PointsAmount', X, Y, X, Y,...,
 *   'Poly1_PointsAmount', X, Y, X, Y,...,
 *   ...
 *   'PolyN_PointsAmount', X, Y, X, Y,...
 * where N == ('ContursAmount' - 1) */
VOID TGR_PutMultiPoly( INT ContursAmount, INT *PolyParts,
         tgrCOLOR Color );

/* Draw fill polygon function, 'PolyPoins' consist of
 * X, Y, X, Y, ... polygon points coordinates */
VOID TGR_PutFillPoly( INT PointsAmount, INT *PolyPoints,
         tgrCOLOR Color );

/* Draw fill multi-parts polygon function, polygon consist from
 * several conturs (sub polygons), all sub-polygons stored in
 * 'PolyParts' parameter (all values are 'INT'):
 *   'Poly0_PointsAmount', X, Y, X, Y,...,
 *   'Poly1_PointsAmount', X, Y, X, Y,...,
 *   ...
 *   'PolyN_PointsAmount', X, Y, X, Y,...
 * where N == ('ContursAmount' - 1) */
VOID TGR_PutFillMultiPoly( INT ContursAmount, INT *PolyParts,
         tgrCOLOR Color );

/*** Pseudo 3D object drawing ***/

/* Draw 3D bar/rectangle function */
VOID TGR_PutBar3D( INT X, INT Y, INT Width, INT Height,
         INT BorderWidth,
         BOOL IsFill, BOOL IsInvert );

/* Draw 3D corner function.
 * Corner type:
 *  +-- 0    --+ 1   |   2     | 3
 *  |          |     +--     --+
 */
VOID TGR_PutCorner3D( INT X, INT Y, INT Width, INT Height,
         INT InsideWidth, INT InsideHeight,
         INT BorderWidth,
         BOOL IsFill, BOOL IsInvert, INT Type );

/* Draw 3D style round bar function */
VOID TGR_PutRoundBar3D( INT X, INT Y, INT Width, INT Height,
         INT Radius, INT BorderWidth,
         BOOL IsInvert, BOOL IsFill );

/***
 * Edit text line support
 ***/

/* Type for edit text filtering support */
typedef WORD (*tgrEDITFILTER)( WORD Key );

/* Set edit line filter function: filter function receives current
 * pressed key at 'Key' parameter (low word - ASCII code, hi word
 * - scan code) or 0x0000 if nothing are pressed (in idle loop)
 * and returns new key value; function return pointer to previous
 * installed function; 'FilterFunc' value 'NULL' disable
 * filtering */
tgrEDITFILTER TGR_SetEditLineFilter( tgrEDITFILTER FilterFunc );

/* Text line editor ('Buffer' should be filled before edit,
 * 'ResPos' - pointer for save last text cursor position,
 * return 'TRUE' if 'ENTER' pressed and 'FALSE' if 'ESC'
 * pressed, uses filter function that set by
 * 'TGR_SetEditLineFilter' function */
BOOL TGR_EditLine( INT X, INT Y, INT Width, INT Height,
         CHAR *Buffer, INT MaxLen, INT StartPos,
         tgrCOLOR TextColor, tgrCOLOR BackColor,
         tgrCOLOR CursorColor, INT *ResPos );

/***
 * Fonts handle types and functions
 ***/

/* Set current font number */
INT TGR_SetFont( INT FontNo );

/* Register font from file function */
INT TGR_RegisterFontFromFile( CHAR *FileName, INT Number );

/* Release a font from font table */
BOOL TGR_ReleaseFont( INT FontNo );

/* Write a string with current font */
INT TGR_PutString( INT X, INT Y, CHAR *Str );

/* Write a string (specified length) with current font */
INT TGR_PutStringN( INT X, INT Y, CHAR *Str, INT Len );

/* Write a char with current font */
INT TGR_PutChar( INT X, INT Y, CHAR Ch );

/* Get current font string height */
INT TGR_GetFontHeight( VOID );

/* Get current font string width */
INT TGR_GetStringWidth( CHAR *String );

/* Get current font string (specified length) width */
INT TGR_GetStringWidthN( CHAR *String, INT Len );

/* Get current font char width */
INT TGR_GetCharWidth( CHAR Ch );

/***
 * Cursor handle types and functions
 ***/

/* Cursor file prefix */
#define TGR_CURSORPREFIX \
  (((DWORD)'C' << 16) | ((DWORD)'S' << 8) | ((DWORD)'G'))

/* Palette description type (quadruple) */
typedef struct tagtgrRGBQ
{
  BYTE Red, Green, Blue, Alpha;  /* Color components */
} tgrRGBQ;

/* Cursor description type
 *   Cursor structure:
 *     Header
 *     XOR mask (color space determine by header)
 *     AND mask (always 1 bit per pixel)
 */
typedef struct tagtgrCURSOR
{
  DWORD Prefix;            /* File prefix - 'GSC\x00'
                            * see TGR_CURSORPREFIX */
  WORD HotSpotX, HotSpotY; /* Cursor hot-spot position */
  WORD Width, Height;      /* Cursor size in pixels */
  WORD BytesPerLineXOR;    /* Bytes per line of XOR mask line */
  WORD BytesPerLineAND;    /* Bytes per line of AND mask line */
  WORD BitsPerPixel;       /* Bits per one cursor image pixel
                            * (for XOR mask, AND mask always
                            * 2 bits per pixel) */
  WORD NumOfColors;        /* Palette size (in triads) */
  tgrRGBQ Palette[];       /* Image palette */
} tgrCURSOR;

/* Add cursor data function */
INT TGR_RegisterCursor( tgrCURSOR *Cursor );

/* Add cursor data function */
INT TGR_RegisterCursorFromFile( CHAR *FileName );

/* Delete cursor data function */
BOOL TGR_ReleaseCursor( INT CursorID );

/* Set cursor function */
INT TGR_SetCursor( INT CursorID );

/* Get current cursor function */
INT TGR_GetCursor( VOID );

/* Hide cursor function */
VOID TGR_CursorHide( VOID );

/* Show cursor function */
VOID TGR_CursorShow( VOID );

/* Move cursor to new position function */
VOID TGR_CursorMove( INT X, INT Y );

/***
 * Mouse handle data and functions
 ***/

/*** Mouse global data ***/

/* Mouse cursor position */
extern INT TGR_MouseX, TGR_MouseY;

/* Mouse buttons state
 * Bits information:
 *     0 - set - left button down, otherwise - up
 *     1 - set - right button down, otherwise - up
 *     2 - set - middle button down, otherwise - up
 */
extern INT TGR_MouseButtons;

/* Mouse relative mikki count */
extern INT TGR_MouseMikkiX, TGR_MouseMikkiY;

/* Mouse number of buttons */
extern INT TGR_MouseNumOfButtons;

/*** Mouse handle functions ***/

/* Get mouse function */
VOID TGR_MouseGetData( VOID );

/* Move mouse cursor function. */
VOID TGR_MouseMove( INT X, INT Y );

/* Set mouse range function */
VOID TGR_MouseSetRange( INT Left, INT Top, INT Right, INT Bottom );

/* Set mouse double speed board function */
VOID TGR_MouseSetDblSpeed( INT MikkiPerSecond );

/* Set mouse sensivity function */
VOID TGR_MouseSetSens( INT SpeedByX, INT SpeedByY );

#endif /* _TGRP_H_ */

/* END OF 'TGRP.H' FILE */
