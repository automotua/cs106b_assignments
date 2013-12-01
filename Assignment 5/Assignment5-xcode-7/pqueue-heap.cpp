/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
    heap = new string[4];
    numAllocated = 4;
    numUsed = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
    delete[] heap;
}

int HeapPriorityQueue::size() {
	return numUsed;
}

bool HeapPriorityQueue::isEmpty() {
	return (size() == 0);
}

void HeapPriorityQueue::enqueue(string value) {
    if ((numUsed + 1) == numAllocated) {
        quadrupleCapacity();
    }
    heap[++numUsed] = value;
    
    int index = numUsed;
    while (true) {
        if (index <= 1 || heap[index / 2] < value) {
            break;
        }
        swap(heap[index / 2], heap[index]);
        index /= 2;
    }
}

string HeapPriorityQueue::peek() {
    if (isEmpty()) {
        error("The queue is empty!");
    }
	return heap[1];
}

string HeapPriorityQueue::dequeueMin() {
    if (isEmpty()) {
        error("The queue is empty!");
    }
    string min = heap[1];
    swap(heap[1], heap[numUsed--]);
    bubbleDown(1);
	return min;
}

void HeapPriorityQueue::quadrupleCapacity() {
    string * bigger = new string[4 * numAllocated];
    for (int i = 1; i <= numUsed; i++) {
        bigger[i] = heap[i];
    }
    delete[] heap;
    heap = bigger;
    numAllocated *= 4;
}

void HeapPriorityQueue::bubbleDown(int index) {
    if (2 * index > size()) {
        return;
    }
    int minIndex = findMinIndex(index);
    if (heap[minIndex] < heap[index]) {
        swap(heap[index], heap[minIndex]);
        bubbleDown(minIndex);
    }
}

int HeapPriorityQueue::findMinIndex(int index) {
    if ((2 * index + 1) > size()) {
        return 2 * index;
    } else {
        return (heap[2 * index] < heap[2 * index + 1]) ? (2 * index) : (2 * index + 1);
    }
}