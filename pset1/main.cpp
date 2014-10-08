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

const float GRAVITATIONAL_CONSTANT = 6.673e-11;

class Body {
	public:
		float mass, x, y;
		void moveTo(float, float);
		void setMass(float);
		float distanceFromBody(Body);
		float gravitationalForceBetweenBody(Body);
};

void Body::moveTo(float xNew, float yNew) {
	x = xNew;
	y = yNew;
}

void Body::setMass(float massNew) {
	mass = massNew;
}

float Body::distanceFromBody(Body body2) {
	return sqrt(pow((body2.x - x), 2) + pow((body2.y - y), 2));
}

float Body::gravitationalForceBetweenBody(Body body2) {
	return ((GRAVITATIONAL_CONSTANT * mass * body2.mass) / pow(this->distanceFromBody(body2), 2));
}

bool readFile(int &seed, Body &body1, Body &body2);
int getMenuChoice(void);
void displayBodies(Body body1, Body body2);
void displayGravitationalForce(Body body1, Body body2);
void displayDistanceBetweenBodies(Body body1, Body body2);

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
	
	// show menu:
	int choice = getMenuChoice();
	while (choice != 7) {
		// show mass and position of bodies:
		displayBodies(body1, body2);

		switch (choice) {
			case 1:
				displayGravitationalForce(body1, body2);
				break;

			case 2:
				displayDistanceBetweenBodies(body1, body2);
				break;

			default: 
				cout << "Invalid choice.  Try again." << endl;
		}

		// ask for another choice:
		choice = getMenuChoice();
	}
	return 0;
}

void displayBodies(Body body1, Body body2) {
	// TODO: add a method to Body which prints itself, so we can do Body.print();

	cout << endl
		<< "Body #1: " << body1.mass << " kg @ (" << body1.x << ", " << body1.y << ")" << endl
		<< "Body #2: " << body2.mass << " kg @ (" << body2.x << ", " << body2.y << ")" << endl
		<< endl;

	return;
} 

void displayGravitationalForce(Body body1, Body body2) {
	// configure floats to be formatted to 5 dec places:
	cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
	cout.precision(5);

	float gravitationalForce;

	cout 	<< "Gravitational Force between bodies: " 
				<< body1.gravitationalForceBetweenBody(body2) << " Newtons" << endl;
}

void displayDistanceBetweenBodies(Body body1, Body body2) {
	// configure floats to be formatted to 5 dec places:
	cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
	cout.precision(5);

	cout << "Distance between bodies: " << body1.distanceFromBody(body2) << " Meters" << endl;
}

// display menu to user; return choice
int getMenuChoice(void) {
	int choice;

	cout << endl << "============== Menu ==============" << endl
		<< "1 Calculate the gravitational attractive force between the two bodies" << endl
		<< "2 Calculate the distance between the two bodies" << endl
		<< "3 Move body #1 a random distance and direction" << endl
		<< "4 Move body #2 a random distance and direction" << endl
		<< "5 Move body #1 a user defined distance and direction" << endl
		<< "6 Move body #2 a user defined distance and direction" << endl
		<< "7 Exit the program" << endl
		<< "Choice: ";

	cin >> choice;

	return choice;
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