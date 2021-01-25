/*
 * Reservation.cpp
 *
 * 14 November 2020
 * Mert Ertugrul
 */


#include <iostream>
#include <string>

#include "Reservation.h"

using namespace std;

//Constructor with parameters
Reservation::Reservation(const int newcode, const int newPassengerNum, const int *seatRow, const char *seatCol)
{
    resCode = newcode;
    passengerNum = newPassengerNum;

    //initializing reserved seat values
    rowArr = new int[passengerNum];
    for (int i= 0; i< passengerNum; i++)
        rowArr[i] = seatRow[i];

    colArr = new char[passengerNum];
    for (int i= 0; i< passengerNum; i++)
        colArr[i] = seatCol[i];
}
//Default constructor
Reservation::Reservation()
{
    resCode = 0;
    passengerNum = 0;
    rowArr = NULL;
    colArr = NULL;
}

//Destructor
Reservation::~Reservation()
{
    if(rowArr != NULL)
        delete[] rowArr;
    if(colArr != NULL)
        delete[] colArr;
}

//to initialize object using another object
//similar to a copy constructor
//alternatively, the "=" operator could be overwritten, this way was preferred
//to avoid confusion
void Reservation::initialize1(const Reservation &other)
{
    resCode = other.resCode;
    passengerNum = other.passengerNum;

    if (rowArr != NULL )
        delete [] rowArr;

    rowArr = new int[passengerNum];
    for (int i= 0; i< passengerNum; i++)
        rowArr[i] = other.rowArr[i];


    if (colArr != NULL )
        delete [] colArr;

    colArr = new char[passengerNum];
    for (int i= 0; i< passengerNum; i++)
        colArr[i] = other.colArr[i];
}
//to initialize object using parameters (used to initialize a new reservation added to an array)
void Reservation::initialize2(const int newcode, const int newPassengerNum, const int *seatRow, const char *seatCol)
{
    resCode = newcode;
    passengerNum = newPassengerNum;

    if (rowArr != NULL )
        delete [] rowArr;

    rowArr = new int[passengerNum];
    for (int i= 0; i< passengerNum; i++)
        rowArr[i] = seatRow[i];


    if (colArr != NULL )
        delete [] colArr;

    colArr = new char[passengerNum];
    for (int i= 0; i< passengerNum; i++)
        colArr[i] = seatCol[i];
}
//prints the reserved seat locations to the console
void Reservation::printOut(){
    for(int i=0; i<passengerNum; i++){
        cout<<rowArr[i]<<colArr[i]<<" ";
    }
}
