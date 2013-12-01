/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
    head = NULL;
    length = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
    cellT * cur, * old = NULL;
    for (cur = head; cur != NULL; cur = cur->next, delete old) {
        old = cur;
    }
}

int LinkedListPriorityQueue::size() {
	return length;
}

bool LinkedListPriorityQueue::isEmpty() {
	return (size() == 0);
}

void LinkedListPriorityQueue::enqueue(string value) {
    cellT * cur, * prev = NULL;
    
    for (cur = head; cur != NULL; cur = cur->next) {
        if (value < cur->value) {
            break;
        }
        prev = cur;
    }
    
    cellT * newCell = new cellT;
    newCell->value = value;
    newCell->next = cur;
    if (prev != NULL) {
        prev->next = newCell;
    } else {
        head = newCell;
    }
    length++;
}

string LinkedListPriorityQueue::peek() {
    if (size() == 0) {
        error("The queue is empty!");
    } else {
        return head->value;
    }
}

string LinkedListPriorityQueue::dequeueMin() {
    if (size() == 0) {
        error("The queue is empty!");
    } else {
        string value = head->value;
        cellT * old = head;
        head = head->next;
        length--;
        delete old;
        return value;
    }
}

