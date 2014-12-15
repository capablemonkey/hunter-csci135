/******************************************************************************
Title: DNA analysis
Author: Gordon Zheng
Created on: 2014-12-09
Description:  Analyzes of FASTA format DNA sequence and outputs 
              Open Reading Frames
Usage: ./dna <inputFile> <outputFile>
Build with: make
      (or) g++ -std=c++11 main.cpp sequence.cpp openReadingFrame.cpp -o dna
Dependencies: none
******************************************************************************/

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

  // open output file for writing
  std::ofstream outputFile;
  outputFile.open(outputFileName.c_str(), std::ios_base::out);

  if (outputFile.fail()) {
    std::cerr << "ERROR: Could not open file for writing: " 
              << outputFileName << std::endl;
    return 1;
  }

  Sequence sequence;
  sequence.loadFromStream(inputFile);
  sequence.findOpenReadingFrames();
  sequence.writeReportToStream(outputFile);

  inputFile.close();
  outputFile.close();
  return 0;
}