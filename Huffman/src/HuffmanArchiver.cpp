#include <iostream>
#include <climits>
#include "HuffmanArchiver.h"
#include "Huffman.h"
#include "FreqsCounter.h"

Huffman::Archiver::Archiver(std::istream &input, std::ostream &output) noexcept
  : _inputStream(input), _outputStream(output)
{
}

Huffman::Archiver::ResultInfo Huffman::Archiver::compress()
{
  Utils::FreqsCounter freqCntr;

  _inputStream.clear();
  _inputStream.seekg(0);
  for (std::char_traits<char>::int_type ch; (ch = _inputStream.get()) != std::char_traits<char>::eof(); )
    freqCntr.updateFreqs(ch);


  _inputStream.clear();
  _inputStream.seekg(0);
  freqCntr.writeFreqsToStream(_outputStream);

  Huffman::Tree tree(freqCntr);
  const auto codes = tree.buildCodes();
  Utils::OutBitStream outputBitStream(_outputStream);
  for (std::char_traits<char>::int_type ch; (ch = _inputStream.get()) != std::char_traits<char>::eof(); )
    for (auto bit : codes[ch])
      outputBitStream.writeBit(bit);

  outputBitStream.flush();

  return {outputBitStream.getNumOfWrittenBytes(),
          freqCntr.getCommonFreq(),
          freqCntr.size() * sizeof(uint64_t)};
}

Huffman::Archiver::ResultInfo Huffman::Archiver::extract()
{
  Utils::FreqsCounter freqsCntr;

  freqsCntr.readFreqsFromStream(_inputStream);
  Huffman::Tree tree(freqsCntr);

  uint64_t numOfBytesForDecode = tree.getFreqFromRoot();
  Utils::InBitStream inputBitStream(_inputStream);
  while (numOfBytesForDecode-- > 0)
    _outputStream.put(tree.getByte(inputBitStream));

  return {inputBitStream.getNumOfReadBytes(),
          freqsCntr.getCommonFreq(),
          freqsCntr.getSizeInByte()};
}
