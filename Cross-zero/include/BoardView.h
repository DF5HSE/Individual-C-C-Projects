#pragma once
#include "Board.h"

class BoardView
{
public:
  explicit BoardView( Board &board );
  Board & getBoardRef();
  bool isExit();

  virtual Position retrieveNextPosition() = 0;
  virtual void printBoard() const = 0;
  virtual void printWrongCoordsMsg() const = 0;
  virtual void printOutcome() const = 0;

protected:
  bool _isExit = false;
  Board &_board;

  static void printErrorAndAbort( const char *error );
};
