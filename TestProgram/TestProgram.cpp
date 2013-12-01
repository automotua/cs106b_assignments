/*
 * File: TestProgram.cpp
 * ----------------------
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"

#include "random.h"
#include "strlib.h"
#include "vector.h"

#include "foreach.h"
#include "simpio.h"
#include "hashmap.h"

using namespace std;

int main() {
    string word = "abc";
    cout << "word -> " << word << endl;;
    cout << "word + a char -> " << word + 'd' << endl;;
    string newWord = word + 'd';
    cout << "newWord -> " << newWord << endl;
	return 0;
}

