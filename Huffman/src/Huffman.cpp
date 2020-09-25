#include <iostream>
#include <algorithm>
#include <array>
#include <cassert>
#include <string>
#include <cstring>
#include <queue>
#include <string_view>
#include <exception>
#include "Huffman.h"

Huffman::Node::Node(uint8_t byte, uint32_t freq) noexcept :  _byte(byte), _freq(freq)
{
}

Huffman::Node::Node(uint8_t byte, uint32_t freq, std::unique_ptr<Node> left,
                    std::unique_ptr<Node> right) noexcept :
                    _byte(byte), _freq(freq), _left(std::move(left)), _right(std::move(right))
{
}

Huffman::Node::Node(std::unique_ptr<Node> left, std::unique_ptr<Node> right) noexcept :
                     _byte(0), _freq(left->_freq + right->_freq), _left(std::move(left)), _right(std::move(right))
{
}

bool Huffman::Node::isLeaf() const noexcept
{
  assert(((!_left && !_right) || (_right && _left)) &&
         "both children have to be null or no null pointer");
  return !_left;
}

Huffman::Forest::Forest(const Utils::FreqsCounter<> &freqs) : _isTreeBuilt(false)
{
  for (std::size_t i = 0; i < SIZE_OF_ALPHABET; ++i)
    if (freqs[i])
      _nodes.emplace_back(std::make_unique<Node>(i, freqs[i]));

  std::sort(_nodes.begin(), _nodes.end(), [](const std::unique_ptr<Node> &a,
                                             const std::unique_ptr<Node> &b) -> bool
                                          {
                                            return a->_freq > b->_freq;
                                          });
}

std::unique_ptr<Huffman::Node> Huffman::Forest::buildTree()
{
  if (_isTreeBuilt)
    throw Huffman::Exception("[Huffman::Forest::buildTree] can't build tree twice");

  std::queue<std::unique_ptr<Node>> newNodes;
  std::unique_ptr<Node> last[2];
  while (_nodes.size() + newNodes.size() >= 2)
  {
    for (int i = 0; i < 2; ++i)
    {
      if (_nodes.empty() || (!newNodes.empty() && _nodes.back()->_freq >= newNodes.front()->_freq))
      {
        last[i] = std::move(newNodes.front());
        newNodes.pop();
      }
      else
      {
        last[i] = std::move(_nodes.back());
        _nodes.pop_back();
      }
    }
    newNodes.push(std::make_unique<Node>(std::move(last[1]), std::move(last[0])));
  }

  if (!newNodes.empty())
  {
    assert(_nodes.size() == 0 && "newNodes and _nodes aren't empty");
    _nodes.emplace_back(std::move(newNodes.front()));
  }
  _isTreeBuilt = true;

  return _nodes.empty() ? nullptr : std::move(_nodes.back());
}

Huffman::Tree::Tree(const Utils::FreqsCounter<> &freqsCntr)
{
  _root = Huffman::Forest(freqsCntr).buildTree();
}

std::array<std::vector<bool>, Huffman::SIZE_OF_ALPHABET> Huffman::Tree::buildCodes() const noexcept
{
  if (!_root)
    return {};

  std::array<std::vector<bool>, SIZE_OF_ALPHABET> codesArray{};
  std::vector<bool> curCode;
  curCode.reserve(SIZE_OF_ALPHABET);
  makeCodes(codesArray, curCode, *_root);

  return codesArray;
}

uint64_t Huffman::Tree::getFreqFromRoot() const noexcept
{
  return _root ? _root->_freq : 0;
}

void Huffman::Tree::makeCodes(std::array<std::vector<bool>, SIZE_OF_ALPHABET> &codesArray,
                              std::vector<bool> &curCode, Node &curNode) const noexcept
{
  if (curNode.isLeaf())
  {
    codesArray[curNode._byte] = curCode;
    return;
  }

  curCode.push_back(0);
  makeCodes(codesArray, curCode, *curNode._left);
  curCode.pop_back();
  curCode.push_back(1);
  makeCodes(codesArray, curCode, *curNode._right);
  curCode.pop_back();
}

uint8_t Huffman::Tree::getByte(Utils::InBitStream &stream) const noexcept
{
  return makeByte(stream, *_root);
}

uint8_t Huffman::Tree::makeByte(Utils::InBitStream &stream, Node &curNode) const noexcept
{
  if (curNode.isLeaf())
     return curNode._byte;
  return makeByte(stream, stream.readBit() ? *curNode._right : *curNode._left);
}
