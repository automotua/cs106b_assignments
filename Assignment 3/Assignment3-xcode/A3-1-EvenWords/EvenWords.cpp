/* File: EvenWords.cpp
 *
 * A program that uses recursion to determine which words are
 * even words.
 */
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: isEvenWord(string input);
 * Usage: if (isEvenWord("tattletale")) { ... }
 * ==================================================================
 * Returns whether the given word is an "even word;" that is, whether
 * every letter in the word appears an even number of times.
 */
bool isEvenWord(string word); 

int main() {
	// TODO: Add your testing code here!
    string word = getLine("Enter word: ");
    cout << "Your word is " << (isEvenWord(word) ? "" : "not ") << "an even word." << endl;
	return 0;
}

bool isEvenWord(string word) {
	// TODO: Implement this!
    if (word.empty()) {
        return true;
    }
    char first = word[0];
    int pos = word.find(first, 1);
    if (pos == string::npos) {
        return false;
    } else {
        string next = word.substr(1, pos - 1) + word.substr(pos + 1);
        return isEvenWord(next);
    }
}

