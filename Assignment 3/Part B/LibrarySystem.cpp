//
//  LibrarySystem.cpp
//  Homework Assignment 3 - PART B
//
//  Author: Mert Ertugrul
//  Date: 09.12.2020
//
#include "LibrarySystem.h"


using namespace std;

LibrarySystem::LibrarySystem(){
    bookHead = NULL;
    studentHead = NULL;
}

LibrarySystem::~LibrarySystem(){

    //deleting all students and the books
    while (studentHead != NULL) {

        StudentNode *nextHead = studentHead->nextStudentNode;
        //deleting node
        delete studentHead;
        //continuing with next node
        studentHead = nextHead;
    }
    while (bookHead != NULL) {

        BookNode *nextHead = bookHead->nextBookNode;
        //deleting node
        delete bookHead;
        //continuing with next node
        bookHead = nextHead;
    }

}

//Functions below are helpers, public functions come later

//the node for the student with given ID is found.
LibrarySystem::StudentNode* LibrarySystem::findStudent(const int studentId) const{

    for (StudentNode *tempPtr = studentHead; tempPtr != NULL; tempPtr = tempPtr->nextStudentNode){
        if ( tempPtr->student.getId() == studentId ) {
            return tempPtr;
        }
    }
    return NULL;

}

//the node for the book with given ID is found.
LibrarySystem::BookNode* LibrarySystem::findBook(const int bookId) const{

    for (BookNode *iterPtr = bookHead; iterPtr != NULL; iterPtr = iterPtr->nextBookNode){
        if ( iterPtr->book.getId() == bookId ) {
            return iterPtr;
        }
    }

    return NULL;
}

//find if a book was checked out and returns the student node pointer that has the book
LibrarySystem::StudentNode* LibrarySystem::findCheckedOut(const int bookId) const{

    for (StudentNode *tempPtr = studentHead; tempPtr != NULL; tempPtr = tempPtr->nextStudentNode){

        if ( tempPtr->student.hasBook(bookId) ) {
            return tempPtr;
        }
    }
    return NULL;
}

//internally used book delete function, to avoid duplicating delete code
bool LibrarySystem::internalDeleteBook(const int bookId){

    if(bookHead != NULL ) {
        //if head node must be deleted
        if (bookHead->book.getId() == bookId ){
            BookNode *tempPtr = bookHead->nextBookNode;
            delete bookHead;
            bookHead = tempPtr;
            return true;
        }
        //looking for book
        for (BookNode *iterPtr = bookHead; iterPtr->nextBookNode != NULL; iterPtr = iterPtr->nextBookNode){
            if ( iterPtr->nextBookNode->book.getId() == bookId ) {
                BookNode *tempPtr = iterPtr->nextBookNode->nextBookNode;
                delete iterPtr->nextBookNode;
                iterPtr->nextBookNode = tempPtr;
                return true;
            }
        }

    }
    return false;
}

//internally used book return function, to avoid having to duplicate return code in many places
bool LibrarySystem::internalReturn(LibrarySystem::StudentNode* studentNode, const int bookId){
    Book returnedBook;
    studentNode->student.deleteBook(bookId,returnedBook);

   if( returnedBook.getId() != 0 ){

        BookNode* newNode = new BookNode;

        //copy constructor and assignment operator caused problems where strings were not being
        //copied, so this method was used instead
        newNode->book.setTitle(returnedBook.getTitle());
        newNode->book.setId(returnedBook.getId());
        newNode->book.setYear(returnedBook.getYear());
        newNode->nextBookNode = bookHead;

        bookHead = newNode;

        cout<<"Book "<<newNode->book.getId()<<" has been returned"<<endl;
        return true;
   }
   return false;
}

//Public functions begin here:

void LibrarySystem::addBook(const int bookId, const string bookName, const int bookYear){

    if (findBook(bookId) != NULL || findCheckedOut(bookId)!= NULL ){
        cout<<"Book "<<bookId<<" already exists"<<endl;
        return;
    }

    BookNode* newNode = new BookNode;
    newNode->book.setTitle(bookName);
    newNode->book.setId(bookId);
    newNode->book.setYear(bookYear);
    newNode->nextBookNode = bookHead;
    bookHead = newNode;
    cout<<"Book "<<bookId<<" has been added"<<endl;
}

void LibrarySystem::deleteBook(const int bookId){

    //delete if book is in library
    if(internalDeleteBook(bookId)){
        cout<<"Book "<<bookId<<" has not been checked out"<<endl;
        cout<<"Book "<<bookId<<" has been deleted"<<endl;
        return;
    }
    //check if book was checked out
    if(studentHead != NULL) {

        StudentNode* studentNode = findCheckedOut(bookId);

        //since the instructions require that we return the book to the system
        //the book is allocated to the linkedlist again at its head before being deleted
        //it could also simply be deleted from the student and not reallocated
        //but this way we simulate the real life scenario as instructed for the assignment
        if (studentNode != NULL){
            internalReturn(studentNode, bookId);
            internalDeleteBook(bookId);
            cout<<"Book "<<bookId<<" has been deleted"<<endl;
            return;
        }
    }

    cout<<"Book "<<bookId<<" does not exist"<<endl;
}

void LibrarySystem::addStudent(const int studentId, const string studentName){

    if (findStudent(studentId) != NULL){
        cout<<"Student "<<studentId<<" already exists"<<endl;
        return;
    }

    StudentNode* newNode = new StudentNode;
    newNode->student = Student(studentName,studentId);
    newNode->nextStudentNode = studentHead;
    studentHead = newNode;

    cout<<"Student "<<studentId<<" has been added"<<endl;
}

void LibrarySystem::deleteStudent(const int studentId){

    if(studentHead != NULL ) {
        //if head node must be deleted
        if (studentHead->student.getId() == studentId ){

            while( internalReturn( studentHead, 0 ) ){}

            StudentNode *tempPtr = studentHead->nextStudentNode;
            delete studentHead;
            studentHead = tempPtr;
            cout<<"Student "<<studentId<<" has been deleted"<<endl;
            return;
        }
        //looking for student
        for (StudentNode *iterPtr = studentHead; iterPtr->nextStudentNode != NULL; iterPtr = iterPtr->nextStudentNode){
            if ( iterPtr->nextStudentNode->student.getId() == studentId ) {

                while( internalReturn( iterPtr->nextStudentNode, 0 ) ){}

                StudentNode *tempPtr = iterPtr->nextStudentNode->nextStudentNode;
                delete (iterPtr->nextStudentNode);
                iterPtr->nextStudentNode = tempPtr;
                cout<<"Student "<<studentId<<" has been deleted"<<endl;
                return;
            }
        }

    }
    //student not found
    cout<<"Student "<<studentId<<" does not exist"<<endl;
}


void LibrarySystem::checkoutBook(const int bookId, const int studentId){

    BookNode* outBook = findBook(bookId);
    //if book not found in library
    if (outBook == NULL ){
        //if book was checked out
        if (findCheckedOut(bookId)!= NULL ){
            cout<<"Book "<<bookId<<" has been already checked out by another student"<<endl;
            return;
        }
        cout<<"Book "<<bookId<<" does not exist for checkout"<<endl;
        return;
    }

    StudentNode* foundStudent = findStudent(studentId);
    //if student not found
    if (foundStudent == NULL ){
        cout<<"Student "<<studentId<<" does not exist for checkout"<<endl;
        return;
    }

    foundStudent->student.addBook(outBook->book);

    cout<<"Book "<<bookId<<" has been checked out by student "<<foundStudent->student.getId() <<endl;

    internalDeleteBook(bookId);
}


void LibrarySystem::returnBook(const int bookId){

    StudentNode* studentNode = findCheckedOut(bookId);
    if (studentNode != NULL){
        internalReturn( studentNode, bookId);
    }
    else if ( findBook(bookId) != NULL) {
        cout<<"Book "<<bookId<<" has not been checked out"<<endl;
    }
    else
        cout<<"Book "<<bookId<<" does not exist"<<endl;
}

void LibrarySystem::showAllBooks() const{

    //printing the title
    std::cout << std::left << std::setfill(' ')
    << std::setw(10) << "Book id"
    << std::setw(24) <<"Book name"
    << std::setw(10) << "Year"
    << std::setw(10) << "Status"<<endl;

    //printing books that have not been checked out
    for (BookNode *iterPtr = bookHead; iterPtr != NULL; iterPtr = iterPtr->nextBookNode){

        std::cout << std::left << std::setfill(' ')
        << std::setw(10) << iterPtr->book.getId()
        << std::setw(24) <<iterPtr->book.getTitle()
        << std::setw(10) << iterPtr->book.getYear()
        << "Not checked out"<<endl;
    }
    //print out the books checked out by all students
    for (StudentNode *tempPtr = studentHead; tempPtr != NULL; tempPtr = tempPtr->nextStudentNode){
        tempPtr->student.showAllBooks();
    }

}

void LibrarySystem::showBook(const int bookId) const{

    BookNode* iterBook = findBook(bookId);

    if (iterBook != NULL){
        std::cout << std::left << std::setfill(' ')
        << std::setw(10)<< bookId
        << std::setw(24) <<iterBook->book.getTitle()
        << std::left << std::setw(10)  << iterBook->book.getYear()<<"Not checked out"<<endl;
    }
    else{

        StudentNode* foundStudent = findCheckedOut(bookId);
        if (foundStudent != NULL){
            foundStudent->student.showBook(bookId);
        }
        else
            cout<<"Book "<<bookId<<" does not exist"<<endl;
    }

}

void LibrarySystem::showStudent(const int studentId) const{

    StudentNode *foundStudent =findStudent(studentId);

    if (foundStudent == NULL)
        cout<<"Student "<<studentId<<" does not exist"<<endl;
    else {
        //printing out student information
        foundStudent->student.showInfo();
    }
}
