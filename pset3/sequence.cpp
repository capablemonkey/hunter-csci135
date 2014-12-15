#include "sequence.h"

Sequence::Sequence(std::string description, std::string bases) {
  this->description = description;
  this->basesDirect = bases;
  this->basesReverse = reverseStrand(bases);
}

void Sequence::findOpenReadingFrames() {
  // TODO: do this for the reverse strand:
  for (int i = 0; i < 3; i++) {
    this->findORFsInFrame(i, false);
    this->findORFsInFrame(i, true);
  }
}

void Sequence::writeReportToStream(std::ostream &out) {
	out << "ORF results for \"" << this->description 
			<< "\" containing " << this->basesDirect.length()
			<< " bases" << std::endl << std::endl;

	// iterate through ORFs, report on each frame for direct and reverse:
	std::vector<OpenReadingFrame>::iterator it;

	for (int i=0; i < 3; i++) {
		if (this->openReadingFramesDirect[i].size() > 0) {
			for (it = this->openReadingFramesDirect[i].begin(); it != this->openReadingFramesDirect[i].end(); it++) {
				(*it).writeReport(out);
			}
		}
		else {
			out << "No ORFs were found in reading frame " << i + 1 << " on the direct strand" << std::endl << std::endl;
		}
	}

	for (int i=0; i < 3; i++) {
		if (this->openReadingFramesReverse[i].size() > 0) {
			for (it = this->openReadingFramesReverse[i].begin(); it != this->openReadingFramesReverse[i].end(); it++) {
				(*it).writeReport(out);
			}
		}
		else {
			out << "No ORFs were found in reading frame " << i + 1 << " on the reverse strand" << std::endl << std::endl;
		}
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

      if (reverse == false) { this->openReadingFramesDirect[frame].push_back(newORF); }
      else { this->openReadingFramesReverse[frame].push_back(newORF); }
    }
  }

  return;
}

// Helper functions:

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