//
//  Book.h
//  Homework Assignment 3 - PART B
//
//  Author: Mert Ertugrul
//  Date: 09.12.2020
//

#ifndef __BOOK_H
#define __BOOK_H
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Book {

public:
    Book( const string bookTile = "" , const int bookId = 0 , const int bookYear = 0  );

    void operator=(const Book& right);

    Book( const Book &otherBook );

    const string getTitle() const;

    const int getId() const;

    const int getYear() const;

    void setTitle(const string bookTitle );

    void setId(const int bookId);

    void setYear(const int bookYear);
    //prints info about book
    void showInfo();

private:
    string bookTitle;
    int bookId;
    int bookYear;
};

#endif

