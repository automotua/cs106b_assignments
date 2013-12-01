/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include "foreach.h"
using namespace std;

void findOneHopList(string & word, Vector<string> & oneHopList, Lexicon & lex);
bool isInLexicon(string word, Lexicon & lex);
void printLadder(Vector<string> & ladder);

int main() {
    Queue<Vector<string> > queue;
    string start, end;
    Vector<string> currentLadder;
    Lexicon lex("EnglishWords.dat");
    Lexicon used;

    cout << "Enter starting word: ";
    start = getLine();
    cout << "Enter ending word: ";
    end = getLine();
    
    used.add(start);
    
    currentLadder.add(start);
    queue.enqueue(currentLadder);
    
    while (!queue.isEmpty()) {
        currentLadder = queue.dequeue();
        string lastWordInLadder = currentLadder[currentLadder.size() - 1];
        if (lastWordInLadder == end) {
            printLadder(currentLadder);
            return 0;
        }
        
        Vector<string> oneHopList;
        findOneHopList(lastWordInLadder, oneHopList, lex);
        foreach(string word in oneHopList) {
            if (!isInLexicon(word, used)) {
                used.add(word);
                Vector<string> newLadder = currentLadder;
                newLadder.add(word);
                queue.enqueue(newLadder);
            }
        }
    }
    cout << "Your word \"" << start << "\" has no match in the lexicon." << endl;
    return 0;
}

void findOneHopList(string & word, Vector<string> & oneHopList, Lexicon & lex) {
    for (int i  = 0; i < word.length(); i++) {
        string subst = word;
        for (char letter = 'a'; letter <= 'z'; letter++) {
            if (letter != word[i]) {
                subst.replace(i, 1, string() + letter);
                if (isInLexicon(subst, lex)) oneHopList.add(subst);                
            }
        }
    }
}

bool isInLexicon(string word, Lexicon & lex) {
    if (lex.contains(word)) {
        return true;
    } else {
        return false;
    }
}

void printLadder(Vector<string> & ladder) {
    int count = 0;
    foreach(string word in ladder) {
        count++;
        if (count == ladder.size()) cout << word << endl;
        else cout << word << " -> ";
    }
}
