/*
 * Reservation.h
 *
 * 14 November 2020
 * Mert Ertugrul
 */
#ifndef RESEVATION_H
#define RESEVATION_H

class Reservation {

public:

int resCode;
int passengerNum;
int* rowArr;
char* colArr;


Reservation(const int newcode, const int newPassengerNum, const int *seatRow, const char *seatCol);
Reservation();
~Reservation();

void initialize1(const Reservation &other);
void initialize2(const int newcode, const int newPassengerNum, const int *seatRow, const char *seatCol);

void printOut();

};
#endif //RESEVATION_H
