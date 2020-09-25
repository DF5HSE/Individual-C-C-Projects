
#include "BoardTest.h"
#include "Board.h"

void BoardTest::testGetStateGameInProgress()
{
  Board b;

  b.move(Position(0, 0), Board::Player::O);
  b.move(Position(0, 1), Board::Player::X);
  b.move(Position(1, 0), Board::Player::O);
  b.move(Position(1, 2), Board::Player::X);
  b.move(Position(2, 0), Board::Player::O);
  b.move(Position(2, 3), Board::Player::X);
  b.move(Position(3, 0), Board::Player::O);
  b.move(Position(3, 4), Board::Player::X);

  b.move(Position(9, 9), Board::Player::O);
  b.move(Position(0, 9), Board::Player::X);
  b.move(Position(9, 8), Board::Player::O);
  b.move(Position(1, 8), Board::Player::X);
  b.move(Position(9, 7), Board::Player::O);
  b.move(Position(2, 7), Board::Player::X);
  b.move(Position(9, 6), Board::Player::O);
  b.move(Position(3, 6), Board::Player::X);

  /***
   *OX.......X
   *O.X.....X.
   *O..X...X..
   *O...X.X...
   *..........
   *..........
   *..........
   *..........
   *..........
   *......OOOO
   ***/
  DO_CHECK(b.getState() == Board::State::GAME_IN_PROGRESS);
}

void BoardTest::testGetStateOWins()
{
  Board b;

  b.move(Position(0, 0), Board::Player::O);
  b.move(Position(1, 0), Board::Player::X);
  b.move(Position(0, 1), Board::Player::O);
  b.move(Position(1, 1), Board::Player::X);
  b.move(Position(0, 2), Board::Player::O);
  b.move(Position(1, 2), Board::Player::X);
  b.move(Position(0, 3), Board::Player::O);
  b.move(Position(1, 3), Board::Player::X);
  b.move(Position(0, 4), Board::Player::O);
  DO_CHECK(b.getState() == Board::State::O_WINS);
}

void BoardTest::testGetStateXWins()
{
  Board b;

  b.move(Position(0, 0), Board::Player::O);
  b.move(Position(1, 0), Board::Player::X);
  b.move(Position(0, 1), Board::Player::O);
  b.move(Position(1, 1), Board::Player::X);
  b.move(Position(0, 2), Board::Player::O);
  b.move(Position(1, 2), Board::Player::X);
  b.move(Position(0, 3), Board::Player::O);
  b.move(Position(1, 3), Board::Player::X);
  b.move(Position(0, 5), Board::Player::O);
  b.move(Position(1, 4), Board::Player::X);
  DO_CHECK(b.getState() == Board::State::X_WINS);
}

void BoardTest::testGetStateDraw()
{
  Board b;
  for (int i = 0; i < 10; i++)
  {
    if (i % 3 > 1)
      for (int j = 0; j < 10; j++)
        b.move(Position(i, j), b.currentPlayer().value());
    else
      for (int j = 9; j >= 0; j--)
        b.move(Position(i, j), b.currentPlayer().value());
  }
  DO_CHECK(b.getState() == Board::State::DRAW);
}

void BoardTest::testCanMoveNotInField()
{
  Board b;

  DO_CHECK(!b.canMove(Position(10, -1), Board::Player::O));
}

void BoardTest::testCanMoveRightSignOnEmptyPlace()
{
  Board b;

  DO_CHECK(b.canMove(Position(0, 0), Board::Player::O));
}

void BoardTest::testCanMoveRightSignOnTakenPlace()
{
  Board b;

  b.move(Position(0, 0), Board::Player::O);
  DO_CHECK(!b.canMove(Position(0, 0), Board::Player::X));
}

void BoardTest::testCanMoveWrongSignOnEmptyPlace()
{
  Board b;

  DO_CHECK(!b.canMove(Position(0, 0), Board::Player::X));
}

void BoardTest::testCanMoveWrongSignOnTakenPlace()
{
  Board b;

  b.move(Position(0, 0), Board::Player::O);
  DO_CHECK(!b.canMove(Position(0, 0), Board::Player::O));
}

void BoardTest::testMove00()
{
  Board b;

  DO_CHECK(b.canMove(Position(0, 0), Board::Player::O));
  b.move(Position(0, 0), Board::Player::O);
  DO_CHECK(!b.canMove(Position(0, 0), Board::Player::X));
}

void BoardTest::testMove99()
{
  Board b;

  DO_CHECK(b.canMove(Position(0, 0), Board::Player::O));
  b.move(Position(0, 0), Board::Player::O);
  DO_CHECK(b.canMove(Position(9, 9), Board::Player::X));
  b.move(Position(9, 9), Board::Player::X);
  DO_CHECK(!b.canMove(Position(9, 9), Board::Player::O));
}

void BoardTest::testMove55()
{
  Board b;

  DO_CHECK(b.canMove(Position(0, 0), Board::Player::O));
  b.move(Position(0, 0), Board::Player::O);
  DO_CHECK(b.canMove(Position(9, 9), Board::Player::X));
  b.move(Position(9, 9), Board::Player::X);
  DO_CHECK(b.canMove(Position(5, 5), Board::Player::O));
  b.move(Position(5, 5), Board::Player::O);
  DO_CHECK(!b.canMove(Position(5, 5), Board::Player::X));
}

void BoardTest::testCurrentPlayerX()
{
  Board b;

  b.move(Position(0, 0), Board::Player::O);
  DO_CHECK(b.currentPlayer() == Board::Player::X);
}

void BoardTest::testCurrentPlayerO()
{
  Board b;

  DO_CHECK(b.currentPlayer() == Board::Player::O);
}

void BoardTest::testNoCurrentPlayer()
{
  Board b;

  b.move(Position(0, 0), Board::Player::O);
  b.move(Position(1, 0), Board::Player::X);
  b.move(Position(0, 1), Board::Player::O);
  b.move(Position(1, 1), Board::Player::X);
  b.move(Position(0, 2), Board::Player::O);
  b.move(Position(1, 2), Board::Player::X);
  b.move(Position(0, 3), Board::Player::O);
  b.move(Position(1, 3), Board::Player::X);
  b.move(Position(0, 5), Board::Player::O);
  b.move(Position(1, 4), Board::Player::X);
  DO_CHECK(!b.currentPlayer().has_value());
}

void BoardTest::testOperatorParenthesisX()
{
  Board b;

  b.move(Position(0, 0), Board::Player::O);
  b.move(Position(1, 0), Board::Player::X);
  DO_CHECK(b(1, 0) == Board::CellContent::X);
}

void BoardTest::testOperatorParenthesisO()
{
  Board b;

  b.move(Position(0, 0), Board::Player::O);
  DO_CHECK(b(0, 0) == Board::CellContent::O);
}

void BoardTest::testOperatorParenthesisEmpty()
{
  Board b;

  DO_CHECK(b(0, 0) == Board::CellContent::EMPTY);
}

void BoardTest::runAllTests()
{
  testGetStateGameInProgress();
  testGetStateXWins();
  testGetStateOWins();
  testGetStateDraw();

  testCanMoveNotInField();
  testCanMoveRightSignOnEmptyPlace();
  testCanMoveRightSignOnTakenPlace();
  testCanMoveWrongSignOnEmptyPlace();
  testCanMoveWrongSignOnTakenPlace();

  testMove00();
  testMove99();
  testMove55();

  testCurrentPlayerX();
  testCurrentPlayerO();
  testNoCurrentPlayer();

  testOperatorParenthesisEmpty();
  testOperatorParenthesisX();
  testOperatorParenthesisO();
}
