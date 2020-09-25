#include <cstdio>
#include <cassert>
#include <string>
#include "StdioBoardView.h"

StdioBoardView::StdioBoardView( Mode mode, Board &board ) : BoardView(board), _mode(mode)
{
}

Position StdioBoardView::retrieveNextPosition()
{
  assert(_board.currentPlayer().has_value() &&
         "There's no player but want to get coordintes for move");
  if (printf("%c move: ", _board.currentPlayer() == Board::Player::X ? 'X' : 'O') < 0)
    printErrorAndAbort("Can't print invitation for move");

  static char str[1000] = {0}, nextChar, lastChar;
  fgets(str, 1000, stdin);
  int x, y;
  if (sscanf(str, "%d%c%d %c", &y, &nextChar, &x, &lastChar) != 3 || nextChar != ' ')
    x = y = -2;
  if (x == -1 && y == -1)
      _isExit = true;
  return Position(x, y);
}

void StdioBoardView::printBoard() const
{
  if (_mode == SILENT && _board.getState() == Board::State::GAME_IN_PROGRESS)
    return;
  std::string boardStr = "";

  boardStr += "\n";
  for (int y = 0; y < _board.SIZE; y++)
  {
    for (int x = 0; x < _board.SIZE; x++)
      if (_board(x, y) == Board::CellContent::X)
        boardStr += "X";
      else if (_board(x, y) == Board::CellContent::O)
        boardStr += "0";
      else
        boardStr += ".";

    boardStr += "\n";
  }

  if (printf("%s", boardStr.c_str()) < 0)
    printErrorAndAbort("Can't print game board");
}

void StdioBoardView::printWrongCoordsMsg() const
{
  if (printf("Bad move!\n") < 0)
    printErrorAndAbort("Can't print output information of game");
}

void StdioBoardView::printOutcome() const
{
  printBoard();

  std::string gameResult;
  if (_board.getState() == Board::State::X_WINS)
    gameResult = "X wins!";
  else if (_board.getState() == Board::State::O_WINS)
    gameResult = "O wins!";
  else
    gameResult = "Draw.";

  if (printf("%s\n", gameResult.c_str()) < 0)
    printErrorAndAbort("Can't print game result");
}
