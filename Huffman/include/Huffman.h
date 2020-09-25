#pragma once
#include <cstdint>
#include <memory>
#include <array>
#include <string_view>
#include <iostream>
#include <vector>
#include <exception>
#include "BitStream.h"
#include "FreqsCounter.h"

namespace Huffman
{
inline constexpr std::size_t SIZE_OF_ALPHABET = Utils::DEFAULT_ALPHABET_SIZE;

class Exception final : public std::logic_error
{
  using std::logic_error::logic_error;
};

class Node final
{
public:
  const uint8_t _byte;
  const uint64_t _freq;
  const std::unique_ptr<Node> _left, _right;

  Node(uint8_t byte, uint32_t freq) noexcept;
  Node(uint8_t byte,  uint32_t freq, std::unique_ptr<Node> left, std::unique_ptr<Node> right) noexcept;
  Node(std::unique_ptr<Node> left, std::unique_ptr<Node> right) noexcept;

  bool isLeaf() const noexcept;

private:
};

class Forest final
{
public:
  std::vector<std::unique_ptr<Node>> _nodes{};

  Forest(const Utils::FreqsCounter<> &freqs);
  std::unique_ptr<Node> buildTree();

private:
  bool _isTreeBuilt;
};

class Tree final
{
public:
  Tree(const Utils::FreqsCounter<> &freqsCntr);

  std::array<std::vector<bool>, SIZE_OF_ALPHABET> buildCodes() const noexcept;
  uint8_t getByte(Utils::InBitStream &stream) const noexcept;
  uint64_t getFreqFromRoot() const noexcept;

private:
  std::unique_ptr<Node> _root;

  void makeCodes(std::array<std::vector<bool>, SIZE_OF_ALPHABET> &codesArray, std::vector<bool> &curCode,
                 Node &curNode) const noexcept;
  uint8_t makeByte(Utils::InBitStream &stream, Node &curNode) const noexcept;

  void debugPrintFreqs() const noexcept;
};
} // end of 'Huffman' namespace
