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

Sequence createSequenceFromFile(std::string inputFileName) {
  std::ifstream inputFile;
  inputFile.open(inputFileName.c_str(), std::ios_base::in);

  if (inputFile.fail()) {
    std::cerr << "ERROR: Could not open file: " << inputFileName << std::endl;

    // TODO: figure out how to float up exception and have it be caught in main elegantly
    throw "oh no";
    // return 1;
  }

  // use these variables to extract data from file
  std::string description;
  std::string buffer;
  std::string bases;

  // first line is a description
  // TODO: get rid of ">"
  std::getline(inputFile, description);

  while (inputFile) {
    // stop parsing if we've reached the end of the file
    if (inputFile.eof()) { break; }

    inputFile >> buffer;
    bases += buffer;

    // TODO: fix bug where a trailing empty line will cause a duplication of the last buffer
  }

  // TODO normalize the case of the bases; convert to upper

  inputFile.close();

  return Sequence(description, bases);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: dna <inputFile> <outputFile>" << std::endl;
    return 1;
  }

  std::string inputFileName = argv[1];
  std::string outputFileName = argv[2];

  // TODO: createSequenceFromFile should be a class method of Sequence, who gets passed the file stream
  Sequence sequence = createSequenceFromFile(inputFileName);

  sequence.findOpenReadingFrames();

  sequence.writeReportToStream(std::cout);

  return 0;
}