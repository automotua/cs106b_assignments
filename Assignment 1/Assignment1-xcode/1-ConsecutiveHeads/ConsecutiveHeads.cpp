/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the coin-flipping problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "random.h"
using namespace std;

int main() {
    int headsCounter = 0;
    int flipCounter = 0;
    while (headsCounter < 3) {
        if (randomChance(0.5) == true) {
            cout << "heads" << endl;
            headsCounter++;
        } else {
            cout << "tails" << endl;
            headsCounter = 0;
        }
        flipCounter++;
    }
    cout << "It took " << flipCounter << " flips to get " << headsCounter <<
    " consecutive heads." << endl;
    return 0;
}
