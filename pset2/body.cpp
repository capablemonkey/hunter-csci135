#include "body.h"

Body::Body(std::string label, double x, double y, double z) {
  this->label = label;
  this->x = x;
  this->y = y;
  this->z = z;
}

double getDistanceBetweenBodies(Body body1, Body body2) {
  return std::sqrt(
    std::pow(body2.getX() - body1.getX(), 2) +
    std::pow(body2.getY() - body1.getY(), 2) +
    std::pow(body2.getZ() - body1.getZ(), 2)
  );
};

void getClosestBodies(Body bodiesList[], Body resultList[]) {
  resultList[0] = bodiesList[1];
  resultList[1] = bodiesList[0];
  return;
}

bool createBodiesFromFile(std::string inputFileName, Body bodiesList[], int &bodiesListCount) {
  // read file, map lines to Body objects:
  std::ifstream inputFile;
  inputFile.open(inputFileName, std::ios_base::in);

  if (inputFile.fail()) {
    std::cout << "ERROR: Could not open file: " << inputFileName << std::endl;
    return READ_BODIES_FAILED;
  }

  // use these variables to extract data from file
  std::string label;
  double x, y, z;
  bool successfullyParsedBodyData;

  while (inputFile) {
    // stop parsing if we've reached the end of the file
    if (inputFile.eof()) { break; }

    // extract data; if success, stream evaluates to true
    successfullyParsedBodyData = (inputFile >> label >> x >> y >> z);

    // exit if we ecountered an error while parsing
    if(successfullyParsedBodyData != true) {
      std::cout  << "ERROR: encountered an error reading file: " 
            << inputFileName << std::endl;
      return READ_BODIES_FAILED;
    }

    // create new Body and assign it as array element; keep count of bodies
    bodiesList[bodiesListCount] = Body(label, x, y, z);
    bodiesListCount++;
  }

  return READ_BODIES_SUCCESS;
}