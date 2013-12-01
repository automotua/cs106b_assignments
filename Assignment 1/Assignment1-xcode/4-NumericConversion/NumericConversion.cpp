/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the numeric-conversion problem
 * in which you implement the functions intToString and stringToInt.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
   // [TODO: fill in the code]
    int n;
    string str;
    
    // int -> string
    cout << "Give me an integer, int -> string: ";
    cin >> n;
    str = intToString(n);
    cout << "int -> string: " << n << " -> " << str << endl;
    
    // string -> int
    cout << "Give me a string, string -> int: ";
    cin >> str;
    n = stringToInt(str);
    cout << "string -> int: " << str << " -> " << n << endl;
    
    return 0;
}


string intToString(int n) {
    char ch;
    int next;
    
    if (n == 0) {
        return (string() + '0');
    } else if (n < 0) {
        ch = '0' + (-1 * n) % 10;
        next = -1 * (n / 10);
    } else {
        ch = '0' + n % 10;
        next = n / 10;        
    }
    if (next == 0) {
        if (n < 0) {
            return (string() + "-" + ch);
        } else {
            return (string() + ch);
        }
    } else {
        return (string() + intToString(next) + ch);        
    }
}

//string intToString(int n) {
//    char ch;
//    int next;
//
//    if (n == 0) {
//        return (string() + '0');
//    } else if (n < 0) {
//        ch = '0' + (-1 * n) % 10;
//    } else {
//        ch = '0' + n % 10;
//    }
//    next = n / 10;
//    if (next == 0) {
//        if (n < 0) {
//            return (string() + "-" + ch);
//        } else {
//            return (string() + ch);
//        }
//    } else {
//        return (string() + intToString(next) + ch);        
//    }
//}

int stringToInt(string str) {
    string nextStr;
    int result, nextResult, currentDigit;
    currentDigit = str[str.length() - 1] - '0';
    if (str.length() == 1) {
        result = currentDigit;
    } else {
        nextStr = str.substr(0, str.length() - 1);
        if (nextStr == "-") {
            result = -1 * currentDigit;
        } else {
            nextResult = stringToInt(nextStr);
            if (nextResult < 0) {
                result = nextResult * 10 - currentDigit;        
            } else {
                result = nextResult * 10 + currentDigit;
            }
        }
    }
    return result;
}
