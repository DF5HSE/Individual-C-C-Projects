#include "BoardView.h"

BoardView::BoardView( Board &board ) : _board(board)
{
}

Board & BoardView::getBoardRef()
{
  return _board;
}

bool BoardView::isExit()
{
  return _isExit;
}

void BoardView::printErrorAndAbort( const char *error )
{
  fprintf(stderr, "%s\n", error);
  std::abort();
}