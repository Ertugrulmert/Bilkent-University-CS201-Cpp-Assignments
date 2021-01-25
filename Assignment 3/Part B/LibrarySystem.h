//
//  LibrarySystem.h
//  Homework Assignment 3 - PART B
//
//  Author: Mert Ertugrul
//  Date: 09.12.2020
//

#ifndef __LIBRARY_SYSTEM_H
#define __LIBRARY_SYSTEM_H

#include "Student.h"
#include "Book.h"


using namespace std;


class LibrarySystem {

public:

    LibrarySystem();

    ~LibrarySystem();

    void addBook(const int bookId, const string bookName, const int bookYear);

    void deleteBook(const int bookId);

    void addStudent(const int studentId, const string studentName);

    void deleteStudent(const int studentId);

    void checkoutBook(const int bookId, const int studentId);

    void returnBook(const int bookId);

    void showAllBooks() const;

    void showBook(const int bookId) const;

    void showStudent(const int studentId) const;

private:

    //for the student linkedlist
    struct StudentNode {

        Student student;
        StudentNode* nextStudentNode;
    };
    StudentNode *studentHead;

    //for the available book linkedlist
    struct BookNode {

        Book book;
        BookNode* nextBookNode;
    };
    BookNode *bookHead;

    //finds a node pointer to a student with given id
    StudentNode* findStudent(const int studentId) const;
    //finds a node pointer to a book with given id
    BookNode* findBook(const int bookId) const;
    //find if a book was checked out and returns the student node pointer that has the book
    StudentNode* findCheckedOut(const int bookId) const;
    //internally used book return function, to avoid having to duplicate return code in many places
    bool internalReturn(StudentNode* studentNode, const int bookId );
    //internally used book delete function, to avoid duplicating delete code
    bool internalDeleteBook(const int bookId);

};
#endif
