#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <vector>
#include "openReadingFrame.h"

const std::string CODON_START = "ATG";
const std::string CODON_STOP_1 = "TAA";
const std::string CODON_STOP_2 = "TAG";
const std::string CODON_STOP_3 = "TGA";

std::string reverseStrand(std::string strandBases);

class Sequence {
  private:
    std::string description;
    std::string basesDirect;
    std::string basesReverse;

    std::vector<OpenReadingFrame> openReadingFramesDirect[3];
    std::vector<OpenReadingFrame> openReadingFramesReverse[3];

  public:
    Sequence(std::string description, std::string bases);

    void findOpenReadingFrames();
    void findORFsInFrame(int frame, bool reverse);
    void writeReportToStream(std::ostream &out);
};

#endif