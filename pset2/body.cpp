#include "body.h"

// Constructor for Body class:
Body::Body(std::string label, double x, double y, double z) {
  this->label = label;
  this->x = x;
  this->y = y;
  this->z = z;
}

/*
 *  BodyCollection methods:
 */

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

bool compareBodyPairsByDistance(BodyPair a, BodyPair b) {
  return a.distance < b.distance;
}

BodyPair BodyCollection::getClosestBodies() {
  return *std::min_element(bodyPairsList.begin(), bodyPairsList.begin() + bodyPairsListCount, compareBodyPairsByDistance);
}

BodyPair BodyCollection::getFurthestBodies() {
  return *std::max_element(bodyPairsList.begin(), bodyPairsList.begin() + bodyPairsListCount, compareBodyPairsByDistance);
}

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

void BodyCollection::findBodyPairsWithBody(std::string label, BodyPair *bodyPairsWithBody[], int &bodyPairsWithBodyCount) {
  for(int i = 0; i < bodyPairsListCount; i++) {
    if (bodyPairsList[i].firstBody->getLabel() == label || 
      bodyPairsList[i].secondBody->getLabel() == label) {

      bodyPairsWithBody[bodyPairsWithBodyCount] = &bodyPairsList[i];
      bodyPairsWithBodyCount++;
    }
  }
}

/*
 *   BodyCollection file input/output methods:
 */

bool BodyCollection::createBodiesFromFile(std::string inputFileName) {
  // read file, map lines to Body objects:
  std::ifstream inputFile;
  inputFile.open(inputFileName.c_str(), std::ios_base::in);

  if (inputFile.fail()) {
    std::cerr << "ERROR: Could not open file: " << inputFileName << std::endl;
    return FILE_IO_FAILED;
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
      std::cerr   << "ERROR: encountered an error reading file: " 
                  << inputFileName << std::endl;
      return FILE_IO_FAILED;
    }

    // create new Body and add it to the BodyCollection
    this->bodiesList[bodiesListCount] = Body(label, x, y, z);
    this->bodiesListCount++;
  }

  inputFile.close();

  return FILE_IO_SUCCESS;
}

bool BodyCollection::outputStatsFile(std::string outputFileName) {
  // open file stream for writing
  std::ofstream outputFile;
  outputFile.open(outputFileName.c_str(), std::ios_base::out);

  // if we were unable to open file for writing, stop here and return
  // IO failure flag:
  if (outputFile.fail()) {
    std::cerr << "ERROR: Could not open file for writing: " << outputFileName << std::endl;
    return FILE_IO_FAILED;
  }

  // set precision for floating point number output:
  outputFile.setf(std::ios::fixed);
  outputFile.setf(std::ios::showpoint);
  outputFile.precision(2);

  // determine stats using BodyCollection methods and write them out
  BodyPair closestBodies = this->getClosestBodies();
  BodyPair furthestBodies = this->getFurthestBodies();
  double averageDistance = this->getAverageDistanceBetweenBodies();
  double volumeOfBoundingBox = this->getVolumeOfBoxBoundingBodies();

  outputFile  << closestBodies.firstBody->getLabel() << " " 
              << closestBodies.secondBody->getLabel() << " "
              << closestBodies.distance << "km"
              << std::endl;

  outputFile  << furthestBodies.firstBody->getLabel() << " " 
              << furthestBodies.secondBody->getLabel() << " " 
              << furthestBodies.distance << "km"
              << std::endl;

  outputFile << averageDistance << "km" << std::endl;
  outputFile << volumeOfBoundingBox << "km^3";

  outputFile.close();
  return FILE_IO_SUCCESS;
}

bool BodyCollection::outputListingsFile(std::string outputFileName) {
  // open file stream for writing
  std::ofstream outputFile;
  outputFile.open(outputFileName.c_str(), std::ios_base::out);

  // if we were unable to open file for writing, stop here and return
  // IO failure flag:
  if (outputFile.fail()) {
    std::cerr << "ERROR: Could not open file for writing: " << outputFileName << std::endl;
    return FILE_IO_FAILED;
  }

  // set precision for floating point number output:
  outputFile.setf(std::ios::fixed);
  outputFile.setf(std::ios::showpoint);
  outputFile.precision(2);

  // get an array of the labels of the bodies in our BodyCollection:
  std::string labels[BODIES_COUNT_MAX];

  for (int i = 0; i < bodiesListCount; i++) {
    labels[i] = bodiesList[i].getLabel();
  }

  // sort the labels alphabetically:
  sortStringsAlpha(labels, bodiesListCount);

  /*
   * For each label, retrieve the BodyPairs that contain the body with that 
   * label.  Then, sort the BodyPairs by distance and output them.
   */
  for (int i = 0; i < bodiesListCount; i++) {
    // array of pointers to BodyPairs that contain body w/ current label
    BodyPair *bodyPairsWithBody[MAX_PAIRS];
    int bodyPairsWithBodyCount = 0;

    // find all BodyPairs that include the body with the current label
    this->findBodyPairsWithBody(labels[i], bodyPairsWithBody, bodyPairsWithBodyCount);
    
    // sort the BodyPairs by distance:
    sortBodyPairsByDistance(bodyPairsWithBody, bodyPairsWithBodyCount);
    
    // write new section:
    outputFile << labels[i] << std::endl;

    // write the distance to the body itself, 0.  
    // (not sure why this would be useful... just following the spec):
    outputFile << "\t" << labels[i] << "\t" << "0.00" << std::endl;

    for (int n = 0; n < bodyPairsWithBodyCount; n++) {
      // get the label of the companion body in each BodyPair
      std::string otherBodyLabel = (
        (*bodyPairsWithBody[n]).firstBody->getLabel() != labels[i])  
          ? (*bodyPairsWithBody[n]).firstBody->getLabel() 
          : (*bodyPairsWithBody[n]).secondBody->getLabel();

      outputFile  << "\t" << otherBodyLabel
                  << "\t" << (*bodyPairsWithBody[n]).distance;

      // if this is not the last line of the file, print a new line:
      if (!(n == bodyPairsWithBodyCount - 1 && i == bodiesListCount - 1)) { 
        outputFile << std::endl; 
      }
    }
  }

  outputFile.close();
  return FILE_IO_SUCCESS;
}

/*
 *  Helper Functions
 */

double getDistanceBetweenBodies(Body body1, Body body2) {
  return std::sqrt(
    std::pow(body2.getX() - body1.getX(), 2) +
    std::pow(body2.getY() - body1.getY(), 2) +
    std::pow(body2.getZ() - body1.getZ(), 2)
  );
};

void sortBodyPairsByDistance(BodyPair *bodyPairs[], int &bodyPairsCount) {
  // Bubble sort
  for (int i = 0; i < bodyPairsCount - 1; i++) {
    for (int n = 0; n < bodyPairsCount - 1; n++) {
      if ( (*bodyPairs[n]).distance > (*bodyPairs[n + 1]).distance) {
        std::swap(bodyPairs[n], bodyPairs[n + 1]);
      }
    }
  }
}

void sortStringsAlpha(std::string strings[], int stringsCount) {
  // Bubble sort

  for (int i = 0; i < stringsCount - 1; i++) {
    for (int n = 0; n < stringsCount - 1; n++) {
      if (strings[n] > strings[n + 1]) {
        std::swap(strings[n], strings[n + 1]);
      }
    }
  }
}