//
//  Student.cpp
//  Homework Assignment 3 - PART B
//
//  Author: Mert Ertugrul
//  Date: 09.12.2020
//


#include "Student.h"

using namespace std;


Student::Student( const string studentName, const int studentId ){

    this->studentName = studentName ;
    this->studentId = studentId ;
    this->head = NULL;
}

Student::Student( const Student &otherStudent  ){

    this->studentName = otherStudent.getName() ;
    this->studentId = otherStudent.getId() ;
}

Student::~Student(){

    while (head != NULL) {

        StudBookNode *nextHead = head->nextBookNode;
        //deleting node
        delete head;
        //continuing with next node
        head = nextHead;
    }
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

Student::StudBookNode* Student::findBook(const int bookId) const{

    //iterating through the student's books
    for (StudBookNode *tempPtr = head; tempPtr != NULL; tempPtr = tempPtr->nextBookNode){
        if ( tempPtr->book.getId() == bookId ) {
            return tempPtr;
        }
    }
    return NULL;
}

void Student::addBook(const Book& newBook){

    StudBookNode* newNode = new StudBookNode;
    newNode->book = Book(newBook);
    newNode->nextBookNode = head;
    head = newNode;
}

void Student::deleteBook(const int bookId, Book& saveBook ){

    if(head != NULL ) {
        //if the book to be deleted is the head node
        if (bookId == 0 || head->book.getId() == bookId ){
            saveBook = head->book;
            StudBookNode *tempPtr = head->nextBookNode;
            delete head;
            head = tempPtr;
            return;
        }
        //iterating through the student's books
        for (StudBookNode *iterPtr = head; iterPtr->nextBookNode != NULL; iterPtr = iterPtr->nextBookNode){
            if ( iterPtr->nextBookNode->book.getId() == bookId ) {
                saveBook = iterPtr->nextBookNode->book;
                StudBookNode *tempPtr = iterPtr->nextBookNode->nextBookNode;
                delete iterPtr->nextBookNode;
                iterPtr->nextBookNode = tempPtr;
                return;
            }
        }
    }
    saveBook = Book();

}

bool Student::hasBook(const int bookId){
    return (findBook(bookId) != NULL);
}

void Student::showInfo(){

    cout <<"Student id: "<< this->studentId <<" student name: "<<this->studentName<<endl;

    if (this->head == NULL) {
        cout <<"Student "<< this->studentId<<" has no books"<<endl;
    }
    else {
        cout <<"Student "<< this->studentId <<" has checked out the following books:"<<endl;

        std::cout << std::left << std::setfill(' ')
        << std::setw(10) << "Book id"
        << std::setw(24) <<"Book name"
        << std::setw(10) << "Year" << endl;

        for (StudBookNode *iterPtr = head; iterPtr != NULL; iterPtr = iterPtr->nextBookNode){
            iterPtr->book.showInfo();
            cout<<endl;
        }
    }
}

void Student::showAllBooks(){

    if (this->head != NULL) {
        for (StudBookNode *iterPtr = head; iterPtr != NULL; iterPtr = iterPtr->nextBookNode){
            iterPtr->book.showInfo();
            cout<<"Checked out by student "<<this->studentId<<endl;
        }
    }
}

void Student::showBook(int bookId){
    findBook(bookId)->book.showInfo();
    cout<<"Checked out by student "<<this->studentId<<endl;
}


