#include <sstream>
#include "doctest.h"
#include "BitStream.h"

TEST_SUITE("Output bit stream")
{
  TEST_CASE("Flush byte")
  {
    std::stringstream outStream(std::ios::out | std::ios::binary);
    Utils::OutBitStream outBitStream(outStream);
    
    SUBCASE("Flush empty byte")
    {
      outBitStream.flush();
      CHECK(outStream.str().size() == 0);
    }
    SUBCASE("Flush byte with one bit")
    {
      outBitStream.writeBit(1);
      CHECK(outStream.str().size() == 0);
      outBitStream.flush();
      CHECK(outStream.str().size() == 1);
    }
  }

  TEST_CASE("Write bit and getNumOfWrittenBytes in nontrivial example")
  {
    std::stringstream outStream(std::ios::out | std::ios::binary);
    Utils::OutBitStream outBitStream(outStream);

    bool bitsToWrite[] =
    {
      1, 1, 0, 0, 1, 0, 1, 0,
      0, 1, 0, 0, 1, 0, 1, 1,
      1, 1, 0, 1, 0, 1, 0, 1,
      1, 0, 0, 1, 0,
    };

    CHECK((outStream.str().size() == 0 && outBitStream.getNumOfWrittenBytes() == 0));
    for (std::size_t i = 0; i < sizeof(bitsToWrite); i++)
      outBitStream.writeBit(bitsToWrite[i]);
    CHECK((outStream.str().size() == 3 && outBitStream.getNumOfWrittenBytes() == 3));

    outBitStream.flush();
    CHECK((outStream.str().size() == 4 && outBitStream.getNumOfWrittenBytes() == 4));

    std::string forCheck;
    for (uint8_t c : {0xCA, 0x4B, 0xD5, 0x90})
      forCheck.push_back(c);
    CHECK(outStream.str() == forCheck);
  }

  TEST_CASE("Read bit")
  {
    std::string inStr;
    for (uint8_t c : {0b1100'1010, 0b0100'1011, 0b1101'0101, 0b1001'0000, 0b1111'1110, 0b1000'0000})
      inStr.push_back(c);
    std::stringstream inStream(inStr, std::ios::in | std::ios::binary);
    Utils::InBitStream inBitStream(inStream);
    bool realBits[] =
    {
      1, 1, 0, 0, 1, 0, 1, 0,
      0, 1, 0, 0, 1, 0, 1, 1,
      1, 1, 0, 1, 0, 1, 0, 1,
      1, 0, 0, 1, 0,
    };

    for (std::size_t i = 0; i < sizeof(realBits); i++)
    {
      CHECK(realBits[i] == inBitStream.readBit());
      CHECK(inBitStream.getNumOfReadBytes() == i / 8 + 1);
    }
  }
}
