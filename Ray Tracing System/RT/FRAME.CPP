/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : FRAME.CPP
 * PURPOSE     : Ray tracing project.
 *               Frame class implementation module.
 * PROGRAMMER  : CGSG'2018.
 *               Filippov Denis.
 * LAST UPDATE : 02.09.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include <thread>
#include "frame.h"

/* Default frame class constructor.
 * ARGUMENTS: None.
 */
firt::frame::frame( VOID )
{
} /* End of 'firt::frame::frame' function */

/* Frame class destructor.
 * ARGUMENTS: None.
 */
firt::frame::~frame( VOID )
{
  for (auto s : Scene.SList.Shapes)
    delete s;
  for (auto s : Scene.LList)
    delete s;
} /* End of 'firt::frame::~frame' function */

/* Frame class constructor.
 * ARGUMENTS:
 *   - hInstance:
 *       HINSTANCE hInst;
 */
firt::frame::frame( HINSTANCE hInst ) : win(hInst)
{
  Img = image(win::hWnd, win::FrameW, win::FrameH);
} /* End of 'firt::frame::frame' function */

/* Frame initialization function.
 * ARGUMENTS: None.
 * RRTURNS: None. 
 */
VOID firt::frame::Init( VOID )
{
  Cam.SetLocAtUp(vec(-6, 5, 4) / 0.7, vec(0), vec(0, 1, 0));
  Cam.Resize(Img.GetW(), Img.GetH());

  material
    Mtl1 = material(vec(0.24, 0.19, 0.07), vec(0.75, 0.60, 0.23), vec(0.63, 0.56, 0.37), vec(0.5), vec(0), 51.2), // Gold
    Mtl2 = material(vec(0.23145), vec(0.2775), vec(0.77391), vec(0.35), vec(0), 51.2), // Silver
    Mtl3 = material(vec(0.1), vec(0.2), vec(0.3), vec(0), vec(0.5), 100),
    Mtl4 = material(vec(0.23145), vec(0.2775), vec(0.77391), vec(0), vec(1), 51.2); // glass

  environment Envi(0.1, 0.8);

  Scene << new sphere(vec(-6, 1, 3), 2, Mtl1, Envi)
        << new sphere(vec(-3, 1, 6), 1, Mtl2, Envi)
        << new tor(4, 1, Mtl1, Envi)
        //<< new quadric(1, 0, 0, 0, 0, 0, -0.5, 1, 0, 0, Mtl1, Envi)
        << new plane(-1, vec(0, 1, 0), Mtl1, Envi)
        << new box(vec(-6, -1, -6), vec(-4, 1, -4), Mtl4, Envi)
        << new light(vec(6, 10, 6), 1, 0.01, 0.01, vec(1, 1, 1));

  INT NumOfThreads = 1; //std::thread::hardware_concurrency() - 1;
  std::thread trs[1]; // = new std::thread[NumOfThreads];
  for (INT i = 0; i < NumOfThreads; i++)
    trs[i] = std::thread([&]( VOID )
      {
        Scene.Render(Cam, &Img, i, NumOfThreads);
      });

    //trs[i] = std::thread(&firt::scene::Render, &Scene, Cam, &Img, i, NumOfThreads);

  for (INT i = 0; i < NumOfThreads; i++)
    trs[i].join();
  //delete[] trs;
  //trs[1] = std::thread(&Scene.Render, this, X1, B1, C1, s, c, Wscr, Hscr, Loc, 1, std::ref(fb));
  //trs[2] = std::thread(&Scene.Render, this, X1, B1, C1, s, c, Wscr, Hscr, Loc, 2, std::ref(fb));
  //trs[3] = std::thread(&Scene.Render, this, X1, B1, C1, s, c, Wscr, Hscr, Loc, 3, std::ref(fb));
  //trs[0].join();
  //trs[1].join();
  //trs[2].join();
  //trs[3].join();

  //Scene.Render(Cam, &Img, 0, 1);
  Img.SaveBMP("test2.bmp");
} /* End of 'firt::frame::Init' function */

/* Paint window content function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID firt::frame::Paint( HDC hDC )
{
  Img.Draw(hDC);
} /* End of 'firt::frame::Paint' function */

/* Change window size handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID firt::frame::Resize( INT W, INT H )
{
  Img.Resize(W, H);
  Cam.Resize(W, H);
} /* End of 'firt::frame::Resize' function */

/* END OF 'FRAME.CPP' FILE*/
