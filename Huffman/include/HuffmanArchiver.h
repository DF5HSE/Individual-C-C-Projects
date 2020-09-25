#pragma once
#include <iosfwd>

namespace Huffman
{
class Archiver final
{
public:
  Archiver(std::istream &input, std::ostream &output) noexcept;

  struct ResultInfo final
  {
    uint64_t compressedData;
    uint64_t readlData;
    uint64_t additionalData;
    bool operator==(const ResultInfo &other) const noexcept
    {
      return compressedData == other.compressedData &&
             readlData == other.readlData &&
             additionalData == other.additionalData;
    }
  };

  ResultInfo compress();
  ResultInfo extract();

private:
  std::istream &_inputStream;
  std::ostream &_outputStream;
};
} // end of 'Huffman' namespace
