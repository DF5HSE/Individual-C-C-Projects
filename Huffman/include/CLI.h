#pragma once
#include <iostream>
#include <exception>
#include <string>

namespace Huffman
{
class CLI final
{
public:
  class Exception final : public std::logic_error
  {
    using std::logic_error::logic_error;
  };
  enum class Mode
  {
     NO_MODE, COMPRESS, EXTRACT
  };

  CLI(std::size_t argc, const char *argv[]);

  std::string getInputFileName() const noexcept;
  std::string getOutputFileName() const noexcept;
  Mode getMode() const noexcept;

private:
  std::string _inputFileName;
  std::string _outputFileName;
  Mode _mode;

  Mode parseMode(std::size_t argc, const char *argv[]) const;
  std::string parseFileName(std::size_t argc, const char *argv[], std::string_view shortKey, std::string_view longKey) const;
};
} // end of 'Huffman' namespace