/******************************************************************************
Title: DNA analysis
Author: Gordon Zheng
Created on: 2014-12-09
Description:  TODO: fill this in
Usage: ./dna <inputFile> <outputFile>
Build with:   g++ main.cpp -o dna
Dependencies: none
******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

const std::string CODON_START = "ATG";
const std::string CODON_STOP_1 = "TAA";
const std::string CODON_STOP_2 = "TAG";
const std::string CODON_STOP_3 = "TGA";
// const int CODON_LENGTH = 3;

class OpenReadingFrame {
private:
  std::string bases;
  std::string direction;

  int beginBaseIndex;
  int endBaseIndex;
  int readingFrame;
  int numberInReadingFrame;

public:
  OpenReadingFrame();
  OpenReadingFrame(std::string bases);

  std::string translateToProteinSequence();
};

std::string translateToProteinSequence() {
  return "foo";
};

class Sequence {
	private:
		std::string description;
		std::string bases;

		std::vector<OpenReadingFrame> openReadingFrames;

	public:
		Sequence(std::string description, std::string bases);
		std::string getReverseStrand();

		void findOpenReadingFrames();
};

Sequence::Sequence(std::string description, std::string bases) {
	this->description = description;
	this->bases = bases;
}

std::string Sequence::getReverseStrand() {
  std::string reverse = this->bases;

  for (int i = 0; i < reverse.length(); i++) {
    if (reverse[i] == 'A') { reverse[i] = 'T'; }
    else if (reverse[i] == 'T') { reverse[i] = 'A'; }
    else if (reverse[i] == 'C') { reverse[i] = 'G'; }
    else if (reverse[i] == 'G') { reverse[i] = 'C'; }
  }

	return reverse;
}

void Sequence::findOpenReadingFrames() {

  bool withinFrame = false;
  int frameBeginIndex;
  std::string currentCodon;

  for (int i=0; i < this->bases.length() - 3; i += 3) {
    currentCodon = this->bases.substr(i, 3);

    if ((currentCodon == CODON_START) && (withinFrame == false)) {
      frameBeginIndex = i;
      withinFrame = true;
      // i += 2; // skip the next 2 bases (since they make up this codon)

    } else if  ((withinFrame == true) && 
                (currentCodon == CODON_STOP_1 || 
                 currentCodon == CODON_STOP_2 || 
                 currentCodon == CODON_STOP_3)) {
      withinFrame = false;

      std::string CRF = this->bases.substr(frameBeginIndex, (i + 3 - frameBeginIndex));
      std::cout << "crf: " << CRF << std::endl;
    }
  }

  return;
}

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

	Sequence sequence = createSequenceFromFile(inputFileName);

	sequence.findOpenReadingFrames();

	// std::cout << sequence.getReverseStrand() << std::endl;

  return 0;
}