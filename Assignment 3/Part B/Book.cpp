//  Book.cpp
//  Homework Assignment 3 - PART B
//
//  Author: Mert Ertugrul
//  Date: 09.12.2020
//


#include "Book.h"

using namespace std;


Book::Book( const string bookTile, const int bookId, const int bookYear ){

    this->bookTitle= bookTitle;
    this->bookId = bookId;
    this->bookYear = bookYear;
}

void Book::operator=(const Book& right){
    this->bookTitle= right.bookTitle;
    this->bookId = right.bookId;
    this->bookYear = right.bookYear;
}

Book::Book( const Book &otherBook ){

    this->bookTitle= otherBook.getTitle();
    this->bookId = otherBook.getId();
    this->bookYear = otherBook.getYear();
}

const string Book::getTitle() const{
    return this->bookTitle;
}

const int Book::getId() const{
    return this->bookId;
}

const int Book::getYear() const{
    return this->bookYear;
}

void Book::setTitle(const string bookTitle ){
    this->bookTitle =bookTitle ;
}

void Book::setId(const int bookId){
    this->bookId=bookId;
}

void Book::setYear(const int bookYear){
    this->bookYear = bookYear;
}

void Book::showInfo(){
    std::cout << std::left << std::setfill(' ')
        << std::setw(10)<< this->bookId
        << std::setw(24)<< this->bookTitle
        << std::setw(10)<< this->bookYear;
}


