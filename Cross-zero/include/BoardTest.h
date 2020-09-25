#pragma once
#include "Test.h"

class BoardTest final : public Test
{
private:
  void testGetStateGameInProgress();
  void testGetStateOWins();
  void testGetStateXWins();
  void testGetStateDraw();

  void testCanMoveNotInField();
  void testCanMoveRightSignOnEmptyPlace();
  void testCanMoveRightSignOnTakenPlace();
  void testCanMoveWrongSignOnEmptyPlace();
  void testCanMoveWrongSignOnTakenPlace();

  void testMove00();
  void testMove99();
  void testMove55();

  void testCurrentPlayerX();
  void testCurrentPlayerO();
  void testNoCurrentPlayer();

  void testOperatorParenthesisX();
  void testOperatorParenthesisO();
  void testOperatorParenthesisEmpty();

public:
  void runAllTests();
};
