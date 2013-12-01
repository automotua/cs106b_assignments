/* File: RandomShuffle.cpp
 *
 * A program that uses recursion to randomly scramble the contents of
 * a string.
 */
#include <iostream>
#include <string>
#include "random.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: randomShuffle(string input);
 * Usage: cout << randomShuffle("keith") << endl; // Might get htiek
 * =================================================================
 * Returns a random permutation of the given string.
 */
string randomShuffle(string input);

int main() {
	// TODO: Add your testing code here!
    string str = getLine("Enter your string: ");
    cout << "The shuffled result: " << randomShuffle(str);
	return 0;
}

string randomShuffle(string input) {
	// TODO: Implement this!
    if (input.empty()) {
        return "";
    }
    int randomIndex = randomInteger(0, input.size() - 1);
    char card = input[randomIndex];
    string next = input.substr(0, randomIndex) + input.substr(randomIndex + 1);
    return (card + randomShuffle(next));
}

