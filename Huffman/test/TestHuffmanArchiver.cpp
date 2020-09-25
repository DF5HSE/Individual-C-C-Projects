#include <sstream>
#include "doctest.h"
#include "HuffmanArchiver.h"
#include "FreqsCounter.h"

namespace
{
void testHuffmanArchiverCompress(std::string_view toCompress, std::string_view compressedData,
                                 const Huffman::Archiver::ResultInfo &resInfo)
{
  Utils::FreqsCounter freqsCntr;
  freqsCntr.updateFreqs(toCompress);

  std::stringstream realOutput(std::ios::out | std::ios::binary);
  freqsCntr.writeFreqsToStream(realOutput);
  realOutput.write(compressedData.data(), compressedData.size());

  std::stringstream
    inStream(toCompress.data(), std::ios::in | std::ios::binary),
    outStream(std::ios::out | std::ios::binary);

  Huffman::Archiver archiver(inStream, outStream);
  CHECK(archiver.compress() == resInfo);
  CHECK(realOutput.str() == outStream.str());
}

void testHuffmanArchiverExtract(std::string_view toExtract, std::string_view extractedData,
                                const Huffman::Archiver::ResultInfo &resInfo)
{
  Utils::FreqsCounter freqsCntr;
  freqsCntr.updateFreqs(extractedData);

  std::stringstream forMakeInput(std::ios::out | std::ios::binary);
  freqsCntr.writeFreqsToStream(forMakeInput);
  forMakeInput.write(toExtract.data(), extractedData.size());

  std::stringstream
      inStream(forMakeInput.str(), std::ios::in | std::ios::binary),
      outStream(std::ios::out | std::ios::binary);
    Huffman::Archiver archiver(inStream, outStream);

  CHECK(archiver.extract() == resInfo);
  CHECK(extractedData == outStream.str());
}
} // end of unnamed namespace

TEST_SUITE("Huffman archiver compress")
{
  TEST_CASE("Empty string")
  {
    testHuffmanArchiverCompress("", "", {0, 0, 2048});
  }

  TEST_CASE("One character string")
  {
    testHuffmanArchiverCompress("a", "", {0, 1, 2048});
  }

  TEST_CASE("String of n same characters")
  {
    testHuffmanArchiverCompress("aaaaaa", "", {0, 6, 2048});
  }
 
  TEST_CASE("Nontrivial string")
  {
    testHuffmanArchiverCompress("abcabcbbbbaabbbbbccdeefffffffbbbbb", std::string{0b0011'0000, 0b0011'0000,
                                static_cast<char>(0b1111'0010), 0b0111'1110, 0b0000'0000, 0b0011'0001, 0b0000'1001,
                                0b0101'0101, 0b0101'1111, static_cast<char>(0b1000'0000)}, {10, 34, 2048});
  }
}

TEST_SUITE("Huffman archiever extract")
{
  TEST_CASE("Empty string")
  {
    testHuffmanArchiverExtract("", "", {0, 0, 2048});
  }

  TEST_CASE("One character string")
  {
    testHuffmanArchiverExtract("", "a", {0, 1, 2048});
  }

  TEST_CASE("String of n same characters")
  {
    testHuffmanArchiverExtract("", "aaaaaa", {0, 6, 2048});
  }

  TEST_CASE("Nontrivial string")
  {
    testHuffmanArchiverExtract(std::string{0b0011'0000, 0b0011'0000, static_cast<char>(0b1111'0010), 0b0111'1110, 0b0000'0000,
                                           0b0011'0001, 0b0000'1001, 0b0101'0101, 0b0101'1111, static_cast<char>(0b1000'0000)},
                               "abcabcbbbbaabbbbbccdeefffffffbbbbb",{10, 34, 2048});
  }
}
