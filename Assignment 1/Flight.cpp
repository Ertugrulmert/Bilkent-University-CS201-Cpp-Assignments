/*
 * Flight.cpp
 *
 * 14 November 2020
 * Mert Ertugrul
 */


#include <iostream>

#include "Flight.h"

using namespace std;

//Constructor with input
Flight::Flight(int flightNum, int rowNum, int colNum)
{
    flightNumber = flightNum;
    //number of rows
    rowNumber = rowNum;
    //number of seats per row
    colNumber = colNum;
    //total number of reservations
    reservationNum = 0;
    //total number of reserved seats
    reservedSeats = 0;
    //array of reservations
    reservationArr = NULL;

    //array representing vacant/reserved seats
    //to increase efficiency, a 1D array is used instead of a 2D array
    rowArr = new char[rowNumber*colNumber];
    for (int i = 0; i < rowNumber*colNumber; i++){
        rowArr[i] = 'o';
    }
}

//Default constructor
Flight::Flight()
{
    flightNumber = 0;
    rowNumber = 0;
    colNumber = 0;
    reservationNum = 0;
    reservedSeats = 0;
    reservationArr = NULL;
    rowArr = NULL;
}
//Destructor
Flight::~Flight()
{
    reservationNum = 0;
    //deallocating arrays
    if (reservationArr != NULL )
        delete [] reservationArr;
    if (rowArr != NULL )
        delete [] rowArr;

}
//to initialize object using another object
//similar to a copy constructor
//alternatively, the "=" operator could be overwritten, this way was preferred
//to avoid confusion
void Flight::initialize1(const Flight &other)
{
    flightNumber = other.flightNumber;
    rowNumber = other.rowNumber;
    colNumber = other.colNumber;
    reservationNum = other.reservationNum;
    reservedSeats = other.reservedSeats;

    //initializing the reservation array
    if (reservationArr != NULL )
        delete [] reservationArr;

    reservationArr = new Reservation[reservationNum];
    for (int i= 0; i< reservationNum; i++)
        reservationArr[i].initialize1(other.reservationArr[i]);

    //initializing the aircraft seating plan array
    if (rowArr != NULL )
        delete [] rowArr;

    rowArr = new char[rowNumber*colNumber];
    for (int i = 0; i < rowNumber*colNumber; i++)
        rowArr[i] = other.rowArr[i];
}
//to initialize object using parameters (used to initialize a new flight added to an array)
void Flight::initialize2(const int flightNum, const int rowNum, const int colNum)
{
    flightNumber = flightNum;
    rowNumber = rowNum;
    colNumber = colNum;
    reservationNum = 0;
    reservedSeats = 0;
    //initializing the reservation array
    if (reservationArr != NULL )
        delete [] reservationArr;
    reservationArr = NULL;
    //initializing the aircraft seating plan array
    if (rowArr != NULL )
        delete [] rowArr;

    rowArr = new char[rowNumber*colNumber];
    for (int i = 0; i < rowNumber*colNumber; i++){
        rowArr[i] = 'o';
    }
}
//used in ReservationSystem to get flight number
int Flight::getFlightNum(){
    return flightNumber;
}
//used in ReservationSystem to get number of available seats
int Flight::getAvailvableSeats(){
    return rowNumber*colNumber - reservedSeats;
}
//adds a new reservation with given code for given seat locations
int Flight::addReservation(const int newcode, const int newPassengerNum, const int *seatRow, const char *seatCol){

    int unavailable = 0;
    //find unavailable seats among those requested for reservation
    for (int i = 0; i < newPassengerNum; i++){
        if ( rowArr[ (seatRow[i]-1)*colNumber + (seatCol[i]-'A') ] != 'o' ){
            cout << seatRow[i] <<seatCol[i] <<" ";
            unavailable++;
        }
    }
    //determining message for single/multiple unavailable seats
    if (unavailable > 0){
        if (unavailable ==1)
            cout << "is not available"<<endl;
        else
            cout << "are not available"<<endl;
        cout<<endl;
        return -1;
    }

    //crossing out the reserved seats on the aircraft seating plan
    for (int i = 0; i < newPassengerNum; i++)
        rowArr[ (seatRow[i]-1)*colNumber + (seatCol[i]-'A') ] = 'x';

    //dynamic array operations for appending a new reservation to existing reservations
    //if this is the first reservation
    if(reservationArr == NULL){
        reservationArr = new Reservation[1];
        reservationArr[0].initialize2(newcode, newPassengerNum, seatRow, seatCol);
    }
    //if other reservations exist
    else {
        Reservation* tempArr = new Reservation[reservationNum+1];
        for (int i=0; i< reservationNum; i++){
            tempArr[i].initialize1( reservationArr[i] );
        }
        tempArr[reservationNum].initialize2(newcode, newPassengerNum, seatRow, seatCol);

        delete [] reservationArr;
        reservationArr = tempArr;
    }
    reservationNum++;
    reservedSeats += newPassengerNum;
    return newcode;
}
//displays the seating plan of the aircraft on the console
void Flight::displayAircraft(){

    //displaying the row of letters for seats
    cout<<"  ";
    for(int i=0 ; i<colNumber ; i++){
        cout<<static_cast<char>(i+'A')<<" ";
    }
    cout<<endl;

    //displaying the aircraft rows
    for(int i=0; i<rowNumber; i++){
        cout<<(i+1)<<" ";
        for(int j=0; j<colNumber; j++){
            cout<<rowArr[i*colNumber + j]<<" ";
        }
        cout<<endl;
    }
}
//finds a reservation by its code and returns its index in the reservation array
int Flight::findReservation(const int resCode){
    for(int i = 0; i<reservationNum; i++){
        if (reservationArr[i].resCode == resCode)
            return i;
    }
    return -1;
}

//shows the reservation information for a given reservation code
//boolean return value is used by the ReservationSystem to detect if the operation was successful
bool Flight::showReservation(const int resCode){
    int result = findReservation(resCode);
    if (result != -1){
        cout << "Reservations under Code "<<resCode <<" in Flight "<<flightNumber<<":";
        reservationArr[result].printOut();
        cout<<endl;
        cout<<endl;
        return true;
    }
    else
        return false;
}

//deletes the reservation for a given reservation code
//boolean return value is used by the ReservationSystem to detect if the operation was successful
bool Flight::cancelReservation(const int resCode){
    //finding the reservation index in array
    int result = findReservation(resCode);
    if (result != -1){
        cout << "Reservation for the seats ";
        reservationArr[result].printOut();
        cout<<" is canceled in Flight "<<flightNumber<<endl;
        cout<<endl;

        //replaces the "x" with a "o" for newly available seats on the aircraft seating plan
        for (int i = 0; i < reservationArr[result].passengerNum; i++)
            rowArr[ (reservationArr[result].rowArr[i]-1)*colNumber + (reservationArr[result].colArr[i]-'A') ] = 'o';

        //if the only reservation is to be discarded
        if (reservationNum == 1){
            delete [] reservationArr;
            reservationNum = 0;
            reservedSeats = 0;
        }
        //dynamic array operations for discarding an element from the reservation array
        else {
            Reservation* tempArr = new Reservation[reservationNum-1];

            for (int j=0; j< result; j++)
                tempArr[j].initialize1( reservationArr[j] );

            for (int j=result+1; j< reservationNum; j++)
                tempArr[j].initialize1( reservationArr[j] );

            reservedSeats -= reservationArr[result].passengerNum;
            delete [] reservationArr;
            reservationArr = tempArr;
            reservationNum--;

        }
        return true;
    }
    else
        return false;
}
