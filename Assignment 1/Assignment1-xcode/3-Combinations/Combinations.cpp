/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the recursive combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

int combination(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    }
    int result;
    result = combination(n - 1, k - 1) + combination(n - 1, k);
    return result;
}






int main() {
   // [TODO: fill in the code]
    
    int n, k, result;
    n = getInteger("Give me the \"n\": ");
    k = getInteger("Give me the \"k\": ");
    if (n < k) {
        cout << "Sorry, your n is less than your k." << endl;
    } else {
        result = combination(n, k);
        cout << "The result of your combination is " << result << endl;
        return 0;        
    }
}
