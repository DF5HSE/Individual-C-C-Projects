#pragma once

#include <iostream>
#include <array>
#include <cassert>

namespace Utils
{
static inline constexpr std::size_t DEFAULT_ALPHABET_SIZE = 256;

template<std::size_t N = DEFAULT_ALPHABET_SIZE>
  class FreqsCounter final
  {
  public:
    void updateFreqs(std::string_view str) noexcept
    {
      for (uint8_t byte : str)
      {
        _freqs[byte]++;
        _commonFreq++;
      }
    }
    void updateFreqs(std::size_t byte) noexcept
    {
      _freqs[byte]++;
      _commonFreq++;
    }

    const std::array<uint64_t, N> & getFreqsArray() const noexcept
    {
      return _freqs;
    }

    void writeFreqsToStream(std::ostream &stream) const
    {
      for (std::size_t i = 0; i < _freqs.size(); i++)
        for (uint8_t j = 0; j < sizeof(uint64_t); j++)
          stream.put((_freqs[i] >> (j * 8)) & 0xFF);
    }

    void readFreqsFromStream(std::istream &stream)
    {
      _commonFreq = 0;
      for (std::size_t i = 0; i < _freqs.size(); i++)
      {
        uint64_t elemFreq = 0;
        for (uint8_t j = 0, byte; j < sizeof(uint64_t); j++)
        {
          byte = stream.get();
          elemFreq |= byte << (j * 8);
        }
        _freqs[i] = elemFreq;
        _commonFreq += elemFreq;
      }
    }

    uint64_t operator[](std::size_t i) const noexcept
    {
      assert(0 <= i && i < N && "index is out of range");
      return _freqs[i];
    }

    uint64_t & operator[](std::size_t i) noexcept
    {
      assert(0 <= i && i < N && "index is out of range");
      return _freqs[i];
    }

    static constexpr std::size_t size() noexcept
    {
      return N;
    }

    uint64_t getCommonFreq() const noexcept
    {
      return _commonFreq;
    }

    static constexpr std::size_t getSizeInByte() noexcept
    {
      return N * sizeof(uint64_t);
    }

  private:
    std::array<uint64_t, N> _freqs{};
    uint64_t _commonFreq = 0;
  };
} // end of 'Utils' namespace