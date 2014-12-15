#include "OpenReadingFrame.h"

std::map<std::string, std::string> MRNA_CODON_TO_PROTEIN = {
	{"FOO", "BAR"}
};

OpenReadingFrame::OpenReadingFrame(std::string bases, std::string direction, int beginBaseIndex, int endBaseIndex, int readingFrame, int numberInReadingFrame) {
  this->bases = bases;
  this->direction = direction;
  this->beginBaseIndex = beginBaseIndex;
  this->endBaseIndex = endBaseIndex;
  this->readingFrame = readingFrame;
  this->numberInReadingFrame = numberInReadingFrame;
}

void OpenReadingFrame::writeReport(std::ostream &out) {
	out << direction
  << " " << beginBaseIndex + 1
  << "-" << endBaseIndex + 1
  << " RF[" << readingFrame + 1
  << "] #" << numberInReadingFrame 
  << " " << bases << std::endl;

  out << this->translateToProteinSequence();
}

std::string OpenReadingFrame::translateToProteinSequence() {

	// translate DNA to mRNA: replace all 'T' bases with 'U'

	std::cout << MRNA_CODON_TO_PROTEIN["FOO"];
  return "foo";
};