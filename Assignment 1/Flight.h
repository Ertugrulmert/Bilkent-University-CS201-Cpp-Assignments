/*
 * Flight.h
 *
 * 14 November 2020
 * Mert Ertugrul
 */

#ifndef FLIGHT_H
#define FLIGHT_H
#include "Reservation.h"

class Flight {

public:

int flightNumber;
int rowNumber;
int colNumber;
int reservationNum;
int reservedSeats;

Reservation* reservationArr;

char* rowArr;

Flight();

Flight(int flightNum, int rowNum, int colNum);

~Flight();

void initialize1(const Flight &other);

void initialize2(const int flightNum, const int rowNum, const int colNum);

int getFlightNum();

int getAvailvableSeats();

int addReservation(const int newcode, const int newPassengerNum, const int *seatRow, const char *seatCol);

void displayAircraft();

int findReservation(const int resCode);

bool showReservation(const int resCode);

bool cancelReservation(const int resCode);

};
#endif //FLIGHT_H
