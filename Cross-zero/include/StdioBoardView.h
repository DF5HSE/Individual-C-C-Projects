#pragma once
#include <optional>
#include "Board.h"
#include "BoardView.h"

class StdioBoardView final : public BoardView
{
public:
  enum Mode
  {
    DEFAULT, SILENT
  };
  explicit StdioBoardView( Mode mode, Board &board );

  Position retrieveNextPosition() override;
  void printBoard() const override;
  void printWrongCoordsMsg() const override;
  void printOutcome() const override;

private:
  const Mode _mode;
};
