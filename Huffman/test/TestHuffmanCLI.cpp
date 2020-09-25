#include "doctest.h"
#include "CLI.h"
#include <vector>
#include <string>

TEST_CASE("Parse correct input with short flags and compress mode")
{
  const char *argv[6] = {"./", "-f", "in", "-o", "outTest", "-c"};
  Huffman::CLI CLI(6, argv);
  CHECK((CLI.getMode() == Huffman::CLI::Mode::COMPRESS && 
         CLI.getInputFileName() == "in" &&
         CLI.getOutputFileName() == "outTest"));
}

TEST_CASE("Parse correct input with long flags and extract mode")
{
  const char *argv[6] = {"./", "--file", "in", "--output", "outTest", "-u"};
  Huffman::CLI CLI(6, argv);
  CHECK((CLI.getMode() == Huffman::CLI::Mode::EXTRACT && 
         CLI.getInputFileName() == "in" &&
         CLI.getOutputFileName() == "outTest"));
}

TEST_CASE("Too many arguments")
{
  const char *argv[7] = {"sdfs", "sdfs", "sdfsdf", "sdfsdf", "sdf", "dsf", ""};
  CHECK_THROWS_WITH(Huffman::CLI(7, argv), "[Huffman::CLI::CLI] too many arguments");
}

TEST_CASE("Try to add input file twice")
{
  const char *argv[6] = {"./", "--file", "in", "--file", "outTest", "-c"};
  CHECK_THROWS_WITH(Huffman::CLI(6, argv), "[Huffman::CLI::parseFileName] --file has been already added");
}

TEST_CASE("Try to add output file twice")
{
  const char *argv[6] = {"-o", "in", "-o", "outTest", "-f", "in"};
  CHECK_THROWS_WITH(Huffman::CLI(6, argv), "[Huffman::CLI::parseFileName] --output has been already added");
}

TEST_CASE("Not give input file")
{
  const char *argv[6] = {"./", "-o", "in", "-o", "outTest", "-c"};
  CHECK_THROWS_WITH(Huffman::CLI(6, argv), "[Huffman::CLI::parseFileName] --file wasn't chosen");
}

TEST_CASE("Not give output file")
{
  const char *argv[6] = {"./", "-f", "in", "sdf", "outTest", "-c"};

  CHECK_THROWS_WITH(Huffman::CLI(6, argv), "[Huffman::CLI::parseFileName] --output wasn't chosen");
}

TEST_CASE("Not give name of input file")
{
  const char *argv[6] = {"./", "-o", "in", "-c", "outTest", "-f"};
  CHECK_THROWS_WITH(Huffman::CLI(6, argv), "[Huffman::CLI::parseFileName] there isn't --file name");
}

TEST_CASE("Not give name of output file")
{
  const char *argv[6] = {"./", "-f", "in", "-c", "outTest", "-o"};
  CHECK_THROWS_WITH(Huffman::CLI(6, argv), "[Huffman::CLI::parseFileName] there isn't --output name");
}

TEST_CASE("Choose compress mode twice")
{
  const char *argv[6] = {"-c", "-f", "in", "-o", "outTest", "-c"};
  CHECK_THROWS_WITH(Huffman::CLI(6, argv), "[Huffman::CLI::parseMode] mode was chosen twice");
}

TEST_CASE("Choose extract mode twice")
{
  const char *argv[6] = {"-u", "-f", "in", "-o", "outTest", "-u"};
  CHECK_THROWS_WITH(Huffman::CLI(6, argv), "[Huffman::CLI::parseMode] mode was chosen twice");
}

TEST_CASE("Choose 2 different modes")
{
  const char *argv[6] = {"-u", "-f", "in", "-o", "outTest", "-c"};
  CHECK_THROWS_WITH(Huffman::CLI(6, argv), "[Huffman::CLI::parseMode] mode was chosen twice");
}

TEST_CASE("Not choose mode")
{
  const char *argv[6] = {"./", "-f", "in", "-o", "outTest", "dsf"};
  CHECK_THROWS_WITH(Huffman::CLI(6, argv), "[Huffman::CLI::parseMode] mode wasn't chosen");
}
