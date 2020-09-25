#include <string>
#include <ncurses.h>
#include "NcursesBoardView.h"

NcursesBoardView::NcursesBoardView( Board &board ) : BoardView(board)
{
  initscr(); // initialization of default window
  keypad(stdscr, TRUE); // enable read press F*, arrows and etc
  noecho(); // do nothing by pressing of key
}

NcursesBoardView::~NcursesBoardView()
{
  endwin(); // deinitialization of default window
}

Position NcursesBoardView::retrieveNextPosition()
{
  static Position pos(0, 0);

  move(pos.y, pos.x);
  int ch;
  while ((ch = getch()) != ' ')
  {
    switch (ch)
    {
    case KEY_UP:
      if (pos.y > 0)
        move(--pos.y, pos.x);
      break;
    case KEY_DOWN:
      if (pos.y < _board.SIZE - 1)
        move(++pos.y, pos.x);
      break;
    case KEY_LEFT:
      if (pos.x > 0)
        move(pos.y, --pos.x);
      break;
    case KEY_RIGHT:
      if (pos.x < _board.SIZE - 1)
        move(pos.y, ++pos.x);
      break;
    case 'x':
      _isExit = true;
      return Position(-1, -1);
    default:
      break;
    }
  }
  return pos;
}

void NcursesBoardView::printBoard() const
{
  move(0, 0); // move cursor on (row, col)
  std::string boardStr = "";

  for (int y = 0; y < _board.SIZE; y++)
  {
    for (int x = 0; x < _board.SIZE; x++)
      if (_board(x, y) == Board::CellContent::X)
        boardStr += "X";
      else if (_board(x, y) == Board::CellContent::O)
        boardStr += "O";
      else
        boardStr += ".";

    boardStr += "\n";
  }

  if (printw("%s", boardStr.c_str()) < 0) // print in default window
    printErrorAndAbort("Can't print game board");
  refresh(); // update window -- put out buffer
}

void NcursesBoardView::printWrongCoordsMsg() const
{
}

void NcursesBoardView::printOutcome() const
{
  printBoard();

  move(_board.SIZE, 0);
  std::string gameResult;
  if (_board.getState() == Board::State::X_WINS)
    gameResult = "X wins!";
  else if (_board.getState() == Board::State::O_WINS)
    gameResult = "O wins!";
  else
    gameResult = "Draw.";

  if (printw("%s\n", gameResult.c_str()) < 0)
    printErrorAndAbort("Can't print game result");

  refresh();
  getch(); // helps to see the result of game
}
