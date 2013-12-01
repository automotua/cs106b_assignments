/*
 * File: KarelGoesHome.cpp
 * -----------------------
 * Starter file for the KarelGoesHome problem.
 */

#include <iostream>
#include <iomanip>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */

int countPaths(int street, int avenue);

/* Main program */

int main() {
   // [Fill this in with a test program]
    int street = getInteger("Enter initial street value: ");
    int avenue = getInteger("Enter initial avenue value: ");
    int count = countPaths(street, avenue);
    cout << "The total no. of paths is: " << count << endl;
    return 0;
}

/*
 * Function: countPaths
 * Usage: int nPaths = countPaths(street, avenue);
 * -----------------------------------------------
 * Counts the paths from a particular street/avenue position in
 * Karel's world to the origin, subject to the restriction that
 * Karel can move only west and south.
 */

int countPaths(int street, int avenue) {
    if (street == 1 || avenue == 1) {       // The origin in the problem description is (1,1)
        return 1;
    }
    return countPaths(street - 1, avenue) + countPaths(street, avenue - 1);
}
