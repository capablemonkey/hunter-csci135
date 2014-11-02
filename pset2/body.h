// include guards
#ifndef BODY_H		
#define BODY_H

#import <iostream>
#import <string>
#import <fstream>
#import <cmath>
#import <iomanip>

const bool FILE_IO_FAILED = true;
const bool FILE_IO_SUCCESS = false;

const int BODIES_COUNT_MAX = 36;
const int BODIES_COUNT_MIN = 3;
const int MAX_PAIRS = 666;			// (n^2 + n) / 2, where n = BODIES_COUNT_MAX - 1

class Body {
  private:
    std::string label;
    double x, y, z;
  public:
  	Body() { }; 		// default constructor
    Body(std::string label, double x, double y, double z);
    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
    std::string getLabel() { return label; }
};

struct BodyPair {
  Body* firstBody;
  Body* secondBody;
  double distance;
};

class BodyCollection {
	private:
		Body bodiesList[BODIES_COUNT_MAX];
		BodyPair bodyPairsList[MAX_PAIRS];
		int bodyPairsListCount;
	public:
		int bodiesListCount;

		BodyCollection() { bodyPairsListCount = 0; };

		bool createBodiesFromFile(std::string inputFileName);
		void calculateDistances();
		BodyPair getClosestBodies();
		BodyPair getFurthestBodies();
		double getAverageDistanceBetweenBodies();
		double getVolumeOfBoxBoundingBodies();
		void findBodyPairsWithBody(std::string label, BodyPair *bodyPairsContainingBody[], int &bodyPairsContainingBodyCount);

		bool outputStatsFile(std::string outputFileName);
		bool outputListingsFile(std::string outputFileName);
};

// Helper functions:

double getDistanceBetweenBodies(Body body1, Body body2);

void sortBodyPairsByDistance(BodyPair *bodyPairs[], int &bodyPairsCount);
void swapBodyPairs(BodyPair *bodyPairs[], int indexA, int indexB);

void swapStrings(std::string strings[], int indexA, int indexB);
void sortStringsAlpha(std::string strings[], int stringsCount);

#endif