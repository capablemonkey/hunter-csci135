#include "OpenReadingFrame.h"

// map mapping MRNA codon to protein single letter code
std::map<std::string, std::string> MRNA_CODON_TO_PROTEIN = {
	{"UUU", "F"},
	{"UUC", "F"},
	{"UUA", "L"},
	{"UUG", "L"},
	{"CUU", "L"},
	{"CUC", "L"},
	{"CUA", "L"},
	{"CUG", "L"},
	{"AUU", "I"},
	{"AUC", "I"},
	{"AUA", "I"},
	{"AUG", "M"},
	{"GUU", "V"},
	{"GUC", "V"},
	{"GUA", "V"},
	{"GUG", "V"},
	{"UCU", "S"},
	{"UCC", "S"},
	{"UCA", "S"},
	{"AGU", "S"},
	{"AGC", "S"},
	{"UCG", "S"},
	{"CCU", "P"},
	{"CCC", "P"},
	{"CCA", "P"},
	{"CCG", "P"},
	{"ACU", "T"},
	{"ACC", "T"},
	{"ACA", "T"},
	{"ACG", "T"},
	{"GCU", "A"},
	{"GCC", "A"},
	{"GCA", "A"},
	{"GCG", "A"},
	{"UAU", "Y"},
	{"UAC", "Y"},
	{"UAA", "*"},
	{"UGA", "*"},
	{"UAG", "*"},
	{"CAU", "H"},
	{"CAC", "H"},
	{"CAA", "Q"},
	{"CAG", "Q"},
	{"AAU", "N"},
	{"AAC", "N"},
	{"AAA", "K"},
	{"AAG", "K"},
	{"GAU", "D"},
	{"GAC", "D"},
	{"GAA", "E"},
	{"GAG", "E"},
	{"UGU", "C"},
	{"UGC", "C"},
	{"UGG", "W"},
	{"CGU", "R"},
	{"CGC", "R"},
	{"CGA", "R"},
	{"AGA", "R"},
	{"AGG", "R"},
	{"CGG", "R"},
	{"GGU", "G"},
	{"GGC", "G"},
	{"GGA", "G"},
	{"GGG", "G"}
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
  out << ">ORF number " << numberInReadingFrame 
  		<< " in reading frame " << readingFrame + 1
  		<< " on the " << direction
  		<<" strand extends from base " << beginBaseIndex + 1
  		<< " to base " << endBaseIndex + 1
  		<< "\n";

 	out << bases << "\n" << "\n";
 	out << ">Translation of ORF number " << numberInReadingFrame
 			<< " in reading frame " << readingFrame + 1
 			<< " on the " << direction
 			<< " strand" << "\n";

  out << this->translateToProteinSequence() << "\n" << "\n";
}

std::string OpenReadingFrame::translateToProteinSequence() {
	// translate DNA to mRNA: replace all 'T' bases with 'U'
	std::string mRNA = this->bases;
	std::replace(mRNA.begin(), mRNA.end(), 'T', 'U');

	// map codons to proteins:
	std::string protein;

	for (int i = 0; i < mRNA.length(); i += 3) {
		protein += MRNA_CODON_TO_PROTEIN[mRNA.substr(i, 3)];
	}

  return protein;
};