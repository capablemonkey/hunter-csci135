#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <vector>
#include <iostream>
#include "openReadingFrame.h"

// constants
const std::string CODON_START = "ATG";
const std::string CODON_STOP_1 = "TAA";
const std::string CODON_STOP_2 = "TAG";
const std::string CODON_STOP_3 = "TGA";

// prototypes for helper functions:
std::string reverseStrand(std::string strandBases);
std::string stringToUpper(std::string strToConvert);

class Sequence {
  private:
    std::string description;
    std::string basesDirect;
    std::string basesReverse;

    std::vector<OpenReadingFrame> openReadingFramesDirect[3];
    std::vector<OpenReadingFrame> openReadingFramesReverse[3];

  public:
  	Sequence();
    Sequence(std::string description, std::string bases);

    void loadFromStream(std::istream &in);
    void findOpenReadingFrames();
    void findORFsInFrame(int frame, bool reverse);
    void writeReportToStream(std::ostream &out);
};

#endif