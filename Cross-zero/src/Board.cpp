#include <cassert>
#include "Board.h"

Position::Position( int X, int Y ) : x(X), y(Y)
{
}

bool Board::checkInvarsSignsCnts() const
{
  return (_cntX == _cntO || _cntX + 1 == _cntO) && _cntO >= 0 && _cntX >= 0;
}

std::optional<Board::Player> Board::currentPlayer() const
{
  assert(checkInvarsSignsCnts() &&
    "[Board::currentPlayer] invariant of counter X and Y wasn't kept");
  if (_state != State::GAME_IN_PROGRESS)
    return std::nullopt;
  if (_cntO == _cntX)
    return Player::O;
  else
    return Player::X;
}

bool Board::isInRowOneSign( Position pos, std::pair<int, int> direction ) const
{
  assert(_field[pos.y][pos.x] != CellContent::EMPTY && "[Board::isInRowOneSign] start from empty cell");
  for (int i = 0, newY, newX; i < INROW; i++)
  {
    newY = pos.y + i * direction.first;
    newX = pos.x + i * direction.second;
    if (newY < 0 || newY >= SIZE || newX < 0 || newX >= SIZE || _field[newY][newX] != _field[pos.y][pos.x])
      return false;
  }
  return true;
}

std::optional<Board::Player> Board::winner() const
{
  // <yDeltaMultip, xDeltaMultip>
  static const std::pair<int, int> directions[] = 
  {
    {1, 1},  // diagonal
    {1, -1}, // back diagonal
    {1, 0},  // vertical
    {0, 1}   // horizontal
  };

  for (auto dir : directions)
    for (int y = 0; y < SIZE; y++)
      for (int x = 0; x < SIZE; x++)
      {
        if (_field[y][x] == CellContent::EMPTY)
          continue;
        if (isInRowOneSign(Position(x, y), dir))
          return std::optional<Player>(_field[y][x] == CellContent::X ? Player::X : Player::O);
      }
  return std::nullopt;
}

bool Board::canMove( Position pos, Player player ) const
{
  if (pos.x < 0 || pos.x >= SIZE || pos.y < 0 || pos.y >= SIZE || _field[pos.y][pos.x] != CellContent::EMPTY ||
      currentPlayer() != player || _state != State::GAME_IN_PROGRESS)
    return false;
  return true;
}

void Board::move( Position pos, Player player )
{
  assert(canMove(pos, player) && "[Board::move] Trying of moving against the rules");
  if (player == Player::X)
  {
    _cntX++;
    _field[pos.y][pos.x] = CellContent::X;
  }
  else
  {
    _cntO++;
    _field[pos.y][pos.x] = CellContent::O;
  }
  if (winner().has_value())
    if (player == Player::X)
      _state = State::X_WINS;
    else
      _state = State::O_WINS;
  else if (_cntX + _cntO == SIZE * SIZE)
    _state = State::DRAW;
}

Board::State Board::getState() const
{
  return _state;
}

Board::CellContent Board::operator()( int x, int y ) const
{
  return _field[y][x];
}
