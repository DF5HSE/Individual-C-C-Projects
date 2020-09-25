#pragma once
#include <cstdint>
#include <string>

class Test
{
protected:
  static int failedNum; // количество тестов, которые сломались
  static int totalNum;  // общее количество тестов
  static std::pair<std::string, std::string> curFuncFile; // текущая тестируемая функция и её файл
                                                          // с её реализацией

  /** Проверяет условие на верность (expr). 
      Сообщает об результате пользователю, в случае неудачи подробно сообщает об источнике. */
  static void check( bool expr, const char *func, const char  *filename, std::size_t lineNum ); 
#define DO_CHECK(EXPR) check(EXPR, __PRETTY_FUNCTION__, __FILE__, __LINE__)

public:
  static void showFinalResult();

  /** Запускает все тесты в конкретном наборе тестов */
  virtual void runAllTests() = 0;

  // Можно добавлять методы при необходимости 
  int getFailedNum();
};
