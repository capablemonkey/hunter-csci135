#include "sequence.h"

// default constructor
Sequence::Sequence() {
  return;
}

void Sequence::findOpenReadingFrames() {
  for (int i = 0; i < 3; i++) {
    // find ORFs for the direct strand.  (reverse=false)
    this->findORFsInFrame(i, false);

    // find ORFs for the reverse strand.  (reverse = true)
    this->findORFsInFrame(i, true);
  }
}

// load a Sequence from a given stream
void Sequence::loadFromStream(std::istream &in) {
  // use these variables to extract data from stream
  std::string description;
  std::string buffer;
  std::string bases;

  // first line is a description
  std::getline(in, description);

  // get rid of ">" as first char in description:
  description = description.substr(1, description.size());

  while (in) {
    // stop parsing if we've reached the end of the file
    if (in.eof()) { break; }

    // extract chunk of data (delimited by whitespace); 
    // append to bases if successful
    if (in >> buffer) { bases += buffer; }
  }

  // normalize the case of the bases; convert to upper
  bases = stringToUpper(bases);

  this->description = description;
  this->basesDirect = bases;
  this->basesReverse = reverseStrand(bases);

  return;
}

void Sequence::writeReportToStream(std::ostream &out) {
  out << "ORF results for \"" << this->description 
      << "\" containing " << this->basesDirect.length()
      << " bases" << "\n" << "\n";

  // iterate through ORFs, report on each frame for direct and reverse:
  std::vector<OpenReadingFrame>::iterator it;

  // direct:
  for (int i=0; i < 3; i++) {
    if (this->openReadingFramesDirect[i].size() > 0) {
      for (it = this->openReadingFramesDirect[i].begin(); 
           it != this->openReadingFramesDirect[i].end(); it++) {
        (*it).writeReport(out);
      }
    }
    else {
      out << "No ORFs were found in reading frame " << i + 1 
          << " on the direct strand" << "\n" << "\n";
    }
  }

  // reverse:
  for (int i=0; i < 3; i++) {
    if (this->openReadingFramesReverse[i].size() > 0) {
      for (it = this->openReadingFramesReverse[i].begin(); 
           it != this->openReadingFramesReverse[i].end(); it++) {
        (*it).writeReport(out);
      }
    }
    else {
      out << "No ORFs were found in reading frame " << i + 1 
          << " on the reverse strand" << "\n" << "\n";
    }
  }
}

void Sequence::findORFsInFrame(int frame, bool reverse) {
  bool withinFrame = false;   // true if we found a START and are currently 
                              // looking for the END

  int frameBeginIndex;        // position where we found the START codon

  std::string currentCodon;   // buffer to store the current codon / substring 
                              // of 3 continuous bases

  int numberOfORFsFound = 0;

  // strand from which to read bases from
  std::string strand = this->basesDirect;

  // if we're dealing with a reverse strand, we will need to reverse 
  // the string (to read it backwards)
  if (reverse == true) {      
    std::string reverseStrand = std::string(this->basesReverse.rbegin(), 
                                            this->basesReverse.rend());
    strand = reverseStrand;
  }

  // find ORFs from reading frame 1 (index 0)
  for (int i = frame; i < strand.length() - 2; i += 3) {
    currentCodon = strand.substr(i, 3);

    // if we find a start codon (and we're not currently hunting 
    // for an END codon)...
    if ((currentCodon == CODON_START) && (withinFrame == false)) {
      frameBeginIndex = i;
      withinFrame = true;
      i += 3;   // skip the next codon since the codon right after the start 
                // codon can't be the end codon. An ORF has a minimum length of 
                // 3 codons, including the start and end codons. 
    } 

    else if ( // if we're searching for an end codon and found it...
        (withinFrame == true) && (
          currentCodon == CODON_STOP_1 ||     
          currentCodon == CODON_STOP_2 || 
          currentCodon == CODON_STOP_3 )) {

      // change state variables...
      withinFrame = false;
      numberOfORFsFound++;

      // create an OpenReadingFrame object
      std::string ORFBases = strand.substr(frameBeginIndex, 
                                           (i + 3 - frameBeginIndex));
      OpenReadingFrame newORF = OpenReadingFrame(
        ORFBases, 
        reverse ? "reverse": "direct", 
        frameBeginIndex, 
        i + 2, 
        frame, 
        numberOfORFsFound);

      // push the new ORF to one of the Sequence's vector for Direct or 
      // Reverse ORFs
      if (reverse == false) { 
        this->openReadingFramesDirect[frame].push_back(newORF); 
      } else { 
        this->openReadingFramesReverse[frame].push_back(newORF); 
      }
    }
  }

  return;
}

// Helper functions:

std::string stringToUpper(std::string strToConvert)
{
  std::transform(strToConvert.begin(), 
                 strToConvert.end(), 
                 strToConvert.begin(), 
                 ::toupper);
  return strToConvert;
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