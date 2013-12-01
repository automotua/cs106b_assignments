/*
 * File: Obenglobish.java
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Obenglobish problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Main program */
string obenglobish(string word);
bool isVowel(char ch);
bool isFollowingVowel(string word, int i);
bool isWordEnd(string word, int i);

int main() {
    while (true) {
        string word = getLine("Enter a word: ");
        if (word == "") break;
        string trans = obenglobish(word);
        cout << word << " -> " << trans << endl;
    }
    return 0; 
}

string obenglobish(string word) {
    string result;
    for (int i = 0; i < word.length(); i++) {
        if (isVowel(word[i]) && !isFollowingVowel(word, i) && !isWordEnd(word, i)) {
            result = result + "ob" + word[i];
        } else {
            result += word[i];
        }
    }
    return result;
}

bool isFollowingVowel(string word, int i) {
    if (i == 0) return false;
    if (isVowel(word[i - 1])) {
        return true;
    } else {
        return false;
    }
}

bool isWordEnd(string word, int i) {
    return (i == word.length() - 1);
}

bool isVowel(char ch) {
    switch (ch) {
        case 'a': 
        case 'e': 
        case 'i': 
        case 'o': 
        case 'u': 
            return true;
        default:
            return false;
    }
}

