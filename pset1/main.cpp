/******************************************************************************
Title: Physics
Author: Gordon Zheng
Created on: 2014-10-08
Description: Reads position and mass data about 2 bodies from a file, data.txt
	in the current directory.  Calculates gravitational force and allows user to
	move bodies' positions.
Usage: ./physics
Build with: g++ main.cpp -o physics
Dependencies: none
******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

class Body {
	public:
		float mass, x, y;
		void moveTo(float, float);
		void setMass(float);
};

void Body::moveTo(float xNew, float yNew) {
	x = xNew;
	y = yNew;
}

void Body::setMass(float massNew) {
	mass = massNew;
}

bool readFile(int &seed, Body &body1, Body &body2);

int main() {
	int seed;
	Body body1, body2;

	// read in file; if error, complain and exit
	bool readSuccess = readFile(seed, body1, body2);
	if (!readSuccess) { 
		cerr << "ERROR: Could not read file 'data.txt'." << endl;
		return 1; 
	}

	// set seed to time if given seed is 0

	if (seed == 0) { seed = time(NULL); }
	srand(seed);

	cout << "seed " << seed << endl;

	cout << "body1" << body1.mass << body1.x << body1.y << endl;

	cout << "rand: " << rand() << endl; 

	return 0;
}

// read in file; extract seed, populate body1 and body2:
bool readFile(int &seed, Body &body1, Body &body2) {
	// read file into stream
	ifstream inputFile("data.txt");
	string line;			// buffer to store file line

	// if no stream, something went wrong opening file
	if (!inputFile) { return false; }

	// read in seed:
	getline(inputFile, line);
	istringstream buffer(line);
	if (!(buffer >> seed)) { return false; };

	float mass, x, y;

	// read in line 2 / body1:
	getline(inputFile, line);
	istringstream buffer1(line);
	if (!(buffer1 >> mass >> x >> y)) { return false; }

	body1.setMass(mass);
	body1.moveTo(x, y);

	// read in line 3 / body2:
	getline(inputFile, line);
	istringstream buffer2(line);
	if (!(buffer2 >> mass >> x >> y)) { return false; }

	body2.setMass(mass);
	body2.moveTo(x, y);
	
	return true;
}