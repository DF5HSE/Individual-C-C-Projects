/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TGLMAIN.cpp
 * PURPOSE     : Tough Graphics Language project.
 *               Main file.
 * PROGRAMMER  : CGSG'2018.
 * LAST UPDATE : 21.10.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <fstream>
#include <conio.h>
#include <string>
#include "tglcontainer.h"
#include "tgllangcl.h"

INT main( VOID )
{
  tgl::language Lang;
  BOOL run = TRUE;

  
  std::cout << "/***************************************************************\n"
            << " * Welcome to test of 'POLIZ' calculator!!!\n"
            << " * 0 - close\n"
            << " * 1 - calculate\n"
            << " * 2 - d1SkA4\n"
            << " ***************************************************************/\n";

  while (run)
  {
    switch (_getch())
    {
    case '0':
      _getch();
      run = FALSE;
      break;
    case '1':
      try
      {
        _getch();

        std::ifstream f = std::ifstream("tglCode/test.tgl");

        std::string Code = std::string((std::istreambuf_iterator<CHAR>(f)), (std::istreambuf_iterator<CHAR>()));

        Lang.Scanner(Code);

        tgl::language::CMD *Proga;

        Lang.ParseProgram(&Proga);
        Lang.DoCmd(Proga);
        //Lang.ParseExpr(Lang.TokQueue);
        std::cout << "= " << Lang.ResultOfCalc << "\n";

        delete Proga;
      }
      catch (std::exception Error)
      {
        _getch();
        std::cout << "ERROR: " << Error.what();
      }
      break;
    default:
      _getch();
      std::cout << "There isn't that function\n";
      break;
    }
    std::cout << "________________________________________________________________\n";
  }

  std::cout << "GoodBy\n";
  getchar();
  return 0;
} /* End of 'main' file */

/* END OF 'TGLMAIN.cpp' FILE */
