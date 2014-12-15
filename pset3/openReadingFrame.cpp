#include "OpenReadingFrame.h"

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