//
//  SimpleStudent.cpp
//  Homework Assignment 3 - PART A
//
//  Author: Mert Ertugrul
//  Date: 09.12.2020
//


#include "SimpleStudent.h"

using namespace std;


Student::Student( const string studentName, const int studentId ){

    this->studentName = studentName ;
    this->studentId = studentId ;
}

Student::Student( const Student &otherStudent  ){

    this->studentName = otherStudent.getName() ;
    this->studentId = otherStudent.getId() ;
}

const string Student::getName() const{
    return this->studentName;
}

const int Student::getId() const{
    return this->studentId;
}

void Student::setName(const string studentName){
    this->studentName = studentName;
}

void Student::setId(const int studentId){
    this->studentId = studentId;
}
