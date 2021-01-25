/*
 * Reservation.h
 *
 * 14 November 2020
 * Mert Ertugrul
 */

#ifndef RESERVATIONSYSTEM_H
#define RESERVATIONSYSTEM_H
#include "Flight.h"

using namespace std;


class ReservationSystem {

private:

int numFlights;
Flight* flightArr;
int reservationCode;

public:

ReservationSystem();

~ReservationSystem();

void addFlight( const int flightNo, const int rowNo, const int seatNo );

void cancelFlight( const int flightNo );

void showAllFlights();

void showFlight( const int flightNo );

int makeReservation( const int flightNo, const int numPassengers,
                     const int *seatRow, const char *seatCol );

void cancelReservation( const int resCode );

void showReservation( const int resCode );

};
#endif //RESERVATIONSYSTEM_H
