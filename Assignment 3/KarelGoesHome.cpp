/* File: KarelGoesHome.cpp
 *
 * A solution to the Karel Goes Home warmup problem for Assignment 3.
 */
#include <iostream>
#include "simpio.h"
using namespace std;

/* Function to compute the number of paths back home. */
int numPathsHome(int street, int avenue);

int main() {
	int street = getInteger("Enter the street number: ");
	int avenue = getInteger("Enter the avenue number: ");
	
	cout << "Number of paths back: " << numPathsHome(street, avenue) << endl;
}

/* Solves the Karel Goes Home problem.  The recursive structure is as follows:
 *
 * Base Case 1: If Karel is at an invalid index, then there are no paths
 *              back home.
 *
 * Base Case 2: If Karel is at (1, 1), then there is exactly one path back:
 *              just stay where you are!
 *
 * Recursive Step: Every journey begins with a single step, as they say (it's
 *              not quite clear who "they" are, though).  Every path Karel can
 *              take either starts with a step left or a step down.  If we count
 *              how many paths there are having taken those first steps, we will
 *              have found the total number of paths back.
 */
int numPathsHome(int street, int avenue) {
	/* Base case 1: If we're not on the map, there's no way back. */
	if (street < 1 || avenue < 1) {
		return 0;
	}
	/* Base case 2: If we're home, there's exactly one path back. */
	else if (street == 1 && avenue == 1) {
		return 1;
	}
	/* Recursive step: Take a step in each direction and sum up the 
	 * number of paths.
	 */
	else {
		return numPathsHome(street - 1, avenue) + numPathsHome(street, avenue - 1);
	}
}

