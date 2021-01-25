//
//  SimpleLibrarySystem.h
//  Homework Assignment 3 - PART A
//
//  Author: Mert Ertugrul
//  Date: 09.12.2020
//

#ifndef __SIMPLE_LIBRARY_SYSTEM_H
#define __SIMPLE_LIBRARY_SYSTEM_H

#include "SimpleStudent.h"
#include <iostream>

using namespace std;


class LibrarySystem {

public:

    LibrarySystem();

    ~LibrarySystem();

    void addStudent(const int studentId, const string studentName);

    void deleteStudent(const int studentId);

    void showStudent(const int studentId) const;

private:
    //struct to be used for the linkedlist
    struct StudentNode {

        Student student;
        StudentNode* nextStudentNode;
    };
    StudentNode *head;

    StudentNode* findById(const int studentId) const;

};
#endif
