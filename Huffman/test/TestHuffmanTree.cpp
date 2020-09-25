#include <cstdlib>
#include <sstream>
#include <string>
#include <string_view>
#include <algorithm>
#include <random>
#include <functional>
#include "doctest.h"
#include "Huffman.h"

TEST_SUITE("Huffman tree node")
{
  TEST_CASE("Check isLeaf funtion")
  {
    CHECK(Huffman::Node(0, 0).isLeaf());
    CHECK(!Huffman::Node(0, 0, std::make_unique<Huffman::Node>(1, 1), std::make_unique<Huffman::Node>(2, 2)).isLeaf());
  }
}

TEST_SUITE("Huffman forest constructor")
{
  TEST_CASE("Building forest of empty string and possibility of building forest twice")
  {
    CHECK(Huffman::Forest({})._nodes.size() == 0);
  }

  TEST_CASE("Building forest of one char")
  {
    Utils::FreqsCounter freqsCntr;
    freqsCntr.updateFreqs("a");

    Huffman::Forest forest(freqsCntr);
    CHECK(forest._nodes.size() == 1);
    CHECK(forest._nodes[0]->isLeaf());
    CHECK(forest._nodes[0]->_byte == 'a');
    CHECK(forest._nodes[0]->_freq == 1);
    CHECK(forest._nodes[0]->isLeaf());
  }

  TEST_CASE("Building forest of 3 same characters")
  {
    Utils::FreqsCounter freqsCntr;
    freqsCntr.updateFreqs("aaa");

    Huffman::Forest forest(freqsCntr);
    CHECK(forest._nodes.size() == 1);
    CHECK(forest._nodes[0]->isLeaf());
    CHECK(forest._nodes[0]->_byte == 'a');
    CHECK(forest._nodes[0]->_freq == 3);
    CHECK(forest._nodes[0]->isLeaf());
  }

  TEST_CASE("Building forest of random strings")
  {
    constexpr std::size_t NUM_OF_TESTS = 20;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> distr(0, UINT64_MAX);
    for (std::size_t j = 0; j < NUM_OF_TESTS; ++j)
    {
      Utils::FreqsCounter freqsCntr;
      for (std::size_t i = 0; i < freqsCntr.size(); ++i)
        freqsCntr[i] = distr(gen);

      Huffman::Forest forest(freqsCntr);
      CHECK(std::is_sorted(forest._nodes.begin(), forest._nodes.end(),
                           [](const std::unique_ptr<Huffman::Node> &a,
                              const std::unique_ptr<Huffman::Node> &b) -> bool
                           {
                             return a->_freq > b->_freq;
                           }));
      CHECK(std::all_of(forest._nodes.begin(), forest._nodes.end(),
                        [](const std::unique_ptr<Huffman::Node> &a) -> bool
                        {
                          return !a->_left && !a->_right;
                        }));
    }
  }
}

TEST_SUITE("Build tree from forest")
{
  TEST_CASE("Build from nothing and check exceptions throwing")
  {
    Huffman::Forest forest({});
    std::unique_ptr<Huffman::Node> root = forest.buildTree();
    CHECK(root == nullptr);
    CHECK_THROWS_WITH(forest.buildTree(), "[Huffman::Forest::buildTree] can't build tree twice");
  }

  TEST_CASE("Build from 1 character")
  {
    Utils::FreqsCounter freqsCntr;
    freqsCntr.updateFreqs("a");
    std::unique_ptr<Huffman::Node> root = Huffman::Forest(freqsCntr).buildTree();

    CHECK(root->_byte == 'a');
    CHECK(root->_freq == 1);
    CHECK(root->isLeaf());
  }
  
  TEST_CASE("Build from nontrivial example")
  {
    Utils::FreqsCounter freqsCntr;
    freqsCntr.updateFreqs("abcaba");

    /* Want to get tree (node = (<byte>, freq)):
     *          (, 6)
     *         /     \
     * ('a', 3)       (, 3)
     *               /     \
     *       ('b', 2)       ('c', 1)
     */
 
    std::unique_ptr<Huffman::Node> root = Huffman::Forest(freqsCntr).buildTree();
    CHECK(!root->isLeaf());
    CHECK(root->_freq == 6);

    struct NodeForCheck
    {
      uint8_t _byte;
      uint64_t _freq;
      bool isLeaf;
    } nodesForCheck[] =
    {
      /* I build this is pairs in DFS path */
      {0, 6, false}, {'a', 3, true}, {0, 3, false}, {'b', 2, true}, {'c', 1, true}
    };
    int32_t i = -1;
    std::function<bool(Huffman::Node &)> dfs =
      [&nodesForCheck, &i, &dfs](Huffman::Node &node) -> bool
      {
        CHECK(node.isLeaf() == nodesForCheck[++i].isLeaf);
        if (!node._left)
          return node._freq == nodesForCheck[i]._freq && node._byte == nodesForCheck[i]._byte;
        return node._freq == nodesForCheck[i]._freq && (!node._left || dfs(*node._left)) &&
                                                       (!node._right || dfs(*node._right));
      };
    CHECK((root && dfs(*root)));
  }
}

TEST_SUITE("Building Huffman codes")
{
  TEST_CASE("Build codes of empty string and check exception throwing")
  {
    CHECK(Huffman::Tree({}).buildCodes() == std::array<std::vector<bool>, Huffman::SIZE_OF_ALPHABET>{});
  }

  TEST_CASE("Build codes of one character")
  {
    Utils::FreqsCounter freqsCntr;
    freqsCntr.updateFreqs("a");
    CHECK(Huffman::Tree(freqsCntr).buildCodes() == std::array<std::vector<bool>, Huffman::SIZE_OF_ALPHABET>{});
  }

  TEST_CASE("Build codes of nontrivial example")
  {
    Utils::FreqsCounter freqsCntr;
    freqsCntr.updateFreqs("abcabcbbbbaabbbbbccdeefffffffbbbbb");

    std::array<std::vector<bool>, Huffman::SIZE_OF_ALPHABET> realCodes;
    realCodes['a'] = {0, 0, 1};
    realCodes['b'] = {1};
    realCodes['c'] = {0, 0, 0, 0};
    realCodes['d'] = {0, 0, 0, 1, 1};
    realCodes['e'] = {0, 0, 0, 1, 0};
    realCodes['f'] = {0, 1};

    CHECK(Huffman::Tree(freqsCntr).buildCodes() == realCodes);
  }
}

TEST_SUITE("Getting frequency from the root of Huffman tree")
{
  TEST_CASE("Get frequency from empty string and check exceptions throwing")
  {
    CHECK(Huffman::Tree({}).getFreqFromRoot() == 0);
  }

  TEST_CASE("Get frequency from nontrivial example")
  {
    Utils::FreqsCounter freqsCntr;
    freqsCntr.updateFreqs("abcabcbbbbaabbbbbccdeefffffffbbbbb");
    CHECK(Huffman::Tree(freqsCntr).getFreqFromRoot() == 34);
  }
}

void testGetByteFromHuffmanTree(std::string_view realStr, const std::string &comprStr)
{
  Utils::FreqsCounter freqsCntr;
  freqsCntr.updateFreqs(realStr);

  std::stringstream stream(comprStr, std::ios::in | std::ios::binary);
  Utils::InBitStream bitStream(stream);
  Huffman::Tree tree(freqsCntr);
  uint64_t freq = tree.getFreqFromRoot();
  std::string decomprStr;
  while (freq-- > 0)
    decomprStr.push_back(tree.getByte(bitStream));

  CHECK(decomprStr == realStr);
}

TEST_SUITE("Getting bytes by code's bits")
{
  TEST_CASE("Get bytes from empty compressed string but not null frequancy")
  {
    testGetByteFromHuffmanTree("aaaaaaaa", "");
  }

  TEST_CASE("Getting bytes from nontrivial example and check exception throwing")
  {
    testGetByteFromHuffmanTree("abcabcbbbbaabbbbbccdeefffffffbbbbb",
                               std::string{0b0011'0000, 0b0011'0000, static_cast<char>(0b1111'0010), 0b0111'1110, 0b0000'0000,
                                           0b0011'0001, 0b0000'1001, 0b0101'0101, 0b0101'1111, static_cast<char>(0b1000'0000)});
  }
}
