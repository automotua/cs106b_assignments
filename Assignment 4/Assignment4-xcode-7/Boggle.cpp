/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */
 
#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include <math.h>
#include "strlib.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const int STANDARD_CUBES_SIZE = 4;
const int BIG_BOGGLE_CUBES_SIZE = 5;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Point structure */
struct pointT {
    int row;
    int col;
    char value;
    bool marked;
};


/* Function prototypes */

void welcome();

void giveInstructions();

// Set up board config
void setupBoardConfig(Vector<string> & vecCubes);
void copyVeccubesToBoard(Vector<string> & vecCubes, Grid<pointT> & board);
void drawBlankBoard();
bool isForcedConf();
void setUpForcedConf(Vector<string> & vecCubes);
void setUpPreConf(Vector<string> & vecCubes);
void copyToVector(Vector<string> & vecCubes, string str = "", int cubesArrSize = STANDARD_CUBES_SIZE * STANDARD_CUBES_SIZE);
void displayConf(Vector<string> & vecCubes);
void shuffle(Vector<string> & vecCubes);

// Human plays the game
void humanPlayGame(Grid<pointT> & board, Set<string> & wordList);
bool isValidWord(string word, Set<string> & wordList);
bool isValidLength(string word);
bool isContainedInLexicon(string word);
bool isGuessedBefore(string word, Set<string> & wordList);
bool isFormedOnBoard(string word, Set<string> & wordList, Grid<pointT> & board, Vector<pointT> & ptList);
bool isRecFormedOnBoard(string word, Grid<pointT> & board, pointT pt, Vector<pointT> & ptList);
void markSquare(pointT & pt);
void unMarkSquare(pointT & pt);
bool isValidPosition(int currentRow, int currentCol, Grid<pointT> & board);
bool isOutOfBound(int currentRow, int currentCol, Grid<pointT> & board);
bool isMarked(pointT pt);
void processWord(string word, Set<string> & wordList);
void displayWord(string word, Vector<pointT> & ptList, Player player);
void highlightWord(Vector<pointT> & ptList);
void unHighlightWord(Vector<pointT> & ptList);

// Computer plays the game
void computerPlayGame(Grid<pointT> & board, Set<string> & humanWordList);
void findAllWords(Grid<pointT> & board, Set<string> & wordList);
void recFindAllWords(pointT & pt, string word, Grid<pointT> & board, Set<string> & wordList);
bool isPrefixContainedInLexicon(string word);

// isGameOver()
bool isGameOver() {
    while (true) {
        string str = toLowerCase(getLine("Do you want to play again? "));
        if (str[0] == 'y') {
            return false;
        } else if (str[0] == 'n') {
            return true;
        } else {
            cout << "Please answer yes or no." << endl;
        }
    }
}

/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    
    welcome();
    giveInstructions();
    
    while (true) {
        initGBoggle(gw);
        Vector<string> vecCubes;
        Grid<pointT> board(STANDARD_CUBES_SIZE, STANDARD_CUBES_SIZE);
        Set<string> humanWordList;
        setupBoardConfig(vecCubes);
        copyVeccubesToBoard(vecCubes, board);
        humanPlayGame(board, humanWordList);
        computerPlayGame(board, humanWordList);
        if (isGameOver()) {
            break;
        }
    }
    
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

// [TODO: Fill in the rest of the code]

/*
 * Set up board configuration
 */
void setupBoardConfig(Vector<string> & vecCubes) {
    drawBlankBoard();
    if (isForcedConf()) {
        setUpForcedConf(vecCubes);
    } else {
        setUpPreConf(vecCubes);
    }
}

void drawBlankBoard() {
    int boardSize = STANDARD_CUBES_SIZE;
    drawBoard(boardSize, boardSize);
}

bool isForcedConf() {
    cout << "I'll give you a chance to set up the board to your specification, ";
    cout << "which makes it easier to confirm your boggle program is working." << endl;
    while (true) {
        string answer = toLowerCase(getLine("Do you want to force the board configuration? "));
        if (answer[0] == 'y') {
            return true; 
        } else if (answer[0] == 'n') {
            return false;
        } else {
            cout << "Please answer yes or no." << endl;
        }
    }
}

void setUpForcedConf(Vector<string> & vecCubes) {
    cout << "Enter a 16-character string to identify which letters you want on the cubes." << endl;
    cout << "The first 4 letters are the cubes on the top row from left to right, the next 4 letters are the second row, and so on." << endl;
    string str = toUpperCase(getLine("Enter the string: "));
    while (true) {
        if (str.size() >= 16) {
            str.erase(16);
            break;
        }
        str = toUpperCase(getLine("String must include 16 characters! Try again: "));
    }
    copyToVector(vecCubes, str);
    displayConf(vecCubes);
    return;
}

void copyToVector(Vector<string> & vecCubes, string str, int cubesArrSize) {
    if (str == "") {
        for (int i = 0; i < cubesArrSize; i++) {
            vecCubes.add(STANDARD_CUBES[i]);
        }
    } else {
        for (int i = 0; i < str.size(); i++) {
            vecCubes.add(str.substr(i, 1));
        }
    }
}

void displayConf(Vector<string> & vecCubes) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++, count++) {
            labelCube(i, j, vecCubes[count][0]); 
        }
    }
}

void setUpPreConf(Vector<string> & vecCubes) {
    copyToVector(vecCubes);
    shuffle(vecCubes);
    displayConf(vecCubes);
}

void shuffle(Vector<string> & vecCubes) {
    // Shuffle all cubes
    // Choose a random index r between i and the last element position, inclusive. Swap the element at positions i and r.
    for (int i = 0; i < vecCubes.size(); i++) {
        int r = randomInteger(i, vecCubes.size() - 1);
        swap(vecCubes[i], vecCubes[r]);
    }
    
    // Shuffle each individual cube
    // Put a random face of the cube to vecCubes[0] for display.
    for (int i = 0; i < vecCubes.size(); i++) {
        int r = randomInteger(0, vecCubes[0].size() - 1);
        swap(vecCubes[i][0], vecCubes[i][r]);
    }
    
}

/*
 * Copy vecCubes to board (with case lowered), and init board's marked field to false
 */
void copyVeccubesToBoard(Vector<string> & vecCubes, Grid<pointT> & board) {
    int count = 0;
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++, count++) {
            board[i][j].value = (char) tolower(vecCubes[count][0]);
            board[i][j].row = i;
            board[i][j].col = j;
            board[i][j].marked = false;
        }
    }
}


/*
 * Human plays the game
 */
void humanPlayGame(Grid<pointT> & board, Set<string> & wordList) {
    cout << endl << endl;
    cout << "Ok, take all the time you want and find all the words you can!";
    cout << "Signal that you're finished by entering an empty line.";
    cout << endl << endl;
    
    while (true) {
        Vector<pointT> ptList;
        string word = toLowerCase(getLine("Enter a word: "));
        if (word.empty()) {
            break;
        }
        if (isValidWord(word, wordList) &&
                isFormedOnBoard(word, wordList, board, ptList)) {
            processWord(word, wordList);
            displayWord(word, ptList, HUMAN);
        }
    }
}

bool isValidWord(string word, Set<string> & wordList) {
    if (!isValidLength(word)) {
        cout << "I'm sorry, but we have our standards." << endl;
        cout << "That word doesn't meet the minimum word length." << endl;
        return false;
    } else if (!isContainedInLexicon(word)) {
        cout << "That's not a word!" << endl;
        return false;
    } else if (isGuessedBefore(word, wordList)) {
        cout << "You've already guessed that!" << endl;
        return false;
    } else {
        return true;
    }
}

bool isValidLength(string word) {
    if (word.size() < 4) {
        return false;
    } else {
        return true;
    }
}

bool isContainedInLexicon(string word) {
    Lexicon lex("EnglishWords.dat");
    if (lex.containsPrefix(word) && lex.contains(word)) {
        return true;
    } else {
        return false;
    }
}

bool isGuessedBefore(string word, Set<string> & wordList) {
    if (wordList.contains(word)) {
        return true;
    } else {
        return false;
    }
}

bool isFormedOnBoard(string word, Set<string> & wordList, Grid<pointT> & board, Vector<pointT> & ptList) {
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            if (board[i][j].value == word[0]) {
                markSquare(board[i][j]);
                bool ok = isRecFormedOnBoard(word.substr(1), board, board[i][j], ptList);
                unMarkSquare(board[i][j]);
                if (ok) {
                    wordList.add(word);
                    return true;                    
                }
            }
        }
    }
    cout << "You can't make that word from the board." << endl;
    return false;
}

bool isRecFormedOnBoard(string word, Grid<pointT> & board, pointT pt, Vector<pointT> & ptList) {
    ptList.add(pt);
    if (word.empty()) {
        return true;
    }
        
    for (int i = pt.row - 1; i <= pt.row + 1; i++) {
        for (int j = pt.col - 1; j <= pt.col + 1; j++) {
                if (isValidPosition(i, j, board) && board[i][j].value == word[0]) {
                    markSquare(board[i][j]);
                    bool ok = isRecFormedOnBoard(word.substr(1), board, board[i][j], ptList);
                    unMarkSquare(board[i][j]);
                    if (ok) {
                        return true;
                    }
                }
        }
    }
    ptList.remove(ptList.size() - 1);
    return false;
}

void markSquare(pointT & pt) {
    pt.marked = true;
}

void unMarkSquare(pointT & pt) {
    pt.marked = false;
}

bool isValidPosition(int currentRow, int currentCol, Grid<pointT> & board) {
    return !isOutOfBound(currentRow, currentCol, board) && !isMarked(board[currentRow][currentCol]);
}

bool isOutOfBound(int currentRow, int currentCol, Grid<pointT> & board) {
    return (currentRow < 0) ||
           (currentRow >= board.numRows()) ||
           (currentCol < 0) ||
           (currentCol >= board.numCols());
}

bool isMarked(pointT pt) {
    return (pt.marked == true);
}


void processWord(string word, Set<string> & wordList) {
    wordList.add(word);
}

void displayWord(string word, Vector<pointT> & ptList, Player player) {
    highlightWord(ptList);
    recordWordForPlayer(word, player);
    unHighlightWord(ptList);
}

void highlightWord(Vector<pointT> & ptList) {
    foreach(pointT pt in ptList) {
        highlightCube(pt.row, pt.col, true);
        pause(100);
    }
}

void unHighlightWord(Vector<pointT> & ptList) {
    foreach(pointT pt in ptList) {
        highlightCube(pt.row, pt.col, false);
        pause(100);
    }
}

/* 
 * Computer plays the game 
 */
void computerPlayGame(Grid<pointT> & board, Set<string> & humanWordList) {
    Set<string> computerWordList;
    findAllWords(board, computerWordList);
    computerWordList -= humanWordList;
    foreach(string word in computerWordList) {
        recordWordForPlayer(word, COMPUTER);
    }
    return;
}

void findAllWords(Grid<pointT> & board, Set<string> & wordList) {
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            recFindAllWords(board[i][j], string() + board[i][j].value, board, wordList);
        }
    }
}

void recFindAllWords(pointT & pt, string word, Grid<pointT> & board, Set<string> & wordList) {
    if (!isPrefixContainedInLexicon(word)) {
        return;
    }
    
    markSquare(pt);
    
    if (isValidLength(word) && 
        isContainedInLexicon(word) && 
        !isGuessedBefore(word, wordList)) {
        processWord(word, wordList);
    }

    for (int i = pt.row - 1; i <= pt.row + 1; i++) {
        for (int j = pt.col - 1; j <= pt.col + 1; j++) {
            if (isValidPosition(i, j, board)) {
                recFindAllWords(board[i][j], word + board[i][j].value, board, wordList);
            }
        }
    }
    unMarkSquare(pt);
}

bool isPrefixContainedInLexicon(string word) {
    Lexicon lex("EnglishWords.dat");
    if (lex.containsPrefix(word)) {
        return true;
    } else {
        return false;
    }
}