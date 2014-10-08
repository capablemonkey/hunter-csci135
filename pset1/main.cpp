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
    int id;
    float mass, x, y;

    Body(int);
    void printMassAndPosition(void);
    void setPosition(float, float);
    void setMass(float);

    void moveRandom();
    void moveByPromptingUser();
    void moveByDistanceAndDirection(float, int);
    
    float distanceFromBody(Body);
    float gravitationalForceBetweenBody(Body);
};

// Constants:
const float GRAVITATIONAL_CONSTANT = 6.673e-11;
const float DISTANCE_MAX = 1000.00;
const float DISTANCE_MIN = 10.00;
const int DIRECTION_MAX = 359;
const int DIRECTION_MIN = 0;

// Function prototypes:
bool readFile(int &seed, Body &body1, Body &body2);
int getMenuChoice(void);
void displayBodies(Body body1, Body body2);
void displayGravitationalForce(Body body1, Body body2);
void displayDistanceBetweenBodies(Body body1, Body body2);

int main() {
  int seed;
  Body body1(1);
  Body body2(2);

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

      case 3:
        body1.moveRandom();
        break;

      case 4:
        body2.moveRandom();
        break;

      case 5:
        body1.moveByPromptingUser();
        break;

      case 6:
        body2.moveByPromptingUser();
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
  cout << endl;
  body1.printMassAndPosition();
  body2.printMassAndPosition();
  cout << endl;

  return;
} 

void displayGravitationalForce(Body body1, Body body2) {
  // configure floats to be formatted to 5 dec places:
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(5);

  float gravitationalForce;

  cout  << "Gravitational Force between bodies: " 
        << body1.gravitationalForceBetweenBody(body2) << " Newtons" << endl;

  return;
}

void displayDistanceBetweenBodies(Body body1, Body body2) {
  // configure floats to be formatted to 5 dec places:
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(5);

  cout << "Distance between bodies: " 
       << body1.distanceFromBody(body2) << " Meters" << endl;
  return;
}

// display menu to user; return choice
int getMenuChoice(void) {
  int choice;

  cout << endl << "============== Menu ==============" << endl
    << "1 Calculate the gravitational attractive force between the two bodies" 
    << endl
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
  string line;      // buffer to store file line

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
  body1.setPosition(x, y);

  // read in line 3 / body2:
  getline(inputFile, line);
  istringstream buffer2(line);
  if (!(buffer2 >> mass >> x >> y)) { return false; }

  body2.setMass(mass);
  body2.setPosition(x, y);
  
  return true;
}

// Body class methods:

// constructor just takes a body number
Body::Body(int idNew) {
  id = idNew;
  return;
}

void Body::setPosition(float xNew, float yNew) {
  x = xNew;
  y = yNew;
  return;
}

void Body::setMass(float massNew) {
  mass = massNew;
  return;
}

float Body::distanceFromBody(Body body2) {
  return sqrt(pow((body2.x - x), 2) + pow((body2.y - y), 2));
}

// calculate gravitational force between this body and another
float Body::gravitationalForceBetweenBody(Body body2) {
  return ((GRAVITATIONAL_CONSTANT * mass * body2.mass) 
    / pow(this->distanceFromBody(body2), 2));
}

void Body::printMassAndPosition() {
  cout  << "Body #" << id << ": " 
        << mass << " kg @ (" << x << ", " << y << ")" << endl;
  return;
}

void Body::moveByDistanceAndDirection(float distance, int direction) {
  x = x + distance * cos(direction);
  y = y + distance * sin(direction);
  return;
}

// move body random distance and direction
void Body::moveRandom() {
  float randomDistance = float(rand() * 1.0 / RAND_MAX) * (
    DISTANCE_MAX - DISTANCE_MIN) + DISTANCE_MIN;
  int randomDirection = float(rand() * 1.0 / RAND_MAX) * (
    DIRECTION_MAX - DIRECTION_MIN) + DIRECTION_MIN;

  cout  << endl << "Moving Body #" << id 
        << " " << randomDistance << " meters in direction " 
        << randomDirection << " degrees" << endl;
  
  this->moveByDistanceAndDirection(randomDistance, randomDirection);

  cout  << "Updated position for Body #" << id 
        << ": (" << x << ", " << y << ")" << endl;

  return;
}

// Move by user-inputted direction and distance
void Body::moveByPromptingUser() {
  float distance;
  int direction;
  bool validDistance = false;
  bool validDirection = false;

  // prompt user for distance:
  while (!validDistance) {
    cout << "Move body #" << id << " by this distance (meters): ";
    cin >> distance;

    if (!(distance >= DISTANCE_MIN && distance <= DISTANCE_MAX)) { 
      cout  << "Distance must be between " << DISTANCE_MIN 
            << " and " << DISTANCE_MAX << ".  Try again." << endl;
    } else { 
      validDistance = true; 
    }
  }

  // prompt user for direction:
  while (!validDirection) {
    cout << "Move body #" << id << " in this direction (degrees): ";
    cin >> direction;

    if (!(direction >= DIRECTION_MIN && direction <= DIRECTION_MAX)) { 
      cout  << "Direction must be between " << DIRECTION_MIN 
            << " and " << DIRECTION_MAX << ".  Try again." << endl;
    } else {
      validDirection = true;
    }
  }

  cout  << endl << "Moving Body #" << id 
        << " " << distance << " meters in direction " 
        << direction << " degrees" << endl;
  
  this->moveByDistanceAndDirection(distance, direction);

  cout  << "Updated position for Body #" << id 
        << ": (" << x << ", " << y << ")" << endl;

  return;
}