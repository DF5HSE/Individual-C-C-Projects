#pragma once
#include <optional>

struct Position final
{
  explicit Position( int X = 0, int Y = 0 );
  int x, y;
};

class Board final
{
public:
  enum class State
  {
    GAME_IN_PROGRESS, DRAW, O_WINS, X_WINS
  };
  enum class CellContent
  {
    EMPTY, O, X
  };
  enum class Player
  {
    O, X
  };

  static constexpr int SIZE = 10;
  static constexpr int INROW = 5;

  bool canMove( Position pos, Player player ) const;
  void move( Position pos, Player player );
  std::optional<Player> currentPlayer() const;
  State getState() const;
  CellContent operator()( int x, int y ) const;

private:
  int _cntO = 0, _cntX = 0;

  State _state = State::GAME_IN_PROGRESS;
  CellContent _field[SIZE][SIZE] = {CellContent::EMPTY};

  bool isInRowOneSign( Position pos, std::pair<int, int> direction ) const;
  bool checkInvarsSignsCnts() const;
  std::optional<Player> winner() const;
};
