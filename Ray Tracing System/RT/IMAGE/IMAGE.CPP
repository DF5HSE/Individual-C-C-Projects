/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : IMAGE.CPP
 * PURPOSE     : Ray tracing project.
 *               Image class implementation module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 25.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "image.h"

/* Default image class constructor.
 * ARGUMENTS: None.
 */
firt::image::image( VOID )
{
} /* End of 'firt::image::image' function */

/* Image class constructor.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 *   - image size:
 *       INT W, H;
 */
firt::image::image( HWND hWnd, INT W, INT H ) : hWnd(hWnd)
{
  HDC hDC = GetDC(hWnd);

  hMemDC = CreateCompatibleDC(hDC);

  memset(&bmih, 0, sizeof(bmih));
  bmih.biSize = sizeof(BITMAPINFOHEADER);
  bmih.biBitCount = 32;
  bmih.biPlanes = 1;
  bmih.biCompression = BI_RGB;
  bmih.biWidth = FrameW = W;
  bmih.biHeight = -H, FrameH = H;
  bmih.biSizeImage = FrameW * FrameH * 4;
  bmih.biClrUsed = 0;
  bmih.biClrImportant = 0;
  bmih.biXPelsPerMeter = bmih.biYPelsPerMeter = 0;

  hBm = CreateDIBSection(NULL, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, (VOID **)&Bits, NULL, 0);

  for (int i = 0; i < FrameH; i++)
    for (int j = 0; j < FrameW; j++)
      Bits[i * FrameW + j] = 0x00FFFF00;

  SelectObject(hMemDC, hBm);
  ReleaseDC(hWnd, hDC);
} /* End of 'firt::image::image' function */

/* Image class destructor.
 * ARGUMENTS: None.
 */
firt::image::~image( VOID )
{
} /* End of 'firt::image::~image' function */

/* Image resize function.
 * ARGUMENTS:
 *   - new frame size:
 *       INT NewW, NewH;
 * RETURNS: None.
 */
VOID firt::image::Resize( INT NewW, INT NewH )
{
  if (hBm != nullptr)
    DeleteObject(hBm);
  DeleteDC(hMemDC);

  HDC hDC = GetDC(hWnd);

  hMemDC = CreateCompatibleDC(hDC);

  memset(&bmih, 0, sizeof(bmih));
  bmih.biSize = sizeof(BITMAPINFOHEADER);
  bmih.biBitCount = 32;
  bmih.biPlanes = 1;
  bmih.biCompression = BI_RGB;
  bmih.biWidth = FrameW = NewW;
  bmih.biHeight = -NewH, FrameH = NewH;
  bmih.biSizeImage = FrameW * FrameH * 4;
  bmih.biClrUsed = 0;
  bmih.biClrImportant = 0;
  bmih.biXPelsPerMeter = bmih.biYPelsPerMeter = 0;

  hBm = CreateDIBSection(NULL, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, (VOID **)&Bits, NULL, 0);
  SelectObject(hMemDC, hBm);
  ReleaseDC(hWnd, hDC);
} /* End of 'firt::image::Resize' function */

/* Draw image function.
 * ARGUMENTS:
 *   - hDC for drawing:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID firt::image::Draw( HDC hDC )
{
  BitBlt(hDC, 0, 0, FrameW, FrameH, hMemDC, 0, 0, SRCCOPY);
} /* End of 'firt::image::Draw' function */

/* Get image width function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) image width.
 */
INT firt::image::GetW( VOID )
{
  return FrameW;
} /* End of 'firt::image::GetW' function */

/* Get image hight function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) image hight.
 */
INT firt::image::GetH( VOID )
{
  return FrameH;
} /* End of 'firt::image::GetH' function */

/* Put pixel function.
 * ARGUMENTS:
 *   - pixels image coordinates:
 *       INT X, Y;
 *   - color:
 *       DWORD Color;
 * RETURNS: None.
 */
VOID firt::image::PutPixel( INT X, INT Y, DWORD Color )
{
  Bits[Y * FrameW + X] = Color;
} /* End of 'firt::image::PutPixel' function */

/* Get pixel function.
 * ARGUMENTS:
 *   - pixels image coordinates:
 *       INT X, Y;
 * RETURNS:
 *   (DWORD) color of pixel.
 */
DWORD firt::image::GetPixel( INT X, INT Y )
{
  return Bits[Y * FrameW + X];
} /* End of 'firt::image::GetPixel' function */

/* Make color from vector to DWORD function.
 * ARGUMENTS:
 *   - color vector:
 *       const vec &Color;
 * RETURNS:
 *   (DWORD) color.
 */
DWORD firt::image::vecRGBtoDWORD( const vec &Color )
{
  return ((DWORD)(Color[0] * 255) << 16) | ((DWORD)(Color[1] * 255) << 8) | ((DWORD)(Color[2] * 255));
} /* End of 'firt::image::vecRGBtoDWORD' function */

/* Save image in BMP format function.
 * ARGUMENTS:
 *   - name of file for saving:
 *        const std::string &SaveFileName;
 * RETURNS:
 *   (BOOL) if succesfull - TRUE, else - FALSE;
 */
BOOL firt::image::SaveBMP( const std::string &SaveFileName )
{
  BITMAPFILEHEADER bfh;
  BITMAPINFOHEADER bih;
  UINT bpl;  // bytes per line - should be multiple 4

  bpl = (FrameW * 3 + 3) / 4 * 4;

  /* заполняем заголовки */
  bfh.bfType = 'B' | ('M' << 8);
  bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bpl * FrameH;
  bfh.bfReserved1 = 0;
  bfh.bfReserved2 = 0;
  bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  bih.biSize = sizeof(BITMAPINFOHEADER);
  bih.biWidth = FrameW;
  bih.biHeight = FrameH;
  bih.biPlanes = 1;
  bih.biBitCount = 24;
  bih.biCompression = BI_RGB;
  bih.biSizeImage = bpl * FrameH;
  bih.biClrImportant = 0;
  bih.biClrUsed = 0;
  bih.biXPelsPerMeter = bih.biYPelsPerMeter = 0;

  FILE *F;
  if ((F = fopen(SaveFileName.c_str(), "wb")) == nullptr)
    return FALSE;
  /* записываем в файл */
  fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, F);
  fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, F);

  BYTE *row = new BYTE[bpl];

  for (INT y = FrameH - 1; y >= 0; y--)
  {
    for (INT x = 0; x < FrameW; x++)
    {
      row[x * 3 + 0] = Bits[y * FrameW + x] & 0xFF;
      row[x * 3 + 1] = (Bits[y * FrameW + x] >> 8) & 0xFF;
      row[x * 3 + 2] = (Bits[y * FrameW + x] >> 16) & 0xFF;
    }
    fwrite(row, 1, bpl, F);
  }
  delete[] row;

  fclose(F);

  return TRUE;
} /* End of 'firt::image::SaveBMP' function */
/* END OF 'IMAGE.CPP' FILE */

