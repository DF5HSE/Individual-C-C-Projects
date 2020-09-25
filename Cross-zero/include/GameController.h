#pragma once
#include "Board.h"
#include "BoardView.h"

class GameController final
{
public:
  explicit GameController( BoardView &view );
  void doGameCycle();

private:
  Board &_board;
  BoardView &_view;
};
