/*
 * File: SierpinskiTriangle.cpp
 * ----------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter code for the Sierpinski Triangle problem
 * fron Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "graphics.h"
#include "simpio.h"
#include <math.h>
#include "gtypes.h"
using namespace std;

const 

void AskForInput(int & edgeLength, int & order) {
    edgeLength = getInteger("What is the edge length? ");
    order = getInteger("What is the order? ");
}

void DrawTriangle(double x, double y, double w, double h) {
    GPoint pt(x, y);
    pt = drawPolarLine(pt, w, 0);
    pt = drawPolarLine(pt, w, 120);
    pt = drawPolarLine(pt, w, -120);
}

void DrawFractal(double x, double y, double w, double h, int order) {
    DrawTriangle(x, y, w, h);
    
    if (order == 0) {
        return;
    }
    double halfH = h / 2;
    double halfW = w / 2;
    DrawFractal(x, y, halfW, halfH, order - 1);                         // left
    DrawFractal(x + halfW / 2, y - halfH, halfW, halfH, order - 1);     // top
    DrawFractal(x + halfW, y, halfW, halfH, order - 1);                 // right
}

/* Main program */

int main() {
    initGraphics();
    // Fill in the necessary code here
    int edgeLength, order;
    int x = 0; 
    int y = getWindowHeight();
    double w, h;
    AskForInput(edgeLength, order);
    w = edgeLength;
    h = edgeLength / 2 * sqrt(3);
    DrawFractal(x, y, w, h, order);
    return 0;
}
