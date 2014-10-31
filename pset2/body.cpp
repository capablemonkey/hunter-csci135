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

// TODO: consider using a Map that maps distance to [body1, body2]
//        in order to only calcuate distances between bodies once
//        for getClosestBodies, getFurthestBodies, and 
//         getAverageDistanceBetweenBodies

void getClosestBodies(Body bodiesList[], int bodiesListCount, Body* resultList[2]) {
  // start off by comparing the first and second Bodies
  double shortestDistance = getDistanceBetweenBodies(bodiesList[0], bodiesList[1]);

  // hold pointers to the current closest pair of bodies
  Body *currentClosestPairBody1 = &bodiesList[0];
  Body *currentClosestPairBody2 = &bodiesList[1];

  // temporarily store distance calculated for each comparison here
  double currentDistance;

  // For i bodies in bodiesList, iterate through i - 1 bodies, calculating the 
  // distances between each body and the bodies after it in the array.
  for (int i = 0; i < bodiesListCount - 1; i++) {
    for (int n = i + 1; n < bodiesListCount; n++) {
      currentDistance = getDistanceBetweenBodies(bodiesList[i], bodiesList[n]);

      // If the current pair's distance is shorter than any previous, set 
      // shortestDistance to the current distance and note the current bodies in currentClosestPairBody1 and currentClosestPairBody2
      if (currentDistance < shortestDistance) {
        shortestDistance = currentDistance;
        currentClosestPairBody1 = &bodiesList[i];
        currentClosestPairBody2 = &bodiesList[n];
      }
    }
  }

  // place pointers to the closest bodies into the results pointer array
  resultList[0] = currentClosestPairBody1;
  resultList[1] = currentClosestPairBody2;

  return;
}

void getFurthestBodies(Body bodiesList[], int bodiesListCount, Body* resultList[2]) {
  // start off by comparing the first and second Bodies
  double furthestDistance = getDistanceBetweenBodies(bodiesList[0], bodiesList[1]);
  
  // hold pointers to the current furthest pair of bodies
  Body *currentFurthestPairBody1 = &bodiesList[0];
  Body *currentFurthestPairBody2 = &bodiesList[1];

  // temporarily store distance calculated for each comparison here
  double currentDistance;

  // For i bodies in bodiesList, iterate through i - 1 bodies, calculating the 
  // distances between each body and the bodies after it in the array.
  for (int i = 0; i < bodiesListCount - 1; i++) {
    for (int n = i + 1; n < bodiesListCount; n++) {
      currentDistance = getDistanceBetweenBodies(bodiesList[i], bodiesList[n]);

      // If the current pair's distance is shorter than any previous, set 
      // furthestDistance to the current distance and note the current bodies in currentFurthestPairBody1 and currentFurthestPairBody2
      if (currentDistance > furthestDistance) {
        furthestDistance = currentDistance;
        currentFurthestPairBody1 = &bodiesList[i];
        currentFurthestPairBody2 = &bodiesList[n];
      }
    }
  }

  // place pointers to the Furthest bodies into the results pointer array
  resultList[0] = currentFurthestPairBody1;
  resultList[1] = currentFurthestPairBody2;

  return;
}

double getAverageDistanceBetweenBodies(Body bodiesList[], int bodiesListCount) {
  double sum = 0;
  int distancesCount = 0;

  for (int i = 0; i < bodiesListCount - 1; i++) {
    for (int n = i + 1; n < bodiesListCount; n++) {
      sum += getDistanceBetweenBodies(bodiesList[i], bodiesList[n]);
      distancesCount++;
    }
  }

  return sum / distancesCount;
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