// include guards
#ifndef BODY_H		
#define BODY_H

#import <iostream>
#import <string>
#import <fstream>
#import <cmath>

const bool READ_BODIES_FAILED = true;
const bool READ_BODIES_SUCCESS = false;

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

		BodyCollection() {
			bodyPairsListCount = 0;
		};

		bool createBodiesFromFile(std::string inputFileName);
		void calculateDistances();
		BodyPair getClosestBodies();
		BodyPair getFurthestBodies();
		double getAverageDistanceBetweenBodies();
		double getVolumeOfBoxBoundingBodies();
};

double getDistanceBetweenBodies(Body body1, Body body2);

#endif