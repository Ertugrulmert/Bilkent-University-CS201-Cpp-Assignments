//
//  Student.h
//  Homework Assignment 3 - PART B
//
//  Author: Mert Ertugrul
//  Date: 09.12.2020
//

#ifndef __STUDENT_H
#define __STUDENT_H
#include "Book.h"


using namespace std;

class Student {

public:
    Student( const string studentName = "", const int studentId = 0  );

    Student( const Student &otherStudent );

    ~Student();

    const string getName() const;

    const int getId() const;

    void setName(const string studentName);

    void setId(const int studentId);

    void addBook(const Book& newbook);

    void deleteBook(const int bookId, Book& newbook);
    //hecks if the student has a specific book
    bool hasBook(const int bookId);
    //shows student info
    void showInfo();
    //shows the books of the students
    void showAllBooks();
    //shows a single book of the student
    void showBook(const int bookId);


private:
    string studentName;
    int studentId;
    //struct used to represent students in a linkedlist
    struct StudBookNode {
        Book book;
        StudBookNode* nextBookNode;
    };
    StudBookNode *head;
    //finds the node pointer to a book with a given Id
    StudBookNode* findBook(const int bookId) const;

};

#endif
