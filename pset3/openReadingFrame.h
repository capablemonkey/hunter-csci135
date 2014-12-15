#ifndef OPEN_READING_FRAME_H
#define OPEN_READING_FRAME_H

#include <string>
#include <map>
#include <iostream>
#include <algorithm>  // std::replace()

class OpenReadingFrame {
  private:
    std::string bases;
    std::string direction;

    int beginBaseIndex;       // 0-based index of first base of ORF 
                              // (from direct or reverse strand)

    int endBaseIndex;         // 0-based index of last base of ORF 
                              // (from direct or reverse strand)

    int readingFrame;         // offset with which we read through the 
                              // direct/rev strand to find this ORF.  
                              // Either 0, 1, or 2.  

    int numberInReadingFrame; // within the readingFrame, which # ORF was 
                              // this one?  {1 (first found in frame), 2, or 3}

  public:
    OpenReadingFrame();
    OpenReadingFrame(std::string bases, std::string direction, 
                     int beginBaseIndex, int endBaseIndex, 
                     int readingFrame, int numberInReadingFrame);

    // returns a string of protein codes, mapped from the ORF's mRNA
    std::string translateToProteinSequence();

    // write to a given output stream a report about the ORF:
    void writeReport(std::ostream &out);
};

#endif