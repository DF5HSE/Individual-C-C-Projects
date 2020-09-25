#pragma once

#include <iostream>
#include <climits>
#include <cassert>

namespace Utils
{
class OutBitStream final
{
public:
  OutBitStream(std::ostream &stream) : _stream(stream)
  {
    static_assert(CHAR_BIT == 8 && "size of char != 8");
    stream.exceptions(std::ios::failbit | std::ios::badbit);
  }

  ~OutBitStream()
  {
    assert(_bitPos == 7 && "byte wasn't flushed");
  }

  void writeBit(bool bit)
  {
    _bitsForWrite |= bit << _bitPos--;
    if (_bitPos < 0)
      writeBitsByte();
  }

  void flush()
  {
    if (_bitPos < 7)
      writeBitsByte();
  }

  uint64_t getNumOfWrittenBytes() const noexcept
  {
    return _numOfWrittenBytes;
  }

private:
  std::ostream &_stream;
  uint8_t _bitsForWrite = 0;
  int _bitPos = 7;
  uint64_t _numOfWrittenBytes = 0;

  void writeBitsByte()
  {
    _stream.put(_bitsForWrite);
    ++_numOfWrittenBytes;
    _bitsForWrite = 0;
    _bitPos = 7;
  }
};

class InBitStream final
{
public:
  InBitStream(std::istream &stream) : _stream(stream)
  {
    stream.exceptions(std::ios::failbit | std::ios::badbit);
  }

  bool readBit()
  {
    if (_bitPos < 0)
    {
      _bitsForRead = _stream.get();
      ++_numOfReadBytes;
      _bitPos = 7;
    }
    return (_bitsForRead >> _bitPos--) & 1;
  }

  uint64_t getNumOfReadBytes() const noexcept
  {
    return _numOfReadBytes;
  }

private:
  std::istream &_stream;
  uint8_t _bitsForRead;
  int _bitPos = -1;
  uint64_t _numOfReadBytes = 0;
};
} // end of 'Utils' namespace