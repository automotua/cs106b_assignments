/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * [TODO: extend the documentation]
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

void openFile(ifstream & inf);
void findMostCommonSeed(string & seed, HashMap<string, Vector<char> > & mp);
void outputMarkovText(string seed, HashMap<string, Vector<char> > & mp);


int main() {
    ifstream inf;
    openFile(inf);

    cout << "Enter the order of Markov model to use (from 1 to 10): ";
    int order = getInteger();
    
    
    Vector<char> charList(order);
    for (int i = 0; i < charList.size(); i++) {
        charList[i] = inf.get();
    }
    
    int ch;
    string seed;
    HashMap<string, Vector<char> > mp;

    while ((ch = inf.get()) != EOF) {
        foreach(char ele in charList) {
            seed += ele;
        }
        mp[seed].add(char (ch));
        
        int i;
        for (i = 1; i < charList.size(); i++) {
            charList[i - 1] = charList[i];
        }
        charList[i - 1] = char (ch);
        seed = "";
    }
    
    findMostCommonSeed(seed, mp);
    outputMarkovText(seed, mp);
    
	return 0;
}

void openFile(ifstream & inf) {
	while (true) {
		cout << "Enter file name: ";
		string filename = getLine();
		inf.open(filename.c_str());
		if (!inf.fail()) break;
		cout << "Couldn't open the file, try again!" << endl;
		inf.clear();
	}
}

void findMostCommonSeed(string & seed, HashMap<string, Vector<char> > & mp) {
    int max = 0;
    foreach(string ele in mp) {
        if (mp[ele].size() > max) {
            max = mp[ele].size();
            seed = ele;
        }
    }
}

void outputMarkovText(string seed, HashMap<string, Vector<char> > & mp) {
    cout << seed;
    for (int i = 0; i < 2000; i++) {
        if (!mp.containsKey(seed)) break;
        int random = randomInteger(0, mp[seed].size() - 1);
        char ch = mp[seed][random];
        cout << ch;
        seed.erase(0, 1);
        seed += ch;
    }
}

//foreach(seed in mp) {
//    cout << seed << ": ";
//    foreach(char ele in mp[seed]) {
//        cout << ele << " ";
//    }
//    cout << endl;
//}

