/*************************************************************
 * File: ;
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
    head = tail = NULL;
    length = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
    cellT * cur, * old = NULL;
    for (cur = head; cur != NULL; cur = cur->next, delete old) {
        old = cur;
    }
}

int DoublyLinkedListPriorityQueue::size() {
	return length;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
    return (size() == 0);
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
    cellT * newCell = new cellT;
    newCell->value = value;
    newCell->next = NULL;
    if (size() == 0) {
        newCell->prev = NULL;
        head = tail = newCell;
    } else {
        tail->next = newCell;
        newCell->prev = tail;
        tail = newCell;
    }
    length++;
}

string DoublyLinkedListPriorityQueue::peek() {
    if (size() == 0) {
        error("The queue is empty!");
    } else {
        string min = head->value;
        cellT * cur;
        for (cur = head->next; cur != NULL; cur = cur->next) {
            if (cur->value < min) {
                min = cur->value;
            }
        }
        return min;
    }
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
    if (size() == 0) {
        error("The queue is empty!");
    } else if (size() == 1) {
        string min = head->value;
        delete head;
        head = tail = NULL;
        length--;
        return min;
    } else {
        string min = head->value;
        cellT * cur;
        cellT * minCell = head;
        for (cur = head->next; cur != NULL; cur = cur->next) {
            if (cur->value < min) {
                min = cur->value;
                minCell = cur;
            }
        }
        
        if (minCell == head) {
            minCell->next->prev = NULL;
            head = minCell->next;
        } else if (minCell == tail) {
            minCell->prev->next = NULL;
            tail = minCell->prev;
        } else {
            minCell->prev->next = minCell->next;
            minCell->next->prev = minCell->prev;
        }
        delete minCell;
        length--;
        return min;
    }
}

