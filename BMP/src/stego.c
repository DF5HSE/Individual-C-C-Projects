#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "stego.h"

static int encodeChar( char c )
{
  if ('A' <= c && c <= 'Z')
    return c - 'A';
  else
    return c == ' ' ? 26 :     // ' ' == 26
           c == '.' ? 27 : 28; // '.' == 27, ',' == 28
}

static char decodeChar( int code )
{
  if (code + 'A' <= 'Z')
    return 'A' + code;
  else
    return code == 26 ? ' ' : code == 27 ? '.' : ',';
}


static int doSomethingInPoses( char *fileNameKey, bmp_image *imageIn, char *msg, char mode )
{
  int x, y, comp, code = 0, numOfReadBits = 0, i = 0;
  char compChar;

  FILE *fin;

  fin = fopen(fileNameKey, "r");
  while (fscanf(fin, "%d %d %c", &x, &y, &compChar) == 3)
  {
    comp = compChar == 'B' ? 0 : compChar == 'G' ? 1 : 2;

    if (mode == 'r')
    {
      code |= (imageIn->bits[(y * imageIn->w + x) * numOfColorComps + comp] & 1) << numOfReadBits++;
      if (numOfReadBits == 5)
      {
        msg[i++] = decodeChar(code);
        code = numOfReadBits = 0;
      }
    }
    else
    {
      numOfReadBits = numOfReadBits > 4 ? 0 : numOfReadBits;
      if (numOfReadBits++ == 0)
        code = encodeChar(msg[i++]);
      imageIn->bits[(y * imageIn->w + x) * numOfColorComps + comp] |= code & 1;
      imageIn->bits[(y * imageIn->w + x) * numOfColorComps + comp] &= 0xFE + code & 1;

      code >>= 1;
    }
  }

  if (mode == 'r')
    return i;
}

int insert_stego( char *InBMPFileName, char *OutBMPFileName, char *fileNameKey,
                  char *fileNameMsg, char *error )
{
  bmp_image imageIn;

  if (load_bmp(InBMPFileName, &imageIn, error) == -1)
    return -1;

  FILE *finMsg;

  if ((finMsg = fopen(fileNameMsg, "r")) == NULL)
  {
    sprintf(error, "Can't open file %s", fileNameMsg);
    free(imageIn.bits);
    return -1;
  }

  int sizeOfMsg;
  fseek(finMsg, 0, SEEK_END);
  sizeOfMsg = ftell(finMsg);
  if (sizeOfMsg < 0)
  {
    sprintf(error, "Can't find size of file %s", fileNameMsg);
    fclose(finMsg);
    free(imageIn.bits);
    return -1;
  }
  if (!sizeOfMsg)
  {
    sprintf(error, "warning: the message is empty\n");
    save_bmp(OutBMPFileName, &imageIn, error + sizeof("warning: the message is empty\n"));
    fclose(finMsg);
    free(imageIn.bits);
    return -1;
  }
  fseek(finMsg, 0, SEEK_SET);

  uint8_t *msg;
  if ((msg = malloc(sizeOfMsg)) == NULL)
  {
    sprintf(error, "Can't allocate memory for message");
    fclose(finMsg);
    free(imageIn.bits);
    return -1;
  }

  fread(msg, sizeof(uint8_t), sizeOfMsg, finMsg);
  fclose(finMsg);

  FILE *finKey;
  if ((finKey = fopen(fileNameKey, "w")) == NULL)
  {
    sprintf(error, "Can't open file %s", fileNameMsg);
    free(imageIn.bits);
    free(msg);
    return -1;
  }

  int
   code, x = 0, y = 0, comp = 0, bit, posInBits,
   numOfCharsBitsPerRow = (sizeOfMsg * 5 + imageIn.h) / imageIn.h -
                          (sizeOfMsg * 5 / imageIn.h * imageIn.h == sizeOfMsg * 5);
  int deltaX = imageIn.w * numOfColorComps  / numOfCharsBitsPerRow;

  if (deltaX < 1)
  {
    sprintf(error, "Too long message for this image");
    fclose(finKey);
    free(imageIn.bits);
    free(msg);
    return -1;
  }

  for (int i = 0; i < sizeOfMsg; i++)
    for (int j = 0; j < 5; j++)
    {
      fprintf(finKey, "%d %d %c\n", x, y, comp == 0 ? 'B' : comp == 1 ? 'G' : 'R');
      posInBits = (y * imageIn.w + x) * numOfColorComps + comp + deltaX;
      comp = posInBits % numOfColorComps;
      y = ((posInBits - comp) / numOfColorComps) / imageIn.w;
      x = (posInBits - comp) / numOfColorComps - y * imageIn.w;
    }

  fclose(finKey);
  doSomethingInPoses(fileNameKey, &imageIn, msg, 'w');
  free(msg);

  if (save_bmp(OutBMPFileName, &imageIn, error) == -1)
  {
    free(imageIn.bits);
    return -1;
  }

  free(imageIn.bits);
  return 0;
}

int extract_stego( char *InBMPFileName, char *fileNameKey, char *fileNameMsg, char *error )
{
  bmp_image imageIn;

  if (load_bmp(InBMPFileName, &imageIn, error) == -1)
    return -1;

  FILE *finKey;
  if ((finKey = fopen(fileNameKey, "r")) == NULL)
  {
    sprintf(error, "Can't open file %s", fileNameMsg);
    free(imageIn.bits);
    return -1;
  }

  uint8_t *msg, str[20];
  /***
   * I don't want to count number of lines in keys file by reading every line.
   * That is why I allocate max size of message which can be coded in image.
   ***/
  if ((msg = malloc(imageIn.w * imageIn.h * numOfColorComps / 5 + 3)) == NULL)
  {
    sprintf(error, "Can't allocate memory for message");
    fclose(finKey);
    free(imageIn.bits);
    return -1;
  }

  int sizeOfMsg;
  sizeOfMsg =  doSomethingInPoses(fileNameKey, &imageIn, msg, 'r');

  fclose(finKey);
  free(imageIn.bits);

  FILE *finMsg;
  if ((finMsg = fopen(fileNameMsg, "w")) == NULL)
  {
    sprintf(error, "Can't open file %s", fileNameMsg);
    free(msg);
    return -1;
  }

  fwrite(msg, sizeof(uint8_t), sizeOfMsg, finMsg);

  fclose(finMsg);
  free(msg);
  return 0;
}
