#include <iostream>
#include <fstream>
#include "CLI.h"
#include "Huffman.h"
#include "HuffmanArchiver.h"

int main(int argc, const char *argv[])
{
  std::string inputFileName, outputFileName;
  Huffman::CLI::Mode mode = Huffman::CLI::Mode::NO_MODE;

  try
  {
    Huffman::CLI CLI(argc, argv);
    inputFileName = CLI.getInputFileName();
    outputFileName = CLI.getOutputFileName();
    mode = CLI.getMode();
  }
  catch (const Huffman::CLI::Exception &e)
  {
    std::cout << e.what() << std::endl;
    return -1;
  }

  std::ifstream inputFile(inputFileName, std::ios::binary);
  if (!inputFile.is_open())
  {
    std::cout << "Can't open " << inputFileName << std::endl;
    return -1;
  }

  std::ofstream outputFile(outputFileName, std::ios::binary);
  if (!outputFile.is_open())
  {
    std::cout << "Can't open " << outputFileName << std::endl;
    return -1;
  }

  Huffman::Archiver archiver(inputFile, outputFile);
  try
  {
    if (mode == Huffman::CLI::Mode::COMPRESS)
    {
      Huffman::Archiver::ResultInfo res = archiver.compress();
      std::cout << res.readlData << std::endl
                << res.compressedData << std::endl
                << res.additionalData << std::endl;
    }
    else
    {
      Huffman::Archiver::ResultInfo res = archiver.extract();
      std::cout << res.compressedData << std::endl
                << res.readlData << std::endl
                << res.additionalData << std::endl;
    }
  }
  catch(const Huffman::Exception &e)
  {
    std::cout << e.what() << std::endl;
    return -1;
  }

  return 0;
}