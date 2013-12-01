/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
#include "simpio.h"
#include <fstream>
#include "tokenscanner.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);

void tryOneLocation(Set<string> & location, Vector< Set<string> > & result);

bool areAllCitiesCovered(Set<string> & cities, Vector< Set<string> > & result);


int main() {
    /* TODO: Add testing code here! */
    Set<string> cities;
    Vector< Set<string> > locations;
    int numHospitals = 8;
    Vector< Set<string> > result;
    
    ifstream input("cities.txt");
    string city;
	
	while (input >> city) {
		cities.add(city);
	}
	
    input.close();
    input.open("locations.txt");
    
    while (true) {
        string cityList;
        getline(input, cityList);
        if (input.fail()) {
            break;
        }
        TokenScanner scanner(cityList);
        scanner.ignoreWhitespace();
        Set<string> location;
        while (scanner.hasMoreTokens()) {
            string city = scanner.nextToken();
            location.add(city);
        }
        locations.add(location);
    }

//    cout << "All cities: " << endl;
//    foreach(string city in cities) {
//        cout << city << endl;
//    }
//    
//    cout << "The locations list: " << endl;
//    foreach(Set<string> s in locations) {
//        foreach(string str in s) {
//            cout << str;
//        }
//        cout << endl;
//    }
    
    if (canOfferUniversalCoverage(cities, locations, numHospitals, result)) {
        cout << "Congrats! All cities can be covered. The result is: " << endl;
        foreach(Set<string> s in result) {
            cout << "Location: ";
            foreach(string str in s) {
                cout << str << " ";
            }
            cout << endl;
        }
    } else {
        cout << "The locations provided cannot cover all cities." << endl;
    }
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

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result) {
    if (areAllCitiesCovered(cities, result) && numHospitals >= 0) {
        return true;
    }
    for (int i = 0; i < numHospitals; i++) {
        Set<string> location = locations.get(i);
        tryOneLocation(location, result);
        locations.remove(i);
        bool ok = canOfferUniversalCoverage(cities, locations, numHospitals - 1, result);
        if (ok) {
            return true;
        } else {
            locations.insert(i, location);
            result.remove(result.size() - 1);
        }
    }
    return false;
}

void tryOneLocation(Set<string> & location, Vector< Set<string> > & result) {
    result.add(location);
}

bool areAllCitiesCovered(Set<string> & cities, Vector< Set<string> > & result) {
    Set<string> tempCities;
    foreach(Set<string> citiesSet in result) {
        tempCities += citiesSet;
    }
    if (tempCities == cities) {
        return true;
    } else {
        return false;
    }
}


// What I found:
// 2 cases for end state:
// 1. don't use the full "numHospitals", but covered all cities already
// 2. use the full "numHospitals", covered / not covered all cities
// Therefore, for each recursion step, we need to see 
//      a) whether all cities have already been covered
//      b) whether numHospitals have been used up
//            b.1) then see if (all cities have been covered)