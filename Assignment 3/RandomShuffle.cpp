/* File: RandomShuffle.cpp
 *
 * A solution to the Random Shuffle warmup problem for Assignment 3.
 */
#include <iostream>
#include <string>
#include "random.h"
#include "simpio.h"
using namespace std;

/* Function to randomly shuffle a string. */
string randomShuffle(string input);

int main() {
	string input = getLine("Enter a string to shuffle: ");
	cout << randomShuffle(input) << endl;
}

/* Randomly shuffles a string using the power of recursion!
 *
 * Base Case: If the string is empty, there is exactly one way to shuffle it,
 *            namely, to just hand back the empty string.
 * Recursive Case: Otherwise, pick a random character from the string, shuffle
 *            the rest of the string, then add that character back to the front.
 */
string randomShuffle(string input) {
	/* Base case: The empty string is its own shuffle. */
	if (input == "") {
		return input;
	}
	/* Recursive step: Pull off a character and shuffle what remains. */
	else {
		int i = randomInteger(0, input.length() - 1);
		return input[i] + randomShuffle(input.substr(0, i) + input.substr(i + 1));
	}
}

