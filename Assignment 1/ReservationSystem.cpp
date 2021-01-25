/*
 * ReservationSystem.cpp
 *
 * 14 November 2020
 * Mert Ertugrul
 */


#include <iostream>
#include <string>

#include "ReservationSystem.h"

using namespace std;

//Reservation System Constructor
ReservationSystem::ReservationSystem(){
    numFlights = 0;
    flightArr = NULL;
    reservationCode = 1;
}

//Reservation System Destructor
ReservationSystem::~ReservationSystem(){
    delete [] flightArr;
}

//Adds flight given flight number, row and column numbers
void ReservationSystem::addFlight( const int flightNo, const int rowNo, const int seatNo ){

        //checking if the flight already exists
        for (int i=0; i< numFlights; i++){
            if (flightArr[i].getFlightNum() == flightNo ){
                cout<<"Flight "<<flightNo<<" already exists"<<endl;
                cout<<endl;
                return;
            }
        }

        //checking if seat and row numbers are valid
        if (rowNo <= 0 || seatNo <= 0){
            cout<<"Invalid row or seat number entered"<<endl;
            cout<<endl;
            return;
        }

        //dynamic array operations to append a new flight tot he array of flights
        //if no other flights are present
        if(flightArr == NULL){
            flightArr = new Flight[1];
            flightArr[0].initialize2(flightNo, rowNo, seatNo);
            numFlights = 1;
        }
        //if other flights exist
        else {
            Flight* tempArr = new Flight[numFlights+1];
            for (int i=0; i< numFlights; i++){
                tempArr[i].initialize1( flightArr[i] );

            }

            tempArr[numFlights].initialize2(flightNo, rowNo, seatNo);

            delete [] flightArr;
            flightArr = tempArr;
            numFlights++;
        }
        cout<<"Flight "<<flightNo<<" has been added"<<endl;
        cout<<endl;
}

//Cancels flight given flight number
void ReservationSystem::cancelFlight( const int flightNo ){

    for (int i=0; i< numFlights; i++){
        if (flightArr[i].getFlightNum() == flightNo ){

            //if this is the only flight that exists
            if (numFlights == 1){
                delete [] flightArr;
                    numFlights = 0;
            }
            //if other flights exist, dynamic array operations needed
            else {
                Flight* tempArr = new Flight[numFlights-1];
                //elements before the discarded flight
                for (int j=0; j< i; j++)
                    tempArr[j].initialize1( flightArr[j] );
                //elements after the discarded flight
                for (int j=i+1; j< numFlights; j++)
                    tempArr[j-1].initialize1( flightArr[j] );

                delete [] flightArr;
                flightArr = tempArr;
                numFlights--;

            }
            cout<<"Flight "<<flightNo<<" and all of its reservations are canceled"<<endl;
            cout<<endl;
            return;
        }
    }
    //if the flight was not found, this section will be reached
    cout<<"Flight "<<flightNo<<" does not exist"<<endl;
    cout<<endl;

}

//Displays all flights' number and number of available seats
void ReservationSystem::showAllFlights(){
    //if there are no flights
    if (numFlights == 0){
        cout<<"No flights exist"<<endl;
        cout<<endl;
    }
    else{
        cout<<"Flights currently operated:"<<endl;
        for (int i=0; i< numFlights; i++)
            cout << "Flight " << flightArr[i].getFlightNum() << " (" << flightArr[i].getAvailvableSeats() <<" available seats)" <<endl;
        cout<<endl;
    }
}

//Displays detailed flight information given flight number
void ReservationSystem::showFlight( const int flightNo ){

    for (int i=0; i< numFlights; i++){
        if (flightArr[i].getFlightNum() == flightNo ){

            cout << "Flight " << flightNo << " has " << flightArr[i].getAvailvableSeats() <<" available seats" <<endl;
            //display the aircraft seating plan
            flightArr[i].displayAircraft();
            cout<<endl;
            return;
        }
    }
    //if the flight was not found, this section will be reached
    cout<<"Flight "<<flightNo<<" does not exist"<<endl;
    cout<<endl;

}

//Makes a reservation for a set of seats in a flight
int ReservationSystem::makeReservation( const int flightNo, const int numPassengers,
                                        const int *seatRow, const char *seatCol ){
    //if there are no flights
    if (numFlights == 0){
        cout<<"No flights exist"<<endl;
        cout<<endl;
        return -1;
    }
    //search for the flight
    for (int i=0; i< numFlights; i++){
        if (flightArr[i].getFlightNum() == flightNo ){
            //adding reservation to flight
            int code = flightArr[i].addReservation(reservationCode, numPassengers, seatRow, seatCol);
            if( code != -1)
                //incrementing the unique reservation code to be used next time
                reservationCode++;
            return code;
        }
    }
    //if the flight was not found, this section will be reached
    cout<<"Flight "<<flightNo<<" does not exist"<<endl;
    cout<<endl;
    return -1;
}

//Cancels the reservation for given unique reservation Code
void ReservationSystem::cancelReservation( const int resCode ){
    for(int i = 0; i<numFlights; i++){
        //if the reservation was found and canceled, function returns
        if ( flightArr[i].cancelReservation(resCode) )
            return;
    }
    //if the reservation was never found, this section is reached
    cout<<"No reservations are found under code "<<resCode<<endl;
    cout<<endl;
}
//Shows the reservation for given unique reservation Code
void ReservationSystem::showReservation( const int resCode ){
    for(int i = 0; i<numFlights; i++){
        //if the reservation was found and displayed, function returns
        if ( flightArr[i].showReservation(resCode) )
            return;
    }
    //if the reservation was never found, this section is reached
    cout<<"No reservations under Code "<<resCode<<endl;
    cout<<endl;
}
