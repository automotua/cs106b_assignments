/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
}

VectorPriorityQueue::~VectorPriorityQueue() {
}

int VectorPriorityQueue::size() {
	return vec.size();
}

bool VectorPriorityQueue::isEmpty() {
	return vec.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
    vec.add(value);
}

string VectorPriorityQueue::peek() {
    if (vec.isEmpty()) {
        error("The queue is empty!");
    } 
    string min = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] < min) {
            min = vec[i];
        }
    }
	return min;
}

string VectorPriorityQueue::dequeueMin() {
    if (vec.isEmpty()) {
        error("The queue is empty!");
    } 
    string min = vec[0];
    int minIndex = 0;
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] < min) {
            min = vec[i];
            minIndex = i;
        }
    }
    vec.remove(minIndex);
	return min;
}

