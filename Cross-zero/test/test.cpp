#include "BoardTest.h"
#include "Test.h"

int main()
{
  BoardTest bt;

  bt.runAllTests();
  Test::showFinalResult();
  if (!bt.getFailedNum())
    return 0;
  return 30;
}
