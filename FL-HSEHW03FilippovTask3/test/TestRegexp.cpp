#include "doctest.h"
#include "Regexp.h"
#include <ctime>
#include <iostream>
#include <iomanip>

namespace
{
} // end of unnamed namespace

void printRes(std::string regStr, Regexp regexp, std::string word, bool isWordInReg)
  {
    std::cout << std::boolalpha << std::fixed << std::setprecision(3);
    static int testNum = 1;
    double start = clock();
    bool isWorkedRight  = (isWordInReg == match(regexp, word));
    CHECK((isWorkedRight && "Real and found result are different"));
    std::cout << "Test #" << testNum++ << ", DeltaTime: " << (clock() - start) / CLOCKS_PER_SEC << ", isWorkedRight: "
              << isWorkedRight << ", Regexp and word: \"" << regStr << "\" and \"" << word << "\"" << std::endl;
  }
Regexp
     a = Char('a'),
     b = Char('b'),
     c = Char('c'),
     aOrb = Alt(a, b),
     ab = Seq(a, b);

TEST_SUITE("No one symbol")
{
  TEST_CASE("regex = EMPTY")
  {
    printRes("EMPTY THIS IS NOT REGEX", Empty(), "adfdsfsdksjlbd", false);
    printRes("EMPTY THIS IS NOT REGEX", Empty(), "", false);
  }
  TEST_CASE("regex = EPSILON")
  {
    printRes("", Epsilon(), "asjlbd", false);
    printRes("", Epsilon(), "", true);
  }
}

TEST_SUITE("One different symbol")
{
  TEST_CASE("regexp = 'a*a'")
  {
    printRes("a*a", Seq(Star(a), a), "aaaaaaaaaaaaa", true);
    printRes("a*a", Seq(Star(a), a), "aabaaaaaaaaaa", false);
    printRes("a*a", Seq(Star(a), a), "", false);
  }
  TEST_CASE("regex = '(a|a)*'")
  {
    printRes("(a|a)*", Star(Alt(a, a)), "aaaaaaaaaaaaa", true);
    printRes("(a|a)*", Star(Alt(a, a)), "aaaaaaaaaaab", false);
    printRes("(a|a)*", Star(Alt(a, a)), "", true);
  }
  TEST_CASE("regex = 'a*'")
  {
    printRes("a*", Star(a), "aaaaaaaaaaaaa", true);
    printRes("a*", Star(a), "aaaaaaaaaaab", false);
    printRes("a*", Star(a), "", true);
  }
}

TEST_SUITE("Two different symbols")
{
  TEST_CASE("regexp = '(a|b)*(a|b)'")
  {
    printRes("(a|b)*(a|b)", Seq(Star(aOrb), aOrb), "aabababbbbababbbababaaa", true);
    printRes("(a|b)*(a|b)", Seq(Star(aOrb), aOrb), "abababcbababab", false);
    printRes("(a|b)*(a|b)", Seq(Star(aOrb), aOrb), "b", true);
    printRes("(a|b)*(a|b)", Seq(Star(aOrb), aOrb), "", false);
  }
  TEST_CASE("regex = '(a|b)*'")
  {
    printRes("(a|b)*", Star(aOrb), "aabababbbbbba", true);
    printRes("(a|b)*", Star(aOrb), "abbabababababbababababababbabbababbabababababababbabababababbababababababbac", false);
  }
  TEST_CASE("regex = '(ab)*'")
  {
    printRes("(ab)*", Star(ab), "abababba", false);
    printRes("(ab)*", Star(ab), "ababababababab", true);
  }
  TEST_CASE("regex = '((a|b)(a|b)(a|b)(a|b)(a|b)(a|b)(a|b))*")
  {
    printRes("((a|b)(a|b)(a|b)(a|b)(a|b)(a|b)(a|b))*",
             Star(Seq(Seq(Seq(Seq(Seq(Seq(aOrb, aOrb), aOrb), aOrb), aOrb), aOrb), aOrb)),
             "aaaaabababababbaababa", true);
  }
  TEST_CASE("regex = '(a|b)*(a|b)*(a|b)*(a|b)*(a|b)*(a|b)*(a|b)*")
  {
    printRes("(a|b)*(a|b)*(a|b)*(a|b)*(a|b)*(a|b)*(a|b)*",
             Seq(Seq(Seq(Seq(Seq(Seq(Star(aOrb), Star(aOrb)), Star(aOrb)), Star(aOrb)), Star(aOrb)), Star(aOrb)), Star(aOrb)),
             "aaaaabc", false);
    printRes("(a|b)*(a|b)*(a|b)*(a|b)*(a|b)*(a|b)*(a|b)*",
             Seq(Seq(Seq(Seq(Seq(Seq(Star(aOrb), Star(aOrb)), Star(aOrb)), Star(aOrb)), Star(aOrb)), Star(aOrb)), Star(aOrb)),
             "aaaaabbabababbaababa", true);

    printRes("(a|b)*(a|b)*(a|b)*(a|b)*(a|b)*(a|b)*(a|b)*",
             Seq(Seq(Seq(Seq(Seq(Seq(Star(aOrb), Star(aOrb)), Star(aOrb)), Star(aOrb)), Star(aOrb)), Star(aOrb)), Star(aOrb)),
             "aaaaabbabababbaaabbbbbbbbbbbbbbbbbbaaaaaaaac", false);
  }
}