// include guards
#ifndef BODY_H    
#define BODY_H

/*
 *  Import std lib headers
 */

#import <iostream>    // std::cerr
#import <string>      // std::string
#import <fstream>     // std::ifstream, std::ofstream
#import <cmath>       // std::pow, std::sqrt

/*
 *  Constants
 */

const bool FILE_IO_FAILED = true;
const bool FILE_IO_SUCCESS = false;

const int BODIES_COUNT_MAX = 36;
const int BODIES_COUNT_MIN = 3;
const int MAX_PAIRS = 666;      // (n^2 + n) / 2, where n = BODIES_COUNT_MAX - 1

/*
 *  Body class represents a point in 3D space.  Consists of X, Y, Z coordinates
 *  and a string label.  Getters defined for each property, but no setters.  
 *  Properties must be set during object instantiation via constructor.
 */

class Body {
  private:
    std::string label;
    double x, y, z;
  public:
    // define a default constructor so we can make an array of Body objects:
    Body() { };     
    Body(std::string label, double x, double y, double z);
    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
    std::string getLabel() { return label; }
};

/*
 *  A BodyPair is a relationship between two Body objects, whose addresses are
 *  pointed to by pointers firstBody and secondBody.  BodyPairs are created for
 *  every possible pairing of Body objects in a BodyCollection, and allow us the
 *  convenience of mapping 2 Body objects to the distance between them, which
 *  is used by many of the BodyCollection methods.
 */

struct BodyPair {
  Body* firstBody;
  Body* secondBody;
  double distance;
};

/*
 *  A BodyCollection contains Body objects.  It contains methods to read Body
 *  Body objects from files and calculate statistics for them.  
 *
 *  BodyCollection stores an array of all possible BodyPairs, which lets us 
 *  avoid having to recalculate the distances between each Body object in order 
 *  to find the average distance, max distance, min distance, and when listing
 *  bodies and their relative distances.
 */

class BodyCollection {
  private:
    // store Body objects in an array:
    Body bodiesList[BODIES_COUNT_MAX];

    // store an array of all BodyPairs.
    BodyPair bodyPairsList[MAX_PAIRS];

    // keep count of how many BodyPairs exist:
    int bodyPairsListCount;
    
  public:
    // keep count of how many Body objects are contained in this BodyCollection
    int bodiesListCount;

    // default constructor:
    BodyCollection() { 
      bodiesListCount = 0;
      bodyPairsListCount = 0; 
    };

    // Given the name of an input file, open the file for reading and create
    // Body objects from it, and store those Body objects in this->bodiesList[].
    bool createBodiesFromFile(std::string inputFileName);

    /*
     *  The following methods require createBodiesFromFile to have already
     *  filled this->bodiesList[] with Body objects...
     */

    // For each possible pairing of Body objects, calculate the distance between
    // them and create a BodyPair object and store it in this->bodyPairsList[]
    void calculateDistances();

    /*
     *  The following methods require calculateDistances() to have filled
     *  this->bodyPairList[] with BodyPair objects...
     */

    // Return the BodyPair in this->bodyPairList[] with the lowest distance
    BodyPair getClosestBodies();

    // Return the BodyPair in this->bodyPairList[] with the greatest distance
    BodyPair getFurthestBodies();

    // Aggregate the distances of all BodyPairs and return the mean distance:
    double getAverageDistanceBetweenBodies();

    // Find the lowest and highest X, Y, and Z values for all Body objects in
    // order to return the volume of the smallest box that bounds them
    double getVolumeOfBoxBoundingBodies();

    // Given a label, find all BodyPairs in this->bodyPairsList[] that contain 
    // the body with that label.  Store pointers to the results in the 
    // provided array bodyPairsContainingBody[].  Keep count of how many results
    // there were in bodyPairsContainingBodyCount:
    void findBodyPairsWithBody(std::string label, BodyPair *bodyPairsContainingBody[], int &bodyPairsContainingBodyCount);

    // Write out stats file.  Return FILE_IO_SUCCESS if able to open file and
    // write successfully, otherwise FILE_IO_FAILED.
    bool outputStatsFile(std::string outputFileName);

    // Write out listings file.  Return FILE_IO_SUCCESS if able to open file and
    // write successfully, otherwise FILE_IO_FAILED.
    bool outputListingsFile(std::string outputFileName);
};

/*
 *  Helper Functions:
 */

// Given 2 Body objects, calculate the distance between them and return it
double getDistanceBetweenBodies(Body body1, Body body2);

// Given an array of pointers to BodyPair objects, sort the array by the 
// distance of each BodyPair 
void sortBodyPairsByDistance(BodyPair *bodyPairs[], int &bodyPairsCount);

// Given an array of BodyPair pointers, swap the pointer at indexA withe the
// pointer at indexB
void swapBodyPairs(BodyPair *bodyPairs[], int indexA, int indexB);

// Given an array of Strings, swap the string at indexA with the string at 
// indexB
void swapStrings(std::string strings[], int indexA, int indexB);

// Given an array of Strings, sort the array alphabetically.
void sortStringsAlpha(std::string strings[], int stringsCount);

#endif