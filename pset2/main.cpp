/******************************************************************************
Title: Distances between 3D Bodies
Author: Gordon Zheng
Created on: 2014-10-28
Description:  Reads 3D positions (X, Y, Z) for between 3-36 bodies from a file,
              command line arg file1, write general stats to file passed
              in CLI arg file2, and write sorted list of bodies to file in 
              CLI arg file3.
Usage: ./bodies <file1> <file2> <file3>
Build with: g++ main.cpp -o bodies
Dependencies: none
******************************************************************************/


#import <iostream>
#import <string>
#import <fstream>

using namespace std;

const int BODIES_COUNT_MAX = 36;
const int BODIES_COUNT_MIN = 3;
const bool READ_FAILED = true;
const bool READ_SUCCESS = false;

class Body {
  private:
    string label;
    double x, y, z;
  public:
    Body();                                             // default constructor
    Body(string label, double x, double y, double z);
};

Body::Body() {

};

Body::Body(string label, double x, double y, double z) {
  this->label = label;
  this->x = x;
  this->y = y;
  this->z = z;
}

bool createBodiesFromFile(string inputFileName, Body bodiesList[], int &bodiesListCount) {
  // read file, map lines to Body objects:
  ifstream inputFile;
  inputFile.open(inputFileName, std::ios_base::in);

  if (inputFile.fail()) {
    cerr << "ERROR: Could not open file: " << inputFileName << endl;
    return READ_FAILED;
  }

  // use these variables to extract data from file
  string label;
  double x, y, z;
  bool successfullyParsedBodyData;

  while (inputFile) {
    // stop parsing if we've reached the end of the file
    if (inputFile.eof()) { break; }

    // extract data; if success, stream evaluates to true
    successfullyParsedBodyData = (inputFile >> label >> x >> y >> z);

    // exit if we ecountered an error while parsing
    if(successfullyParsedBodyData != true) {
      cerr  << "ERROR: encountered an error reading file: " 
            << inputFileName << std::endl;
      return READ_FAILED;
    }

    // create new Body and assign it as array element; keep count of bodies
    bodiesList[bodiesListCount] = Body(label, x, y, z);
    bodiesListCount++;
  }

  return READ_SUCCESS;
}

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
  if (readResult == READ_FAILED) { return 1; }

  cout << bodiesList[2].label;

  // check to make sure there are at least 3 bodies, not more than 36

  if (bodiesListCount < 3 || bodiesListCount > 36) {
    cerr << "ERROR: input file must contain between 3 and 36 bodies." << endl;
    return 1;
  }

  return 0;
}