/******************************************************************************
Title: Distances between 3D Bodies
Author: Gordon Zheng
Created on: 2014-10-28
Description:  Reads 3D positions (X, Y, Z) for between 3-36 bodies from a file,
              command line arg file1, write general stats to file passed
              in CLI arg file2, and write sorted list of bodies to file in 
              CLI arg file3.
Usage: ./bodies <file1> <file2> <file3>
Build with:   g++ main.cpp body.cpp -o bodies
Dependencies: none
******************************************************************************/

#import <iostream>
#import "body.h"

const int BODIES_COUNT_MAX = 36;
const int BODIES_COUNT_MIN = 3;

using namespace std;

int main(int argc, char *argv[]) {
  // make sure we've got at least 3 arguments (any extra will be ignored)
  if (argc < 4) {
    cerr << "Usage: ./bodies <file1> <file2> <file3>" << endl;
    return 1;
  }

  // give args some meaningful names...
  string inputFileName = argv[1];
  string outputFileName1 = argv[2];
  string outputFileName2 = argv[3];

  // store all bodies into this array:
  Body bodiesList[BODIES_COUNT_MAX];
  int bodiesListCount = 0;

  // read file and create Body objects to store in bodiesList with the 
  // number of created objects in bodiesListCount
  bool readResult = createBodiesFromFile(inputFileName, bodiesList, bodiesListCount);
  if (readResult == READ_BODIES_FAILED) { return 1; }

  // check to make sure there are at least 3 bodies, not more than 36
  if (bodiesListCount < 3 || bodiesListCount > 36) {
    cerr << "ERROR: input file must contain between 3 and 36 bodies." << endl;
    return 1;
  }

  Body* closestBodies[2];
  Body* furthestBodies[2];
  getClosestBodies(bodiesList, bodiesListCount, closestBodies);
  getFurthestBodies(bodiesList, bodiesListCount, furthestBodies);

  cout << "closest " << closestBodies[0]->getLabel() << " " << closestBodies[1]->getLabel() << endl;
  cout << "furthest" << furthestBodies[0]->getLabel() << " " << furthestBodies[1]->getLabel() << endl;

  double averageDistance = getAverageDistanceBetweenBodies(bodiesList, bodiesListCount);
  cout << "average dist: " << averageDistance << endl;
  return 0;
}