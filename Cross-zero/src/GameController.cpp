#include <cassert>
#include <optional>
#include "GameController.h"

GameController::GameController( BoardView &view ) : _board(view.getBoardRef()), _view(view)
{
}

void GameController::doGameCycle()
{
  Position pos;
  std::optional<Board::Player> player;
  while (_board.getState() == Board::State::GAME_IN_PROGRESS)
  {
    _view.printBoard();
    pos = _view.retrieveNextPosition();
    player = _board.currentPlayer();
    assert(player.has_value() &&
           "[GameController::doGameCycle] There's no player, but game in progress");
    while (!_board.canMove(pos, player.value()))
    {
      if (_view.isExit())
        return;
      _view.printWrongCoordsMsg();
      pos = _view.retrieveNextPosition();
    }
    _board.move(pos, player.value());
  }

  _view.printOutcome();
}
