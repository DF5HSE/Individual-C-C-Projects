#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"
#include "stego.h"

int crop_rotate_bmp( int argc, char *argv[], char *error )
{
  bmp_image image;

  if (argc != 8)
  {
    sprintf(error, "Wrong number of arguments\n");
    return -1;
  }

  if (load_bmp(argv[2], &image, error) == -1)
    return -1;

  bmp_image croppedImage;
  int cropX = atoi(argv[4]), cropY = atoi(argv[5]), cropW = atoi(argv[6]), cropH = atoi(argv[7]);
  if (crop(&image, &croppedImage, cropX, cropY, cropW, cropH, error) == -1)
    return -1;

  bmp_image rotatedCroppedImage;
  int rotCropW, rotCropH;
  if (rotate(&croppedImage, &rotatedCroppedImage, error) == -1)
    return -1;

  if (save_bmp(argv[3], &rotatedCroppedImage, error) == -1)
    return -1;

  free(croppedImage.bits);
  free(rotatedCroppedImage.bits);
  free(image.bits);
  return 0;
}

int stego_bmp( int argc,  char *argv[], char *error )
{
  if (strcmp(argv[1], "insert") == 0)
  {
    if (argc != 6)
    {
      sprintf(error, "Wrong number of arguments\n");
      return -1;
    }

    return insert_stego(argv[2], argv[3], argv[4], argv[5], error);
  }

  if (argc != 5)
  {
    sprintf(error, "Wrong number of arguments\n");
    return -1;
  }

  return extract_stego(argv[2], argv[3], argv[4], error);
}

int main( int argc, char *argv[] )
{
  char error[100];
  if (strcmp(argv[1], "crop-rotate") == 0)
  {
    if (crop_rotate_bmp(argc, argv, error) == -1)
    {
      printf("%s\n", error);
      return 0;
    }
  }
  else
  {
    if (stego_bmp(argc, argv, error) == -1)
    {
      printf("%s\n", error);
      return 0;
    }
  }

 return 0;
}