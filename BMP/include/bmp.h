#pragma once

#include <stdint.h>

#pragma pack (push, 1)

#define numOfColorComps 3

typedef struct BITMAPFILEHEADER
{
  uint16_t bfType;      // type of file (must be "BM")
  uint32_t bfSize;      // size of file in bytes
  uint16_t bfReserved1; // reserved variable (must be 0)
  uint16_t bfReserved2; // reserved variable (must be 0)
  uint32_t bfOffBits;   // offset in bytes from the beginning of the BITMAPFILEHEADER structure to the bitmap bits
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
 {
   uint32_t biSize;         // size of BITMAPINFOHEADER structure
   int32_t biWidth;         // width of image in pixels
   int32_t biHeight;        // height of image in pixels (if height < 0 bitmap is top-down DIB, else bitmap is bottom-down DIB)
   uint16_t biPlanes;       // number of planes (usually 1)
   uint16_t biBitCount;     // number of bits for color of each pixel
   uint32_t biCompression;  // type of compression (it is 0 in our situation)
   uint32_t biSizeImage;    // size of image in bytes (can be 0)
   int32_t biXPelsPerMeter; // horizontal resolution in pixels per meter of the target device
   int32_t biYPelsPerMeter; // vertical resolution in pixels per meter of the target device
   uint32_t biClrUsed;      // number of differrent colors
                            // (it is 0 in our situation -> all colors that BitCount provides)
   uint32_t biClrImportant; // number of important colors
                            // (it is 0 in our situation -> all colors important)
 } BITMAPINFOHEADER;

typedef struct bmp_image
{
  BITMAPFILEHEADER bmfh;
  BITMAPINFOHEADER bmih;

  int w, h;
  uint8_t *bits; // blue, green, red
} bmp_image;

int load_bmp( char *fileName, bmp_image *image, char *error );
int crop( bmp_image *imageForCrop, bmp_image *croppedImage,
          int cropX, int cropY, int cropW, int cropH, char *error );
int rotate( bmp_image *imageForRotate, bmp_image *rotatedImage, char *error );
int save_bmp( char *fileName, bmp_image *image, char *error );

void test_save_ppm( uint8_t *bits, int w, int h );

#pragma pack (pop)