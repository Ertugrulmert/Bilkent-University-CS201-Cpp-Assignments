//
//  Stack.h
//  Homework Assignment 4
//
//  Author: Mert Ertugrul
//  Date: 26.12.2020
//


#ifndef __STACK_H
#define __STACK_H

#include <string>

class Stack{

    public:

        Stack();
        Stack(const Stack& otherStack);
        ~Stack();

        bool isEmpty() const;

        bool push(int newItem);

        bool pop();

        bool pop(int& stackTop);

        bool peek(int& stackTop) const;

    private:
        //unit of the stack items
        struct StackNode {
            //integer used to store city indexes
            int item;
            //the stack node below this node
            StackNode *next;
        };
        //top of the stack
        StackNode *topNode;
};

#endif
