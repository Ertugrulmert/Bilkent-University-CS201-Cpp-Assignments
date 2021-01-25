//
//  SimpleLibrarySystem.cpp
//  Homework Assignment 3 - PART A
//
//  Author: Mert Ertugrul
//  Date: 09.12.2020
//
#include "SimpleLibrarySystem.h"


using namespace std;

LibrarySystem::LibrarySystem(){
    head = NULL;
}

LibrarySystem::~LibrarySystem(){
    //we need to delete every node in the Linked-List
    while (head != NULL) {

        StudentNode *nextHead = head->nextStudentNode;
        //deleting node
        delete head;
        //continuing with next node
        head = nextHead;
    }

}
//Finds the pointer to the student node for a given student Id
LibrarySystem::StudentNode* LibrarySystem::findById(const int studentId) const{

    for (StudentNode *tempPtr = head; tempPtr != NULL; tempPtr = tempPtr->nextStudentNode){
        if ( tempPtr->student.getId() == studentId ) {
            return tempPtr;
        }
    }
    //if student was not found, returns NULL
    return NULL;

}
//adds student to linkedlist
void LibrarySystem::addStudent(const int studentId, const string studentName){

    if (findById(studentId) != NULL){
        cout<<"Student "<<studentId<<" already exists"<<endl;
        return;
    }
    //if there were no students previously
    if (head == NULL){

        StudentNode* newNode = new StudentNode;
        newNode->student = Student(studentName,studentId);
        newNode->nextStudentNode = NULL;
        head = newNode;
    }
    else {
        StudentNode* newNode = new StudentNode;
        newNode->student = Student(studentName,studentId);
        newNode->nextStudentNode = head;
        head = newNode;
    }
    cout<<"Student "<<studentId<<" has been added"<<endl;
}
//delete student if they exist
void LibrarySystem::deleteStudent(const int studentId){

    if(head != NULL ) {
        //if teh student is the head node
        if (head->student.getId() == studentId ){
            StudentNode *tempPtr = head->nextStudentNode;
            delete head;
            head = tempPtr;
            cout<<"Student "<<studentId<<" has been deleted"<<endl;
            return;
        }
        //search for student
        for (StudentNode *iterPtr = head; iterPtr->nextStudentNode != NULL; iterPtr = iterPtr->nextStudentNode){
            if ( iterPtr->nextStudentNode->student.getId() == studentId ) {

                StudentNode *tempPtr = iterPtr->nextStudentNode->nextStudentNode;
                delete iterPtr->nextStudentNode;
                iterPtr->nextStudentNode = tempPtr;
                cout<<"Student "<<studentId<<" has been deleted"<<endl;
                return;
            }
        }

    }

    cout<<"Student "<<studentId<<" does not exist"<<endl;
}



//shows detailed information about student
void LibrarySystem::showStudent(const int studentId) const{
    //pointer to student node is found
    StudentNode *studentPtr =findById(studentId);

    if (studentPtr == NULL)
        cout<<"Student "<<studentId<<" does not exist"<<endl;
    else
        cout<<"Student id: "<<studentId<<" student name: "<< studentPtr->student.getName()<<endl;
}
