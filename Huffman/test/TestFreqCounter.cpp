#include <string>
#include <vector>
#include <sstream>
#include <random>
#include "doctest.h"
#include "FreqsCounter.h"

TEST_SUITE("Huffman frequencies counter")
{
  TEST_CASE("Check updateFreqs by string funtion functions")
  {
    Utils::FreqsCounter freqsCntr;
    std::array<uint64_t,Utils::DEFAULT_ALPHABET_SIZE>
      checkFreqsArray{};
    CHECK(freqsCntr.getFreqsArray() == checkFreqsArray);

    std::string str;
    for (uint32_t i = 0; i < Utils::DEFAULT_ALPHABET_SIZE; ++i)
      str.push_back(static_cast<uint8_t>(i));
    freqsCntr.updateFreqs(str);
    checkFreqsArray.fill(1);
    CHECK(freqsCntr.getFreqsArray() == checkFreqsArray);

    freqsCntr.updateFreqs("xxy");
    checkFreqsArray['x'] = 3;
    checkFreqsArray['y'] = 2;
    CHECK(freqsCntr.getFreqsArray() == checkFreqsArray);
  }

  TEST_CASE("Check updateFreqs by byte funtion functions")
  {
    Utils::FreqsCounter freqsCntr;
    std::array<uint64_t, Utils::DEFAULT_ALPHABET_SIZE>
      checkFreqsArray{};

    freqsCntr.updateFreqs('a');
    checkFreqsArray['a'] = 1;
    CHECK(freqsCntr.getFreqsArray() == checkFreqsArray);

    freqsCntr.updateFreqs('x');
    checkFreqsArray['x'] = 1;
    CHECK(freqsCntr.getFreqsArray() == checkFreqsArray);
  }

  TEST_CASE("Check read random freqs from stream")
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> distr(INT8_MIN, INT8_MAX);

    constexpr int NUM_OF_TESTS = 10;
    for (int test = 0; test < NUM_OF_TESTS; ++test)
    {
      std::string freqsStreamStr;
      freqsStreamStr.resize(Utils::FreqsCounter<>::getSizeInByte());
      for (std::size_t i = 0; i < freqsStreamStr.size(); i++)
        freqsStreamStr[i] = distr(gen);

      std::stringstream inputStream(freqsStreamStr.c_str(), std::ios::in | std::ios::binary);
      Utils::FreqsCounter freqsCntr;
   
      freqsCntr.readFreqsFromStream(inputStream);
      bool freqsCntrSuccess = true;
      for (std::size_t i = 0; i < freqsCntr.size(); ++i)
        for (std::size_t j = 0; j < sizeof(uint64_t); ++j)
          freqsCntrSuccess |= (freqsCntr[i] >> (j * 8)) ==
                               static_cast<uint8_t>(freqsStreamStr[i * sizeof(uint64_t) + j]);
      CHECK(freqsCntrSuccess);
    }
  }

  TEST_CASE("Check write random freqs to stream")
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> distr(0, UINT64_MAX);
 
    constexpr int NUM_OF_TESTS = 10;
    for (int test = 0; test < NUM_OF_TESTS; ++test)
    {
      Utils::FreqsCounter freqsCntr;
      for (std::size_t i = 0; i < freqsCntr.size(); i++)
        freqsCntr[i] = distr(gen);

      std::stringstream outputStream(std::ios::in | std::ios::binary);
      freqsCntr.writeFreqsToStream(outputStream);

      bool freqsCntrSuccess = true;
      for (std::size_t i = 0; i < freqsCntr.size(); ++i)
        for (std::size_t j = 0; j < sizeof(uint64_t); ++j)
          freqsCntrSuccess |= (freqsCntr[i] >> (j * 8)) ==
                               static_cast<uint8_t>(outputStream.str().c_str()[i * sizeof(uint64_t) + j]);
      CHECK(freqsCntrSuccess);
    }
  }
}