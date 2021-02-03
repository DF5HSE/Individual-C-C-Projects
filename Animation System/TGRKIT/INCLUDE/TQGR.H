/***************************************************************
 * Copyright (C) 1998
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : TQGR.H
 * PURPOSE     : Quick Graphics Library.
 *               Main declaration module.
 * PROGRAMMER  : CGSG 1997/1998.
 * LAST UPDATE : 07.03.1998
 * NOTE        : Module prefix 'QGR'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium
 */

#ifndef _TQGR_H_
#define _TQGR_H_

#include "commondf.h"

/***
 * Color handle macros
 ***/

/***
 * Color convertion (combine-extract) helpful macros
 * True-color DWORD value format (by bits):
 *  MSB                         LSB
 *   |31..24|23..16|15..08|07..00|
 *   [alpha]  red   green   blue
 * Alpha is optional color component (e.g. 'alpha-channel')
 * Monochrome color is one-byte intence value from 0 (black) to
 * 255 (white)
 ***/

/* Combine red, green and blue components to one DWORD value */
#define QGR_RGB(R, G, B) \
    ((((DWORD)(BYTE)(R)) << 16) | \
     (((WORD)(BYTE)(G)) << 8) |   \
     (BYTE)(B))

/* Combine alpha, red, green and blue components to one
 * DWORD value */
#define QGR_ARGB(A, R, G, B) \
    ((((DWORD)(BYTE)(A)) << 24) | \
     (((DWORD)(BYTE)(R)) << 16) | \
     (((WORD)(BYTE)(G)) << 8) |   \
     (BYTE)(B))

/* Extract alpha component from one DWORD true-color
 * representation */
#define QGR_GetAlpha(ARGB) \
    ((BYTE)((RGB) >> 24))
/* Extract red component from one DWORD true-color
 * representation */
#define QGR_GetRed(RGB) \
    ((BYTE)((RGB) >> 16))
/* Extract green component from one DWORD true-color
 * representation */
#define QGR_GetGreen(RGB) \
    ((BYTE)((RGB) >> 8))
/* Extract blue component from one DWORD true-color
 * representation */
#define QGR_GetBlue(RGB) \
    ((BYTE)(RGB))

/* Macro for convert RGB value to monochrome one
 * (by separate values) */
#define QGR_RGB2MonoByValues(Red, Green, Blue) \
  ((30 * (Red) + 59 * (Green) + 11 * (Blue)) / 100)

/* Macro for convert RGB value to monochrome one */
#define QGR_RGB2Mono(RGB) \
  QGR_RGB2MonoByValues(QGR_GetRed(RGB),   \
                       QGR_GetGreen(RGB), \
                       QGR_GetBlue(RGB))

/* Macro for convert monochrome value to RGB one */
#define QGR_Mono2RGB(I) \
  QGR_RGB(I, I, I)

/* Macro for obtain component values from [A]RGB by number
 * 2 - red, 1 - green, 0 - blue, 3 - alpha */
#define QGR_GetRGBComponent(ARGB, Comp) \
    ((BYTE)((ARGB) >> ((Comp) << 3)))

/***
 * Library types
 ***/

/* Color representation type */
typedef DWORD qgrCOLOR;

/* Color 3D representation type */
typedef struct
{
  qgrCOLOR Light, Back, Dark;
} qgrCOLOR3D;

/* Logic operation type */
typedef enum tagqgrLOGOP
{
  QGR_COPY = 0,
  QGR_XOR  = 1,
  QGR_OR   = 2,
  QGR_AND  = 3
} qgrLOGOP;

/* Color model type */
typedef enum tagqgrCOLORMODEL
{
  QGR_CMODEL_INDEX = 0,
  QGR_CMODEL_PAL   = 1,
  QGR_CMODEL_MONO  = 2,
  QGR_CMODEL_RGB   = 3
} qgrCOLORMODEL;

/* Color mode type */
typedef enum tagqgrCOLORMODE
{
  QGR_CMODE_SOLID  = 0,
  QGR_CMODE_SPREAD = 1
} qgrCOLORMODE;

/***
 * Color and palette entry description structures
 ***/

/* Palette description type (triad) */
typedef struct tagqgrRGBT
{
  BYTE Red, Green, Blue;  /* Color components */
} qgrRGBT;

/* Palette description type (quadruple) */
typedef struct tagqgrRGBQ
{
  BYTE Red, Green, Blue, Alpha;  /* Color components */
} qgrRGBQ;

/***
 * Cursor shape description
 ***/

/* Prefix of cursor structure ("GSC\0") */
#define QGR_CURSORPREFIX \
  (((DWORD)'C' << 16) | ((DWORD)'S' << 8) | (DWORD)'G')

/* Cursor description type
 *   Cursor structure:
 *     Header
 *     XOR mask (color space determine by header)
 *     AND mask (always 1 bit per pixel)
 */
typedef struct tagqgrCURSOR
{
  DWORD Prefix;            /* File prefix - "GSC\x00"
                            * see QGR_CURSORPREFIX */
  WORD HotSpotX, HotSpotY; /* Cursor hot-spot position */
  WORD Width, Height;      /* Cursor size in pixels */
  WORD BytesPerLineXOR;    /* Bytes per line of XOR mask line */
  WORD BytesPerLineAND;    /* Bytes per line of AND mask line */
  WORD BitsPerPixel;       /* Bits per one cursor image pixel
                            * (for XOR mask, AND mask always
                            * 1 bits per pixel) */
  WORD  ColorsAmount;      /* Palette size (in quads) */
  qgrRGBQ Palette[];       /* Image palette */
} qgrCURSOR;

/***
 * Handle functions
 ***/

/* Library initialize function */
BOOL QGR_Init( INT Width, INT Height, INT ColorBits );

/* Library deinitialize function */
VOID QGR_Close( VOID );

/* Draw pixel function */
VOID QGR_PutPixel( INT X, INT Y, qgrCOLOR Color );

/* Obtain pixel color function */
qgrCOLOR QGR_GetPixel( INT X, INT Y );

/* Put pixel gray */
VOID QGR_PutPixelGray( INT X, INT Y, INT Intense );

/* Put pixel RGB */
VOID QGR_PutPixelRGB( INT X, INT Y, INT R, INT G, INT B );

/* Set current logic operation function (return old value) */
qgrLOGOP QGR_SetLogOp( qgrLOGOP LogOp );

/* Obtain current logic operation function */
qgrLOGOP QGR_GetLogOp( VOID );

/***
 * Global screen values, coordinate system shifting and
 * clipping handle
 ***/

/* Set new coordinate system shift values */
VOID QGR_SetCenter( INT X, INT Y );

/* Obtain coordinate system shift values */
VOID QGR_GetCenter( INT *X, INT *Y );

/* Set clip to full screen region */
VOID QGR_SetFullClip( VOID );

/* Set new clip area */
VOID QGR_SetClip( INT Left, INT Top, INT Right, INT Bottom );

/* Set new clip area by rectangle */
VOID QGR_SetRectClip( INT X, INT Y, INT Width, INT Height );

/* Obtain current clip area */
VOID QGR_GetClip( INT *Left, INT *Top, INT *Right, INT *Bottom );

/* Obtain screen width */
INT QGR_GetWidth( VOID );

/* Obtain screen height */
INT QGR_GetHeight( VOID );

/* Obtain bits per pixel value */
INT QGR_GetBitsPerPixel( VOID );

/* Obtain colors amount value */
LONG QGR_GetColorsAmount( VOID );

/***
 * Color mode/model handle functions
 ***/

qgrCOLORMODEL QGR_SetColorModel( qgrCOLORMODEL );
qgrCOLORMODEL QGR_GetColorModel( VOID );
qgrCOLORMODE  QGR_SetColorMode( qgrCOLORMODE );
qgrCOLORMODE  QGR_GetColorMode( VOID );

/***
 * Line functions
 ***/

/* Put line function */
VOID QGR_PutLine( INT x1, INT y1, INT x2, INT y2, qgrCOLOR Color );

/* Put horizontal line by 2 points */
VOID QGR_PutHLineBy2Points( INT X, INT Y, INT X2, qgrCOLOR Color );

/**/
VOID QGR_PutVLineBy2Points( INT X, INT Y, INT Y2, qgrCOLOR Color );

/* Put line */
VOID QGR_PutHLine( INT X, INT Y, INT Width, qgrCOLOR Color );

/**/
VOID QGR_PutVLine( INT X, INT Y, INT Height, qgrCOLOR Color );

/***
 * Bar/rectangle functions.
 ***/

/* Put bar */
VOID QGR_PutBar( INT X, INT Y, INT Width, INT Height, qgrCOLOR Color );

/* Put bar by 2 points */
VOID QGR_PutBarBy2Points( INT X1, INT Y1, INT X2, INT Y2, qgrCOLOR Color );

/* Put rectangle function */
VOID QGR_PutRect( INT X, INT Y, INT Width, INT Height, qgrCOLOR Color );

/* Put rectangle by 2 points */
VOID QGR_PutRectBy2Points( INT X1, INT Y1, INT X2, INT Y2,
         qgrCOLOR Color );

/***
 * Pseudo 3D object drawing
 ***/

/* Draw 3D bar/rectangle function */
VOID QGR_PutBar3D( INT X, INT Y, INT Width, INT Height,
         INT BorderWidth, qgrCOLOR3D *Color,
         BOOL IsFill, BOOL IsInvert );

/***
 * Circle/ellipse functions.
 ***/

/* Put circle */
VOID QGR_PutCircle( INT Xc, INT Yc, INT R, qgrCOLOR Color );

/* Put filling circle */
VOID QGR_PutFillCircle( INT Xc, INT Yc, INT R, qgrCOLOR Color );

/* Ellipse drawing function */
VOID QGR_PutEllipse( INT Xc, INT Yc, INT Rx, INT Ry,
         qgrCOLOR Color );

/* Fill ellipse drawing function */
VOID QGR_PutFillEllipse( INT Xc, INT Yc, INT Rx, INT Ry,
         qgrCOLOR Color );

/***
 * Poly functions.
 ***/

/* Put fill triangle function */
VOID QGR_PutTriangle( INT X0, INT Y0, INT X1, INT Y1,
         INT X2, INT Y2, qgrCOLOR Color );

/* Soft triangle filling (Gouraud shading) */
VOID QGR_PutGouraudTriangle( INT X0, INT Y0, qgrCOLOR Color0,
         INT X1, INT Y1, qgrCOLOR Color1,
         INT X2, INT Y2, qgrCOLOR Color2 );

/***
 * Fonts function
 ***/

/* Put char in graphic mode function */
INT QGR_PutChar( INT X, INT Y, CHAR Ch );

/* Put string in graphics mode function */
VOID QGR_PutString( INT X, INT Y, CHAR *Str, INT Width );

/* Load binary font from file function */
BOOL QGR_LoadBinFont( CHAR *FileName );

/* Set font number function */
VOID QGR_SetFontNo( INT FontNumber );

/* Get font number function */
INT QGR_GetFontNo( VOID );

/* Set attributes for current font function */
VOID QGR_SetTextAttr( qgrCOLOR ForeColor, qgrCOLOR BackColor,
         BOOL Transparent );

/* Set fore color for current font function */
VOID QGR_SetTextForeColor( qgrCOLOR ForeColor );

/* Set back color for current font function */
VOID QGR_SetTextBackColor( qgrCOLOR BackColor );

/* Set transparent for current font function */
VOID QGR_SetTextTransparent( BOOL Transparent );

/* Get fore color for current font function */
qgrCOLOR QGR_GetTextForeColor( VOID );

/* Get back color for current font function */
qgrCOLOR QGR_GetTextBackColor( VOID );

/* Get transparent for current font function */
BOOL QGR_GetTextTransparent( VOID );

/* Save current font from memory function */
VOID QGR_ClearFont( BYTE Amount, ... );

/***
 * Mouse global variables
 ***/

extern UINT
  QGR_MouseX,       /* Mouse X coordinate */
  QGR_MouseY;       /* Mouse Y coordinate */
extern INT
  QGR_MouseXMikki,  /* Mouse mikki X position */
  QGR_MouseYMikki;  /* Mouse mikki Y position */
extern UINT
  QGR_MouseButtons; /* Mouse buttons state */
extern UINT
  QGR_MouseButtonsAmount; /* Mouse buttons amount */

/***
 * Mouse functions
 ***/

/* Initialise mouse function */
BOOL QGR_InitMouse( VOID );

/* Set mouse to X, Y */
VOID QGR_MoveMouse( INT X, INT Y );

/* Get status of mouse : X, Y, Buttons to modul structure */
VOID QGR_GetMouseData( VOID );

/* Set horizontal and vertical range */
VOID QGR_SetMouseRange( INT Left, INT Top, INT Right, INT Bottom);

/* Set speed of mouse for horizontal and vertical */
VOID QGR_SetMouseSpeed( INT HorizontalSpeed, INT VerticalSpeed);

/* Set point of double speed */
VOID QGR_SetDoubleSpeedPoint( INT DoubleSpeedPoint );

/***
 * Cursor handle
 ***/

/* Register cursor in global stock function
 * (return -1 if any error occure) */
INT QGR_RegisterCursor( qgrCURSOR *CursorPtr );

/* Register cursor from file in global stock function
 * (return -1 if any error occure) */
INT QGR_RegisterCursorFile( CHAR *FileName );

/* Unregister cursor in global stock function */
BOOL QGR_UnregisterCursor( INT CursorNum );

/* Set new cursor in function */
BOOL QGR_SetCursor( INT Number );

/* Hide cursor function */
VOID QGR_HideCursor( VOID );

/* Show cursor function */
VOID QGR_ShowCursor( VOID );

/* Set cursor position function */
VOID QGR_MoveCursor( INT X, INT Y );

/***
 * Logic palette functions.
 ***/

/* Set color of logic palette */
VOID QGR_SetLogPal( INT Index, BYTE R, BYTE G, BYTE B );

/* Get color of logic palette */
qgrCOLOR QGR_GetEntryLogPal( INT Index );

#endif /* _TQGR_H_ */

/* END OF 'TQGR.H' FILE */
