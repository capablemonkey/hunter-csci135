#ifndef SEQUENCE_H
#define SEQUENCE_H

// includes
#include <string>
#include <vector>
#include <iostream>
#include "openReadingFrame.h"

// constants
const std::string CODON_START = "ATG";
const std::string CODON_STOP_1 = "TAA";
const std::string CODON_STOP_2 = "TAG";
const std::string CODON_STOP_3 = "TGA";

// return complement of DNA to find MRNA:
std::string reverseStrand(std::string strandBases); 

// returns copy of string in uppercase: 
std::string stringToUpper(std::string strToConvert);

class Sequence {
  private:
    std::string description;  // sequence description from input file
    std::string basesDirect;  // bases in direct direction
    std::string basesReverse; // bases in reverse direction

    /* Arrays of vectors which store ORFs.  Structure:
     *
     * array direct/reverse = {
     *  [first frame],  : vector of ORFs
     *  [second frame], : vector of ORFs
     *  [third frame]   : vector of ORFs
     * }
     */
    std::vector<OpenReadingFrame> openReadingFramesDirect[3];
    std::vector<OpenReadingFrame> openReadingFramesReverse[3];

  public:
    Sequence();

    void loadFromStream(std::istream &in);  // loads Sequence from file stream
    void findOpenReadingFrames();           // determine ORFs in both directions

    void findORFsInFrame(int frame, bool reverse);  // used by 
                                                    // findOpenReadingFrames
                                                    // to find ORFs in a 
                                                    // particular frame and 
                                                    // direction

    void writeReportToStream(std::ostream &out);  // writes report about 
                                                  // sequence and all ORFs to a 
                                                  // given output stream
};

#endif