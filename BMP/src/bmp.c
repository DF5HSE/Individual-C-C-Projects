#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bmp.h"

int load_bmp( char *fileName, bmp_image *image, char *error )
{
  FILE *fin;

  if ((fin = fopen(fileName, "rb")) == NULL)
  {
    if (error != NULL)
      sprintf(error, "Can't open file %s", fileName);
    return -1;
  }

  fread(&image->bmfh, sizeof(BITMAPFILEHEADER), 1, fin);
  fread(&image->bmih, sizeof(BITMAPINFOHEADER), 1, fin);

  if (image->bmih.biBitCount != 24)
  {
    if (error != NULL)
      sprintf(error, "Can't load image cropWith not 24-bit format");
    fclose(fin);
    return -1;
  }

  image->w = image->bmih.biWidth;
  image->h = abs(image->bmih.biHeight);
  if ((image->bits = malloc(image->w * abs(image->h) * numOfColorComps)) == NULL)
  {
    if (error != NULL)
      sprintf(error, "Can't allocate memory for image from %s", fileName);
    fclose(fin);
    return -1;
  }

  int isWidthNotMultip4 = (image->w * numOfColorComps) % 4;
  for (int i = 0; i < image->h; i++)
  {
    fread(image->bits + i * image->w * numOfColorComps, 1, image->w * numOfColorComps, fin);
    if (isWidthNotMultip4)
      for (int j = 0; j < 4 - isWidthNotMultip4; j++)
        fgetc(fin);
  }

  fclose(fin);
  return 0;
}

void test_save_ppm( uint8_t *bits, int w, int h )
{
  FILE *fout;

  if ((fout = fopen("samples/test.ppm", "wb")) == NULL)
    return;

  fprintf(fout, "P6\n\n%d %d\n%d\n", w, h, 255);
  for (int i = 0; i < h; i++)
    for (int j = 0; j < w; j++)
      for (int k = numOfColorComps - 1; k >= 0; k--)
        fputc(*(bits + i * w * numOfColorComps + j * numOfColorComps + k), fout);

  fclose(fout);
}

int crop( bmp_image *imageForCrop, bmp_image *croppedImage,
          int cropX, int cropY, int cropW, int cropH, char *error )
{
  if (!(0 <= cropX && cropX < cropX + cropW && cropX + cropW <= imageForCrop->w &&
        0 <= cropY && cropY < cropY + cropH && cropY + cropH <= imageForCrop->h))
  {
    if (error != NULL)
      sprintf(error, "Wrong arguments for cropping (going beyond the boundaries of image)");
    return -1;
  }

  if ((croppedImage->bits = malloc(cropW * cropH * numOfColorComps)) == NULL)
  {
    if (error != NULL)
      sprintf(error, "Can't allocate memory for cropped image bits");
    return -1;
  }

  croppedImage->bmfh.bfType = (uint16_t)((((int)('M')) << 8) + (int)('B'));
  croppedImage->bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
                              ((cropW * numOfColorComps + 3) / 4) * 4 * cropH;
  croppedImage->bmfh.bfReserved1 = croppedImage->bmfh.bfReserved2 = 0;
  croppedImage->bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  croppedImage->bmih.biSize = sizeof(BITMAPINFOHEADER);
  croppedImage->bmih.biWidth = croppedImage->w = cropW;
  croppedImage->bmih.biHeight = croppedImage->h = cropH;
  croppedImage->bmih.biPlanes = 1;
  croppedImage->bmih.biBitCount = 24;
  croppedImage->bmih.biCompression = 0;
  croppedImage->bmih.biSizeImage = ((cropW * numOfColorComps + 3) / 4) * 4 * cropH;
  croppedImage->bmih.biXPelsPerMeter = croppedImage->bmih.biYPelsPerMeter = 0;
  croppedImage->bmih.biClrUsed = 0;
  croppedImage->bmih.biClrImportant = 0;

  for (int i = 0; i < cropH; i++)
    memcpy(croppedImage->bits + i * cropW * numOfColorComps, 
           imageForCrop->bits + ((i + cropY) * imageForCrop->w + cropX) * numOfColorComps,
           cropW * numOfColorComps);

  return 0;
}

int rotate( bmp_image *imageForRotate, bmp_image *rotatedImage, char *error )
{
  if ((rotatedImage->bits = malloc(imageForRotate->w * imageForRotate->h * numOfColorComps)) == NULL)
  {
    if (error != NULL)
      sprintf(error, "Can't allocate memory for cropped image bits");
    return -1;
  }

  rotatedImage->bmfh.bfType = (uint16_t)((((int)('M')) << 8) + (int)('B'));
  rotatedImage->bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
                              ((imageForRotate->h * numOfColorComps + 3) / 4) * 4 * imageForRotate->w;
  rotatedImage->bmfh.bfReserved1 = rotatedImage->bmfh.bfReserved2 = 0;
  rotatedImage->bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  rotatedImage->bmih.biSize = sizeof(BITMAPINFOHEADER);
  rotatedImage->bmih.biWidth = rotatedImage->w = imageForRotate->h;
  rotatedImage->bmih.biHeight = rotatedImage->h = imageForRotate->w;
  rotatedImage->bmih.biPlanes = 1;
  rotatedImage->bmih.biBitCount = 24;
  rotatedImage->bmih.biCompression = 0;
  rotatedImage->bmih.biSizeImage = ((imageForRotate->h * numOfColorComps + 3) / 4) * 4 * imageForRotate->w;
  rotatedImage->bmih.biXPelsPerMeter =rotatedImage->bmih.biYPelsPerMeter = 0;
  rotatedImage->bmih.biClrUsed = 0;
  rotatedImage->bmih.biClrImportant = 0;

  for (int i = 0; i < imageForRotate->h; i++)
    for (int j = 0; j < imageForRotate->w; j++)
       memcpy(rotatedImage->bits + ((rotatedImage->h - 1 - j) * rotatedImage->w + i) *  numOfColorComps,
              imageForRotate->bits + (i * imageForRotate->w + j) * numOfColorComps, numOfColorComps);

  return 0;
}

int save_bmp( char *fileName, bmp_image *image, char *error )
{
  FILE *fout;

  if ((fout = fopen(fileName, "wb")) == NULL)
  {
    if (error != NULL)
      sprintf(error, "Can't open file %s", fileName);
    return -1;
  }

  fwrite(&image->bmfh, sizeof(BITMAPFILEHEADER), 1, fout);
  fwrite(&image->bmih, sizeof(BITMAPINFOHEADER), 1, fout);

  int isWidthNotMultip4 = (image->w * numOfColorComps) % 4;
  for (int i = 0; i < image->h; i++)
  {
    fwrite(image->bits + i * image->w * numOfColorComps, 1, image->w * numOfColorComps, fout);
    if (isWidthNotMultip4)
      for (int j = 0; j < 4 - isWidthNotMultip4; j++)
        fputc(0, fout);
  }

  fclose(fout);
  return 0;
}
