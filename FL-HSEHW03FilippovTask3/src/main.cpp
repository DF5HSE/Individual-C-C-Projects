#include "Regexp.h"
#include "map"
#include <string>
#include <iostream>


int main(int argc, const char *argv[])
{
  if (argc != 3)
  {
    std::cout << "Wrong number of arguments" << std::endl;
    return 0;
  }

  std::map<std::string, Regexp> regexps = 
  {
    {"r1", Regexp(SEQ, Regexp(STAR, Regexp(CHAR, 'a')), Regexp(CHAR, 'a'))}, // very long, use customer wrops (next example)
    {"r2", Seq(Star(Alt(Char('a'), Char('a'))), Epsilon())},
    {"r3", Empty()}
  };

  if (regexps.find(argv[1]) != regexps.end())
    std::cout << std::boolalpha << match(regexps[argv[1]], argv[2]) << std::endl;
  else
    std::cerr << "There isn't that regex in map" << std::endl;

  return 0;
}