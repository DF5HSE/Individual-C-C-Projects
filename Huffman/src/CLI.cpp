#include <fstream>
#include <string_view>
#include <cassert>
#include "CLI.h"

Huffman::CLI::CLI(const std::size_t argc, const char *argv[])
{
  static constexpr std::size_t NUM_OF_ARGUMENTS = 5;
  if (argc - 1 > NUM_OF_ARGUMENTS)
    throw Exception("[Huffman::CLI::CLI] too many arguments");

  _inputFileName = parseFileName(argc, argv, "-f", "--file");
  _outputFileName = parseFileName(argc, argv, "-o", "--output");
  _mode = parseMode(argc, argv);

  assert(argc - 1 >= NUM_OF_ARGUMENTS &&
         "error in arguments wasn't found but there isn't enough of arguments");
}

std::string Huffman::CLI::getInputFileName() const noexcept
{
  return _inputFileName;
}

std::string Huffman::CLI::getOutputFileName() const noexcept
{
  return _outputFileName;
}

Huffman::CLI::Mode Huffman::CLI::getMode() const noexcept
{
  return _mode;
}

std::string Huffman::CLI::parseFileName(std::size_t argc, const char *argv[],
                                        std::string_view shortKey, std::string_view longKey) const
{
  std::string result;
  std::string msg = "[Huffman::CLI::parseFileName] ";

  for (std::size_t i = 0; i < argc; ++i)
  {
    if (argv[i] == shortKey || argv[i] == longKey)
    {
      if (!result.empty())
      {
        msg += longKey;
        msg += " has been already added";
        throw Exception(msg);
      }
      if (++i >= argc)
      {
        msg += "there isn't ";
        msg += longKey;
        msg += " name";
        throw Exception(msg);
      }
      result = argv[i];
    }
  }

  if (result.empty())
  {
    msg += longKey;
    msg += " wasn't chosen";
    throw Exception(msg);
  }

  return result;
}

Huffman::CLI::Mode Huffman::CLI::parseMode(std::size_t argc, const char *argv[]) const
{
  Mode result = Mode::NO_MODE;
  std::string msg = "[Huffman::CLI::parseMode] ";

  for (std::size_t i = 0; i < argc; ++i)
  {
    if (std::string_view(argv[i]) == "-c" || std::string_view(argv[i]) == "-u")
    {
      if (result != Mode::NO_MODE)
      {
        msg += "mode was chosen twice";
        throw Exception(msg);
      }
      result = std::string_view(argv[i]) == "-c" ?  Mode::COMPRESS : Mode::EXTRACT;
    }
  }

  if (result == Mode::NO_MODE)
  {
    msg += "mode wasn't chosen";
    throw Exception(msg);
  }

  return result;
}
