//
//  SimpleStudent.h
//  Homework Assignment 3 - PART A
//
//  Author: Mert Ertugrul
//  Date: 09.12.2020
//

#ifndef __SIMPLE_STUDENT_H
#define __SIMPLE_STUDENT_H
#include <string>


using namespace std;

class Student {

public:
    Student( const string studentName = "", const int studentId = 1  );

    Student( const Student &otherStudent );

    const string getName() const;

    const int getId() const;

    void setName(const string studentName);

    void setId(const int studentId);

private:
    string studentName;
    int studentId;
};

#endif
