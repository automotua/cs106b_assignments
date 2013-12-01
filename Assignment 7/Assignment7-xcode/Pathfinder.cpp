/*
 * File: Pathfinder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Pathfinder application
 * on Assignment #6.
 */
 
// [TODO: complete this implementation]

#include <iostream>
#include <string>
#include "console.h"
#include "graphtypes.h"
#include "gpathfinder.h"
using namespace std;

/* Function prototypes */

void quitAction();

/* Main program */

int main() {
   initPathfinderGraphics();
   addButton("Quit", quitAction);
   pathfinderEventLoop();
   return 0;
}

/* Sample callback function */

void quitAction() {
   exit(0);
}
