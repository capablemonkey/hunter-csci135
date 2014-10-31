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

void BodyCollection::calculateDistances() {
  for (int i = 0; i < bodiesListCount - 1; i++) {
    for (int n = i + 1; n < bodiesListCount; n++) {
      BodyPair pair;
      pair.distance = getDistanceBetweenBodies(bodiesList[i], bodiesList[n]);
      pair.firstBody = &bodiesList[i];
      pair.secondBody = &bodiesList[n];

      this->bodyPairsList[this->bodyPairsListCount] = pair;
      this->bodyPairsListCount++;
    }
  }
}

BodyPair BodyCollection::getClosestBodies() {
  double closestDistance = bodyPairsList[0].distance;
  int indexOfClosestPair = 0;

  for (int i = 1; i < bodyPairsListCount; i++) {
    if (bodyPairsList[i].distance < closestDistance) {
      closestDistance = bodyPairsList[i].distance;
      indexOfClosestPair = i;
    }
  }

  return bodyPairsList[indexOfClosestPair];
}

BodyPair BodyCollection::getFurthestBodies() {
  double furthestDistance = bodyPairsList[0].distance;
  int indexOfFurthestPair = 0;

  for (int i = 1; i < bodyPairsListCount; i++) {
    if (bodyPairsList[i].distance > furthestDistance) {
      furthestDistance = bodyPairsList[i].distance;
      indexOfFurthestPair = i;
    }
  }

  return bodyPairsList[indexOfFurthestPair];
}

// void sortBodiesListByLabel(Body &bodiestList[], int bodiesListCount) {

// }

double BodyCollection::getVolumeOfBoxBoundingBodies() {
  // keep track of lowest and highest X, Y, and Z values:
  double lowestX, lowestY, lowestZ, highestX, highestY, highestZ;

  // initialize them to the first Body's coordinates:
  lowestX = bodiesList[0].getX();
  highestX = bodiesList[0].getX();

  lowestY = bodiesList[0].getY();
  highestY = bodiesList[0].getY();

  lowestZ = bodiesList[0].getZ();
  highestZ = bodiesList[0].getZ();

  for (int index = 1; index < bodiesListCount; index++) {
    if (bodiesList[index].getX() < lowestX) { lowestX = bodiesList[index].getX(); }
    if (bodiesList[index].getX() > highestX) { highestX = bodiesList[index].getX(); }

    if (bodiesList[index].getY() < lowestY) { lowestY = bodiesList[index].getY(); }
    if (bodiesList[index].getY() > highestY) { highestY = bodiesList[index].getY(); }

    if (bodiesList[index].getZ() < lowestZ) { lowestZ = bodiesList[index].getZ(); }
    if (bodiesList[index].getZ() > highestZ) { highestZ = bodiesList[index].getZ(); }
  }

  return (highestX - lowestX) * (highestY - lowestY) * (highestZ - lowestZ);
}

double BodyCollection::getAverageDistanceBetweenBodies() {
  double sum = 0;

  for (int i = 0; i < bodyPairsListCount; i++) {
    sum += bodyPairsList[i].distance;
  }

  return sum / bodyPairsListCount;
}

bool BodyCollection::createBodiesFromFile(std::string inputFileName) {
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

    // create new Body and add it to the BodyCollection
    this->bodiesList[bodiesListCount] = Body(label, x, y, z);
    this->bodiesListCount++;
  }

  return READ_BODIES_SUCCESS;
}