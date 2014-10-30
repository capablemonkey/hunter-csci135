// include guards
#ifndef BODY_H		
#define BODY_H

#import <iostream>
#import <string>
#import <fstream>
#import <cmath>

const bool READ_BODIES_FAILED = true;
const bool READ_BODIES_SUCCESS = false;

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

bool createBodiesFromFile(std::string inputFileName, Body bodiesList[], int &bodiesListCount);

double getDistanceBetweenBodies(Body body1, Body body2);

void getClosestBodies(Body bodiesList[], Body resultList[]);

#endif