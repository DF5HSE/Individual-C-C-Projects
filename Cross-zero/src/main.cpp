#include <cstring>
#include <cstdio>
#include "Board.h"
#include "StdioBoardView.h"
#include "NcursesBoardView.h"
#include "GameController.h"

int main( int argc, char *argv[] )
{
  Board board;

  if (argc == 2 && !strcmp(argv[1], "curses"))
  {
    NcursesBoardView view(board);
    GameController gameController(view);
    gameController.doGameCycle();
    return 0;
  }
  else
  {
    StdioBoardView::Mode silent = StdioBoardView::DEFAULT;
    if (argc == 2 && !strcmp(argv[1], "silent"))
      silent = StdioBoardView::SILENT;
    if (argc == 1 || silent == StdioBoardView::SILENT)
    {
      StdioBoardView view(silent, board);
      GameController gameController(view);
      gameController.doGameCycle();
      return 0;
    }
  }

  printf("There isn't that mode.\n");
  return 0;
}
