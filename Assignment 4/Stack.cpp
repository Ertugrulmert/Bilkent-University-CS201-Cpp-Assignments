//
//  Stack.cpp
//  Homework Assignment 4
//
//  Author: Mert Ertugrul
//  Date: 26.12.2020
//

#include "Stack.h"

using namespace std;

// default constructor
Stack::Stack(){
    topNode = NULL;
}

// copy constructor
Stack::Stack(const Stack& otherStack){

    //other stack is empty
    if (otherStack.topNode == NULL)
        topNode = NULL;

    else {
        //first node
        topNode = new StackNode;
        topNode->item = otherStack.topNode->item;

        StackNode *tempNode = topNode;
        for (StackNode *iterNode = otherStack.topNode->next; iterNode != NULL; iterNode = iterNode->next){

            tempNode->next = new StackNode;
            tempNode = tempNode->next;
            tempNode->item = iterNode->item;
        }
        tempNode->next = NULL;
    }
}


// destructor
Stack::~Stack(){

    while (!isEmpty())
        pop();
}

bool Stack::isEmpty() const {

    return topNode == NULL;
}

//adds an item to the top of the stack
bool Stack::push(int item) {

    StackNode *newNode = new StackNode;
    newNode->item = item;
    newNode->next = topNode;
    topNode = newNode;
    return true;
}

//deletes the item at the top of the stack
bool Stack::pop() {

    //no node left to pop
    if (isEmpty())
        return false;

    else{
        StackNode *tempNode = topNode;
        topNode = topNode->next;
        //we break the node's access to the stack
        tempNode->next = NULL;
        delete tempNode;
        return true;
   }
}
//pop that outputs popped item
bool Stack::pop(int& returnItem) {
    //no node left to pop
    if (isEmpty())
        return false;

    else{
        returnItem = topNode->item;
        StackNode *temp = topNode;
        topNode = topNode->next;
        //we break the node's access to the stack
        temp->next = NULL;
        delete temp;
        return true;
    }
}

//retrieves the item at the top of the stack
bool Stack::peek(int& returnItem) const {

    if (isEmpty())
        return false;
    else
        returnItem = topNode->item;
    return true;
}

