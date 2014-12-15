/******************************************************************************
Title: DNA analysis
Author: Gordon Zheng
Created on: 2014-12-09
Description:  TODO: fill this in
Usage: ./dna <inputFile> <outputFile>
Build with: g++ -std=c++11 main.cpp sequence.cpp openReadingFrame.cpp -o dna
Dependencies: none
******************************************************************************/

// TODO: write makefile

#include <iostream>
#include <fstream>
#include <string>

#include "sequence.h"
#include "openReadingFrame.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: dna <inputFile> <outputFile>" << std::endl;
    return 1;
  }

  // extract file names
  std::string inputFileName = argv[1];
  std::string outputFileName = argv[2];

  // open input file as stream
  std::ifstream inputFile;
  inputFile.open(inputFileName.c_str(), std::ios_base::in);

  if (inputFile.fail()) {
    std::cerr << "ERROR: Could not open file: " << inputFileName << std::endl;
    return 1;
  }

  Sequence sequence;
  sequence.loadFromStream(inputFile);
  sequence.findOpenReadingFrames();
  sequence.writeReportToStream(std::cout);

  return 0;
}