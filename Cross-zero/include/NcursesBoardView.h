#pragma once
#include "Board.h"
#include "BoardView.h"

class NcursesBoardView final : public BoardView
{
public:
  explicit NcursesBoardView( Board &board );
  ~NcursesBoardView();

  Position retrieveNextPosition() override;
  void printBoard() const override;
  void printWrongCoordsMsg() const override;
  void printOutcome() const override;

};
