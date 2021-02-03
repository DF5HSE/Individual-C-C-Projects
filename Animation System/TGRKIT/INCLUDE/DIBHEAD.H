/***************************************************************
 * Copyright (C) 1992-1996
 *    Galinsky Software
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : DIBHEAD.H
 * PURPOSE     : DIB (Device Independent Bitmap)
 *               CUR (Cursor)
 *               ICO (Icon)
 *               of MS-Windows 3.* (*.BMP, *.CUR, *.ICO)
 *               files headers and handle macros.
 * PROGRAMMER  : Vitaly A. Galinsky.
 * LAST UPDATE : 15.10.1996
 * NOTE        : Module prefix 'DIB'.
 *               All structures, constants, names and comments
 *               was copied from MS-Windows SDK Help.
 *
 * No part of this file may be changed without agreement of
 * Vitaly A. Galinsky personally and Computer Graphics Support
 * Group of 30 Phys-Math Gymnasium.
 */

#ifndef _DIBHEAD_H_
#define _DIBHEAD_H_

#include <commondf.h>

/* File 2-bytes prefix ("BM") (see dibBITMAPFILEHEADER) */
#define DIB_FILEPREFIX ('B' | ('M' << 8))

/* Possible values for 'biCompression' field
 * (see dibBITMAPINFOHEADER) */
#define DIB_BI_RGB  0  /* Bitmap in not compressed format */
#define DIB_BI_RLE8 1  /* Use RLE compression for 8 bit picture */
#define DIB_BI_RLE4 2  /* Use RLE compression for 4 bit picture */

/* Determine MS-Windows BitMaps bytes per line value */
#define DIB_GetBytesPerLine(BitCount, Width) \
    ((BitCount) == 1 ? (((((Width) + 7) >> 3) + 3) >> 2) << 2 : \
     (BitCount) == 4 ? (((((Width) + 1) >> 1) + 3) >> 2) << 2 : \
     (BitCount) == 8 ? (((Width) + 3) >> 2) << 2 :              \
     (BitCount) == 24 ? (((Width) * 3 + 3) >> 2) << 2 : 0)

/* Obtain amount of colors in palette table by
 * bitmap info header structure */
#define DIB_GetColorsAmount(BitmapInfoHeader) \
    ((WORD)(BitmapInfoHeader).biClrUsed ?                    \
         (WORD)(BitmapInfoHeader).biClrUsed :                \
         COM_MAX((WORD)(1 << (BitmapInfoHeader).biBitCount), \
                 (WORD)(BitmapInfoHeader).biClrImportant))

/* Obtain specified line file position (from file begin and from
 * bitmap info header) by bitmap info header structure, bytes per
 * line amount and colors amount (not compressed images) */
#define DIB_GetLineFilePos(BmpInfoHeader, BytesPerLine, ClrAmount, Y) \
    (sizeof(dibBITMAPFILEHEADER) +          \
     sizeof(dibBITMAPINFOHEADER) +          \
     sizeof(dibRGBQUAD) * (ClrAmount) +     \
     (DWORD)(BytesPerLine) *                \
     ((BmpInfoHeader).biHeight - 1L - (Y)))

#define DIB_GetLineInfoPos(BmpInfoHeader, BytesPerLine, ClrAmount, Y) \
    (sizeof(dibBITMAPINFOHEADER) +          \
     sizeof(dibRGBQUAD) * (ClrAmount) +     \
     (DWORD)(BytesPerLine) *                \
     ((BmpInfoHeader).biHeight - 1L - (Y)))

/* Obtain image pixel bits from byte buffer */
#define DIB_GetPixelFromBuffer(Buf, BitsCount, X) \
    ((biBitCount) == 1 ?                            \
         !!((Buf)[(X) / 8] & (0x80 >> ((X) & 7))) : \
     (biBitCount) == 4 ?                            \
         ((X) & 1 ? (Buf)[(X) / 2] & 0x0F :         \
                    (Buf)[(X) / 2] >> 4) :          \
     (biBitCount) == 8 ?                            \
         (Buf)[(X)] :                               \
         (DWORD)(Buf)[(X)] << 16 |                  \
         (WORD)(Buf)[(X)] << 8 |                    \
         (Buf)[(X)])

/* Structure of the MS-Windows bitmap files:
 *     Bitmap file header.
 *     Bitmap info header.
 *     Palette table.
 *     Image bits (from last to first lines).
 */

/*
 * The dibBITMAPFILEHEADER structure contains information
 * about the type, size, and layout of a device-independent
 * bitmap (DIB) file.
 */
typedef struct tagdibBITMAPFILEHEADER /* bmfh */
{
  WORD  bfType;      /* Specifies the type of file.
                      * This member must be 'BM'.
                      * (see DIB_FILEPREFIX) */
  DWORD bfSize;      /* Specifies the size of the file, in bytes. */
  WORD  bfReserved1; /* Reserved; must be set to zero. */
  WORD  bfReserved2; /* Reserved; must be set to zero. */
  DWORD bfOffBits;   /* Specifies the byte offset from the
                      * dibBITMAPFILEHEADER structure to the actual
                      * bitmap data in the file. */
} dibBITMAPFILEHEADER;

/* The dibRGBQUAD structure describes a color consisting
 * of relative intensities of red, green, and blue.
 * The bmiColors member of the dibBITMAPINFO structure
 * consists of an array of dibRGBQUAD structures.
 */
typedef struct tagdibRGBQUAD     /* rgbq */
{
  BYTE  rgbBlue;     /* Specifies the intensity of blue
                      * in the color. */
  BYTE  rgbGreen;    /* Specifies the intensity of green
                      * in the color. */
  BYTE  rgbRed;      /* Specifies the intensity of red
                      * in the color. */
  BYTE  rgbReserved; /* Not used; must be set to zero. */
} dibRGBQUAD;

/* The dibBITMAPINFOHEADER structure contains information
 * about the dimensions and color format of a Windows
 * 3.0 or later device-independent bitmap (DIB).
 */
typedef struct tagdibBITMAPINFOHEADER /* bmih */
{
  /* Specifies the number of bytes required by the
   * dibBITMAPINFOHEADER structure. (always 40) */
  DWORD biSize;

  /* Specifies the width of the bitmap, in pixels. */
  LONG  biWidth;

  /* Specifies the height of the bitmap, in pixels. */
  LONG  biHeight;

  /* Specifies the number of planes for the target device.
   * This member must be set to 1. */
  WORD  biPlanes;

  /* Specifies the number of bits per pixel.
   * This value must be 1, 4, 8, or 24. */
  WORD  biBitCount;

  /* Specifies the type of compression for a compressed bitmap.
   * It can be one of the following values:
   * Value    Meaning
   * ------------------------------------------------------------
   * DIB_BI_RGB  Specifies that the bitmap is not compressed.
   * DIB_BI_RLE8 Specifies a run-length encoded format for
   *             bitmaps with 8 bits per pixel. The compression
   *             format is a 2-byte format consisting of a
   *             count byte followed by a byte containing a
   *             color index.
   * DIB_BI_RLE4 Specifies a run-length encoded format for
   *             bitmaps with 4 bits per pixel. The compression
   *             format is a 2-byte format consisting of a count
   *             byte followed by two word-length color indexes.
   * (See also DIB_BI_***) */
  DWORD biCompression;

  /* Specifies the size, in bytes, of the image. It is valid
   * to set this member to zero if the bitmap is in the
   * DIB_BI_RGB format. */
  DWORD biSizeImage;

  /* Specifies the horizontal resolution, in pixels per meter, of
   * the target device for the bitmap. An application can use this
   * value to select a bitmap from a resource group that best matches
   * the characteristics of the current device. */
  LONG  biXPelsPerMeter;

  /* Specifies the vertical resolution, in pixels per meter, of the
   * target device for the bitmap. */
  LONG  biYPelsPerMeter;

  /* Specifies the number of color indexes in the color table
   * actually used by the bitmap. If this value is zero, the
   * bitmap uses the maximum number of colors corresponding to
   * the value of the biBitCount member. For more information
   * on the maximum sizes of the color table, see the description
   * of the dibBITMAPINFO structure earlier in this topic.
   *
   * If the biClrUsed member is nonzero, it specifies the actual
   * number of colors that the graphics engine or device driver
   * will access if the biBitCount member is less than 24. If
   * biBitCount is set to 24, biClrUsed specifies the size of
   * the reference color table used to optimize performance of
   * Windows color palettes.
   *
   * If the bitmap is a packed bitmap (that is, a bitmap in which
   * the bitmap array immediately follows the dibBITMAPINFO header
   * and which is referenced by a single pointer), the biClrUsed
   * member must be set to zero or to the actual size of the color
   * table. */
  DWORD biClrUsed;

  /* Specifies the number of color indexes that are considered
   * important for displaying the bitmap. If this value is zero,
   * all colors are important. */
  DWORD biClrImportant;
} dibBITMAPINFOHEADER;

/* The dibBITMAPINFO structure fully defines the dimensions
 * and color information for a Windows 3.0 or later
 * device-independent bitmap (DIB).
 */
typedef struct tagdibBITMAPINFO /* bmi */
{
  /* Specifies a dibBITMAPINFOHEADER structure that contains
   * information about the dimensions and color format
   * of a DIB. */
  dibBITMAPINFOHEADER bmiHeader;

  /* Specifies an array of dibRGBQUAD structures that define the
   * colors in the bitmap. */
  dibRGBQUAD bmiColors[];
} dibBITMAPINFO;

/* Structure of the MS-Windows cursor files:
 *     Cursor file header.
 *     Cursor dir. entries (one for every cursor in file).
 *       For every cursor:
 *         Bitmap info header.
 *         Palette table (2 entries).
 *         XOR image.
 *         AND image.
 */

/* Cursor file header */
typedef struct tagdibCURSORHEADER
{
  WORD chReserved; /* Should be 0 */
  WORD chType;     /* Should be 2 */
  WORD chCount;    /* Cursors amount */
} dibCURSORHEADER;

/* One cursor entry description */
typedef struct tagdibCURSORDIRENTRY
{
  BYTE  bWidth;        /* Width of cursor image */
  BYTE  bHeight;       /* Height of cursor image */
  BYTE  bColorCount;   /* Color amount (2) */
  BYTE  bReserved;     /* Should be 0 */
  WORD  wXHotSpot;     /* Hot spot X coordinate */
  WORD  wYHotSpot;     /* Hot spot Y coordinate */
  DWORD dwBytesInRes;  /* Bytes amount in all resource */
  DWORD dwImageOffset; /* Cursor image offset from file begin */
} dibCURSORDIRENTRY;

/* Structure of the MS-Windows icon files:
 *     Icon file header.
 *     Icon dir. entries (one for every icon in file)
 *       For every icon:
 *         Bitmap info header
 *         Palette table (due to color information entries)
 *         XOR image
 *         AND image
 */

/* Icon file header */
typedef struct tagdibICONHEADER
{
  WORD ihReserved; /* Should be 0 */
  WORD ihType;     /* Should be 1 */
  WORD ihCount;    /* Icons amount */
} dibICONHEADER;

/* One icon entry description */
typedef struct tagdibICONDIRENTRY
{
  BYTE  bWidth;        /* Width of cursor image */
  BYTE  bHeight;       /* Height of cursor image */
  BYTE  bColorCount;   /* Color amount (2) */
  BYTE  bReserved;     /* Should be 0 */
  WORD  bReserved1;    /* Should be 0 */
  WORD  bReserved2;    /* Should be 0 */
  DWORD dwBytesInRes;  /* Bytes amount in all resource */
  DWORD dwImageOffset; /* Icon image offset from file begin */
} dibICONDIRENTRY;

#endif /* _DIBHEAD_H_ */

/* END OF 'DIBHEAD.H' FILE */

