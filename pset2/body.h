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
  Body firstBody;
  Body secondBody;
  double distance;
};

class BodyCollection {
	public:
		Body bodiesList[BODIES_COUNT_MAX];
		int bodiesListCount;

		BodyCollection() {};
		bool createBodiesFromFile(std::string inputFileName);
		void getClosestBodies(Body* resultList[2]);
		void getFurthestBodies(Body* resultList[2]);
		double getAverageDistanceBetweenBodies();
		double getVolumeOfBoxBoundingBodies();
};

double getDistanceBetweenBodies(Body body1, Body body2);

#endif