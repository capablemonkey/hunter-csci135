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

std::string reverseStrand(std::string strandBases);

class OpenReadingFrame {
private:
  std::string bases;
  std::string direction;

  int beginBaseIndex;       // 0-based index of first base of ORF (from direct or reverse strand)
  int endBaseIndex;         // 0-based index of last base of ORF (from direct or reverse strand)
  int readingFrame;         // offset with which we read through the direct/rev strand to find this ORF.  Either 0, 1, or 2.  
  int numberInReadingFrame; // within the readingFrame, which # ORF was this one?  Either 1 (first found in frame), 2, or 3

public:
  OpenReadingFrame();
  OpenReadingFrame(std::string bases, std::string direction, int beginBaseIndex, int endBaseIndex, int readingFrame, int numberInReadingFrame);

  std::string translateToProteinSequence();
};

class Sequence {
  private:
    std::string description;
    std::string basesDirect;
    std::string basesReverse;

    std::vector<OpenReadingFrame> openReadingFrames;

  public:
    Sequence(std::string description, std::string bases);

    void findOpenReadingFrames();
    void findORFsInFrame(int frame, bool reverse);
};

OpenReadingFrame::OpenReadingFrame(std::string bases, std::string direction, int beginBaseIndex, int endBaseIndex, int readingFrame, int numberInReadingFrame) {
  this->bases = bases;
  this->direction = direction;
  this->beginBaseIndex = beginBaseIndex;
  this->endBaseIndex = endBaseIndex;
  this->readingFrame = readingFrame;
  this->numberInReadingFrame = numberInReadingFrame;

  std::cout << direction
  << " " << beginBaseIndex + 1
  << "-" << endBaseIndex + 1
  << " RF[" << readingFrame + 1
  << "] #" << numberInReadingFrame 
  << " " << bases << std::endl;
}

std::string translateToProteinSequence() {
  return "foo";
};

Sequence::Sequence(std::string description, std::string bases) {
	this->description = description;
	this->basesDirect = bases;
  this->basesReverse = reverseStrand(bases);
}

std::string reverseStrand(std::string strandBases) {
  std::string reverse = strandBases;

  for (int i = 0; i < reverse.length(); i++) {
    if (reverse[i] == 'A') { reverse[i] = 'T'; }
    else if (reverse[i] == 'T') { reverse[i] = 'A'; }
    else if (reverse[i] == 'C') { reverse[i] = 'G'; }
    else if (reverse[i] == 'G') { reverse[i] = 'C'; }
  }

  return reverse;
}

void Sequence::findOpenReadingFrames() {
  // TODO: do this for the reverse strand:
  for (int i = 0; i < 3; i++) {
    this->findORFsInFrame(i, false);
    this->findORFsInFrame(i, true);
  }
}

void Sequence::findORFsInFrame(int frame, bool reverse) {
  bool withinFrame = false;   // true: we found a START and are currently looking for the END
  int frameBeginIndex;        // position where we found the START codon
  std::string currentCodon;   // buffer to store the current codon / substring of 3 continuous bases
  int numberOfORFsFound = 0;

  std::string strand = this->basesDirect;

  if (reverse == true) {      // if reverse strand, we will need to reverse the string (to read it backwards)
    std::string reverseStrand = std::string(this->basesReverse.rbegin(), this->basesReverse.rend());
    strand = reverseStrand;
  }

  // find ORFs from reading frame 1 (index 0)
  for (int i = frame; i < strand.length() - 2; i += 3) {
    currentCodon = strand.substr(i, 3);

    if ((currentCodon == CODON_START) && (withinFrame == false)) {
      frameBeginIndex = i;
      withinFrame = true;
      i += 3;       // skip the next codon since the codon right after the start codon can't be the end codon. An ORF has a minimum length of 3 codons, including the start and end codons. 

    } else if  ((withinFrame == true) && 
                (currentCodon == CODON_STOP_1 || 
                 currentCodon == CODON_STOP_2 || 
                 currentCodon == CODON_STOP_3)) {
      withinFrame = false;
      numberOfORFsFound++;

      std::string ORFBases = strand.substr(frameBeginIndex, (i + 3 - frameBeginIndex));
      OpenReadingFrame newORF = OpenReadingFrame(ORFBases, reverse ? "reverse": "direct", frameBeginIndex, i + 2, frame, numberOfORFsFound);

      this->openReadingFrames.push_back(newORF);
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

  return 0;
}